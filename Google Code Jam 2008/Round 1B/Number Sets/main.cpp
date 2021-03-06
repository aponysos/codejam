// Round 1B 2008
// Problem C. Mousetrap
// https://code.google.com/codejam/contest/32017/dashboard#s=p2
// Command Arguments : < $(Configuration).in > $(Configuration).out
//

#include <iostream>
#include <vector>
#include <numeric> // iota
#include <algorithm> // lower_bound
#include <cmath> // sqrt
#include <chrono>

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

typedef unsigned long long Integer;

class Case
{
public:
  void ReadFrom(std::istream &is);      // read from input stream
  void WriteTo(std::ostream &os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  Integer MergeSets(Integer p); // merge sets of mutiples of p, return # of sets decreased, 0 if none

public:
  static void ConstructPrimes(Integer val); // the max prime number is equal or greater than val
  static bool IsPrime(Integer val);         // if val is a prime number

private:
  // input & output
  Integer a_, b_, p_; // input
  Integer nSets_;     // output

  // intermediate variables
  Integer nInt_;                  // length of interval: b_ - a_ + 1
  vector<Integer> m_;             // sets map
  static vector<Integer> primes_; // prime numbers cache
};

// auto-output execution time of a function
class AutoClock
{
public:
  AutoClock(const std::string &funcName) : funcName_(funcName), start_(std::chrono::system_clock::now()) {}
  ~AutoClock()
  {
    auto elapsed_ = std::chrono::system_clock::now() - start_;
    std::clog << funcName_ << ": " << (double)elapsed_.count() / 1000 / 1000 << "ms" << std::endl;
  }

private:
  std::string funcName_;
  std::chrono::time_point<std::chrono::system_clock> start_;
};

//#define TRACE() AutoClock ac(__FUNCTION__)
#define TRACE()

int main(int argc, char **argv)
{
  Case::ConstructPrimes(1000000);

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
  TRACE();

  nSets_ = nInt_ = b_ - a_ + 1;
  m_.resize(nInt_);
  iota(m_.begin(), m_.end(), 0); // init map {0, 1, 2, ...}

  auto ip = lower_bound(primes_.begin(), primes_.end(), p_);      // min prime number >= p_
  auto iend = lower_bound(primes_.begin(), primes_.end(), nInt_); // max one >= length of interval
  clog << *ip << "->" << *iend << " : " << iend - ip << " primes" << '\n';

  // traverse prime numbers from *ip to *iend
  for (; ip < iend; ++ip)
  {
    Integer nMerged = MergeSets(*ip);
    nSets_ -= nMerged;
  }
}

Integer Case::MergeSets(Integer p)
{
  Integer nMerged = 0;
  // to is the min number that is multiples of p, from is second min one
  // merge set of from to set of to
  // advance from by p
  for (Integer to = (0 == a_ % p ? 0 : p - a_ % p), from = to + p;
       from < nInt_; from += p)
  {
    Integer f = from, t = to;
    while (m_[f] != f) // find set root of from
      f = m_[f];
    while (m_[t] != t) // find set root of from
      t = m_[t];

    if (m_[f] != m_[t]) // merge
    {
      m_[f] = m_[t];
      ++nMerged;
    }

    // link from & to directly to set root
    // this optimization reduces the execution time greatly
    m_[from] = m_[f];
    m_[to] = m_[t];
  }
  return nMerged;
}

//static
vector<Integer> Case::primes_ = {2, 3};

//static
bool Case::IsPrime(Integer val)
{
  Integer sq = sqrt(val); // check primes numbers up to square of val
  for (int i = 0; primes_[i] <= sq; ++i)
    if (0 == val % primes_[i])
      return false;
  return true;
}

//static
void Case::ConstructPrimes(Integer val)
{
  Integer pLast = *primes_.rbegin(); // last one of primes_
  Integer pNew = pLast;

  // construct new prime number from the last one of primes_
  while (pLast < val)
  {
    pNew += 2; // step 2
    if (IsPrime(pNew))
    {
      primes_.push_back(pNew);
      pLast = pNew;
    }
  }

  clog << primes_.size() << " primes constructed. the max one is " << *(primes_.end() - 1) << '\n';
}
