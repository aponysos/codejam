// Round 1A 2008
// Problem B. Milkshakes
// https://code.google.com/codejam/contest/32016/dashboard#s=p1
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

typedef vector<pair<int, int>> Customer;

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  // add case-related members here
  int nFlavors_;
  vector<Customer> likes_;
  bool satisfied_;
  vector<int> flavors_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> nFlavors_;
  int nCustomers = 0;
  is >> nCustomers;
  likes_.resize(nCustomers);
  for (int i = 0; i < nCustomers; ++i) {
    int nLikes = 0;
    is >> nLikes;
    likes_[i].resize(nLikes);
    for (int j = 0; j < nLikes; ++j)
      is >> likes_[i][j].first >> likes_[i][j].second;
  }
  satisfied_ = false;
  flavors_.resize(nCustomers);
}

void Case::Compute()
{
}

void Case::WriteTo(std::ostream & os) const
{
  if (satisfied_) {
    for (auto i : flavors_)
      os << i << ' ';
  }
  else
    os << "IMPOSSIBLE";
}
