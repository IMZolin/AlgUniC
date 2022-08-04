#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LENGTH 9

int Size_of(int number);  //определяем длинну числа
float Random(float a, float b);  //находим случайное целые числа в диапазоне (a,b) и представляем их в вещественные
void FillFloats(float arr[], int size, const float a, const float b);  //возвращаем результат из Random, записываем в массив
void PrintFloats(float const arr[], int size);  //выводим массив с вещественными числами с 2 знаками после точки, в фигурных скобках
void WriteText(char const* filename, float arr[], int length);  //открываем файл (.txt) и записываем туда наш массив
void WriteBinary(char const* filename, float arr[], int length);
float* ReadText(char const* filename, int* length);
float* ReadBinary(char const* filename, int* length);
void FileDump(char const* filename);

int main(void)
{
	int size = 0;
	const float a = 0;
	const float b = 100;
	float arr[LENGTH];
	FillFloats(arr, LENGTH, a, b);
	PrintFloats(arr, LENGTH);
	WriteText("array.txt", arr, LENGTH);
	WriteBinary("array.bin", arr, LENGTH);
	PrintFloats(ReadText("array.txt", &size), LENGTH);
	PrintFloats(ReadBinary("array.bin", &size), LENGTH);
	FileDump("array.txt");
	FileDump("array.bin");
	return 0;
}

int Size_of(int number)
{
	int size = 1;
	while (number / 10 != 0)
	{
		size++;
		number /= 10;
	}
	return size;
}

float Random(float a, float b)
{
	float result;
	int num = rand();
	result = (float)((num / pow(10, Size_of(num))) * ((double)b - a) + a);
	return result - (result - (int)result);
}

void FillFloats(float arr[], int size, const float a, const float b)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = Random(a, b);
	}
}

void PrintFloats(float const arr[], int size)
{
	printf("{");
	for (int i = 0; i < size; i++)
	{
		if (i == size - 1)
		{
			printf("%.2f}\n", arr[i]);
			break;
		}
		printf("%.2f, ", arr[i]);
	}
}

void WriteText(char const* filename, float arr[], int length)
{
	FILE* file = fopen(filename, "w");	 //открываем файл (.txt) для записи
	if (file == NULL)					//если файл пустой, мы пишем об ошибке
	{
		printf("Error...\n");
		return;
	}
	for (int i = 0; i < LENGTH; i++)  //записываем тот же массив в файл
	{
		fprintf(file, "%.1f ", arr[i]);
	}
	fclose(file);  //закрываем файл
}

void WriteBinary(char const* filename, float arr[], int length)
{
	FILE* file = fopen(filename, "wb");  //открываем файл (.bin)
	if (file == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	fwrite(arr, sizeof(float), LENGTH, file);
	fclose(file);
}

float* ReadText(char const* filename, int* length)
{
	float* tmp = (float*)malloc(sizeof(float));						//создаём массив tmp с выделенной под него памятью размером sizeof(float), с помощью malloc
	float* arr = (float*)malloc(sizeof(float));
	FILE* file = fopen(filename, "r");							  //открываем файл (.txt) для чтения
	int i = 0;
	for (; fscanf(file, "%f", arr + i) != EOF; i++)				//считываем файл с помощью fscanf
	{
		tmp = (float*)realloc(arr, (2 + i) * sizeof(float));  //изменяем выделенную память в (2 + i) раз, с помощью realloc
		if (tmp)
		{
			arr = tmp;
		}
		else
		{
			printf("You've made something wrong!\n");
			exit(1);
		}
	}
	*length = i;
	fclose(file);
	return arr;
}

float* ReadBinary(char const* filename, int* length)
{
	FILE* file = fopen(filename, "rb");                   //открываем файл (.bin) для чтения
	if (file == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	int size;
	float* arr;
	fseek(file, 0, SEEK_END);                            //измеряем размер
	size = ftell(file);									//ftell(file) возвращает текущее положение указателя в файле
	fseek(file, 0, SEEK_SET);
	arr = malloc(size);
	fread(arr, sizeof(float), size, file);
	*length = size;
	return arr;
}

void FileDump(char const* filename)
{
	FILE* file = fopen(filename, "rb");
	int k;
	if (file == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	for (int i = 0; (k = fgetc(file)) != EOF; i++)		//fgets(file) возвращает код считанного байта
	{
		if (i % 16 == 0)
		{
			printf("\n%08d:", ftell(file));           //с помощью ftell(file) выводим текущее смещение от начала файла
		}
		printf(" %X", k);
	}
}