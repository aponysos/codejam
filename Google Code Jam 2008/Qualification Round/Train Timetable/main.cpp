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

private:
  void ReadTrip(istream & is, Trip & trip);

private:
  // add case-related members here
  int turnRoundTime_; // turnaround time
  vector<Trip> tripsA_, tripsB_; // trips' departure times & arrival times
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

  size_t nTripsA = tripsA_.size(), nTripsB = tripsB_.size();
  size_t nTripsAB = nTripsA + nTripsB;

  // init timelines
  vector<pair<int, int>> timelineA(nTripsAB), timelineB(nTripsAB);
  auto iTimelineA = transform(tripsA_.begin(), tripsA_.end(), timelineA.begin(), 
    [](const auto & trip) { return make_pair(trip.first, 0); }
  );
  transform(tripsB_.begin(), tripsB_.end(), iTimelineA,
    [this](const auto & trip) { return make_pair(trip.second + turnRoundTime_, 1); }
  );
  auto iTimelineB = transform(tripsB_.begin(), tripsB_.end(), timelineB.begin(),
    [](const auto & trip) { return make_pair(trip.first, 0); }
  );
  transform(tripsA_.begin(), tripsA_.end(), iTimelineB,
    [this](const auto & trip) { return make_pair(trip.second + turnRoundTime_, 1); }
  );

  // sort timelines
  sort(timelineA.begin(), timelineA.end(),
    [](const auto & tm1, const auto & tm2) { 
      return tm1.first < tm2.first || (tm1.first == tm2.first && tm1.second > tm2.second); }
  );
  sort(timelineB.begin(), timelineB.end(),
    [](const auto & tm1, const auto & tm2) {
    return tm1.first < tm2.first || (tm1.first == tm2.first && tm1.second > tm2.second); }
  );


  // traverse timelines
  int availA = 0, availB = 0;
  for (const auto & i : timelineA) {
    if (i.second == 0) { // departure
      if (availA > 0)
        --availA;
      else
        ++nTrainsNeededA_;
    }
    else { // arrival
      ++availA;
    }
  }
  for (const auto & i : timelineB) {
    if (i.second == 0) { // departure
      if (availB > 0)
        --availB;
      else
        ++nTrainsNeededB_;
    }
    else { // arrival
      ++availB;
    }
  }
}

void Case::WriteTo(std::ostream & os) const
{
  os << nTrainsNeededA_ << ' ' << nTrainsNeededB_;
}

void Case::ReadTrip(istream & is, Trip & trip)
{
  int hh, mm;
  is >> hh;
  is.get();
  is >> mm;
  trip.first = hh * 60 + mm;
  is >> hh;
  is.get();
  is >> mm;
  trip.second = hh * 60 + mm;
}
