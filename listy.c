#include <stdlib.h>
#include <stdio.h>


struct element{
int liczba;
struct element *nast;
struct element *poprz;
};

struct element *pierwszy=NULL;
struct element *ostatni=NULL;
int rozmiar=0;

int dodaj(int liczba){
struct element *nowy;
if((nowy=(struct element *)malloc(sizeof(struct element)))==NULL)
return 0;
/*if((nowy->liczba=(int *)malloc(sizeof(liczba)))==NULL)
return 0;*/
nowy->liczba=liczba;
if(pierwszy==NULL){ 
nowy->nast=NULL; 
nowy->poprz=NULL; 
pierwszy=nowy; 
ostatni=nowy; 
} else {
nowy->nast=NULL; 
nowy->poprz=ostatni; 
ostatni->nast=nowy; 
ostatni=nowy; 
}
//return 1;
rozmiar++;
}

int dodajZa(struct element *za, int liczba){
struct element *nowy; 
if((nowy=(struct element *)malloc(sizeof(struct element)))==NULL)
return 0;
/*if((nowy->liczba=(int *)malloc(sizeof(liczba)))==NULL)
return 0;*/
nowy->liczba=liczba;
if(za==ostatni){
nowy->nast=NULL;
nowy->poprz=ostatni;
ostatni->nast=nowy;
ostatni=nowy;
} else {
nowy->poprz=za;
nowy->nast=za->nast;
za->nast=nowy;
}
//return 1;
rozmiar++;
}

int dodajPrzed(struct element *przed, int liczba){
struct element *nowy;
if((nowy=(struct element *)malloc(sizeof(struct element)))==NULL)
return 0;
/*if((nowy->liczba=(int *)malloc(sizeof(liczba)))==NULL)
return 0;*/
nowy->liczba=liczba;
if(przed==pierwszy){
nowy->poprz=NULL;
nowy->nast=pierwszy;
pierwszy->poprz=nowy;
pierwszy=nowy;
} else {
nowy->nast=przed;
nowy->poprz=przed->poprz;
przed->poprz=nowy;
}
//return 1;
rozmiar++;
}

void usun(struct element *pozycja){
if(pozycja==NULL) // Zabezpieczenie przed otrzymaniem wskaŸnika NULL
return;
if (rozmiar==1) pierwszy=NULL;
else {
if(pozycja==pierwszy){
pierwszy=pozycja->nast;
pierwszy->poprz=NULL;
} else if(pozycja==ostatni){
ostatni=pozycja->poprz;
ostatni->nast=NULL;
} else {
pozycja->poprz->nast=pozycja->nast;
pozycja->nast->poprz=pozycja->poprz;
}
}
free(pozycja);
rozmiar--;
}

void pokazListe(){
struct element *tmp;
tmp=pierwszy;
while(tmp!=NULL){
printf("Liczba: %d\n", tmp->liczba);
tmp=tmp->nast;
}
}

/*
main(){
int x=5, y=2, z=9;
rozmiar=rozmiar+dodaj(z);
rozmiar+=dodaj(y);
rozmiar+=dodajPrzed(pierwszy, x);
printf("Rozmiar: %d\n", rozmiar);
pokazListe();
usun(pierwszy);
printf("Rozmiar: %d\n", rozmiar);
pokazListe();
 

}
*/