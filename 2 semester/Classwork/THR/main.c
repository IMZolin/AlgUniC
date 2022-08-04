#include <stdio.h>
#include "labengine.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>


/*
* @brief Точка и её координаты
* @param x абцисса точки
* @param y ордината точки
*/
typedef struct
{
    double x;
    double y;
}point_t;

/*
*@brief Параметры системы координат(прямоугольника, области координат)
*@param x1
*@param x2
*@param y1
*@param y2
*/
typedef struct
{
    point_t A;
    point_t C;
}rect_t;

/*
*@brief Параметры задания вектора
*@param A Проекция на ось ОХ
*@param B Проекция на ось ОУ
*/
typedef struct {
    double x;
    double y;
} vec_t;

point_t Transform(point_t p, rect_t const* from, rect_t const* to);
void DrawAxes(rect_t const* math, rect_t const* screen);
void DrawAnalyticalPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0, double dt);
void DrawEulerPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0, double dt);
void SimulateEulerPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0);
int main(void)
{
    if (LabInit())
    {
        int width = LabGetWidth();
        int height = LabGetHeight();
        double alfa = M_PI / 3;
        double absV0 = 20;
        double dt1 = 1;
        double dt2 = 0.5;
        vec_t v0 = { absV0*cos(alfa),absV0 * sin(alfa) };
        vec_t a0 = {0, -9.8};
        vec_t r0 = { 0, 0 };

        rect_t world = { {-3,28}, {41,-5} };
        rect_t screen = { {0, 0}, {width, height} };

        DrawAxes(&world, &screen);
        DrawAnalyticalPath(&world, &screen, r0, v0, a0, dt1);
        DrawAnalyticalPath(&world, &screen, r0, v0, a0, dt2);
        DrawEulerPath(&world, &screen, r0, v0, a0, dt1);
        DrawEulerPath(&world, &screen, r0, v0, a0, dt2);
        SimulateEulerPath(&world, &screen, r0, v0, a0);
        LabDrawFlush();
        LabInputKey();
        LabTerm();
    }
    return 0;
}

/*
*@brief Преобразование координаты точки из одной произвольной прямоугольной области в другую
*@param p Точка с координатами в математической СК
*@param from Ск, из которой мы переводим (математическая СК)
*@param to СК, в которую мы переводим (экранная СК)
*/
point_t Transform(point_t p, rect_t const* from, rect_t const* to)
{
    point_t q;
    q.x = (p.x - from->A.x) * (to->C.x - to->A.x) / (from->C.x - from->A.x) + to->A.x;
    q.y = (p.y - from->A.y) * (to->C.y - to->A.y) / (from->C.y - from->A.y) + to->A.y;
    return q;
}

/*
*@brief Рисование осей координат
*@param math Математическая СК
*@param screen Экранная СК
*/
void DrawAxes(rect_t const* math, rect_t const* screen)
{
    int width = LabGetWidth();
    int height = LabGetHeight();
    point_t math_o = { 0,0 };
    point_t screen_o = { 0, 0 };
    screen_o = Transform(math_o, math, screen);
    LabSetColor(LABCOLOR_WHITE);
    LabDrawLine(0, (int)screen_o.y, width, (int)screen_o.y);
    LabDrawLine((int)screen_o.x, 0, (int)screen_o.x, height);
}

/*
*@brief Рисование аналитической(идеальной) траектории движения
*@param math Математическая СК
*@param screen Экранная СК
*@param r0 Начальное положение
*@param v0 Начальная скорость
*@param a0 Начальное ускорние
*@param dt Интервал измениея времени
*/
void DrawAnalyticalPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0, double dt)
{
    vec_t r = r0;
    double tmax = 2*v0.y/fabs(a0.y);
    point_t r_m;
    point_t r_m0;
    point_t r_s;
    point_t r_s0;
    r_m0.x = r0.x;
    r_m0.y = r0.y;
    for (double t = 0; t < tmax; t += dt)
    {
        r.x = r0.x + v0.x * t + 0.5*a0.x * t * t;
        r.y = r0.y + v0.y * t + 0.5*a0.y * t * t;
        r_m.x = r.x;
        r_m.y = r.y;
        r_s = Transform(r_m, math, screen);
        r_s0 = Transform(r_m0, math, screen);
        LabSetColor(LABCOLOR_GREEN);
        LabDrawLine((int)r_s0.x,(int)r_s0.y, (int)r_s.x, (int)r_s.y);
        r_m0.x = r_m.x;
        r_m0.y = r_m.y;
    }
}

/*
*@brief Рисование "реальной" траектории движения методом Эйлера
*@param math Математическая СК
*@param screen Экранная СК
*@param r0 Начальное положение
*@param v0 Начальная скорость
*@param a0 Начальное ускорние
*@param dt Интервал измениея времени
*/
void DrawEulerPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0, double dt)
{
    vec_t r = r0;
    vec_t rk = r0;
    point_t r_m;
    point_t r_m0;
    point_t r_s;
    point_t r_s0;
    vec_t v = v0;
    vec_t dv;
    r_m.x = rk.x;
    r_m.y = rk.y;
    while(1)
    {
        rk.x = r.x;
        rk.y = r.y;

        r.x = rk.x + v.x * dt;
        r.y = rk.y + v.y * dt;

        dv.x = a0.x * dt;
        dv.y = a0.y * dt;
        v.x += dv.x;
        v.y += dv.y;

        r_m.x = r.x;
        r_m.y = r.y;
        r_m0.x = rk.x;
        r_m0.y = rk.y;

        r_s = Transform(r_m, math, screen);
        r_s0 = Transform(r_m0, math, screen);
        if (r_m.y < r0.y)
        {
            break;
        }
        LabSetColor(LABCOLOR_RED);
        LabDrawLine((int)r_s0.x, (int)r_s0.y, (int)r_s.x, (int)r_s.y);
    }
}

/*
*@brief Рисование траектории в реальном времени
*@param math Математическая СК
*@param screen Экранная СК
*@param r0 Начальное положение
*@param v0 Начальная скорость
*@param a0 Начальное ускорние
*/
void SimulateEulerPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0)
{
    vec_t r = r0;
    vec_t rk = r0;
    point_t r_m;
    point_t r_m0;
    point_t r_s;
    point_t r_s0;
    vec_t v = v0;
    vec_t dv;
    double dt;
    double b_time;
    LARGE_INTEGER counter, frequency;
    r_m.x = rk.x;
    r_m.y = rk.y;

    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);

    b_time = (double)counter.QuadPart;
    while (1)
    {
        dt = (double)((double)counter.QuadPart - b_time) /(double) frequency.QuadPart;
        b_time = (double)counter.QuadPart;
        rk.x = r.x;
        rk.y = r.y;

        r.x = rk.x + v.x * dt;
        r.y = rk.y + v.y * dt;

        dv.x = a0.x * dt;
        dv.y = a0.y * dt;
        v.x += dv.x;
        v.y += dv.y;

        r_m.x = r.x;
        r_m.y = r.y;
        r_m0.x = rk.x;
        r_m0.y = rk.y;

        r_s = Transform(r_m, math, screen);
        r_s0 = Transform(r_m0, math, screen);
        if (r_m.y < r0.y)
        {
            break;
        }
        LabSetColor(LABCOLOR_YELLOW);
        LabDrawLine((int)r_s0.x, (int)r_s0.y, (int)r_s.x, (int)r_s.y);
        QueryPerformanceCounter(&counter);
    }
}