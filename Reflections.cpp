// https://hh.ru/vacancy/70477165
// https://drive.google.com/file/d/1AMJl8gYxXCmk_8r_09pgKwprUq68_Daz/view?usp=sharing

#include <iostream>
#include <vector>
//#include <cassert>

//#include "Reflections.h"

using namespace std;

//struct Point
//{
//    double x;
//    double z;
//};

void ReflectionsP(double* p, int n, double fR, double fS, double fA)
{
    if (0 >= fR)
        throw invalid_argument("The value of R must be greater than zero.");
    if (0 >= fS)
        throw invalid_argument("The value of S must be greater than zero.");
    if (fS >= fR)
        throw invalid_argument("The value of S must be less than R.");
    if (abs(fA) >= 90)
        throw invalid_argument("The absolute value of angle A is too large.");
    double fTga = tan(fA * acos(-1) / 180);
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
    if (fA < 0)
        x = -x;
    double fPhi = atan2(x, y);
    for (int i = 0; i < n; i++)
    {
        double a = fPhi * (i + 1);
        double r = vR[i % 2];
        *p++ = r * sin(a);
        *p++ = fR - r * cos(a);
    }
}

/*
void Reflections(vector<Point>& v, double fR, double fS, double fA)
{
    if (0 >= fR)
        throw invalid_argument("The value of R must be greater than zero.");
    if (0 >= fS)
        throw invalid_argument("The value of S must be greater than zero.");
    if (fS >= fR)
        throw invalid_argument("The value of S must be less than R.");
    if (abs(fA) >= 90)
        throw invalid_argument("The absolute value of angle A is too large.");
    double fTga = tan(fA * acos(-1) / 180);
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
        if(fD<0)
            throw invalid_argument("Bad A value.");
    }
    y = 0.5 * (b + nSign * sqrt(fD)) / (a);
    x = sqrt(fRS * fRS - y * y);
    if (fA < 0)
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
*/




double InputParam(const char* cszMsg)
{
    cout << cszMsg<<">";
    double fRes;
    cin >> fRes;
    return fRes;
}
int main()
{
    try
    {
        const int N = 5;
        //vector<Point> v(N);
        double vd[N * 2];
        /*
        double fR = InputParam("R");
        double fS = InputParam("S");
        double fA = InputParam("a");
        cout << fR << "; " << fS << "; " << fA << endl;
        Reflections(v, fR, fS, fA);
        /*/
        //Reflections(v, 10, 6, 15);
        //for (Point point : v) { cout << point.x << "; " << point.z << endl; }
        ReflectionsP(vd, N, 10, 6, 15);
        for (int i = 0; i < N; i++) { cout << vd[i * 2] << "; " << vd[i * 2 + 1] << endl; }
        //*/
        //Reflections(v, 10, 6, 30);
        //for (Point point : v) { cout << point.x << "; " << point.z << endl; }
        ReflectionsP(vd, N, 10, 6, 30);
        for (int i = 0; i < N; i++) { cout << vd[i * 2] << "; " << vd[i * 2 + 1] << endl; }
        //*/
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
}
