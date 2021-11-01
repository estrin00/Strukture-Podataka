#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//3.ZADATAK

typedef struct person* position;
struct person {
	char name[30];
	char surname[30];
	int year;
	position next;

};

int InsertAtTheBeginning(position p);
int Print(position p);
int InsertAtTheEnd(position p);
int SearchBySurname(position p);
int Delete(position p);

// FUNKCIJE TRECEG ZADATKA

int AddAfter(position p);
int AddBefore(position p);
int SortBySurname(position p);
void AddListToAFile(position p);
void ReadListFromAFile(position p);



int main()
{
	struct person head;
	head.next = NULL;
	char option;

	printf("Unesi p za unos na pocetak, i za ispis, k za unos na kraj,t za trazenje po prezimenu i b za brisanje elementa; ");
	printf(" a za dodavanje iza elementa, n za dodavanje ispred elementa, s za sortiranje po prezimenu, d za dodavanje liste datoteci i c za citanje liste iz datoteke:\n");
	scanf("%c", &option);

	if (option == 'p')
		InsertAtTheBeginning(&head);

	else if (option == 'i')
		Print(head.next);

	else if (option == 'k')
		InsertAtTheEnd(&head);

	else if (option == 't')
		SearchBySurname(head.next);

	else if (option == 'b')
		Delete(&head);

	// POZIV FUNKCIJA TRECEG ZADATKA

	else if (option == 'a')
		AddAfter(&head);

	else if (option == 'n')
		AddBefore(&head);

	else if (option == 's')
		SortBySurname(head.next);

	else if (option == 'd')
		AddListToAFile(head.next);

	else if (option == 'c')
		ReadListFromAFile(head.next);

	else
		printf("Greska!\n");


	return 0;
}

int InsertAtTheBeginning(position p)
{
	position q = NULL;
	q = (position)malloc(sizeof(struct person));

	if (q == NULL)
	{
		printf("Greska, memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe: ");
	scanf("%s", q->name);
	printf("Prezime osobe: ");
	scanf("%s", q->surname);
	printf("Godine: ");
	scanf("%d", &q->year);

	q->next = p->next;
	p->next = q;

	return 0;
}

int InsertAtTheEnd(position p)
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	position q = NULL;
	q = (position)malloc(sizeof(struct person));

	if (q == NULL)
	{
		printf("Greska, memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe: ");
	scanf("%s", q->name);
	printf("Prezime osobe: ");
	scanf("%s", q->surname);
	printf("Godine: ");
	scanf("%d", &q->year);

	q->next = p->next;
	p->next = q;

	return 0;
}

int SearchBySurname(position p)
{
	char surn[50];
	printf("Prezime trazene osobe: ");
	scanf(" %s", &surn);

	while (p != NULL && strcmp(surn, p->surname) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
		printf("Greska,takva osoba ne postoji!\n");
	else
		printf("Adresa osobe koju trazis je %d.\n", p);

	return 0;
}

int Delete(position p)
{
	position prev = NULL;
	char surn[50];

	printf("Unesi prezime osobe koju zelisi izbrisati s liste: ");
	scanf(" %s", &surn);

	while (p->next != NULL && strcmp(surn, p->surname) != 0)
	{
		prev = p;
		p = p->next;
	}

	if (prev != NULL && strcmp(surn, p->surname) == 0)
	{
		p = prev->next;
		prev->next = p->next;
		free(p);
	}

	return 0;
}

int AddAfter(position p)
{

	char surname2[50];

	position q=NULL;
	q = (position)malloc(sizeof(struct person));

	if (q == NULL)
	{
		printf("Greska, memorija nije alocirana!\n");
		return 1;
	}
	
	printf("\nUPIS NOVE OSOBE\n");
	// q je nova osoba u listi

	printf("Ime osobe: ");
	scanf(" %s", q->name);

	printf("Prezime osobe: ");
	scanf(" %s", q->surname);

	printf("Godine: ");
	scanf("%d", &q->year);

	printf("Prezime osobe iza koje dodajes novu osobu:\n");
	scanf(" %s", &surname2);

	while (p->next != NULL && p->next->surname!=surname2);
	{
		p = p->next;
	}

	if(p->next!=NULL)
	{
		q->next = p->next;
		p->next = q;
	}
	


	return 0;
}

int AddBefore(position p)
{

	char surname2[50];
	
	position q;
	position prev;

	q = (position)malloc(sizeof(struct person));

	if (q == NULL)
	{
		printf("Greska, memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe: ");
	scanf(" %s", q->name);

	printf("Prezime osobe: ");
	scanf(" %s", q->name);

	printf("Godine: ");
	scanf("%d", &q->year);

	printf("Prezime osobe ispred koje dodajes drugu osobu:\n");
	scanf(" %s", &surname2);

	prev = p;
	while (p->next != NULL &&  p->next->surname != surname2)
	{
		p = p->next;
	}

	if (p->next != NULL)
	{
		q->next = p->next;
		p->next = q;
	}

	return 0;
}
int SortBySurname(position p)
{
	char surname2[50];
	printf("Unesi prezime osobe koju trazis:\n");
	scanf(" %s", &surname2);

	if (surname2 == NULL)
	{
		printf("Greska!\n");
		return 1;
	}

	while (p != NULL && p->surname != surname2)
	{
		p = p->next;
	}
	
	return 0;
}





void AddListToAFile(position p)
{
	FILE* dat = NULL;
	dat = fopen("ListaImena.txt", "w");

	if (dat == NULL)
	{
		printf("Greska, ne moze otvoriti datoteku!\n");
		return 1;
	}
	
	while (p != NULL)
	{
		fprintf(dat, "%s    %s    %d\n", p->name, p->surname, p->year);
		p = p->next;
	}

	fclose(dat);
}

void ReadListFromAFile(position p)
{
	position q = NULL;
	char* fName = NULL;
	FILE* dat = NULL;

	printf("Unesi ime datoteke: ");
	scanf(" %s", &fName);

	dat = fopen(fName, "w");
	if (dat == NULL)
	{
		printf("Greska,ne moze otvoriti datoteku!\n");
		return 1;
	}

	int i = 0, j = 0;

	while (!feof(dat))
	{
		if (fgetc(dat) == '\n')
		{
			j++;
		}
	}

	if (j > 0)
	{
		for (i = 0; i < j; i++)
		{
			q = (position)malloc(sizeof(person));
			fscanf(dat, "%s %s %d", q->name, q->surname, q->year);
			q->next = p->next;
			p->next = q;
		}
	}

	fclose(dat);
}