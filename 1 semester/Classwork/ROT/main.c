#include<stdio.h>
//Печатаем массив
void Print(int arr[], int size)
{
    int i = 0;
    for (; i <= size - 1; i++)
    {
        printf("%i", arr[i]);
    }
    printf("\n");
}

//Генерируем массив от 1 до 9
void Fill(int arr[], int size)
{
    int i = 0;
    for (; i <= size - 1; i++)
    {
        arr[i] = i + 1;
    }
}
//Переворачиваем массив
void Reverse(int arr[], int left, int right)
{
    int i = left;
    int j = right;
    int buf = 0;

    for (; i < j; i++,j--)
    {
        buf = arr[i];
        arr[i] = arr[j];
        arr[j] = buf;

    }
}

//Сдвиг элементов (1 способ)
void Shift_Ver1(int arr[], int size, int delta)
{
    printf("The first way:\n");
    int n = 0;
    for (; n < delta; n++)
    {
        int tmp = 0;
        tmp = arr[0];
        int i = 0;
        for (; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[i] = tmp;
    }
}

//Сдвиг элементов (2 способ)
void Shift_Ver2(int arr[], int size, int delta)
{
    printf("The second way:\n");
    Fill(arr, size);
    Reverse(arr,0,size-1);// передаём полностью развёрнутый массив
    Reverse(arr, 0, size-1-delta);
    Reverse(arr,size-delta,size-1);

}

int main(void)
{
    int arr[10];
    int size = 9;
    int delta;
    printf("Enter your shift:\n");
    scanf_s("%i", &delta);
    Fill(arr, size);
    printf("Our array:\n");
    Print(arr,size);
    Shift_Ver1(arr, size, delta);
    Print(arr, size);
    Shift_Ver2(arr, size, delta);
    Print(arr, size);
    return 0;
}