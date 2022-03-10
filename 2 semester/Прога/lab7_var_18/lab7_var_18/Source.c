#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

struct Fio
{
	char* surname;
	char* name;
};

struct Date
{
	int day;
	char* month;
	int year;
};

struct Letter
{
	double cost;
	int senderPostCode;
	struct Fio sender;
	int recipintPostCode;
	struct Fio recipient;
	struct Date departureDate;
	int deliverTime;
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
	newLetter.sender.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.sender.name, buff);

	printf("Enter sender surname: ");
	scanf("%25s", buff);
	newLetter.sender.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.sender.surname, buff);

	printf("Enter recipient post code: ");
	scanf("%d", &newLetter.recipintPostCode);

	printf("Enter recipient name: ");
	scanf("%25s", buff);
	newLetter.recipient.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.recipient.name, buff);

	printf("Enter recipient surname: ");
	scanf("%25s", buff);
	newLetter.recipient.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.recipient.surname, buff);

	printf("Enter departure date\n");
	printf("Day: ");
	scanf("%d", &newLetter.departureDate.day);
	printf("Month (Jan/ßíâ, Feb/Ôåâ, Mar/Ìàð, Apr/Àïð, May/Ìàé, June/Èþíü, July/Èþëü, Aug/Àâã, Sept/Ñåí, Oct/Îêò, Nov/Íîÿ, Dec/Äåê): ");
	scanf("%25s", buff);
	newLetter.departureDate.month = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newLetter.departureDate.month, buff);
	printf("Year: ");
	scanf("%d", &newLetter.departureDate.year);

	printf("Enter deliver time(days): ");
	scanf("%d", &newLetter.deliverTime);

	return newLetter;
}

