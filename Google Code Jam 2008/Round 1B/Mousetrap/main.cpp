// Round 1B 2008
// Problem B. Number Sets
// https://code.google.com/codejam/contest/32017/dashboard#s=p1
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm> // for_each

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
      TCase c;
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
  void ReadFrom(std::istream &is);      // read from input stream
  void WriteTo(std::ostream &os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  // input & output
  int k_, nd_;
  vector<int> d_;
  vector<int> deck_;

  // auto-output execution time of a function
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
//#define TRACE()

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream &is)
{
  is >> k_;
  is >> nd_;
  d_.resize(nd_);
  for_each(d_.begin(), d_.end(), [&is](int &a) { is >> a; });

  deck_.resize(k_); // init deck
}

void Case::WriteTo(std::ostream &os) const
{
  for_each(d_.begin(), d_.end(), [&os, this](int a) { os << deck_[a - 1] << ' '; });
}

void Case::Compute()
{
  TRACE();

  vector<bool> removed_(k_);
  deck_[0] = 1;
  removed_[0] = 1;

  for (int card = 2, cur = 0; card <= k_; ++card)
  {
    int step = 0;

    do
    {
      cur = (cur + 1) % k_;
      if (!removed_[cur])
        ++step;
    } while (step < card);

    while (removed_[cur])
      cur = (cur + 1) % k_;

    deck_[cur] = card;
    removed_[cur] = true;
  }
}
