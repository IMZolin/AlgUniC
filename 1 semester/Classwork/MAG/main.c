// Классная работа 21.09
#include <stdio.h>

void MAG(int ch, char ar[], int sys_ch, int buf)
{
	int i = 0;
	int digit = 0;
	int back_buf = buf;
	ar[0] = buf + '0';
	for (i = 1; i < 50; i++)
	{
		buf = buf * ch + digit;
		back_buf = buf;
		buf = buf % sys_ch;
		if (buf == ch && ar[i - 1] - '0' == 1)
		{
			printf("This number was founded!\n");
			for (i = i - 1; i >= 0; i--)
			{
				printf("%c", ar[i]);
			}
			break;
		}

		else if (i == 49)
		{
			printf("Sorry, this nuber is too long!\n");
		}
		if (buf > 9)
		{
			ar[i] = buf + 'A' - 10;
		}
		else
		{
			ar[i] = buf + '0';
		}
		digit = back_buf / sys_ch;
	}



}

int main(void)
{
	int buf = 1;
	char A[50];
	int ch;
	int sys_ch;
	printf("Enter your count system : ");
	scanf_s("%i", &sys_ch);
	printf("Enter yur number: ");
	scanf_s("%i", &ch);
	buf = ch;
	MAG(ch, A, sys_ch, buf);
	return 0;
}