//Домашняя работа BIT №6
#include <stdio.h>
#include <math.h>

typedef unsigned long max_int;
//typedef unsigned char integer_t;
//typedef unsigned short integer_t;
typedef unsigned int integer_t;
//typedef unsigned long integer_t;

integer_t Reverse_bite(integer_t n)//меняем местами биты младший бит четвёрки с старшим, 2 сверху со 2 снизу и тд.
{
    integer_t res, buf;
    int i = 0;
    res = 0;
    for (; n != 0; i++)
    {
        buf = n & 0xFF; //оставляем только первый байт (8 бит)
        buf = (buf & 0x55) << 1 | (buf & 0xAA) >> 1; //меняем соседние биты, то есть например 1 бит становиться 2, а 5 -> 6
        buf = (buf & 0x33) << 2 | (buf & 0xCC) >> 2; //меняем соседние пары соседних битов, то еесть 1 бит становиться 4(5 -> 8)
        buf <<= (i * 8);
        res += buf;
        n >>= 8;
    }
    return res;
}

int Size(integer_t x, int system)//вычисляем длинну числа в конкретной СС(второй аргумент в функции)
{
    int i;
    i = 1;
    for (; x / system != 0; i++)
    {
        x /= system;
    }
    return i;
}

void Bin_system(integer_t num, int system)//переводим в другую систему счисления(2 или 16)
{
    integer_t num2;
    int buf, i;
    char arr[50] = { 0 };
    i = 0;
    num2 = num;
    for (i; num / system != 0; i++) //заполняем массив
    {
        buf = num % system;
        arr[i] = buf + '0';
        num /= system;
    }
    arr[i] = num + '0';
    int s;
    s = i;
    for (; i >= 0; i--)//выводим массив
    {
        if ((i + 1) % 8 == 0 && i != s)
        {
            printf(" ");
        }
        printf("%c", arr[i]);
    }
}

int Max(int num1, int num2)//находим максимум среди двух чисел
{
    if (num1 >= num2)
    {
        return num1;
    }
    else
    {
        return num2;
    }
}

void Rank(int max, int s)//выравниваем 2 числа путём записи доп. нулей слева
{
    while (max - s != 0)
    {
        printf("0");
        s++;
    }
}

int main(void)
{
    max_int scanf_num;
    integer_t num, result;
    int s_num10, s_res10, s_num16, s_res16, s_num2, s_res2, max10, max16, max2;
    printf("Enter a number: ");
    scanf_s("%u", &scanf_num);
    num = (integer_t)scanf_num;
    while (num != 0)
    {
        result = Reverse_bite(num);
        s_num10 = Size(num, 10);
        s_res10 = Size(result, 10);
        max10 = Max(s_num10, s_res10);

        s_num16 = Size(num, 16);
        s_res16 = Size(result, 16);
        max16 = Max(s_num16, s_res16);

        s_num2 = Size(num, 2);
        s_res2 = Size(result, 2);
        max2 = Max(s_num2, s_res2);

        while (max2 % 8 != 0)
        {
            max2++;
        }
        printf("You entered: %*d = 0x", max10, num);
        Rank(max16, s_num16);
        printf("%X", num);
        printf(" = ");
        Rank(max2, s_num2);
        Bin_system(num, 2);
        printf("\n");

        printf(" Result is :  %*d = 0x", max10, result);
        Rank(max16, s_res16);
        printf("%X", result);
        printf(" = ");
        Rank(max2, s_res2);
        Bin_system(result, 2);
        printf("\n");

        printf("Enter a number: ");
        scanf_s("%u", &scanf_num);
        num = (integer_t)scanf_num;
    }

    return 0;
}