#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int MyStrlen(char const array[]);
int Verification(char symbol);
int WriteLine(char const* filename);
char* ReadLine(char const* filename, int const length);
char* ProcessingMask(char const* filename);
int MaskCheck(char const* array, int ArrayIndex, char const* mask);
char* FindMaskWords(char const* array, int Size, char const* mask);

int main()
{
    setlocale(LC_ALL, "Rus");

    char* mask, * string, * result;
    int length;

    printf("Вариант DST–7 (Поиск по маске)\n\n");

    //объявление маски
    mask = ProcessingMask("mask.txt");
    printf("\n");

    //Цикл тестирования строк для заданной маски
    while (1)
    {
        length = WriteLine("string.txt");
        string = ReadLine("string.txt", length);
        result = FindMaskWords(string, length, mask);

        //елси пользоваетль введет пустую строку, то произойдет остановка цикла
        if (string[0] == '\0') break;

        printf("Результат          : %s\n", result);

        printf("\n");
    }

    printf("\nПрограмма завершает работу.\n");

    //Очистка памяти
    free(mask);
    free(string);
    free(result);

    return 0;
}


//Функция считает кол-во элементов в строке
int MyStrlen(char const array[])
{
    int length = 0, i = 0;
    while (1)
    {
        if (array[i] != '\0')
        {
            length++;
            i++;
        }
        else break;
    }

    return length;
}


//Функция проверяет является ли символ разделителем
//(возвращает "1" если символ - разделитель, "0" если нет)
int Verification(char symbol)
{
    char delimiters[] = { ' ','.',',','-',':',';','!','?' };

    for (int i = 0; i < 8; i++)
        if (symbol == delimiters[i]) return 1;

    return 0;
}


//Функция записывает обработанную строку в файл, возвращает ее финальную длину
int WriteLine(char const* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char symbol = NULL;

    //переменные содержат:
    int   Delta = 0,	//счетчик разделителей, которые идут подряд в строке
    length = 0;	//длина уже обработанной строки(т.е. строки, которая будет сохранена в динамический массив)

    //Цикл записывает символы, введенные с клавиатуры в файл(getchar), пока пользователь не нажмет "enter"
    //Так же цикл обрабатывает строку для корректной работы функций, которые проверют слово на соответсвие маске
    printf("Введите предложение: ");
    do
    {
        symbol = getchar();

        //Исследование разделителя: (Verification возвращает "1" если символ является разделителем слов)
        //- если разделитель одиночный, то он заменяется на ' ';
        //- если разделители идут подряд, то на их место ставиться ' ';
        if (Verification(symbol) == 1)
        {
            if (Delta != 0 || length == 0);
            else
            {
                fputc(' ', file);
                length++;
            }
            Delta++;
        }

        else
        {
            //Игнорируем сивол "enter"
            if (symbol != '\n')
            {
                fputc(symbol, file);
                Delta = 0;
                length++;
            }
        }

    } while (symbol != '\n');

    //добавляем символ конца строки
    fputc('\0', file);
    length++;

    fclose(file);

    return length;
}


//Функция записывает строку в динамический массив, возвращает указатель на него
char* ReadLine(char const* filename, int const length)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char* String = (char*)malloc(sizeof(char) * length), symbol = NULL;
    if (String == NULL)
    {
        printf("Memory error");
        exit(1);
    }

    fgets(String, length, file);

    fclose(file);

    return String;
}


