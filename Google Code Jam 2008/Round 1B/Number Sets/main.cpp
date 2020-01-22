// Round 1B 2008
// Problem C. Mousetrap
// https://code.google.com/codejam/contest/32017/dashboard#s=p2
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

template <typename TCase>
class Problem
{
public:
  void Solve(std::istream &is, std::ostream &os)
  {
    int nCase = 0;
    is >> nCase;
    for (int i = 0; i < nCase; ++i)
    {
      TCase c;
      c.ReadFrom(is);
      c.Compute();
      os << "Case #" << i + 1 << ": ";
      c.WriteTo(os);
      os << '\n';
    }
  }
};

typedef long long Integer;

class Case
{
public:
  void ReadFrom(std::istream &is);      // read from input stream
  void WriteTo(std::ostream &os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  Integer MergeSets(Integer p);

  static Integer NextPrime(Integer val);
  static bool IsPrime(Integer val);
  static Integer ConstructPrimes(Integer val);

private:
  // input & output
  Integer a_, b_, p_; // input
  Integer nSets_;     // output

  // intermediate variables
  Integer nInt_;
  vector<Integer> m_;
  static vector<Integer> primes_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream &is)
{
  is >> a_ >> b_ >> p_;

  // init result
  nSets_ = 0;
}

void Case::WriteTo(std::ostream &os) const
{
  os << nSets_;
}

void Case::Compute()
{
  nSets_ = nInt_ = b_ - a_ + 1;
  m_.resize(nInt_);
  iota(m_.begin(), m_.end(), 0);

  Integer maxp = ConstructPrimes(nInt_);
  for (Integer p = NextPrime(p_ - 1); p <= maxp; p = NextPrime(p))
  {
    Integer nMerged = MergeSets(p);
    nSets_ -= nMerged;
  }
}

Integer Case::MergeSets(Integer p)
{
  Integer nMerged = 0;
  for (Integer to = (0 == a_ % p ? 0 : p - a_ % p), from = to + p; 
    from < nInt_; from += p)
  {
    Integer f = from, t = to;
    while (m_[f] != f)
      f = m_[f];
    while (m_[t] != t)
      t = m_[t];

    if (m_[f] != m_[t])
    {
      m_[f] = m_[t];
      ++nMerged;
    }
  }
  return nMerged;
}

//static
vector<Integer> Case::primes_ = {2, 3};

//static
Integer Case::NextPrime(Integer val)
{
  auto iNext = upper_bound(primes_.begin(), primes_.end(), val);
  if (iNext != primes_.end())
    return *iNext;
  else
    return ConstructPrimes(val);
}

//static
bool Case::IsPrime(Integer val)
{
  Integer sq = sqrt(val);
  for (int i = 0; primes_[i] <= sq; ++i)
    if (0 == val % primes_[i])
      return false;
  return true;
}

//static
Integer Case::ConstructPrimes(Integer val)
{
  Integer pNew = primes_[primes_.size() - 1] + 2;
  for (; pNew <= val; pNew += 2)
  {
    if (IsPrime(pNew))
      primes_.push_back(pNew);
  }

  while (!IsPrime(pNew))
    pNew += 2;

  primes_.push_back(pNew);
  return pNew;
}
