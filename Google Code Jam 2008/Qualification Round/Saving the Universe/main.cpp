// Qualification Round 2008
// Problem A. Saving the Universe
// https://code.google.com/codejam/contest/32013/dashboard#s=p0
//

#include <iostream>
#include <vector>
#include <string>
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
  std::vector<std::string> engines_;
  std::vector<std::string> queries_;
  int minSwitchTimes_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  // read search engine names
  int nEngines = 0;
  cin >> nEngines;
  cin.get(); // read '\n'
  engines_.resize(nEngines);
  for (int i = 0; i < nEngines; ++i) {
    getline(is, engines_[i]);
  }

  // read queries
  int nQueries = 0;
  cin >> nQueries;
  cin.get(); // read '\n'
  queries_.resize(nQueries);
  for (int i = 0; i < nQueries; ++i) {
    getline(is, queries_[i]);
  }
}

void Case::Compute()
{
  minSwitchTimes_ = 0; // init result

  size_t nEngines = engines_.size(), nQuereis = queries_.size();
  vector<vector<int>> switches(nQuereis + 1); // switches[nQuereis + 1][nEngines]
  for (int iq = 0; iq <= nQuereis; ++iq) {
    switches[iq].resize(nEngines);
  }

  for (int iq = 1; iq <= nQuereis; ++iq) {
    const string & query = queries_[nQuereis - iq]; // reverse
    for (int is = 0; is < nEngines; ++is) {
      if (query == engines_[is]) { // 上一组中非此engine的最小值+1
        vector<int> last_switches(switches[iq - 1]);
        last_switches.erase(last_switches.begin() + is);
        int min_last_switch = *min_element(last_switches.begin(), last_switches.end());
        switches[iq][is] = min_last_switch + 1;
      }
      else { // 上一组中此engine的值
        switches[iq][is] = switches[iq - 1][is];
      }
    }
  }

  minSwitchTimes_ = *min_element(switches[nQuereis].begin(), switches[nQuereis].end());
}

void Case::WriteTo(std::ostream & os) const
{
  os << minSwitchTimes_;
}