void PrintTable(struct Letter* Letters, int LettersCount)
{
	if (LettersCount > 0)
	{
		printf("%-15s%-10s%-26s%-26s%-26s%-26s%-26s%-15s%s", "Cost", "Sender", "Sender", "Sender", "Recipient", "Recipient", "Recipient", "Departure", "Deliver\n");
		printf("%-15s%-10s%-26s%-26s%-26s%-26s%-26s%-15s%s", "", "post code", "name", "surname", "post code", "name", "surname", "date", "time\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < LettersCount; i++)
		{
			printf("%-15f%-10d%-26s%-26s%-26d%-26s%-26s%d %s %-10d%d\n", Letters[i].cost, 
				Letters[i].senderPostCode, Letters[i].sender.name, Letters[i].sender.surname,
				Letters[i].recipintPostCode, Letters[i].recipient.name, Letters[i].recipient.surname, 
				Letters[i].departureDate.day, Letters[i].departureDate.month, Letters[i].departureDate.year, 
				Letters[i].deliverTime);
		}
	}
}

void FindBySender(struct Letter* letters, int letterCount, char* name, char* surname)
{
	struct Letter* senderLetters = (struct Letter*)malloc(0);
	int count = 0;

	for (int i = 0; i < letterCount; i++)
		if (strcmp(letters[i].sender.name, name) == 0 && strcmp(letters[i].sender.surname, surname) == 0)
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
			if (strcmp(Letters[j].recipient.surname, Letters[j + 1].recipient.surname) == 1 ||
				(strcmp(Letters[j].recipient.surname, Letters[j + 1].recipient.surname) == 0 && strcmp(Letters[j].recipient.name, Letters[j + 1].recipient.name) == 1))
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

void UndeliverLetter(struct Letter* letters, int lettersCount)
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	double timeNow = 0.0;
	struct Letter* tmpLetter = (struct Letter*)malloc(0);
	int count = 0;

	for (int i = 0; i < lettersCount; i++)
	{
		int day = letters[i].departureDate.day;
		int month = -1;
		int year = letters[i].departureDate.year;
		if (strcmp(letters[i].departureDate.month, "Jan") == 0 || strcmp(letters[i].departureDate.month, "ßíâ") == 0)
			month = 1;
		else if (strcmp(letters[i].departureDate.month, "Feb") == 0 || strcmp(letters[i].departureDate.month, "Ôåâ") == 0)
			month = 2;
		else if (strcmp(letters[i].departureDate.month, "Mar") == 0 || strcmp(letters[i].departureDate.month, "Ìàð") == 0)
			month = 3;
		else if (strcmp(letters[i].departureDate.month, "Apr") == 0 || strcmp(letters[i].departureDate.month, "Àïð") == 0)
			month = 4;
		else if (strcmp(letters[i].departureDate.month, "May") == 0 || strcmp(letters[i].departureDate.month, "Ìàé") == 0)
			month = 5;
		else if (strcmp(letters[i].departureDate.month, "June") == 0 || strcmp(letters[i].departureDate.month, "Èþíü") == 0)
			month = 6;
		else if (strcmp(letters[i].departureDate.month, "July") == 0 || strcmp(letters[i].departureDate.month, "Èþëü") == 0)
			month = 7;
		else if (strcmp(letters[i].departureDate.month, "Aug") == 0 || strcmp(letters[i].departureDate.month, "Àâã") == 0)
			month = 8;
		else if (strcmp(letters[i].departureDate.month, "Sept") == 0 || strcmp(letters[i].departureDate.month, "Ñåí") == 0)
			month = 9;
		else if (strcmp(letters[i].departureDate.month, "Oct") == 0 || strcmp(letters[i].departureDate.month, "Îêò") == 0)
			month = 10;
		else if (strcmp(letters[i].departureDate.month, "Nov") == 0 || strcmp(letters[i].departureDate.month, "Íîÿ") == 0)
			month = 11;
		else if (strcmp(letters[i].departureDate.month, "Dec") == 0 || strcmp(letters[i].departureDate.month, "Äåê") == 0)
			month = 12;

		timeNow = (double)(now->tm_year + 1900 - year) * 12 * 365 + (now->tm_mon + 1 - month) * 30 + (double)(now->tm_mday - day);

		if (timeNow > letters[i].deliverTime)
		{
			count++;
			tmpLetter = (struct Letter*)realloc(tmpLetter, sizeof(struct Letter) * count);
			tmpLetter[count - 1] = letters[i];
		}
	}
	PrintTable(tmpLetter, count);

	free(tmpLetter);
}

void LoadFromFile(struct Letter** letters, int* count)
{
	FILE* fin;
	int pos;
	char buff[26];
	if ((fin = fopen("base.txt", "r")) == NULL)
	{
		FILE* f = fopen("base.txt", "w");
		fclose(f);

		fin = fopen("base.txt", "r");
	}

	fseek(fin, 0, SEEK_END);
	pos = ftell(fin);
	if (pos > 0)
	{
		fseek(fin, 0, SEEK_SET);
		while (!feof(fin))
		{
			(*letters) = (struct Letters*)realloc((*letters), sizeof(struct Letter) * (*count + 1));

			fscanf(fin, "%lf", &(*letters)[*count].cost);

			fscanf(fin, "%d", &(*letters)[*count].senderPostCode);

			fscanf(fin, "%25s", &buff);
			(*letters)[*count].sender.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*letters)[*count].sender.name, buff);

			fscanf(fin, "%25s", &buff);
			(*letters)[*count].sender.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*letters)[*count].sender.surname, buff);

			fscanf(fin, "%d", &(*letters)[*count].recipintPostCode);

			fscanf(fin, "%25s", &buff);
			(*letters)[*count].recipient.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*letters)[*count].recipient.name, buff);

			fscanf(fin, "%25s", &buff);
			(*letters)[*count].recipient.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*letters)[*count].recipient.surname, buff);

			fscanf(fin, "%d", &(*letters)[*count].departureDate.day);

			fscanf(fin, "%25s", &buff);
			(*letters)[*count].departureDate.month = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*letters)[*count].departureDate.month, buff);

			fscanf(fin, "%d", &(*letters)[*count].departureDate.year);

			fscanf(fin, "%d", &(*letters)[*count].deliverTime);
			(*count)++;
		}
	}
	fclose(fin);
}

void SaveToFile(struct Letter* letters, int count)
{
	FILE* fout;
	if ((fout = fopen("base.txt", "w")) == NULL)
	{
		printf("File not found.\n");
		return;
	}
	for (int i = 0; i < count; i++)
	{
		fprintf(fout, "%lf\t", letters[i].cost);
		fprintf(fout, "%d\t", letters[i].senderPostCode);
		fputs(letters[i].sender.name, fout);
		fputc('\t', fout);
		fputs(letters[i].sender.surname, fout);
		fputc('\t', fout);
		fprintf(fout, "%d\t", letters[i].recipintPostCode);
		fputs(letters[i].recipient.name, fout);
		fputc('\t', fout);
		fputs(letters[i].recipient.surname, fout);
		fputc('\t', fout);
		fprintf(fout, "%d\t", letters[i].departureDate.day);
		fputs(letters[i].departureDate.month, fout);
		fputc('\t', fout);
		fprintf(fout, "%d\t", letters[i].departureDate.year);
		fprintf(fout, "%d", letters[i].deliverTime);
		if (i != count - 1)
			fputc('\n', fout);
	}

	fclose(fout);
}

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Letter* Letters = (struct Letter*)malloc(0);
	int count = 0;
	LoadFromFile(&Letters, &count);
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
		printf("5.Undeliver letter\n");
		printf("6.Exit\n");
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
			UndeliverLetter(Letters, count);
			break;
		case 6:
			SaveToFile(Letters, count);
			exit = 0;
		default:
			break;
		}
	}

	free(Letters);
}