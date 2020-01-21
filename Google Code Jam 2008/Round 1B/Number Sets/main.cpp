// Round 1B 2008
// Problem C. Mousetrap
// https://code.google.com/codejam/contest/32017/dashboard#s=p2
// Command Arguments : < $(Configuration).in > $(Configuration).out
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

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void WriteTo(std::ostream & os) const; // write result to output stream
  void Compute(); // main body of alogrithm

private:
  // add case-related members here
  long long a_, b_, p_;
  int nSets_; // result
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> a_ >> b_ >> p_;

  // init result
  nSets_ = 0;
}

void Case::WriteTo(std::ostream & os) const
{
  os << nSets_;
}

void Case::Compute()
{
}
