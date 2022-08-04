// LIB_Z_HW.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "frac.h"




/*#define const rational_t NaN { 0,0 }
#define const rational_t ZERO { 0,1 }*/

int NOD(int a, int b) {

    int nod = 1;
    if ((a < 0) || (b < 0))
    {
        a = abs(a);
        b = abs(b);
    }
    while (a != b)
    {
        if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    nod = b;
    return nod;
}

int NOK(int a, int b)
{
    int nok = 1;
    int nod = 1;
    nod = NOD(a, b);
    nok = a * b / nod;
    return nok;
}
rational_t CreateSimplify(rational_t frac)
{
    if (frac.den != 0)
    {
        int n = 1;
        rational_t copyfrac;
        copyfrac = frac;
        if (frac.num == 0)
            return ZERO;
        n = NOD(copyfrac.num, copyfrac.den);
        frac.num = frac.num / n;
        frac.den = frac.den / n;
        if (frac.den < 0)
        {
            frac.num = -frac.num;
            frac.den = -frac.den;
        }
        return frac;
    }
    else
    {
        fprintf(stderr, "NaN.DIVISION BY ZERO\n");
        return NaN;
    }

}






rational_t FromDouble(double doublefrac)
{
    rational_t frac;
    int i = 1;
    double epsilon = 0.0000001;
    while (fabs(i * doublefrac - round(i * doublefrac)) > epsilon)
    {
        i++;
    }
    frac.den = i;
    frac.num = round(i * doublefrac);
    return frac;
}

double AsDouble(rational_t frac)
{
    double doublefrac = 0;
    if (frac.den != 0)
    {
        doublefrac = (double)(frac.num) / frac.den;
        return doublefrac;
    }
    else
        printf("ENTER THE CORRECT DENOMINATOR\n");
    //return NAN;
}

int AsInt(rational_t frac)
{
    int intfrac = 0;
    if (frac.den != 0)
    {
        intfrac = frac.num / frac.den;
        return intfrac;
    }
    else
        printf("ENTER THE CORRECT DENOMINATOR\n");
}

rational_t Parse(char* str)
{
    int n;
    rational_t frac;
    n = sscanf(str, "%d\\%d", &frac.num, &frac.den);
    if ((n == 2) && (frac.den != 0))
    {

        return CreateSimplify(frac);
    }
    else
    {
        fprintf(stderr, "INVALID INPUT OR DENOMINATOR == 0\n");
    }
}

char* Format(rational_t frac)
{
    rational_t outputfrac = CreateSimplify(frac);
    rational_t copyfrac = outputfrac;
    int n = 0;
    int dn = 0;
    if (frac.den != 0)
    {
        while (copyfrac.num != 0)
        {
            copyfrac.num /= 10;
            n++;
        }
        while (copyfrac.den != 0)
        {
            copyfrac.den /= 10;
            dn++;
        }
        //printf("%d %d ", n, dn);

        char* str = malloc((1 + n + dn) * sizeof(char));
        sprintf(str, "%d\\%d", outputfrac.num, outputfrac.den);
        return str;
    }
}

rational_t Read(FILE* f)
{
    if (!f)
    {
        printf("FILE WAS NOT OPENED");
        return ZERO;
    }
    rational_t frac;
    rational_t outputfrac;
    int n = 0;
    //char str[4];
    n = fscanf(f, "%d\\%d", &(frac.num), &(frac.den));
    outputfrac = CreateSimplify(frac);
    return outputfrac;
}

void Write(rational_t frac, FILE* f)
{
    rational_t outputfrac = CreateSimplify(frac);
    if (!f)
    {
        printf("FILE WAS NOT OPENED");
        exit(1);
    }
    fprintf(f, "%d\\%d", outputfrac.num, outputfrac.den);
}
rational_t Add(rational_t frac1, rational_t frac2)
{
    if ((frac1.den == 0) || (frac2.den == 0))
    {
        printf("THERE`S 0 DENUM.\n");
        return NaN;
    }
    rational_t frac3 = ZERO;
    frac3.num = frac1.num * frac2.den + frac2.num * frac1.den;
    frac3.den = frac1.den * frac2.den;

    frac3 = CreateSimplify(frac3);
    return frac3;
}
rational_t Sub(rational_t frac1, rational_t frac2)
{
    if ((frac1.den == 0) || (frac2.den == 0))
    {
        printf("THERE`S 0 DENUM.\n");
        return NaN;
    }
    rational_t frac3 = ZERO;
    frac3.num = frac1.num * frac2.den - frac2.num * frac1.den;
    frac3.den = frac1.den * frac2.den;
    frac3 = CreateSimplify(frac3);
    return frac3;
}
rational_t Mul(rational_t frac1, rational_t frac2)
{
    if ((frac1.den == 0) || (frac2.den == 0))
    {
        printf("THERE`S 0 DENUM.\n");
        return NaN;
    }
    rational_t frac3 = ZERO;
    frac3.num = frac1.num * frac2.num;
    frac3.den = frac1.den * frac2.den;
    frac3 = CreateSimplify(frac3);
    return frac3;
}
rational_t Div(rational_t frac1, rational_t frac2)
{
    if ((frac1.den == 0) || (frac2.den == 0))
    {
        printf("THERE`S 0 DENUM.\n ");
        return NaN;
    }
    rational_t frac3;
    frac3.num = frac1.num * frac2.den;
    frac3.den = frac1.den * frac2.num;
    frac3 = CreateSimplify(frac3);
    return frac3;
}
rational_t Negate(rational_t frac)
{
    if (frac.den == 0)
    {
        printf("THERE`S 0 DENUM.\n ");
        return NaN;
    }
    rational_t nfrac = frac;
    nfrac.num = -frac.num;
    nfrac.den = frac.den;
    frac = CreateSimplify(nfrac);
    return frac;
}
rational_t Rec(rational_t frac)
{
    if (frac.den == 0)
    {
        printf("THERE`S 0 DENUM.\n ");
        return NaN;
    }
    int buf = frac.num;
    rational_t rfrac;
    rfrac.num = frac.den;
    rfrac.den = buf;
    frac = CreateSimplify(rfrac);
    return frac;
}
rational_t Abs(rational_t frac)
{
    if (frac.den == 0)
    {
        printf("THERE`S 0 DENUM.\n ");
        return NaN;
    }
    rational_t afrac = ZERO;
    afrac.num = abs(frac.num);
    afrac.den = abs(frac.den);
    frac = CreateSimplify(afrac);
    return frac;
}

int Floor(rational_t frac)
{
    if (frac.den == 0)
    {
        printf("THERE`S 0 DENUM.\n ");
        exit(1);
    }
    int floor_result = frac.num / frac.den;
    return floor_result;
}
int Ceil(rational_t frac)
{
    if (frac.den == 0)
    {
        printf("THERE`S 0 DENUM.\n ");
        exit(2);
    }
    if (frac.num * frac.den < 0)
    {
        frac.num = -frac.num;
        return -(Floor(frac));
    }
    int ceil_result = !!(frac.num % frac.den) + frac.num / frac.den;
    return ceil_result;
}



/*
*@brief Округление (математическая версия)
*@param x дробно-рациональная дробь
*/
int Round(rational_t frac)
{
    if (frac.den == 0)
    {
        printf("THERE`S 0 DENUM.\n ");
        exit(3);
    }
    int round_result = 0;
    if (2 * (frac.num % frac.den) / frac.den)
        return Ceil(frac);

    else
        return Floor(frac);
}



void Compare(rational_t frac1, rational_t frac2)
{
    rational_t copyfrac1 = CreateSimplify(frac1);
    rational_t copyfrac2 = CreateSimplify(frac2);
    int nok = 0;
    int nod = 0;
    if ((frac1.den == 0) || (frac2.den == 0))
    {
        exit(4);
    }
    nod = NOD(frac1.den, frac2.den);
    nok = NOK(frac1.den, frac2.den);
    int m1 = frac2.den / nod;
    int m2 = frac1.den / nod;
    frac1.den = nok;
    frac2.den = nok;
    frac1.num = frac1.num * m1;
    frac2.num = frac2.num * m2;
    if (frac1.num > frac2.num)
    {
        printf("%d\\%d > %d\\%d", copyfrac1.num, copyfrac1.den, copyfrac2.num, copyfrac2.den);
    }
    if (frac1.num < frac2.num)
    {
        printf("%d\\%d < %d\\%d", copyfrac1.num, copyfrac1.den, copyfrac2.num, copyfrac2.den);
    }
    if (frac1.num == frac2.num)
    {
        printf("%d\\%d = %d\\%d", copyfrac1.num, copyfrac1.den, copyfrac2.num, copyfrac2.den);
    }

}





