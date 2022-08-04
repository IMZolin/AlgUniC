#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include "labengine.h"
/*
* @brief Точка и её координаты
* @param x абцисса точки
* @param y ордината точки
*/
typedef struct {
    int x;
    int y;
} point;

/*
*@brief Кривая-лесенка
*@param A Первая точка
*@param B Вторая точка
*@param C Приближение

*/
void Curve(point A, point B, int n)
{
    if (n == 0)
    {
        point D = { B.x, A.y };
        LabSetColor(LABCOLOR_CYAN);
        LabDrawLine(A.x, A.y, D.x, D.y);
        LabDrawLine(D.x, D.y, B.x, B.y);
    }
    else
    {
        point C = { (A.x + B.x) / 2, (A.y + B.y) / 2 };
        Curve(A, C, n - 1);
        Curve(C, B, n - 1);

    }
}
/*
*@brief  Деление отрезка в данном отношении
*@param A Первая точка
*@param B Вторая точка
*@param q Отношение
*/
point Division_segment(point A, point B, double q)
{
    int x = (int)(A.x + q * B.x) / (1 + q);
    int y = (int)(A.y + q * B.y) / (1 + q);
    point M = { x, y };
    return M;
}

/*
*@brief Кривая Коха
* @param A Первая точка
* @param B Вторая точка
* @param n Приближение
*/
void Koch_curve(point A, point B, int n)
{
    if (n == 0)
    {
        LabSetColor(LABCOLOR_CYAN);
        LabDrawLine(A.x, A.y, B.x, B.y);
    }
    else
    {
        point M1 = Division_segment(A, B, 0.5);
        point M2 = Division_segment(A, B, 2);

        int X = (A.x + B.x) / 2 - (A.y - B.y) / (int)(2 * sqrt(3));
        int Y = (A.y + B.y) / 2 - (B.x - A.x) / (int)(2 * sqrt(3));
        point C = { X,Y };

        Koch_curve(A, M1, n - 1);
        Koch_curve(M1, C, n - 1);
        Koch_curve(C, M2, n - 1);
        Koch_curve(M2, B, n - 1);

    }
}
/*
*@brief Интерактивная кривая Коха
*
*/
void Lab_Koch_curve(void)
{
    int a = LabGetWidth() - 10;
    int b = LabGetHeight() - 10;
    point A = { 10, 10 };
    point B = { a, b };
    int n = 0;

    Koch_curve(A, B, n);

    LabDrawFlush();

    while (1)
    {
        char c = _getch();
        switch (c)
        {
            case '+':
                n++;
                LabClear();
                Koch_curve(A, B, n);
                LabDrawFlush();
                break;
            case '-':
                if (n == 0)
                {
                    break;
                }
                else
                {
                    n--;
                }

                LabClear();
                Koch_curve(A, B, n);
                LabDrawFlush();
                break;
            case 27:
                exit(0);
            default:
                continue;
        }

    }

    LabClear();
    LabDrawFlush();
    LabInputKey();
}


void Lab_curve(void)
{
    int a = LabGetWidth() - 10;
    int b = LabGetHeight() - 10;
    point A = { 10, 10 };
    point B = { a, b };
    int n = 2;

    Curve(A, B, n);
    LabDrawFlush();
    while (1)
    {
        char c = _getch();
        switch (c)
        {
            case '+':
                n++;
                LabClear();
                Curve(A, B, n);
                LabDrawFlush();
                break;

            case '-':
                if (n == 0)
                {
                    break;
                }
                else
                {
                    n--;
                }

                LabClear();
                Curve(A, B, n);
                LabDrawFlush();
                break;
            case 27:
                exit(0);
        }

    }

    LabClear();
    LabDrawFlush();
    LabInputKey();
}

int main(void)
{

    if (LabInit())
    {
        int a = LabGetWidth() - 10;
        int b = LabGetHeight() - 10;
        point A = { 10, 10 };
        point B = { a, b };
        int n = 3;
        //Lab_Koch_curve();
        //Lab_curve();
        Koch_curve(A, B, n);
        //Curve(A, B, n);
        LabInputKey();
        LabTerm();
    }

    return 0;
}
