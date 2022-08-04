#include<stdio.h>
#include<ctype.h>
#include<string.h>
void FillInt(int a[], int size)
{
    int i = 0;
    int j = 0;
    for (; i < size; i++, j += 2)
    {
        a[i] = j + 600;
    }
}

void PrintInt(int a[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        printf("%i ", a[i]);
    }
    printf("\n");
}

void FillDouble(double a[], int size)
{
    int i = 0;
    int j = 0;
    for (; i < size; i++, j += 2)
    {
        a[i] = j + 600.0;
    }

}

void PrintlDouble(double a[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        printf("%lf ", a[i]);
    }
    printf("\n");
}

void MemoryDump(void const* ptr, int size)
{
    int i, q = 0, a;
    for (i = 0; i < size; i++)
    {
        if ((q % 16) == 0)
        {
            printf("\n%p: ", ((unsigned char*)ptr + i));
        }
        printf("%02X ", *((unsigned char*)ptr + i));

        if ((q % 16) == 15)
        {
            printf(" ");
            for (i = (q - 15); i < q; i++)
            {
                if (isprint(*((unsigned char*)ptr + i))) printf(" %c", *((unsigned char*)ptr + i));
                else printf(" .");
            }
        }

        else if (q == (size - 1))
        {
            printf(" ");
            a = q % 16;
            for (i = 0; i < (15 - a); i++) printf(" ");
            for (i = (size - (a + 1)); i < size; i++)
            {
                if (isprint(*((unsigned char*)ptr + i))) printf(" %c", *((unsigned char*)ptr + i));
                else printf(" .");
            }
        }
        q++;
    }
}

int main(void)
{
#pragma warning(disable : 4996)
    int a[9];
    double b[9];
    FillInt(a, 9);
    PrintInt(a, 9);
    FillDouble(b, 9);
    PrintlDouble(b, 9);
    printf("\n");
    MemoryDump(a, sizeof(a));
    printf("\n");
    MemoryDump(b, sizeof(b));
    char s0[10] = "Hello!"; // в конце нули
    char s1[10]; // в конце мусор CC CC CC ...
    char* s2 = malloc(10); // в конце мусор CD CD CD ...
    strcpy(s1, s0);
    strcpy(s2, s0);
    MemoryDump(s0, 10);
    MemoryDump(s1, 10);
    MemoryDump(s2, 10);
    printf_s("\n%s", s0);
    printf_s("\n%s", s1);
    printf_s("\n%s", s2);
    return 0;
}