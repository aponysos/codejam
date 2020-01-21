// Round 1B 2008
// Problem A. Crop Triangles
// https://code.google.com/codejam/contest/32017/dashboard#s=p0
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <vector>
#include <algorithm>

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
  static bool next_combination(vector<bool> & s);

private:
  // add case-related members here
  int n_;
  long long A_, B_, C_, D_, x0_, y0_, M_; // input parameters
  int nTriangles_; // output result

  // intermediate variables
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
  // init intermediate variables
  vector<long long> xnmod3_(n_), ynmod3_(n_);
  xnmod3_[0] = x0_;
  ynmod3_[0] = y0_;
  for (int i = 1; i < n_; ++i) {
    xnmod3_[i] = (A_ * xnmod3_[i - 1] + B_) % M_;
    ynmod3_[i] = (C_ * ynmod3_[i - 1] + D_) % M_;
  }

  vector<bool> c(n_);
  c[0] = c[1] = c[2] = true; // first 3 elements selected

  do {
    auto iTrue = find(c.begin(), c.end(), true);
    auto v1 = iTrue - c.begin();
    iTrue = find(iTrue + 1, c.end(), true);
    auto v2 = iTrue - c.begin();
    iTrue = find(iTrue + 1, c.end(), true);
    auto v3 = iTrue - c.begin();

    auto sumx = xnmod3_[v1] + xnmod3_[v2] + xnmod3_[v3];
    auto sumy = ynmod3_[v1] + ynmod3_[v2] + ynmod3_[v3];

    if (sumx % 3 == 0 && sumy % 3 == 0)
      ++nTriangles_;
  }
  while (next_combination(c));
}

void Case::WriteTo(std::ostream & os) const
{
  os << nTriangles_;
}

//static 
bool Case::next_combination(vector<bool>& s)
{
  const vector<bool> TRUE_FALSE = { true, false }; // const 10 sequence
  auto iLastTrueFalse = find_end(
    s.begin(), s.end(), TRUE_FALSE.begin(), TRUE_FALSE.end()); // find last 10 sequence

  if (iLastTrueFalse == s.end()) // no 10 sequence, no more combination
    return false;

  swap(*iLastTrueFalse, *(iLastTrueFalse + 1)); // change 10 to 01

  auto i = iLastTrueFalse + 2; // first element after 01
  auto nTrue = count(i, s.end(), true); // number of 1's after 01
  if (nTrue > 0) { // move all 1's to the front after 01
    fill_n(i, nTrue, true);
    fill(i + nTrue, s.end(), false);
  }

  return true;
}
