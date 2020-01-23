// Round
// Problem
// URL
// Command Arguments : < $(Configuration).in > $(Configuration).out
// 

#include <iostream>
#include <chrono>

using namespace std;

template<typename TCase>
class Problem
{
public:
  void Solve(std::istream & is, std::ostream & os)
  {
    int nCase = 0;
    is >> nCase;
    for (int i = 0; i < nCase; ++i) {
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
  void ReadFrom(std::istream & is); // read from input stream
  void WriteTo(std::ostream & os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  // input & output

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

void Case::ReadFrom(std::istream & is)
{
}

void Case::WriteTo(std::ostream & os) const
{
}

void Case::Compute()
{
  TRACE();
}
