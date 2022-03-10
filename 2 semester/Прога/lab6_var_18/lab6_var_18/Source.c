#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>

struct Letter
{
	double cost;
	int senderPostCode;
	char* senderName;
	char* senderSurname;
	int recipintPostCode;
	char* recipientName;
	char* recipientSurname;
};

struct Letter CreateLetter()
{
	struct Letter newLetter;
	char buff[26];
	double d;

	printf("Enter cost of letter: ");
	scanf("%lf", &newLetter.cost);

	printf("Enter sender post code: ");
	scanf("%d", &newLetter.senderPostCode);

	printf("Enter sender name: ");
	scanf("%25s", buff);
	newLetter.senderName = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.senderName, buff);

	printf("Enter sender surname: ");
	scanf("%25s", buff);
	newLetter.senderSurname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.senderSurname, buff);

	printf("Enter recipient post code: ");
	scanf("%d", &newLetter.recipintPostCode);

	printf("Enter recipient name: ");
	scanf("%25s", buff);
	newLetter.recipientName = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.recipientName, buff);

	printf("Enter recipient surname: ");
	scanf("%25s", buff);
	newLetter.recipientSurname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.recipientSurname, buff);

	return newLetter;
}


void PrintTable(struct Letter* Letters, int LettersCount)
{
	if (LettersCount > 0)
	{
		printf("%-15s%-10s%-26s%-26s%-26s%-26s%s", "Cost", "Sender", "Sender", "Sender", "Recipient", "Recipient", "Recipient\n");
		printf("%-15s%-10s%-26s%-26s%-26s%-26s%s", "", "post code", "name", "surname", "post code", "name", "surname\n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < LettersCount; i++)
		{
			printf("%-15f%-10d%-26s%-26s%-26d%-26s%s\n", Letters[i].cost, Letters[i].senderPostCode, Letters[i].senderName, Letters[i].senderSurname, 
				Letters[i].recipintPostCode, Letters[i].recipientName, Letters[i].recipientSurname);
		}
	}
}

void FindBySender(struct Letter* letters, int letterCount, char* name, char* surname)
{
	struct Letter* senderLetters = (struct Letter*)malloc(0);
	int count = 0;

	for (int i = 0; i < letterCount; i++)
		if (strcmp(letters[i].senderName, name) == 0 && strcmp(letters[i].senderSurname, surname) == 0)
		{
			count++;
			senderLetters = (struct Letter*)realloc(senderLetters, sizeof(struct Letter) * count);
			senderLetters[count - 1] = letters[i];
		}

	PrintTable(senderLetters, count);
}

struct Letter* SortByRecipientName(struct Letter* Letters, int LettersCount)
{
	for (int i = 0; i < LettersCount - 1; i++)
		for (int j = 0; j < LettersCount - 1; j++)
			if (strcmp(Letters[j].recipientSurname, Letters[j + 1].recipientSurname) == 1 || 
				(strcmp(Letters[j].recipientSurname, Letters[j + 1].recipientSurname) == 0 && strcmp(Letters[j].recipientName, Letters[j + 1].recipientName) == 1))
			{
				struct Letter tmp = Letters[j];
				Letters[j] = Letters[j + 1];
				Letters[j + 1] = tmp;
			}

	return Letters;
}

void FindByCost(struct Letter* letters, int letterCount, double cost)
{
	struct Letter* senderLetters = (struct Letter*)malloc(0);
	int count = 0;

	for (int i = 0; i < letterCount; i++)
		if (letters[i].cost > cost)
		{
			count++;
			senderLetters = (struct Letter*)realloc(senderLetters, sizeof(struct Letter) * count);
			senderLetters[count - 1] = letters[i];
		}

	senderLetters = SortByRecipientName(senderLetters, count);

	PrintTable(senderLetters, count);
}


int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Letter* Letters = (struct Letter*)malloc(0);
	int count = 0;
	char buff[51];
	char buff2[51];
	double intBuff;
	int c;
	int exit = 1;
	while (exit)
	{
		printf("1.Add letter\n");
		printf("2.Print info about letters\n");
		printf("3.Find sender letters\n");
		printf("4.Find all letters with a cost than a given\n");
		printf("5.Exit\n");
		printf("Enter command: ");

		scanf("%d", &c);

		switch (c)
		{
		case 1:
			count++;
			Letters = (struct Letter*)realloc(Letters, sizeof(struct Letter) * count);
			Letters[count - 1] = CreateLetter();
			break;
		case 2:
			PrintTable(Letters, count);
			break;
		case 3:
			printf("\nEnter sender name: ");
			scanf("%s50", buff);
			printf("\nEnter sender surname: ");
			scanf("%s50", buff2);
			FindBySender(Letters, count, buff, buff2);
			break;
		case 4:
			printf("\nEnter cost: ");
			scanf("%lf", &intBuff);
			FindByCost(Letters, count, intBuff);
			break;
		case 5:
			exit = 0;
		default:
			break;
		}
	}

	free(Letters);
}