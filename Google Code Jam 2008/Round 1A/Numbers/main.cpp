// Round 1A 2008
// Problem C. Numbers
// https://code.google.com/codejam/contest/32016/dashboard#s=p2
//

#include <iostream>
#include <vector>
#include <iomanip>
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

typedef unsigned long long Integer;

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  static int Mod125(Integer n); // n mod 125
  static int Power3Mod125(Integer n); // (3 ^ n) mod 125
  static vector<int> cachePower3Mod125_;
  static int Mod1000FromMod125(int mod125); // get mod1000 from mod125
  static vector<int> cacheMod1000FromMod125_;

private:
  // add case-related members here
  Integer n_;

  // results
  int mod1000_; // modulus of one thousand
};

//static 
vector<int> Case::cachePower3Mod125_;

//static 
vector<int> Case::cacheMod1000FromMod125_;

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> n_;

  cachePower3Mod125_.resize(125, -1);
  cachePower3Mod125_[0] = 1;

  cacheMod1000FromMod125_.resize(125, -1);
  for (int i = 0; i < 1000; i += 8)
    cacheMod1000FromMod125_[i % 125] = i % 1000;

  // init results
  mod1000_ = 0;
}

void Case::Compute()
{
  if (n_ <= 4) {
    long double base = 3 + sqrt(5);
    mod1000_ = static_cast<int>(floor(pow(base, n_)));
    mod1000_ %= 1000;
  }
  else {
    int nmod125  = Mod125(n_);
    int n1mod125 = Mod125(n_ - 1);
    int n2mod125 = Mod125(n_ - 2);
    int n3mod125 = Mod125(n_ - 3);
    int power3nmod125  = Power3Mod125(n_);
    int power3n2mod125 = Power3Mod125(n_ - 2);
    int power3n4mod125 = Power3Mod125(n_ - 4);

    int xnmod125 = 0; // xn mod 125
    xnmod125 += Mod125(power3nmod125);
    xnmod125 += Mod125(nmod125 * n1mod125 / 2 * power3n2mod125 * 5);
    xnmod125 += Mod125(nmod125 * n1mod125 * n2mod125 * n3mod125 / 4 / 3 / 2 * power3n4mod125 * 25);
    xnmod125  = Mod125(xnmod125 * 2);

    mod1000_ = Mod1000FromMod125(xnmod125) - 1;
    mod1000_ = mod1000_ < 0 ? 999 : mod1000_; // check -1
  }
}

void Case::WriteTo(std::ostream & os) const
{
  os << setw(3) << setfill('0') << mod1000_;
}

int Case::Mod125(Integer n)
{
  return n % 125;
}

int Case::Power3Mod125(Integer n)
{
  n = n % 124;

  int & cache = cachePower3Mod125_[n];
  if (cache >= 0)
    return cache;
  else
    return cache = Mod125(Power3Mod125(n - 1) * 3);
}

int Case::Mod1000FromMod125(int mod125)
{
  return cacheMod1000FromMod125_[mod125];
}
