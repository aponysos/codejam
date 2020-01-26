// Round 1B 2008
// Problem B. Number Sets
// https://code.google.com/codejam/contest/32017/dashboard#s=p1
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm> // fill, for_each

using namespace std;

template <typename TCase>
class Problem
{
public:
  void Solve(std::istream &is, std::ostream &os)
  {
    int nCase = 0;
    is >> nCase;
    for (int i = 0; i < nCase; ++i)
    {
      TCase c(i + 1);
      c.ReadFrom(is);
      c.Compute();
      os << "Case #" << i + 1 << ": ";
      c.WriteTo(os);
      os << '\n';
    }
  }
};

class Case
{
public:
  Case(int iCase) : iCase_(iCase) {}

public:
  void ReadFrom(std::istream &is);      // read from input stream
  void WriteTo(std::ostream &os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  int iCase_; // case # iCase_, 1-based

  // input & output
  int nCards_, nQueries_;
  vector<int> queries_;
  vector<int> answers_;

  // intermediate members
};

// auto-output execution time of a function
class AutoClock
{
public:
  AutoClock(const std::string &funcName) : funcName_(funcName), start_(std::chrono::system_clock::now()) {}
  ~AutoClock()
  {
    auto elapsed_ = std::chrono::system_clock::now() - start_;
    std::clog << funcName_ << ": " << (double)elapsed_.count() / 1000 / 1000 << "ms" << std::endl;
  }

private:
  std::string funcName_;
  std::chrono::time_point<std::chrono::system_clock> start_;
};

#define TRACE() AutoClock ac(__FUNCTION__)
//#define TRACE(str) AutoClock ac(str)
//#define TRACE()

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream &is)
{
  is >> nCards_;
  is >> nQueries_;
  queries_.resize(nQueries_);
  for_each(queries_.begin(), queries_.end(), [&is](int &a) { is >> a; });

  // init answers with -1
  answers_.resize(nQueries_);
  fill(answers_.begin(), answers_.end(), -1);
}

void Case::WriteTo(std::ostream &os) const
{
  for_each(answers_.begin(), answers_.end(), [&os, this](int i) { os << i + 1 << ' '; });
}

void Case::Compute()
{
  TRACE();
  clog << "Case #" << iCase_ << ": " << nCards_ << " cards" << '\n';

  for (int i = 0, pos = 0; i < nCards_; ++i) // card i + 1
  {
    // Compute the next position, after wrap-around.
    pos = (pos + i) % (nCards_ - i); // i card(s) been removed, the modular base decreased by i 
    for (int j = 0; j < nQueries_; j++) // traverse all queries
      if (answers_[j] < 0) // query j is not answered yet
      {
        if (queries_[j] == pos + 1) // query j is on pos
        {
          queries_[j] = -1; // query j is answered
          answers_[j] = i; // the answer is the current card
        }
        else if (queries_[j] > pos + 1) // queries beyond pos
        {
          // The effect of deleting the next position.
          // position pos deleted, so queries beyond pos decrease its modular base by 1
          // in order to match the modular base of pos in the next round
          --queries_[j];
        }
      }
  }
}
