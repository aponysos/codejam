// Round 1A 2008
// Problem C. Numbers
// https://code.google.com/codejam/contest/32016/dashboard#s=p2
//

#include <iostream>
#include <vector>

using namespace std;

template<typename TCase>
class Problem
{
public:
  void Solve(std::istream & is, std::ostream & os)
  {
    int nCase = 0;
    is >> nCase;
    cases_.resize(nCase);
    for (int i = 0; i < nCase; ++i) {
      TCase & c = cases_[i];
      c.ReadFrom(is);
      c.Compute();
      os << "Case #" << i + 1 << ": ";
      c.WriteTo(os);
      os << '\n';
    }
  }

private:
  std::vector<TCase> cases_;
};

typedef unsigned long long Integer;

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  // add case-related members here
  Integer n_;

  // results
  Integer modt_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> n_;

  // init results
  modt_ = 0;
}

void Case::Compute()
{
}

void Case::WriteTo(std::ostream & os) const
{
  os << modt_;
}
