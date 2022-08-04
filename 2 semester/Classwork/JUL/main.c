#include "labengine.h"
#include <stdio.h>

#include <math.h>
#define PI 3.14
typedef struct
{
    float x;
    float y;
}point_t;
typedef struct
{
    point_t A;
    point_t C;
}rect_t;
point_t Transform(point_t p, rect_t const* from, rect_t const* to)
{
    point_t t;
    t.x = (p.x - from->A.x) * (to->C.x - to->A.x) / (from->C.x - from->A.x) + to->A.x;
    t.y = (p.y - from->A.y) * (to->C.y - to->A.y) / (from->C.y - from->A.y) + to->A.y;
    return t;
}
void DrawAxes2(rect_t const* math, rect_t const* screen)
{
    int width = LabGetWidth();
    int height = LabGetHeight();
    point_t o = { 0,0 };
    point_t O = { 0,0 };
    O = Transform(o, math, screen);
    LabSetColor(LABCOLOR_LIGHT_GREY);
    LabDrawLine(0, (int)O.y, (int)(O.x * 2), (int)O.y);
    LabDrawLine((int)O.x, 0, (int)O.x, (int)(O.y * 2));
}
labbool_t IsInsideDisk(point_t p)
{
    if ((p.x * p.x + p.y * p.y) <= 1)
        return LAB_TRUE;
    return LAB_FALSE;
}
void DrawDisk2(rect_t const* math, rect_t const* screen)
{
    point_t p = { 0,0 };
    point_t pmath = { 0,0 };
    int tmp = 0;
    for (p.x = 0; p.x < screen->C.x; p.x++)
    {
        for (p.y = 0; p.y < screen->C.y; p.y++)
        {
            pmath = Transform(p, screen, math);
            if (IsInsideDisk(pmath))
            {
                LabSetColor(LABCOLOR_GREEN);
                LabDrawPoint((int)p.x, (int)p.y);
            }
        }
    }
}

int main()
{
    if (LabInit())
    {
        int width = LabGetWidth();
        int height = LabGetHeight();
        rect_t mathrec = { -2, 3, 2, -3 };
        rect_t screenrec = { 0, 0, width / 2, height };
        rect_t screenrec2 = { width / 2, 0, width, height };
        rect_t screenrec3 = { (width - height), 0, (width - height) + height * 2 / 3, height };
        DrawAxes2(&mathrec, &screenrec);
        DrawAxes2(&mathrec, &screenrec2);
        DrawDisk2(&mathrec, &screenrec);
        //DrawJulia(&mathrec, &screenrec2);
        //DrawJulia2(&mathrec, &screenrec3);
        LabDrawFlush();
        LabInputKey();
        LabTerm();
    }
    return 0;
}