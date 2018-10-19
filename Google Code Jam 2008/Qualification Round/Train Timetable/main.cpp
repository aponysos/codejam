// Qualification Round 2008
// Problem B. Train Timetable
// https://code.google.com/codejam/contest/32013/dashboard#s=p1
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

  typedef pair<int, int> Trip;
  typedef vector<Trip> Timeline;
  enum { DEPARTURE, ARRIVAL };

private:
  void ReadTrip(istream & is, Trip & trip);
  void InitTimeline(Timeline & tml, const Timeline & dpt, const Timeline & arv);
  int ComputeTrainsNeeded(const Timeline & tml);

private:
  // add case-related members here
  int turnRoundTime_; // turnaround time
  Timeline tripsA_, tripsB_; // trips' departure times & arrival times
  int nTrainsNeededA_, nTrainsNeededB_; // results
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  // input turnaround time
  is >> turnRoundTime_;

  // input number of trips
  int nTripsA, nTripsB;
  is >> nTripsA >> nTripsB;
  tripsA_.resize(nTripsA);
  tripsB_.resize(nTripsB);

  // input departure and arrival time
  for (int i = 0; i < nTripsA; ++i) {
    ReadTrip(is, tripsA_[i]);
  }
  for (int i = 0; i < nTripsB; ++i) {
    ReadTrip(is, tripsB_[i]);
  }
}

void Case::Compute()
{
  nTrainsNeededA_ = nTrainsNeededB_ = 0; // init result

  size_t nTripsAB = tripsA_.size() + tripsB_.size();

  // init timelines
  Timeline timelineA(nTripsAB), timelineB(nTripsAB);
  InitTimeline(timelineA, tripsA_, tripsB_);
  InitTimeline(timelineB, tripsB_, tripsA_);

  // traverse timelines
  nTrainsNeededA_ = ComputeTrainsNeeded(timelineA);
  nTrainsNeededB_ = ComputeTrainsNeeded(timelineB);
}

void Case::WriteTo(std::ostream & os) const
{
  os << nTrainsNeededA_ << ' ' << nTrainsNeededB_;
}

void Case::ReadTrip(istream & is, Trip & trip)
{
  int hh, mm;
  is >> hh;
  is.get(); // read ':'
  is >> mm;
  trip.first = hh * 60 + mm;
  is >> hh;
  is.get(); // read ':'
  is >> mm;
  trip.second = hh * 60 + mm;
}

void Case::InitTimeline(Timeline & tml, const Timeline & dpt, const Timeline & arv)
{
  // add departure times
  auto i = transform(dpt.begin(), dpt.end(), tml.begin(),
    [](const auto & trip) { return make_pair(trip.first, DEPARTURE); }
  );

  // add arrival times
  transform(arv.begin(), arv.end(), i,
    [this](const auto & trip) { return make_pair(trip.second + turnRoundTime_, ARRIVAL); }
  );

  // sort timelines
  sort(tml.begin(), tml.end(),
    [](const auto & tm1, const auto & tm2) {
    return tm1.first < tm2.first || (tm1.first == tm2.first && tm1.second > tm2.second); }
  );
}

int Case::ComputeTrainsNeeded(const Timeline & tml)
{
  int nTrainsAvail = 0, nTrainsNeeded = 0;

  for (const auto & i : tml) {
    if (i.second == DEPARTURE) { // departure
      if (nTrainsAvail > 0)
        --nTrainsAvail;
      else
        ++nTrainsNeeded;
    }
    else { // arrival
      ++nTrainsAvail;
    }
  }

  return nTrainsNeeded;
}
