#include <stdio.h>

// Находим размер массива
int size_of(int digits[], int length)
{
    int size = 0;
    int i = length - 1;
    for (; i >= 0; i--) {
        if (digits[i] != 0) {
            size = i;
            break;

        }
    }
    return size;
}

// Обрабатываеи число и переводим в массив
void Fill(int number, int digits[], int length)
{
    int i = 0;
    for (i; i < length; i++) {
        digits[i] = number % 10;
        number = number / 10;
    }

}

// Печатаем результат
void Print_num(int const digits[], int length, int size, int width)
{
    int i = length - 1;
    for (; i >= 0; i--) {
        if (i <= size) {
            printf("%d", digits[i]);
        }
        else {
            if (width >= i) {
                printf(" ");
            }
        }
    }
    printf("\n");
}

// Складываем массивы
void Add(int const x[], int const y[], int xy[], int length)
{
    int i = 0;
    int buf = 0;
    int back_buf = 0;
    for (; i <= length; i++) {
        if (i == length) {
            xy[i] = back_buf;
            break;
        }
        buf = x[i] + y[i] + back_buf;
        back_buf = buf / 10;
        xy[i] = buf % 10;
    }
}

// Переводим массив с результатом в число
int Collect(int const digits[], int length)
{
    int i = length;
    int buf = 0;
    for (; i >= 0; i--) {
        buf = buf * 10 + digits[i];
    }
    return buf;
}

// Строим черту
void line(int size_of)
{
    int i = 1;
    for (; i <= 11; i++)
    {
        if (size_of + 1 == i)
        {
            while (i > 0)
            {
                printf("-");
                i--;
            }
            printf("\n");
            break;
        }
    }

}


int main(void)
{
    int i = 0;
    int a;
    int b;
    int с;

    int A[10];
    int Size_A;
    int B[10];
    int Size_B;
    int C[11];
    int Size_C;

    printf("Enter first number\n");
    scanf_s("%d", &a);
    printf("Enter second number\n");
    scanf_s("%d", &b);

    Fill(a, A, 10);
    Size_A = size_of(A, 10);
    Fill(b, B, 10);
    Size_B = size_of(B, 10);

    Add(A, B, C, 10);
    Size_C = size_of(C, 11);

    Print_num(A, 10, Size_A, Size_C);
    Print_num(B, 10, Size_B, Size_C);

    line(Size_C);

    Print_num(C, 11, Size_C, Size_C);
    с = Collect(C, Size_C);

    if (с == a + b) {
        printf("YES \n");
    }
    else {
        printf("NO \n");
    }
    return 0;
}