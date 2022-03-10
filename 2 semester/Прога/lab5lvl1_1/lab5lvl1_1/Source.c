#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#define N 100

char* create_str()
{
	char buff[N];
	char* str;
	printf("¬ведите строку:\n");
	gets(buff);
	str = (char*)malloc(sizeof(char)*(strlen(buff) + 1));
	strcpy(str, buff);
	return str;
}

char* del_symbol(char* str, char sym)
{
	char* new_str = (char*)calloc(2, sizeof(char));
	int count = 0;
	for (int i = 0; i < strlen(str) + 1; i++)
		if (*(str + i) != sym)
		{
			new_str = (char*)realloc(new_str, sizeof(char)*(count + 1));
			new_str[count] = str[i];
			count++;
		}
	return new_str;
}

int search_digit(char* str)
{
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
		if (isdigit(str[i]))
			count++;
	return count;
}

int main()
{
	setlocale(0, "russian");
	char *str1, *str2, sym;
	str1 = create_str();
	str2 = create_str();
	printf("¬ведите символ, который хотите удалить:");
	scanf("%c", &sym);
	str1 = del_symbol(str1, sym);
	str2 = del_symbol(str2, sym);
	if (search_digit(str1) > search_digit(str2))
	{
		printf("%s\n", str1);
		printf("%s", str2);
	}
	else
	{
		printf("%s\n", str2);
		printf("%s", str1);
	}
	free(str1);
	free(str2);
}