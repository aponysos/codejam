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

typedef complex<double> Point;

class Case
{
public:
  Case(int iCase) : iCase_(iCase) {}

public:
  void ReadFrom(std::istream &is);      // read from input stream
  void WriteTo(std::ostream &os) const; // write result to output stream

  void Compute(); // main body of alogrithm

private:
  int iCase_; // case # iCase_, 1-based

private:
  static constexpr double PI = 3.14159265358979323846;
  static constexpr double SPI = PI / 2;

private:
  static double Nonnegative(double d);
  static double SectorArea(double radius, double theta);
  static double ChordArea(double radius, double theta);
  static double ModulusOf(double x, double y);
  static Point HorizontalCrossoverPoint(double radius, double y);
  static Point VerticalCrossoverPoint(double radius, double x);

private:
  // add case-related members here
  double rFly_, rOuter_, thick_, rString_, gap_;
  double probability_;
};

int main(int argc, char **argv)
{
  Problem<Case> p;
  p.Solve(cin, cout);

  return 0;
}

void Case::ReadFrom(std::istream &is)
{
  is >> rFly_ >> rOuter_ >> thick_ >> rString_ >> gap_;
}

void Case::WriteTo(std::ostream &os) const
{
  os << setiosflags(ios::fixed) << setprecision(6) << probability_;
}

void Case::Compute()
{
  probability_ = 0.0; // init result

  // intermediate variables
  double rUnhitting = Nonnegative(rOuter_ - thick_ - rFly_); // R - t - f, radius of unhitting area
  double slLattice = Nonnegative(gap_ / 2 - rFly_);          // g/2 - f, semi-length of a side of a single lattice
  double slGap = rString_ + gap_ / 2;                        // r + g/2, semi-gap between lattices

  double aLattice = slLattice * slLattice * 4; // area of a single lattice
  double aUnhitting = 0.0;                     // area of unhitting area

  for (int i = 0;; ++i)
  {
    double xCenter = slGap * (2 * i + 1); // x coordinate of certer point
    double xLeft = xCenter - slLattice;   // x coordinate of left edge
    double xRight = xCenter + slLattice;  // x coordinate of right edge

    // get the top lattice(i, jLB) with its left-bottom point inside the sector
    int jLB = -1;                                          // -1 means none
    double sdLB = rUnhitting * rUnhitting - xLeft * xLeft; // square difference
    if (sdLB > 0)
      jLB = static_cast<int>(floor(((sqrt(sdLB) + slLattice) / slGap) - 1) / 2);

    if (jLB < 0) // no more lattices
      break;

    // get the top lattice(i, jRT) with its right-top point inside the sector
    int jRT = -1;                                            // -1 means none
    double sdRT = rUnhitting * rUnhitting - xRight * xRight; // square difference
    if (sdRT > 0)
      jRT = static_cast<int>(floor(((sqrt(sdRT) - slLattice) / slGap) - 1) / 2);

    // interior complete lattices
    aUnhitting += aLattice * (jRT + 1);

    // edge incomplete lattices
    for (int j = jRT + 1; j <= jLB; ++j)
    {
      double yCenter = slGap * (j * 2 + 1); // y coordinate of certer point
      double yTop = yCenter + slLattice;    // y coordinate of top edge
      double yBottom = yCenter - slLattice; // y coordinate of bottom edge

      // modulus of vertices
      //double mLB = ModulusOf(xLeft, yBottom);  // left bottom point
      double mLT = ModulusOf(xLeft, yTop);     // left bottom point
      //double mRT = ModulusOf(xRight, yTop);    // right top point
      double mRB = ModulusOf(xRight, yBottom); // right bottom point

      // crossover points
      Point pTop = HorizontalCrossoverPoint(rUnhitting, yTop);       // top crossover point
      Point pBottom = HorizontalCrossoverPoint(rUnhitting, yBottom); // bottom crossover point
      Point pLeft = VerticalCrossoverPoint(rUnhitting, xLeft);       // left crossover point
      Point pRight = VerticalCrossoverPoint(rUnhitting, xRight);     // right crossover point

      double theta = 0.0;    // angle of chord
      double aPolygon = 0.0; // area of polygon

      if (mLT >= rUnhitting && mRB >= rUnhitting)
      { // triangle
        theta = arg(pLeft) - arg(pBottom);
        aPolygon = (pLeft.imag() - yBottom) * (pBottom.real() - xLeft) / 2;
      }
      else if (mLT <= rUnhitting && mRB <= rUnhitting)
      { // pentagon
        theta = arg(pTop) - arg(pRight);
        aPolygon = aLattice - (yTop - pRight.imag()) * (xRight - pTop.real()) / 2;
      }
      else if (mLT >= rUnhitting && mRB <= rUnhitting)
      { // trapezoid
        theta = arg(pLeft) - arg(pRight);
        aPolygon = ((pLeft.imag() - yBottom) + (pRight.imag() - yBottom)) * slLattice;
      }
      else if (mLT <= rUnhitting && mRB >= rUnhitting)
      { // trapezoid
        theta = arg(pTop) - arg(pBottom);
        aPolygon = ((pTop.real() - xLeft) + (pBottom.real() - xLeft)) * slLattice;
      }
      else // should not get here
        continue;

      double aChord = ChordArea(rUnhitting, theta); // area of chord
      aUnhitting += (aPolygon + aChord);            // acumulate area of chord and polygon
    }                                               // for j
  }                                                 // for i

  // hitting probability + unhitting probability == 1
  probability_ = 1 - aUnhitting / SectorArea(rOuter_, SPI);
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
double Case::ModulusOf(double x, double y)
{
  return abs(Point(x, y));
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
