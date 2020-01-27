// Round
// Problem
// URL
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm> // transform sort

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

  // input & output members
  int nLettersInKey_, nKeys_, nLetters_;
  vector<int> frequencies_;

  // intermediate members
  long long nPresses_;
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
  is >> nLettersInKey_ >> nKeys_ >> nLetters_;
  frequencies_.resize(nLetters_);
  for (int i = 0; i < nLetters_; ++i)
    is >> frequencies_[i];

  nPresses_ = 0; // init result
}

void Case::WriteTo(std::ostream &os) const
{
  os << nPresses_;
}

void Case::Compute()
{
  TRACE();
  clog << "Case #" << iCase_ << ": " << '\n';

  vector<pair<int, int>> f(nLetters_);
  transform(frequencies_.begin(), frequencies_.end(), f.begin(), 
           [i = 0](int a) mutable { return make_pair(i++, a); });
  sort(f.begin(), f.end(), [](auto a, auto b) { return a.second > b.second; });

  int level = 1, j = 0;
  for (auto ff : f)
  {
    if (j >= nKeys_) {
      ++level;
      j = 0;
    }
    nPresses_ += ff.second * level;
    ++j;
  }
}
