// Qualification Round 2008
// Problem C. Fly Swatter
// https://code.google.com/codejam/contest/32013/dashboard#s=p2
//

#include <iostream>
#include <vector>
#include<iomanip>

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

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  // add case-related members here
  double rFly_, rOuter_, thick_, rString_, gap_;
  double probability_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> rFly_ >> rOuter_ >> thick_ >> rString_ >> gap_;
}

void Case::Compute()
{
  probability_ = 0.0; // init result
}

void Case::WriteTo(std::ostream & os) const
{
  os << setiosflags(ios::fixed) << setprecision(6) << probability_;
}
