#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LENGTH 10
#define SYMBOLS 16

int Size_of(int number);//вычисляем длинну числа
double Random(double a, double b);//находим случайное число в диапазоне (a,b)
void FillRandom(double arr[], int size, double a, double b);//заполняем массив
void Print(double const arr[], int size);//выводим массив
void BuildHistogram(double const arr[], int size, double left, double right, int counters[], int num_counters);//заполняем массив-счётчик counters
void PrintHistogram(int counters[], int num_counters);//выводим массив-счётчик counters
void DrawHistogram(int counters[], int numCounters, int width);//рисуем диаграмму
//void DrawHistogramV(int counters[], int numCounters, int width);//переворачиваем вертикально диаграмму

int main(void)
{
    double a;
    double b;
    int n = 0;
    int numCounters = 0;//колличество подинтервалов
    printf("Enter your left border: ");
    scanf_s("%lf", &a);
    printf("Enter your right border: ");
    scanf_s("%lf", &b);
    printf("How many numbers do you want to generate: ");
    scanf_s("%d", &n);
    printf("Enter your number of interval: ");
    scanf_s("%d", &numCounters);
    double* massiv = (double*)malloc(n * sizeof(double));//создаём массив с выделенной под него памятью размером n*sizeof(double), с помощью malloc
    FillRandom(massiv, n, a, b);
    Print(massiv, n);//выводим массив
    int* counters = (int*)calloc(numCounters, sizeof(int));//создаём массив-счётчик с выделенной под него памятью размером numCounters*sizeof(int),забивая нулями память, с помощью calloc
    FillRandom(massiv, n, a, b);
    BuildHistogram(massiv, n, a, b, counters, numCounters);
    free(massiv);
    PrintHistogram(counters, numCounters);
    printf("\n");
    DrawHistogram(counters, numCounters, SYMBOLS);
    printf("\n");
    free(counters);//освобождаем память
    return 0;
}



double Random(double a, double b)
{
    double number = rand();
    return number / ((double)RAND_MAX + 1) * (b - a) + a;
}

void FillRandom(double arr[], int size, double a, double b)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = Random(a, b);
    }
}

void Print(double const arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}

void BuildHistogram(double const arr[], int size, double left, double right, int counters[], int num_counters)//заполняем массив-счётчик counters
{
    int buf = 0;
    for (int i = 0; i < size; i++)
    {
        buf = (int)((arr[i] - left) / (right - left) * num_counters); //buf - номер в массиве - число в подинтервале
        counters[buf] += 1;
    }
}

void PrintHistogram(int counters[], int num_counters)//выводим массив-счётчик counters
{
    for (int i = 0; i < num_counters; i++)
    {
        printf("%d ", counters[i]);
    }
    printf("\n");
}

int Max(int massiv[], int size)//вычисляем максимальный элемент
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (massiv[i] > max)
        {
            max = massiv[i];
        }
    }
    return max;
}

void DrawHistogram(int counters[], int numCounters, int width)
{
    int buf = 0;
    int max = Max(counters, numCounters);//находим максимум
    for (int i = 0; i < numCounters; i++)
    {
        if (counters[i] == max)//если мы находим max, то отдаём ему width
        {
            buf = width;
        }
        else
        {
            buf = (int)(width / max * counters[i]);//если элемент не max, то выделяем под него строку, длинна которой
            //пропорциональна колличеству элементам, относительно max
        }
        printf("%d ", i);
        for (int j = 0; j < buf; j++)
        {
            printf("o");
        }
        for (int j = 0; j < width - buf; j++)
        {
            printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

