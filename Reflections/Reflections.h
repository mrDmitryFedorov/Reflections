#pragma once
#include <vector>
struct Point
{
    double x;
    double z;
};

/// <summary>
/// ��������� ���������� ����� ������������� � �������� ������� R � �������� ������ S ��� ���� ������� A.
/// ��� ������������ ���������� �������� ���������� invalid_argument.
/// </summary>
/// <param name="v">������ �� ������ ����� � ������������ x,z.</param>
/// <param name="fR">������ ��������</param>
/// <param name="fS">������� ������</param>
/// <param name="fA">���� ����</param>
void Reflections(std::vector<Point>& v, double fR, double fS, double fA);
