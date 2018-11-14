// Round 1B 2008
// Problem A. Crop Triangles
// https://code.google.com/codejam/contest/32017/dashboard#s=p0
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
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  // add case-related members here
  int n_, A_, B_, C_, D_, x0_, y0_, M_; // input parameters
  int nTriangles_; // output result
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> n_ >> A_ >> B_ >> C_ >> D_ >> x0_ >> y0_ >> M_;

  // init result
  nTriangles_ = 0;
}

void Case::Compute()
{
}

void Case::WriteTo(std::ostream & os) const
{
  os << nTriangles_;
}
