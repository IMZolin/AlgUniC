#include <stdio.h>
#include "labengine.h"
#include <math.h>
#define MAX_DISTANCE    2.0
#define MAX_ITERATIONS  1023


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

typedef struct {
    unsigned char r, g, b;
} color_t;

static color_t s_palette[] = {
        {0x00, 0x00, 0xFF},
        {0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0xFF, 0x00},
        {0x00, 0xFF, 0xFF},
        {0x00, 0x00, 0xFF},
};

const int MAX_COLORS = sizeof(s_palette) / sizeof(s_palette[0]);

point_t Transform(point_t p, rect_t const* from, rect_t const* to);
void DrawAxes(rect_t const* math, rect_t const* screen);
int IsOutsideJulia(point_t p);
void DrawJulia(rect_t const* math, rect_t const* screen);
int IsOutsideMandelbrot(point_t p);
void DrawMandelbrot(rect_t const* math, rect_t const* screen);
color_t DetermineColor(double n);


/*
*@brief Определение цвета
*@param n
*/
color_t DetermineColor(double n)
{
    double t = n / (MAX_ITERATIONS + 1.0);
    t = t * t * t*(MAX_COLORS - 1.0);
    int k = t;//берётся целая часть от t
    double a = t - k; //берётся дробная часть от t
    color_t color;
    color.r = (1 - a) * s_palette[k].r + a * s_palette[k + 1].r;
    color.g = (1 - a) * s_palette[k].g + a * s_palette[k + 1].g;
    color.b = (1 - a) * s_palette[k].b + a * s_palette[k + 1].b;

    return color;
}

int main()
{
    if (LabInit())
    {
        int width = LabGetWidth();
        int height = LabGetHeight();
        rect_t math = { {-2, 3},{ 2, -3} };
        rect_t math_poq = { -0.7454356, 0.113019, -0.7454215, 0.1129986 };
        rect_t screenL = { 0, 0, width / 2, height };
        rect_t screenR = { width / 2, 0, width, height };
        rect_t screenC = { (double)(width - height), 0, (double)((width - height) + height * 2) / 3, (double)height };

        DrawAxes(&math, &screenL);
        DrawAxes(&math_poq, &screenR);
        DrawJulia(&math, &screenL);
        DrawMandelbrot(&math_poq, &screenR);

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
    point_t screen_o = { 0,0 };
    screen_o = Transform(math_o, math, screen);
    LabSetColor(LABCOLOR_WHITE);
    LabDrawLine(0, (int)screen_o.y, (int)(screen_o.x * 2), (int)screen_o.y);
    LabDrawLine((int)screen_o.x, 0, (int)screen_o.x, (int)(screen_o.y * 2));
}



/*
*@brief Проверка что точка находится в множестве Жюлиа
*@param p Точка
*/
int IsOutsideJulia(point_t p)
{
    point_t c = { -0.835, 0.2321 };
    point_t z = { 0,0 };

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        z.x = p.x * p.x - p.y * p.y + c.x;
        z.y = 2 * p.x * p.y + c.y;

        if ((z.x * z.x) + (z.y * z.y) > MAX_DISTANCE * MAX_DISTANCE)
        {

            return MAX_ITERATIONS - i;

        }
        p.x = z.x;
        p.y = z.y;

    }
    return LAB_FALSE;

}


/*
*@brief Рисование множества Жюлиа
*@param math Математическая СК
*@param screen Экранная СК
*/
void DrawJulia(rect_t const* math, rect_t const* screen)
{
    point_t p = { screen->A.x, screen->A.y };
    point_t pmath = { math->A.x, math->A.x };
    point_t c = { p.x, p.y };
    color_t color = { 0 };
    int n = 0;
    for (; p.x < screen->C.x; p.x++)
    {
        for (p.y = screen->A.y; p.y < screen->C.y; p.y++)
        {
            pmath = Transform(p, screen, math);
            n = IsOutsideJulia(pmath);
            if (n != 0)
            {


                color = DetermineColor(n);
                LabSetColorRGB(color.r, color.g, color.b);
                LabDrawPoint((int)p.x, (int)p.y);


            }

        }
    }
}

/*
*@brief Проверка что точка находится в множестве Мандельброта
*@param p Точка
*/
int IsOutsideMandelbrot(point_t c)
{
    point_t p = { 0,0 };
    point_t z = { 0,0 };

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        z.x = p.x * p.x - p.y * p.y + c.x;
        z.y = 2 * p.x * p.y + c.y;

        if ((z.x * z.x) + (z.y * z.y) > MAX_DISTANCE * MAX_DISTANCE)
        {
            return MAX_ITERATIONS - i;
        }
        p.x = z.x;
        p.y = z.y;
    }
    return LAB_FALSE;

}

/*
*@brief Рисование множества Мандельброта
*@param math Математическая СК
*@param screen Экранная СК
*/
void DrawMandelbrot(rect_t const* math, rect_t const* screen)
{
    point_t p = { screen->A.x, screen->A.y };
    point_t pmath = { math->A.x, math->A.y };
    point_t c = { p.x, p.y };
    int n = 0;
    color_t color = {0};
    for (; p.x < screen->C.x; p.x++)
    {
        for (p.y = screen->A.y; p.y < screen->C.y; p.y++)
        {
            pmath = Transform(p, screen, math);
            c.x = pmath.x;
            c.y = pmath.y;
            n = IsOutsideMandelbrot(pmath);
            color = DetermineColor(n);
            LabSetColorRGB(color.r, color.g, color.b);
            LabDrawPoint((int)p.x, (int)p.y);


        }
    }

}






