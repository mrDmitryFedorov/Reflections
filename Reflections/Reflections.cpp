#include "pch.h"
#include "framework.h"
#include <vector>
#include <stdexcept>
#include "Reflections.h"

using namespace std;

void Reflections(vector<Point>& v, double fR, double fS, double fA)
{
    if (0 >= fR)
        throw invalid_argument("The value of R must be greater than zero.");
    if (0 >= fS)
        throw invalid_argument("The value of S must be greater than zero.");
    if (fS >= fR)
        throw invalid_argument("The value of S must be less than R.");
    if (cos(fA) <= cos(acos(-1) / 2))
        throw invalid_argument("The absolute value of angle A must be less than Pi/2.");
    double fTga = tan(fA);
    double vR[] = { fR - fS, fR };
    double y = fR;
    double x = 0;
    double fRS = fR - fS;
    double a = NAN;
    double b = NAN;
    auto getD = [&]() {double fTga2 = fTga * fTga; a = fTga2 + 1; b = 2 * fR * fTga2; double c = fR * fR * fTga2 - fRS * fRS; return b * b - 4 * a * c; };
    double fD = getD();
    int nSign = 1;
    if (fD < 0)
    {
        nSign = -1;
        fRS = fR;
        vR[0] = fR;
        fD = getD();
        if (fD < 0)
            throw invalid_argument("Bad A value.");
    }
    y = 0.5 * (b + nSign * sqrt(fD)) / (a);
    x = sqrt(fRS * fRS - y * y);
    if (fTga < 0)
        x = -x;
    double fPhi = atan2(x, y);
    for (int i = 0; i < (int)v.size(); i++)
    {
        double a = fPhi * (i + 1);
        double r = vR[i % 2];
        v[i].x = r * sin(a);
        v[i].z = fR - r * cos(a);
    }
}
