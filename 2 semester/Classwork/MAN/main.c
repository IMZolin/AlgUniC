#include "labengine.h"
#include <math.h>
#include <stdlib.h>
//Параметры для построения правильного многоугольника
struct Poly_t {
    int X; //координата OX центра многоугольника
    int Y; //координата OY центра многоугольника
    int N;
    double angle;// угол
    int R;
    //int C;
}polygon;


int Random(int a, int b);
void DrawMyPoly(struct Poly_t* p);

int main(void)

{
    // Инициализировать библиотеку
    if (LabInit())
    {

        /*// Узнать размеры окна
        int width = LabGetWidth();
        int height = LabGetHeight();
        //Данные и фигуры для Задания №2
        int xc = height / 6; //координата OX центра многоугольника
        int yc = width / 7; //координата OY центра многоугольника
        int num_corners = 0;

        const double PI = 3.14;
        const double RADIUS = height / 2;

        double fi = 0.0;// угол
        double prx = 0.0;//проекция отрезка на ось OX
        double pry = 0.0;//проекция отрезка на ось OY
        */
        /*
        * // Нарисовать красный прямоугольник
        LabSetColor(LABCOLOR_RED);
        LabDrawRectangle(0, 0, width, height);


        //Данные и фигуры для Задания №1
        //Нарисовать светлосерые оси координат
        LabSetColor(LABCOLOR_LIGHT_GREY);
        LabDrawLine(1, height / 2, width - 1, height / 2);//Ось ОХ
        LabDrawLine(width / 2, 1, width / 2, height - 1);//Ось ОY
        // Нарисовать зелёный отрезок
        LabSetColor(LABCOLOR_GREEN);
        LabDrawLine(width/2, height/2, 7*width/8, height/2);

        //Нарисовать синюю окружность
        LabSetColor(LABCOLOR_DARK_CYAN);
        LabDrawCircle(width/2,height/2, RADIUS);
        LabDrawFlush();



        while (!LabInputKeyReady())
        {
        //отрезок в действующем положении
        LabSetColor(LABCOLOR_GREEN);
        LabDrawLine(width / 2, height / 2, width/2 + RADIUS*cos(fi),height/2 + RADIUS * sin(fi));
        prx = width / 2 + RADIUS * cos(fi);
        pry = height / 2 + RADIUS * sin(fi);



        if (fi != 0)
        {
        //Проекции действующего отрезка
        LabSetColor(LABCOLOR_DARK_MAGENTA);
        LabDrawLine(width / 2, height / 2, prx, height / 2);
        LabDrawLine(width / 2, height / 2, width / 2, pry);
        //LabInputKey();
        }

        //Выводим только действующий отрезок
        LabDrawFlush();
        //Очищаем действующий отрезок, с помощью заливки его чёрным цветом
        LabSetColor(LABCOLOR_BLACK);
        LabDrawLine(width / 2, height / 2, width / 2 + RADIUS * cos(fi), height / 2 + RADIUS * sin(fi));
        LabDelay(10);
        if (fi == 0)
        {
        LabSetColor(LABCOLOR_LIGHT_GREY);
        LabDrawLine(width / 2, height / 2, width - 1, height / 2);
        }
        fi -= 0.1;
        }
        */
        int width = LabGetWidth();
        int height = LabGetHeight();

        //Выбираем случайные цвета
        int r_255 = Random(0, 255);
        int g_255 = Random(0, 255);
        int b_255 = Random(0, 255);
        LabSetColorRGB(r_255, g_255, b_255);

        //Структура параметров правильного многоугольника
        struct Poly_t arg;
        arg.X = height / 2;
        arg.Y = width / 2;
        arg.N = 3;
        arg.angle = 0.71;
        arg.R = height / 4;
        //arg.C = (int)LabSetColorRGB;

        DrawMyPoly(&arg);

        // Подождать нажатия клавиши и закончить работу
        LabInputKey();
        LabTerm();
    }
    return 0;
}


/**
* @brief Случайное число из диапазона
* @param a нижняя граница
* @param b верхняя раница
*/

int Random(int a, int b)
{

    return rand() % (b - a + 1) + a;

}


/**
* @brief Рисование многоугольника
* @param xc координата OX центра многоугольника
* @param yc координата OY центра многоугольника
* @param fi первый угол
* @param polyrad радиус
* @param num_corners кол-во углов
*/
void DrawMyPoly(struct Poly_t* p) {
    int width = LabGetWidth();
    int height = LabGetHeight();

    const double PI = 3.14;
    //Нарисовать синюю окружность
    LabSetColor(LABCOLOR_DARK_CYAN);
    LabDrawCircle(p->X, p->Y, p->R);
    LabDrawFlush();

    int x = p->X + p->R * cos(p->angle);
    int y = p->X + p->R * sin(p->angle);
    int x_old = x;
    int y_old = y;
    double delta = 2 * PI / p->N;
    while (LabInputKeyReady() == LAB_FALSE) {
        LabSetColor(LABCOLOR_DARK_CYAN);
        LabDrawCircle(p->X, p->Y, p->R);
        for (int i = 0; i <= p->N; i++) {
            x_old = x;
            y_old = y;
            x = p->X + p->R * cos(p->angle + delta * i);
            y = p->Y + p->R * sin(p->angle + delta * i);
            if (i != 0) {
                LabSetColor(LABCOLOR_GREEN);
                LabDrawLine(x_old, y_old, x, y);
                //LabSetColor(LABCOLOR_LIGHT_GREY);
                //LabDrawLine(p->X, p->Y, x, y);

            }

        }
        LabDelay(100);
        LabDrawFlush();
        p->angle += 0.1;
        LabClear();
    }


}