#include <iostream>
#include <list>

using namespace std;

main()
{
  const int MAXINT = 2147483647;
  int n, m, s, t, fmax, cp, x, y, esc, i, j;
  list <int> q;

// Ze standardowego wejœcia odczytujemy
// n - liczbê wierzcho³ków w grafie sieci
// m - liczbê krawêdzi

  cin >> n >> m;

// Tworzymy macierze:
// C[][] - przepustowoœci krawêdzi
// F[][] - przep³ywy w krawêdziach

  int C[n+1][n+1], F[n+1][n+1];

// Tworzymy tablice:
// p[]   - poprzedniki na œcie¿kach tworzonych przez BFS
// cfp[] - przepustowoœæ œcie¿ek

  int p[n+1], cfp[n+1];

// Zerujemy macierze przepustowoœci i przep³ywów

  for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++) F[i][j] = C[i][j] = 0;

// Ze standardowego wejœcia odczytujemy definicje krawêdzi.
// Ka¿da definicja sk³ada siê z trzech liczb
// x,y - wierzcho³ki grafu po³¹czone krawêdzi¹
// cp  - przepustowoœæ krawêdzi
// Odczytane dane zapamiêtujemy: C[x][y] = cp

	cout << "Podaj kolejno numery wierzcholkow polaczonych krawedzia oraz przepustowosci tych krawedzi: ";

  for(i = 1; i <= m; i++)
  {
    cin >> x >> y >> cp;
    C[x][y] = cp;
  }

// Na koniec odczytujemy numer wierzcho³ka Ÿród³a s
// oraz numer wierzcho³ka ujœcia t

  cout << "Podaj numer wierzcholka zrodla s i ujscia t: ";
  cin >> s >> t;

//**************************************************
//** Tutaj rozpoczyna siê algorytm Edmondsa-Karpa **
//**************************************************

// Rozpoczynamy od maksymalnego przep³ywu równego zero

  fmax = 0;

// W pêtli szukamy œcie¿ek rozszerzaj¹cych dot¹d,
// dopóki istniej¹ w sieci residualnej. Ka¿da znaleziona
// œcie¿ka zwiêksza przep³yw wzd³u¿ zawartych w niej
// krawêdzi grafu sieci przep³ywowej

  do
  {

// Na pocz¹tku pêtli zerujemy tablicê poprzedników p[]

    for(i = 1; i <= n; i++) p[i] = 0;

// Ÿród³o nie posiada poprzednika. Wpisujemy tutaj -1,
// aby BFS nie wybiera³o Ÿród³a

    p[s] = -1;

// Do cfp[s] wpisujemy najwiêksz¹ liczbê ca³kowit¹

    cfp[s] = MAXINT;

// Zerujemy kolejkê i umieszczamy w niej Ÿród³o s

    q.clear(); 
    q.push_back(s);

// Zmienna esc umo¿liwia odpowiednie wychodzenie z
// dwóch zagnie¿d¿onych pêtli

    esc = 0;

// Rozpoczynamy pêtlê wyszukuj¹c¹ œcie¿ki BFS. Pêtla koñczy
// siê w przypadku braku dalszych wierzcho³ków w kolejce

    while(q.size())
    {

// Z pocz¹tku kolejki pobieramy element i usuwamy go z kolejki

      x = q.front(); q.pop_front();

// Sprawdzamy wszystkich s¹siadów wierzcho³ka x przegl¹daj¹c
// wiersz macierzy C[x][]

      for(y = 1; y <= n; y++)
      {

// Dla s¹siada y wyznaczamy przepustowoœæ residualn¹
// krawêdzi x->y. Jeœli krawêdŸ nie istnieje w sieci,
// to otrzymamy w cp wynik zero

        cp = C[x][y] - F[x][y];

// Sprawdzamy, czy krawêdŸ istnieje oraz, czy wierzcho³ek
// y nie by³ ju¿ wczeœniej wybrany przez BFS. W takim
// przypadku p[y] ma wartoœæ ró¿n¹ od zera.

        if(cp && !p[y])
        {

// W p[y] zapamiêtujemy, i¿ poprzednikiem y jest x

          p[y] = x;

// Dla wierzcho³ka y obliczamy dotychczasow¹ przepustowoœæ
// residualn¹ œcie¿ki. Jest to mniejsza wartoœæ z przepustowoœci
// œcie¿ki dla poprzednika x i bie¿¹cej przepustowoœci
// residualnej krawêdzi x->y.

          cfp[y] = cfp[x] > cp ? cp : cfp[x];

// Jeœli osi¹gnêliœmy ujœcie, to œcie¿ka jest kompletna

          if(y == t)
          {

// Zwiêkszamy przep³yw maksymalny o przepustowoœæ residualn¹
// œcie¿ki - wykorzystujemy tablicê cfp[]

             fmax += cfp[t];

// Idziemy wstecz po œcie¿ce zwiêkszaj¹c przep³ywy
// wzd³u¿ jej krawêdzi w kierunku zgodnym ze œcie¿k¹
// oraz zmniejszaj¹c przep³ywy w kierunku przeciwnym

             while(y != s)
             {
               x = p[y];
               F[x][y] += cfp[t];
               F[y][x] -= cfp[t];
               y = x;
             } //koniec while(y != s)

// Ustawiamy esc na 1, co spowoduje wyjœcie z obu pêtli

             esc = 1; break;

          } //koniec if(y == t)

// Jeœli wierzcho³ek y nie jest ujœciem t, to dopisujemy
// go na koñcu kolejki q i kontynuujemy pêtlê BFS

          q.push_back(y);

        } //koniec if(cp && !p[y])

      } // koniec for(y = 1; y <= n; y++)

// Tutaj wychodzimy z pêtli while(q.size()), jeœli
// zosta³a znaleziona œcie¿ka rozszerzaj¹ca

      if(esc) break;

    } //koniec while(q.size())

// Jeœli nie znaleziono œcie¿ki rozszerzaj¹cej, to esc = 0
// i w tym miejscu nast¹pi wyjœcie z g³ównej pêtli do

    if(!esc) break;

  } while(true);

// Prezentujemy wyniki obliczeñ. Najpierw wypisujemy
// wartoœæ maksymalnego przep³ywu

  cout << "\nfmax = " << fmax << endl << endl;

  for(x = 1; x <= n; x++)
    for(y = 1; y <= n; y++)
      if(C[x][y])
        cout << x << " -> " << y << " "
             << F[x][y] << "/" << C[x][y] << endl;

  cout << endl;
  system("PAUSE");
}
