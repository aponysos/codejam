// Qualification Round 2008
// Problem C. Fly Swatter
// https://code.google.com/codejam/contest/32013/dashboard#s=p2
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <complex>

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

typedef complex<double> Point;

class Case
{
public:
  void ReadFrom(std::istream & is); // read from input stream
  void Compute(); // main body of alogrithm
  void WriteTo(std::ostream & os) const; // write result to output stream

private:
  static constexpr double PI = 3.14159265358979323846;
  static constexpr double SPI = PI / 2;

private:
  static double Nonnegative(double d);
  static double SectorArea(double radius, double theta);
  static double ChordArea(double radius, double theta);
  static Point HorizontalCrossoverPoint(double radius, double y);
  static Point VerticalCrossoverPoint(double radius, double x);

private:
  // add case-related members here
  double rFly_, rOuter_, thick_, rString_, gap_;
  double probability_;

  // intermediate variables
  double aUnhitting_; // area of unhitting area
  double rUnhitting_; // radius of unhitting area
  double slLattice_; // semi-length of a side of a single lattice
  double aLattice_; // area of a single lattice
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream & is)
{
  is >> rFly_ >> rOuter_ >> thick_ >> rString_ >> gap_;
}

void Case::Compute()
{
  probability_ = 0.0; // init result

  // init intermediate variables
  aUnhitting_ = 0.0;
  rUnhitting_ = Nonnegative(rOuter_ - thick_ - rFly_);
  slLattice_  = Nonnegative(gap_ / 2 - rFly_);
  aLattice_   = slLattice_ * slLattice_ * 4;

  bool isDone = false;
  for (int i = 0; !isDone; ++i) {
    for (int j = 0; ; ++j) {
      Point pCenter(
        rString_ + gap_ / 2 + i * (rString_ * 2 + gap_), 
        rString_ + gap_ / 2 + j * (rString_ * 2 + gap_)); // center point of lattic (i, j)
      Point pLT(pCenter + Point(-slLattice_,  slLattice_)); // left top point
      Point pLB(pCenter + Point(-slLattice_, -slLattice_)); // left bottom point
      Point pRT(pCenter + Point( slLattice_,  slLattice_)); // right top point
      Point pRB(pCenter + Point( slLattice_, -slLattice_)); // right bottom point

      // modulus of points
      double mLT = abs(pLT);
      double mLB = abs(pLB);
      double mRT = abs(pRT);
      double mRB = abs(pRB);

      if (mRT <= rUnhitting_) { // interior lattice
        aUnhitting_ += aLattice_;
        continue;
      }

      if (mLB >= rUnhitting_) { // exterior lattice
        if (j == 0) // no more lattices
          isDone = true;
        break;
      }

      // edge lattice
      Point pTop    = HorizontalCrossoverPoint(rUnhitting_, pLT.imag()); // top crossover point
      Point pBottom = HorizontalCrossoverPoint(rUnhitting_, pRB.imag()); // bottom crossover point
      Point pLeft   = VerticalCrossoverPoint(rUnhitting_, pLB.real()); // left crossover point
      Point pRight  = VerticalCrossoverPoint(rUnhitting_, pRT.real()); // right crossover point

      double theta = 0.0; // angle of chord
      double aPolygon = 0.0; // area of polygon

      if (mLT >= rUnhitting_ && mRB >= rUnhitting_) { // triangle
        theta = arg(pLeft) - arg(pBottom);
        aPolygon = (pLeft.imag() - pLB.imag()) * (pBottom.real() - pLB.real()) / 2;
      }
      else if (mLT <= rUnhitting_ && mRB <= rUnhitting_) { // pentagon
        theta = arg(pTop) - arg(pRight);
        aPolygon = aLattice_ - (pRT.imag() - pRight.imag()) * (pRT.real() - pTop.real()) / 2;
      }
      else if (mLT >= rUnhitting_ && mRB <= rUnhitting_) { // trapezoid
        theta = arg(pLeft) - arg(pRight);
        aPolygon = ((pLeft.imag() - pLB.imag()) + (pRight.imag() - pRB.imag())) * slLattice_;
      }
      else if (mLT <= rUnhitting_ && mRB >= rUnhitting_) { // trapezoid
        theta = arg(pTop) - arg(pBottom);
        aPolygon = ((pTop.real() - pLT.real()) + (pBottom.real() - pLB.real())) * slLattice_;
      }

      double aChord = ChordArea(rUnhitting_, theta); // area of chord
      aUnhitting_ += (aPolygon + aChord); // acumulate area of chord and polygon
    }
  }

  // hitting probability + unhitting probability == 1
  probability_ = 1 - aUnhitting_ / SectorArea(rOuter_, SPI);
}

void Case::WriteTo(std::ostream & os) const
{
  os << setiosflags(ios::fixed) << setprecision(6) << probability_;
}

//static 
double Case::Nonnegative(double d)
{
  return d < 0 ? 0.0 : d;
}

//static 
double Case::SectorArea(double radius, double theta)
{
  return radius * radius * theta / 2;
}

//static 
double Case::ChordArea(double radius, double theta)
{
  return SectorArea(radius, theta) - radius * radius * sin(theta / 2) * cos(theta / 2);
}

//static 
Point Case::HorizontalCrossoverPoint(double radius, double y)
{
  return polar(radius, asin(y / radius));
}

//static 
Point Case::VerticalCrossoverPoint(double radius, double x)
{
  return polar(radius, acos(x / radius));
}
