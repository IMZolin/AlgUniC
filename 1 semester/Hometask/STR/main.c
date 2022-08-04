#include <stdio.h>

void TitleCase(char str[]) // if there are spacebar and after it, the lowercase letter
{
	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] = str[0] - ('a'-'A');
	for (int i = 0;str[i] != 0; i++)
	{
		if (i >= 1 && (str[i - 1] < 48 || (str[i-1]>57 && str[i - 1]<65)|| (str[i - 1] > 90 && str[i - 1] < 97)|| str[i - 1] > 122) && str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - ('a' - 'A');
		if (i >= 1 && ((str[i - 1] >= 'a' && str[i - 1] <= 'z') || (str[i - 1] >= 'A' && str[i - 1] <= 'Z') || (str[i - 1] >= '0' && str[i - 1] <= '9')) && (str[i] >= 'A' && str[i] <= 'Z'))
			str[i] = str[i] + ('a' - 'A');


	}
	fputs(str, stdout);
}

int main(void)
{
	char s[100];
	while (s != 0)
	{
		printf("Your string:\n");
		fgets(s, 100, stdin);
		printf("Result is:\n");
		TitleCase(s);
		printf("\n");
	}
	return 0;
}
