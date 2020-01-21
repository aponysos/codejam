// Round 1B 2008
// Problem A. Crop Triangles
// https://code.google.com/codejam/contest/32017/dashboard#s=p0
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

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
  static long long C3(long long n); // C(N, 3)

private:
  // add case-related members here
  int n_, A_, B_, C_, D_, x0_, y0_, M_; // input parameters
  long long nTriangles_; // output result

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
  // coordinates sequences
  vector<long long> xn(n_), yn(n_);
  xn[0] = x0_;
  yn[0] = y0_;
  for (int i = 1; i < n_; ++i) {
    xn[i] = (A_ * xn[i - 1] + B_) % M_;
    yn[i] = (C_ * yn[i - 1] + D_) % M_;
  }

  // coordinates mod 3
  vector<long long> xnmod3(n_), ynmod3(n_);
  generate(xnmod3.begin(), xnmod3.end(), [&, i = 0] () mutable { return xn[i++] % 3; });
  generate(ynmod3.begin(), ynmod3.end(), [&, i = 0] () mutable { return yn[i++] % 3; });

  // divide points into 9 sets according to coordinates mod3
  // count the numbers of the 9 sets
  long long cmod3[3][3] = {0};
  for (int i = 0; i < n_; ++i)
    ++cmod3[xnmod3[i]][ynmod3[i]];

  auto c3_add = [] (auto & a, auto & b) {
    assert(a >= 0);
    auto c3 = C3(b);
    assert(c3 >= 0);
    c3 += a;
    assert(c3 >= 0);
    return c3;
  };
  long long * pcmod3 = &cmod3[0][0];
  nTriangles_ += accumulate(pcmod3, pcmod3 + 9, 0LL, c3_add);
  nTriangles_ += cmod3[0][0] * cmod3[0][1] * cmod3[0][2];
  nTriangles_ += cmod3[1][0] * cmod3[1][1] * cmod3[1][2];
  nTriangles_ += cmod3[2][0] * cmod3[2][1] * cmod3[2][2];
  nTriangles_ += cmod3[0][0] * cmod3[1][0] * cmod3[2][0];
  nTriangles_ += cmod3[0][1] * cmod3[1][1] * cmod3[2][1];
  nTriangles_ += cmod3[0][2] * cmod3[1][2] * cmod3[2][2];
  nTriangles_ += cmod3[0][0] * cmod3[1][1] * cmod3[2][2];
  nTriangles_ += cmod3[0][0] * cmod3[2][1] * cmod3[1][2];
  nTriangles_ += cmod3[1][0] * cmod3[0][1] * cmod3[2][2];
  nTriangles_ += cmod3[1][0] * cmod3[2][1] * cmod3[0][2];
  nTriangles_ += cmod3[2][0] * cmod3[1][1] * cmod3[0][2];
  nTriangles_ += cmod3[2][0] * cmod3[0][1] * cmod3[1][2];
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

//static 
long long Case::C3(long long n)
{
  long long c3 = 0;
  if (n >= 3) {
    c3 = n;
    c3 *= n - 1;
    assert(c3 >= 0);
    c3 *= n - 2;
    assert(c3 >= 0);
    c3 /= 6;
  }
  return c3;
}
