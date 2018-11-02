// Round 1A 2008
// Problem A. Minimum Scalar Product
// https://code.google.com/codejam/contest/32016/dashboard
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <functional>
#include <cmath>

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

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

void Case::Compute()
{
  minSP_ = 0;

  auto absGt = [](auto lhs, auto rhs) {
    return abs(lhs) > abs(rhs) || (abs(lhs) == abs(rhs) && sgn(lhs) > sgn(rhs));
  };
  sort(v1.begin(), v1.end(), absGt);
  sort(v2.begin(), v2.end(), absGt);

  vector<long long> v3;
  list<long long> l1(v1.begin(), v1.end()), l2(v2.begin(), v2.end());
  list<long long> *la = nullptr, *lb = nullptr;
  int s = 0;
  while (!l1.empty()) {
    bool b = absGt(*l1.begin(), *l2.begin());
    auto i = b ? l1.begin() : l2.begin();
    la = b ? &l1 : &l2;
    lb = b ? &l2 : &l1;
    s = sgn(*i);

    auto j = find_if(lb->begin(), lb->end(), [s](auto k) { return sgn(k) != s; });

    if (j == lb->end())
      break;

    //if (la == &l1)
    //  cout << *i << " * " << *j << '\n';
    //else
    //  cout << *j << " * " << *i << '\n';
    v3.push_back((*i) * (*j));
    la->erase(i);
    lb->erase(j);
  }

  while (!l1.empty()) {
    auto i = find_if(la->begin(), la->end(), [s](auto k) { return sgn(k) != s; });

    if (i == la->end())
      break;

    auto j = find_if(lb->begin(), lb->end(), [s](auto k) { return sgn(k) == s; });

    if (j == lb->end())
      break;

    //if (la == &l1)
    //  cout << *i << " * " << *j << '\n';
    //else
    //  cout << *j << " * " << *i << '\n';
    v3.push_back((*i) * (*j));
    la->erase(i);
    lb->erase(j);
  }

  transform(l1.begin(), l1.end(), l2.rbegin(), back_inserter(v3), multiplies<long long>());
  //for (auto i : l1)
  //  cout << i << ' ';
  //cout << '\n';
  //for (auto i : l2)
  //  cout << i << ' ';
  //cout << '\n';

  minSP_ = accumulate(v3.begin(), v3.end(), 0LL);
}

void Case::WriteTo(std::ostream & os) const
{
  os << minSP_;
}
