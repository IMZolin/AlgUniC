#include<stdio.h>
#include <stdlib.h>

typedef int binary_op_t(int sk, int ak);
int Random(int a, int b);//Генерируем рандомные числа
void FillRandom(int arr[], int size, int a, int b);//Записываем рандомное число в массив
void Print(int const arr[], int size);//Выводим массив
int BinarySum(int sk, int ak);
int BinaryMax(int sk, int ak);
int BinaryNeg(int sk, int ak);
int Accumulate(int const a[], int n, int s0, binary_op_t* op);

int main(void)
{
    int n = 0;
    int a = -10;
    int b = 10;
    int s0 = 0;
    int sum = 0;
    int max = 0;
    int negc = 0;
    Random(a, b);
    printf("Enter size of massive:\n");
    scanf_s("%d", &n);
    int* massive = (int*)malloc(n * sizeof(int));
    FillRandom(massive, n, a, b);
    Print(massive, n);
    sum = Accumulate(massive, n, s0, BinarySum);
    printf("This is sum of numbers this massive = %d\n", sum);
    s0 = -32768;
    max = Accumulate(massive, n, s0, BinaryMax);
    printf("This is maximum of numbers this massive = %d\n", max);
    s0 = 0;
    negc = Accumulate(massive, n, s0, BinaryNeg);
    printf("This is number of negative numbers = %d\n", negc);
    free(massive);
    return 0;
}

int Random(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

void FillRandom(int arr[], int size, int a, int b)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = Random(a, b);
    }
}

void Print(int const arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int BinarySum(int sk, int ak)//sk-переменная-накопитель, ak-очередной элемент массива/ возвращает сумму элементов массива
{
    return sk + ak;
}
int BinaryMax(int sk, int ak)//sk-переменная-накопитель, ak-очередной элемент массива/ возвращает максимальное число
{
    if (ak > sk)
    {
        sk = ak;
    }

    return sk;
}
int BinaryNeg(int sk, int ak)//sk-переменная-накопитель, ak-очередной элемент массива/ возвращает колличество отрицательных чисел
{

    if (ak < 0)
    {
        sk += 1;
    }

    return sk;
}
int Accumulate(int const a[], int n, int s0, binary_op_t* op)
{
    int i = 0;
    for (; i < n; i++)
    {
        s0 = op(s0,a[i]);
    }
    return s0;
}
