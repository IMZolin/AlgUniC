//
// Created by zolin on 04.08.2022.
//

#ifndef LIB_FRAC_H
#define LIB_FRAC_H
#pragma once

#define WIN32_LEAN_AND_MEAN
// Исключите редко используемые компоненты из заголовков Windows
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
/*
*@pragma тип «несократимая рациональная дробь»
*@param num числитель
*@param den знаменатель
*/
typedef struct
{
    int num;
    int den;
}rational_t;

/** @brief Константа NaN
*	Константа "результат деления на ноль"
*/
extern const __declspec(selectany) rational_t NaN = { 0,0 };
/** @brief ZERO
*	Константа "ноль"
*/
extern const __declspec(selectany) rational_t ZERO = { 0,1 };

/*
*@brief NOD
*Поиск НОД при помощи алгоритма Евклида. Возвращает НОД.
*@param a Первое число
*@param b Второе число
*/
int NOD(int a, int b);
/** @brief NOK
*Поиск НОК при помощи алгоритма Евклида. Возвращает НОК.
*@param a Первое число
*@param b Второе число
*/
int NOK(int a, int b);

/*@brief Create_simplify
*Создает и сразу упрощает дробь при помощи алгоритма Евклида.
*Возвращает дробь.
*@param frac Дробь
*/
rational_t CreateSimplify(rational_t frac);

/** @brief FromDouble
*Переводит из формата double в rational_t.
*Возвращает дробь типа rational_t
*@param dec_frac Десятичное число типа double
*/
rational_t FromDouble(double dec_frac);

/*
*@brief AsDouble
*Перевод рациональной дроби в десятичную типа double
*@param frac Дробь
*/
double AsDouble(rational_t frac);

/*
*@brief AsInt
*Перевод рациональной дроби в целое число тпа int
*@param frac Дробь
*/
int AsInt(rational_t frac);

/** @brief Parse
*Создание  по  строке дробь из формата char* str в rational_t.Записывается с помощью sprintf.
*@param str */
rational_t Parse(char* str);

/** @brief Format
*Записывает дробь из формата rational_t в char* str. Записывается с помощью sscanf.
*@param frac Дробь
*/
char* Format(rational_t frac);

/** @brief Read
*Считывает из потока FILE* информацию о дроби в формате "a\b".
*@param f Поток(файл)
*/
rational_t Read(FILE* f);

/** @brief Write
*Записывает в поток FILE* дробь формата rational.t.
*@param frac Дробь
*@param f Поток(файл)
*/
void Write(rational_t frac, FILE* f);

/** @brief Add
*Складывает две дроби путем арифметического сложения двух дробей. Возвращает дробь.
*@param 1-ая дробь
*@param 2-ая дробь
*/
rational_t Add(rational_t frac1, rational_t frac2);

/** @brief Sub
*Вычитает две дроби путем арифметического вычитания двух дробей. Возвращает дробь.
*@param 1-ая дробь
*@param 2-ая дробь
*/
rational_t Sub(rational_t frac1, rational_t frac2);

/** @brief Mul
*Умножает две дроби путем арифметического умножения двух дробей. Возвращает дробь.
*@param 1-ая дробь
*@param 2-ая дробь
	*/
rational_t Mul(rational_t frac1, rational_t frac2);

/** @brief Div
*Делит одну дробь на другую путем "переворачивания" второй дроби. Возвращает дробь.
*@param 1-ая дробь
*@param 2-ая дробь*/
rational_t Div(rational_t frac1, rational_t frac2);

/** @brief Negate
*Меняет знак у дроби. Возвращает дробь.
*@param Дробь	*/
rational_t Negate(rational_t frac);

/**	@brief Rec
*Переворачивает дробь с использованием буфера. Возвращает дробь.
*@param Дробь*/
rational_t Rec(rational_t frac);

/** @brief Abs
*Возвращает модуль введённой дроби.
*@param Дробь*/
rational_t Abs(rational_t frac);

/** @brief Floor
*Округление вниз до целого. Возвращает округленное значение.
*@param frac Дробь*/
int Floor(rational_t frac);

/** @brief Ceil
*Округление вверх до целого. Возвращает округленное значение.
*@param frac Дробь*/
int Ceil(rational_t frac);

/** @brief Round
*Округление по правилам математики. Возвращает округленное значение.
*@param frac Дробь*/
int Round(rational_t frac);

/** @brief Compare
*Сравнивает и упрощает две дроби. Выводит неравенство (или равенство) для двух дробей.
*@param frac Дробь*/
void Compare(rational_t frac1, rational_t frac2);


#endif //LIB_FRAC_H
