// Round 1A 2008
// Problem B. Milkshakes
// https://code.google.com/codejam/contest/32016/dashboard#s=p1
//

#include <iostream>
#include <vector>
#include <set>
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

typedef pair<int, int> Like;
typedef vector<Like> Customer;

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  bool CheckFlavors(set<int> & maltedDemands);  // what flavors are demanded to be malted
                                                // return false if can not be satisfied

  void Satisfy(const set<int> & maltedDemands); // satisfy malted-likes of unsatisfied customers

private:
  // add case-related members here
  set<Customer> likes_; // unsatisfied customers

  // results
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
  for (int i = 0; i < nCustomers; ++i) {
    int nLikes = 0;
    is >> nLikes;
    Customer c;
    for (int j = 0; j < nLikes; ++j) {
      Like l;
      is >> l.first >> l.second;
      c.push_back(l);
    }
    likes_.insert(move(c));
  }

  // init results
  satisfied_ = false;
  flavors_.resize(nFlavors); // none flavor is malted at first
}

void Case::Compute()
{
  // keep checking the malted-demands of unsatified customer and satisfying them, 
  // until no more damands or current damands can not be satisfied.
  set<int> maltedDemands;
  while (CheckFlavors(maltedDemands)) { // check for malted-demands
    if (maltedDemands.size() > 0)
      Satisfy(maltedDemands); // satisfy malted-demands
    else { // no more malted-demands
      satisfied_ = true;
      break;
    }
  }
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

bool Case::CheckFlavors(set<int> & maltedDemands)
{
  maltedDemands.clear();

  // traverse all unsatisfied customers
  for (auto ic = likes_.cbegin(); ic != likes_.cend(); ) {
    bool isSatisfied = false; // is customer satisfied
    int maltedFlavor = 0;     // which malted flavor does customer like

    // traverse all likes of customer
    for (auto l : *ic) {
      // record down customer's malted flavor
      if (l.second == 1)
        maltedFlavor = l.first;

      if (flavors_[l.first - 1] == l.second) { // customer satified
        isSatisfied = true;

        if (l.second == 1)        // malted flavor satisfied, forever satisfied
          ic = likes_.erase(ic);  // delete customer, move to next customer
        else    // unmalted flavor satisfied, temporarily satisfied
          ++ic; // move to next customer

        break; // break likes traversal
      }
    } // for likes

    // for unsatisfied customer, check if he can be satisfied and record down his malted flavor
    if (!isSatisfied) {
      if (maltedFlavor == 0)  // this unsatisfied customer does not have a malted flavor,
        return false;         // so he can never be satisfied
      else {
        maltedDemands.insert(maltedFlavor); // this flavor will be malted to satisfy this customer
        ic = likes_.erase(ic);        // delete to-be-satisfied customer
      }
    }
  } // for customers

  return true;
}

void Case::Satisfy(const set<int> & maltedDemands)
{
  for (auto m : maltedDemands)
    flavors_[m - 1] = 1;
}
