#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student
{
  char ime[MAX_SIZE];
  char prezime[MAX_SIZE];
  double bodovi;
}student;



int ProcitajBrojRedakaIzDatoteke(char* NazivDatoteke)
{
  int brojac=0;
  FILE *datoteka=NULL;
  char buffer[MAX_LINE]={0};

  datoteka=fopen(NazivDatoteke,"r");
  if(!datoteka)
  {
    printf("Greska, nema datoteke!\n");
    return -1;
  }

  while(!feof(datoteka))
  {
    fgets(buffer,MAX_LINE,datoteka);

    brojac++;
  }
  fclose(datoteka);

  return brojac;

}

student *ProcitajMemorijuIAlocirajStudente(int BrojStudenata,char *NazivDatoteke)
{
  int brojac=0;
  FILE *datoteka=NULL;
  student *studenti=NULL;

  studenti=(student*)malloc(BrojStudenata*sizeof(student));
  datoteka=fopen(NazivDatoteke,"r");

  if(!datoteka)
  {
    printf("Greska u alociranju!\n");
    return -1;
  }

  while(!feof(datoteka))
  {
    fscanf(datoteka,"%s %s %lf",studenti[brojac].ime,studenti[brojac].prezime,&studenti[brojac].bodovi);
    brojac++;
  }

  fclose(datoteka);
  return studenti;
}



int main()
{
  int i;
  

  int BrojStudenata=ProcitajBrojRedakaIzDatoteke("KolokvijStudenti.txt");
  student*studenti=ProcitajMemoruijuIAlocirajStudente(BrojStudenata,"KolokvijStudenti.txt");

  printf("IME   PREZIME   BROJ BODOVA\n");
  for(i=0;i<BrojStudenata;i++)
  {

    printf("%s %s %lf\n",studenti[i].ime,studenti[i].prezime,studenti[i].bodovi);

  }

  double RelativanBrojBodova[BrojStudenata];

  // maksimalan broj bodova je 75

  printf("POPIS S RELATIVNIM BROJEM BODOVA:\n");
  for(i=0;i<BrojStudenata;i++)
  {
    RelativanBrojBodova[i]=studenti[i].bodovi/75*100;
    printf("%s %s %lf\n",studenti[i].ime,studenti[i].prezime,RelativanBrojBodova[i]);
  }

  return 0;

  return 0;
}