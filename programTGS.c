#include <stdio.h>
#include <stdlib.h>
#include "listy.c"


main()
{
  const int MAXINT = 2147483647;
  int n, m, s, t, fmax, cp, x, y, esc, i, j;
    
// Ze standardowego wej�cia odczytujemy
// n - liczb� wierzcho�k�w w grafie sieci
// m - liczb� kraw�dzi
  printf("\nPodaj liczbe wierzcholkow i krawedzi grafow w sieci: ");
  scanf("%d %d",&n,&m);
  
// Tworzymy macierze:
// C[][] - przepustowo�ci kraw�dzi
// F[][] - przep�ywy w kraw�dziach

  int C[n+1][n+1], F[n+1][n+1];
  
// Tworzymy tablice:
// p[]   - poprzedniki na �cie�kach tworzonych przez BFS
// cfp[] - przepustowo�� �cie�ek

  int p[n+1], cfp[n+1];              
  
// Zerujemy macierze przepustowo�ci i przep�yw�w

  for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++){ 
	F[i][j] = 0;
	C[i][j] = 0;
    }  
// Ze standardowego wej�cia odczytujemy definicje kraw�dzi.
// Ka�da definicja sk�ada si� z trzech liczb
// x,y - wierzcho�ki grafu po��czone kraw�dzi�
// cp  - przepustowo�� kraw�dzi
// Odczytane dane zapami�tujemy: C[x][y] = cp

  for(i = 1; i <= m; i++)
  {
    printf("\nPodaj numery wierzcholkow polaczonych krawedzia oraz przepustowosc tej krawedzi: ");
	scanf("%d %d %d", &x, &y, &cp);
    C[x][y] = cp;        
  }

// Na koniec odczytujemy numer wierzcho�ka �r�d�a s
// oraz numer wierzcho�ka uj�cia t

  printf("\nPodaj numer wierzcholka zrodla i wierzcholka ujscia: ");
  scanf("%d %d",&s,&t);
  
//**************************************************
//** Tutaj rozpoczyna si� algorytm Edmondsa-Karpa **
//**************************************************

// Rozpoczynamy od maksymalnego przep�ywu r�wnego zero

  fmax = 0;

// W p�tli szukamy �cie�ek rozszerzaj�cych dot�d,
// dop�ki istniej� w sieci residualnej. Ka�da znaleziona
// �cie�ka zwi�ksza przep�yw wzd�u� zawartych w niej
// kraw�dzi grafu sieci przep�ywowej

  
  do{

// Na pocz�tku p�tli zerujemy tablic� poprzednik�w p[]

    for(i = 1; i <= n; i++) p[i] = 0;

// �r�d�o nie posiada poprzednika. Wpisujemy tutaj -1,
// aby BFS nie wybiera�o �r�d�a

    p[s] = -1;

// Do cfp[s] wpisujemy najwi�ksz� liczb� ca�kowit�

    cfp[s] = MAXINT;

//  Umieszczamy w kolejce �r�d�o s

	dodaj(s);

// Zmienna esc umo�liwia odpowiednie wychodzenie z
// dw�ch zagnie�d�onych p�tli

    esc = 0;

// Rozpoczynamy p�tl� wyszukuj�c� �cie�ki BFS. P�tla ko�czy
// si� w przypadku braku dalszych wierzcho�k�w w kolejce

   

    while(rozmiar)
    {

// Z pocz�tku kolejki pobieramy element i usuwamy go z kolejki

      x = pierwszy->liczba; 
	  usun(pierwszy);

// Sprawdzamy wszystkich s�siad�w wierzcho�ka x przegl�daj�c
// wiersz macierzy C[x][]

      for(y = 1; y <= n; y++)
      {

// Dla s�siada y wyznaczamy przepustowo�� residualn�
// kraw�dzi x->y. Je�li kraw�d� nie istnieje w sieci,
// to otrzymamy w cp wynik zero

        cp = C[x][y] - F[x][y];

// Sprawdzamy, czy kraw�d� istnieje oraz, czy wierzcho�ek
// y nie by� ju� wcze�niej wybrany przez BFS. W takim
// przypadku p[y] ma warto�� r�n� od zera.

        if(cp && !p[y])
        {
  
// W p[y] zapami�tujemy, i� poprzednikiem y jest x

          p[y] = x;

// Dla wierzcho�ka y obliczamy dotychczasow� przepustowo��
// residualn� �cie�ki. Jest to mniejsza warto�� z przepustowo�ci
// �cie�ki dla poprzednika x i bie��cej przepustowo�ci
// residualnej kraw�dzi x->y.

          cfp[y] = (cfp[x] > cp) ? cp : cfp[x];

// Je�li osi�gn�li�my uj�cie, to �cie�ka jest kompletna

          if(y == t)
          {

// Zwi�kszamy przep�yw maksymalny o przepustowo�� residualn�
// �cie�ki - wykorzystujemy tablic� cfp[]

             fmax += cfp[t];

// Idziemy wstecz po �cie�ce zwi�kszaj�c przep�ywy
// wzd�u� jej kraw�dzi w kierunku zgodnym ze �cie�k�
// oraz zmniejszaj�c przep�ywy w kierunku przeciwnym

             while(y != s)
             {
               //printf("x=%d y=%d p[y]=%d F[x][y]=%d F[y][x]=%d t=%d cfp[t]=%d\n\n",x,y,p[y],F[x][y],F[y][x],t,cfp[t]);
			   x = p[y];
			   //if(F[x][y]<0) break;
               F[x][y] += cfp[t];
               F[y][x] -= cfp[t];
               y = x;        
             } //koniec while(y != s)
             
// Ustawiamy esc na 1, co spowoduje wyj�cie z obu p�tli
             
             esc = 1; break;
    
          } //koniec if(y == t)

// Je�li wierzcho�ek y nie jest uj�ciem t, to dopisujemy
// go na ko�cu kolejki i kontynuujemy p�tl� BFS

          dodaj(y); 
     
        } //koniec if(cp && !p[y])     

      } // koniec for(y = 1; y <= n; y++)

// Tutaj wychodzimy z p�tli while(rozmiar), je�li
// zosta�a znaleziona �cie�ka rozszerzaj�ca

      if(esc) break;              

    } //koniec while(rozmiar)

// Je�li nie znaleziono �cie�ki rozszerzaj�cej, to esc = 0
// i w tym miejscu nast�pi wyj�cie z g��wnej p�tli do

    if(!esc) break;

  } while(1);
  
// Prezentujemy wyniki oblicze�. Najpierw wypisujemy
// warto�� maksymalnego przep�ywu
  
  printf("\nfmax = %d\n\n", fmax);
  
  for(x = 1; x <= n; x++)
    for(y = 1; y <= n; y++)
      if(C[x][y])
        printf("%d -> %d %d/%d\n", x, y, F[x][y], C[x][y]);
                   
  printf("\n");
}