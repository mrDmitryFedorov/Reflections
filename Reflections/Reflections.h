#pragma once
#include <vector>
struct Point
{
    double x;
    double z;
};

/// <summary>
/// Вычисляет координаты точек переотражений в цилиндре радиуса R и толщиной стенки S для угла падения A.
/// При некорректных параметрах вызывает исключение invalid_argument.
/// </summary>
/// <param name="v">Ссылка на массив точек с координатами x,z.</param>
/// <param name="fR">Радиус цилиндра</param>
/// <param name="fS">Толщина стенки</param>
/// <param name="fA">Угол луча</param>
void Reflections(std::vector<Point>& v, double fR, double fS, double fA);