//Функция записывает маску, введенную пользователем, в динамический массив; возвращает указатель на этот массив
char* ProcessingMask(char const* filename)
{
    //поток для записи
    FILE* file1 = fopen(filename, "w");
    if (file1 == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char symbol = NULL;
    int length = 0; //длина маски

    //цикл записи маски; происходит посимвольное чтение, пока пользователь не нажмет "enter"
    printf("Введите слово-маску: ");
    do {

        symbol = getchar();
        if (symbol != '\n') putc(symbol, file1);
        length++;

    } while (symbol != '\n');
    putc('\0', file1);
    length++;

    fclose(file1);

    //поток для чтения
    FILE* file2 = fopen(filename, "r");
    if (file2 == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }


    char* MaskPointer = (char*)malloc(sizeof(char) * length);
    if (MaskPointer == NULL)
    {
        printf("Memory error");
        exit(1);
    }

    fgets(MaskPointer, length, file2);

    fclose(file2);

    return MaskPointer;
}


//Функция проверяет слова(по индексу их первой буквы), находящиеся в обработанной строке, на соответсвие маске:
//eсли слово подходит, возвращает длину маски;
//eсли слово не подходит, возвращает 0.
int MaskCheck(char const* array, int ArrayIndex, char const* mask)
{
    int        truth = 0,	 //Индикатор совпадений, если число совпадений равно числу элементов маски, то слово подходит
    delta = 0,	 //Вспомогательная переменная для случая mask[i] = '*'
    length,	 //Длина маски
    MaskIndex = 0;    //Индекс маски

    length = MyStrlen(mask);

    //Запуск цилка провекри
    while (array[ArrayIndex] != '\0' && array[ArrayIndex] != ' ')
    {
        //Случай номер I: элемент маски не равен '*'
        if (mask[MaskIndex] != '*')
        {
            if (mask[MaskIndex] == array[ArrayIndex])
                truth++;

            else
                return 0;
        }

            //Случай номер II: элемент маски равен '*'
        else
        {
            if (MaskIndex + 1 == length) //Проверяем, не стоит ли '*' в конце маски
            {
                truth++;
                return truth;
            }

            //Если '*' стоит не в конце маски, то запускаем цикл проверки
            MaskIndex++;
            while (array[ArrayIndex] != '\0' && array[ArrayIndex] != ' ')
            {
                if (array[ArrayIndex] == mask[MaskIndex])
                {
                    delta++;
                    break;
                }
                ArrayIndex++;
            }

            if (delta != 0)
            {
                truth += 2;
                delta = 0;
            }
            else return 0;

        }

        //Подготавливаем следующую итерацию основного цикла
        MaskIndex++;
        ArrayIndex++;
    }

    return truth;
}


//Функция записывает слова, удовлетворяющие маске, в отдельный динамический массив; возвращает указатель на этот массив
char* FindMaskWords(char const* array, int Size, char const* mask)
{
    char* MainString = (char*)malloc(sizeof(char));
    if (MainString == NULL)
    {
        printf("Memory error");
        exit(1);
    }

    char* ptr = NULL;

    //переменнаы содержат:
    int		          start = 0,	//начало слова, которое проходит проверку в данный момент
    finish = 0,	//конец слова, которое проходит проверку в данный момент
    length = 0,	//длинну маски
    truth = 0,	//индикатор совпадения
    MainStringIndex = 0,	//индекс массива
    memory = 0;	//кол-во динамической памяти, котрую необходимо выделить

    length = MyStrlen(mask);

    //запуск цикла проверки
    while (array[start] != '\0' && start < Size)
    {
        //запуск цикла, который определяет начало и конец слова, которое проходит проверку в данный момент
        while (array[start + finish] != ' ')
        {
            if (array[start + finish] == '\0') break;
            finish++;
        }

        //быстрая проверка на соотвествие слова маске
        if (mask[length - 1] != '*' && mask[length - 1] != array[start + finish - 1]);

            //стандартная провека
        else
        {
            truth = MaskCheck(array, start, mask); //проверка слова

            //если слово подходит, то происходит:
            //- выделение динамической памяти(realloc);
            //- запись в финальный массив;
            if (truth != 0)
            {
                memory += (finish + 2) * sizeof(char);
                ptr = (char*)realloc(MainString, memory);
                if (ptr == NULL)
                {
                    printf("memory error");
                    exit(1);
                }
                else MainString = ptr;

                for (int i = start; i < finish + start; i++)
                {
                    MainString[MainStringIndex] = array[i];
                    MainStringIndex++;
                }
                MainString[MainStringIndex] = ',';
                MainStringIndex++;
                MainString[MainStringIndex] = ' ';
                MainStringIndex++;
            }
        }

        //подготовка к следующей итерации цикла
        start += finish + 1;
        finish = 0;
    }

    //Добавление в конец массива служебного символа конца строки, если присутствуют слова, удовлетворяющие маске
    //(на это указывает то, то была выделена дополнительная память)
    if (memory != 0) MainString[MainStringIndex - 2] = '\0';

        //В случае отсутствия подходящих слов, функция возвращает строку с одним символом - '\0'
    else MainString[0] = '\0';

    return MainString;
}