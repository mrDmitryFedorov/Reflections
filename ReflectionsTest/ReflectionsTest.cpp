#include "pch.h"
#include "CppUnitTest.h"
#include "..\Reflections\Reflections.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <strstream>

using namespace std;

namespace ReflectionsTest
{
	TEST_CLASS(ReflectionsTest)
	{
	public:
		TEST_METHOD(TestMethodReflections_RA)
		{
			const double EPSILON = 1e-10;
			const int N = 5;
			double fR = 10;
			double fS = 6;
			const double fPi180 = acos(-1) / 180;
			wchar_t buffer[256];
			for (double fA : {-60,-30,-15,0,15, 30, 60})
			{
				fA *= fPi180;
				vector<Point> v(N);
				double fRS = fR - fS;
				Reflections(v, fR, fS, fA);
				double x0 = 0;
				double y0 = fR;
				double r0 = fR;
				auto lR = [](double x, double y) {return sqrt(x * x + y * y); };
				for (int i = 0; i < N; i++)
				{
					double x = v[i].x;
					double y = fR - v[i].z;
					double r = lR(x, y);
					double r1 = lR(x - x0, y - y0);
					double a = acos((i % 2) ? ((-x * (x0 - x) - y * (y0 - y)) / (r * r1)) : ((-x0 * (x - x0) - y0 * (y - y0)) / (r0 * r1)));
					swprintf_s(buffer, L"%0.3f\t%0.3f\t%0.3f\t%0.3f\n", x, y, r, a / fPi180);
					Logger::WriteMessage(buffer);
					if(i==0)
						Assert::IsTrue((v[0].x * sin(fA)) >= 0, L"Wrong direction.");
					Assert::IsTrue((abs(fR - r) < EPSILON) || (abs(fRS - r) < EPSILON), L"Wrong radius value.");
					Assert::IsTrue((abs(a - abs(fA)) < EPSILON), L"Wrong angle value.");
					r0 = r;
					x0 = x;
					y0 = y;
				}
			}
			Logger::WriteMessage("Ok\n");
		}
		TEST_METHOD(TestMethodReflections_Throw)
		{
			struct Param
			{
				double fR;
				double fS;
				double fA;
			};


			Param vParams[] = { 
				{10,6,-100},
				{10,6,-90},
				{10,6,90},
				{10,6,100},
				{10,0,0},
				{10,10,0},
				{6,10,0}
			};
			const int N = 5;
			const double fPi180 = acos(-1) / 180;
			wchar_t buffer[256];
			for (int i = 0; i < N; i++)
			{
				vector<Point> v(N);
				bool bOk = false;
				try
				{
					swprintf_s(buffer, L"%0.3f\t%0.3f\t%0.3f\n", vParams[i].fR, vParams[i].fS, vParams[i].fA);
					Logger::WriteMessage(buffer);
					Reflections(v, vParams[i].fR, vParams[i].fS, vParams[i].fA * fPi180);
					for (int i = 0; i < N; i++)
					{
						double x = v[i].x;
						double y = vParams[i].fR - v[i].z;
						swprintf_s(buffer, L"\t%0.3f\t%0.3f\n", x, y);
						Logger::WriteMessage(buffer);
					}
				}
				catch (const std::exception& e)
				{
					bOk = true;
					Logger::WriteMessage("\t");
					Logger::WriteMessage(e.what());
					Logger::WriteMessage("\n");
				}
				Assert::IsTrue(bOk, L"Missed exception.");
			}
			Logger::WriteMessage("Ok\n");
		}
	};
}
