// Qualification Round 2008
// Problem A. Saving the Universe
// https://code.google.com/codejam/contest/32013/dashboard#s=p0
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // min_element
#include <limits>    // numeric_limits<size_t>::max()
#include <set>       // Greedy Solution

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
      TCase c(i + 1);
      c.ReadFrom(is);
      c.Compute();
      os << "Case #" << i + 1 << ": ";
      c.WriteTo(os);
      os << '\n';
    }
  }
};

class Case
{
public:
  Case(int iCase) : iCase_(iCase) {}

public:
  void ReadFrom(std::istream &is);      // read from input stream
  void WriteTo(std::ostream &os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  void MySolution();
  void GreedySolution();

private:
  int iCase_; // case # iCase_, 1-based

private:
  // input & output members
  vector<string> engines_;
  vector<string> queries_;
  size_t minSwitchTimes_;

  // intermediate members
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream &is)
{
  // read search engine names
  size_t nEngines = 0;
  is >> nEngines;
  is.get(); // read '\n'
  engines_.resize(nEngines);
  for (size_t i = 0; i < nEngines; ++i)
    getline(is, engines_[i]);

  // read queries
  size_t nQueries = 0;
  is >> nQueries;
  is.get(); // read '\n'
  queries_.resize(nQueries);
  for (size_t i = 0; i < nQueries; ++i)
    getline(is, queries_[i]);

  minSwitchTimes_ = 0; // init result
}

void Case::WriteTo(std::ostream &os) const
{
  os << minSwitchTimes_;
}

void Case::Compute()
{
  //MySolution();
  GreedySolution();
}

// My Solution: recursive algorithm
void Case::MySolution()
{
  // switchTimes[iq][is] is the minimum switches needed when
  // there are iq queries left and the current engine is engines_[is]
  // NOTE: results in switchTimes[0] are all 0, for that, no more query, no more switch
  size_t nEngines = engines_.size(), nQueries = queries_.size();
  vector<vector<size_t>> switchTimes(nQueries + 1); // switchTimes[nQuereis + 1][nEngines]
  for (size_t iq = 0; iq <= nQueries; ++iq)
    switchTimes[iq].resize(nEngines);

  // from where only last ONE query need to be sent, to where all queries need to be sent
  for (size_t iq = 1; iq <= nQueries; ++iq)
  {
    const string &query = queries_[nQueries - iq]; // current query, in reverse order
    for (size_t ie = 0; ie < nEngines; ++ie)
    {
      // the results for the last iq - 1 queries
      const vector<size_t> &lastSwitchTimes = switchTimes[iq - 1];
      if (query == engines_[ie]) // the engine's name matches the query
      {
        // find the min result in lastSwitchTimes excluding the current engine
        size_t min_last_switch = numeric_limits<size_t>::max();
        for (size_t i = 0; i < nEngines; ++i)
        {
          if (i == ie) // ignore current engine
            continue;
          if (min_last_switch > lastSwitchTimes[i])
            min_last_switch = lastSwitchTimes[i];
        }

        switchTimes[iq][ie] = min_last_switch + 1; // one more switch
      }
      else // the engine's name doesn't match the query, no more switch
        switchTimes[iq][ie] = lastSwitchTimes[ie];
    }
  }

  // the minimum result for all queries
  minSwitchTimes_ = *min_element(switchTimes[nQueries].begin(), switchTimes[nQueries].end());
}

// Contest Analysis Solution: Greedy Solution
void Case::GreedySolution()
{
  set<string> segment;
  for (auto &q : queries_)
  {
    if (segment.find(q) == segment.end() && segment.size() == engines_.size() - 1)
    { // q is the last type of query in segment
      ++minSwitchTimes_;
      segment.clear();
    }
    segment.insert(q);
  }
}
