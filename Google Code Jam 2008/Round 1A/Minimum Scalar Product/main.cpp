// Round 1A 2008
// Problem A. Minimum Scalar Product
// https://code.google.com/codejam/contest/32016/dashboard
//

#include <iostream>
#include <vector>
#include <algorithm>  // sort, transform
#include <numeric>    // accumulate

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
  vector<long long> v1, v2;
  long long minSP_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  size_t n = 0;
  cin >> n;
  v1.resize(n);
  v2.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> v1[i];
  for (int i = 0; i < n; ++i)
    cin >> v2[i];
}

void Case::Compute()
{
  minSP_ = 0LL;

  // sort
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());

  // multiply
  vector<long long> v3;
  transform(v1.begin(), v1.end(), v2.rbegin(), back_inserter(v3), multiplies<long long>()); // 'long long' is needed to instantiate template to long long

  // accumulate
  minSP_ = accumulate(v3.begin(), v3.end(), 0LL); // 'LL' is needed to instantiate template to long long
}

void Case::WriteTo(std::ostream & os) const
{
  os << minSP_;
}
