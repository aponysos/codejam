// Round 1A 2008
// Problem B. Milkshakes
// https://code.google.com/codejam/contest/32016/dashboard#s=p1
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

typedef vector<pair<int, int>> Customer;

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  vector<Customer> CheckFlavors() const;
  bool CheckCustomer(const Customer & c) const;
  bool Satisfy(const vector<Customer> & unsatisfied);

private:
  // add case-related members here
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
  int nFlavors = 0;
  is >> nFlavors;
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

  // init results
  satisfied_ = false;
  flavors_.resize(nFlavors);
}

void Case::Compute()
{
  for (vector<Customer> unsatisfied = CheckFlavors(); unsatisfied.size() > 0; unsatisfied = CheckFlavors()) {
    if (!Satisfy(unsatisfied))
      return;
  }

  satisfied_ = true;
}

void Case::WriteTo(std::ostream & os) const
{
  if (satisfied_) {
    for (const auto & i : flavors_)
      os << i << ' ';
  }
  else
    os << "IMPOSSIBLE";
}

vector<Customer> Case::CheckFlavors() const
{
  vector<Customer> unsatisfied;

  for (const auto & c : likes_)
    if (!CheckCustomer(c))
      unsatisfied.push_back(c);

  return unsatisfied;
}

bool Case::CheckCustomer(const Customer & c) const
{
  for (const auto & l : c) {
    if (flavors_[l.first - 1] == l.second)
      return true;
  }

  return false;
}

bool Case::Satisfy(const vector<Customer> & unsatisfied)
{
  for (const auto c : unsatisfied) {
    auto i = find_if(c.begin(), c.end(), [](auto l) { return l.second == 1; });
    if (i != c.end())
      flavors_[i->first - 1] = 1;
    else
      return false;
  }

  return true;
}
