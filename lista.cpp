#include <iostream> //dostep do cin cout
using namespace std;

// deklaracja elementu
class Element 
{
  public:              //class domyslnie wszystko jest private
  Element * nastepny;  //wskaznik na nastepny element
  int wartosc;         // wartosc ktora chcemy zapisac
};

// deklaracja listy
class Lista
{
  private:                         //class domyslnie wszystko jest private
    Element * poczatek, * koniec;  //wskaznik na pierwszy i ostatni element

  public:  
    int licznik;                 //liczba elementow       
    Lista() // konstruktor       //uzupelnienie wartosciami poczatkowymi
    {                            //pusta lista
      poczatek = koniec = NULL;  //poczatkowy=koncowy elem na liscie
      licznik  = 0;              //brak elementow
    }
    ~Lista() // destruktor        //zwolnienie zasobów zajetych przez klasę
    {
      Element * adres;               //adres nastepnego elementu
      while(poczatek)                //usuwanie wszystkich elementow listy
      {    
                                     // -> umożliwia dostęp do elementów w strukturach
        adres = poczatek->nastepny;  //zapamietanie adresu nastepnego elementu
       delete poczatek;            //usuwanie tylko pierwszego elementu
        poczatek = adres;            //poczatek ma nowy adres
      }              
    }

// Dodaje element na początku i zwraca jego adres
    Element * dodaj_poczatek(Element * nowyel)   //wstawia nowyel na poczatek listy
    {
      nowyel->nastepny = poczatek;              //wskaznik nowyel(tu) ustawiony na pierwszy elem
      poczatek = nowyel;                        //nowyel staje sie pierwszym elem
      if(!koniec) koniec = poczatek;            //jesli lista pusta to wstawia pierwszy elem
      licznik++;                                //zwiekszamy liczbe elementow o 1
      return poczatek;                          //zwraca adres wstawionego elementu
    }
    
// Dodaje element na końcu i zwraca jego adres
    Element * dodaj_koniec(Element * nowyel)   //wstawia nowyel na koniec listy
    {
      if(koniec) koniec->nastepny = nowyel;    //jesli sa elem to teraz wskazuje na nowyel
      nowyel->nastepny = NULL;                 //wskaznik nowyel wskazuje NULL/brak dalszych
      koniec = nowyel;                         //nowyel staje sie ostatnim
      if(!poczatek) poczatek = koniec;         //jesli pusto to nowyel to poczatek=koniec
      licznik++;                               //zwiekszamy liczbe elementow o 1
      return koniec;                           //zwraca adres wstawionego elementu
    }
    
// Dodaje element w srodku i zwraca jego adres
    Element * dodaj_srodek(Element * el1, Element * el2) //wstawia el1 w srodek listy(za)
    {
      el1->nastepny = el2->nastepny;                     //nastepny(pnik) el2 staje sie nastepnym el1
      el2->nastepny = el1;                               //nastepny el2 to teraz el1
      if(!(el1->nastepny)) koniec = el1;                 //jesli nastepny nie istnieje to el1 to teraz koniec
      licznik++;                                         //zwiekszamy liczbe elementow o 1
      return el1;                                        //zwraca adres wstawionego elementu
    }
    
// Usuwa element z początku i zwraca adres usuniętego elem
    Element * usun_poczatek()             //usuwa z poczatku listy /odlacza element ktory tkwi w przestworzach pamieci
    {
      Element * adres;                    //wskaznik na adres
      if(poczatek)                        //czy ma elementy
      {
        adres = poczatek;                 //adres poczatek elem
        poczatek = poczatek->nastepny;    //w poczatku umieszczony adres nastepnego elem
        if(!poczatek) koniec = NULL;      //czy zostaly jakies elementy
        licznik--;                        //zmniejszamy liczbe elementow o 1
        return adres;                     //zwraca adres usunietego elementu
      }
      else return NULL;                   //nie zawiera zadnych elementow
    }
    
// Usuwa element z końca i zwraca adres usuniętego elem
    Element * usun_koniec()                  //usuwa z konca listy
    {
      Element * adres;
      if(koniec)                             //czy ma elementy
      {
        adres = koniec;                      //adres ostatniego elem
        if(adres == poczatek)                //lista jednoelementowa?
        poczatek = koniec = NULL;            //lista pusta
        else
        {
          koniec = poczatek;                 //koniec staje sie poczatkiem
          while(koniec->nastepny != adres)   //dopuki sa inne elementy
          koniec = koniec->nastepny;         //wskazuje na nastepny potencjalny element
          koniec->nastepny = NULL;           //zerowanie nastepny(nik)
        }
        licznik--;                           //zmniejszamy liczbe elementow o 1
        return adres;                        //zwraca adres usunietego elementu
      }
      else return NULL;                      //nie zawiera zadnych elementow
    }
    
// usuwa wybrany element i zwraca adres usuniętego elem
    Element * usun_srodek(Element * usuwany)              ////usuwa ze srodka listy /stary adres
    {
      Element * adres;                          
      if(usuwany == poczatek)                     //czy jest pierwszym na liscie
      return usun_poczatek();                     //wywolanie funkcji gdy jest pierwszym elem
      else
      {
        adres = poczatek;                        //adres ustawiamy na poczatek
        while(adres->nastepny != usuwany)        //dopuki adres jest rozny od adresu usuwanego
        adres = adres->nastepny;                 //adres to teraz nastepny adres
        adres->nastepny = usuwany->nastepny;     //nastepny znalezionego adresu to nastepny usuwanego
        if(!(adres->nastepny))                   //czy nowy adres jest ostatnim elementem
        koniec = adres;                          //zapisuje adres jako koniec
        licznik--;                               //zmniejszamy liczbe elementow o 1
        return usuwany;                          //zwraca adres usunietego elementu
      }
    } 

// zwraca wybrany element listy, jeśli lista ma mniej elem niz n, to NULL
    Element * miejsce(int x)  //wybrany element
    {
      Element * adres;                         //adres x elementu
      if((!x) || ( x > licznik)) return NULL;  //czy element znajduje sie na liscie jesli nie
      else if(x == licznik) return koniec;     //czy element jest ostatni jedyny
      else 
      {
        adres = poczatek;                     //adres ustawiamy na poczatek
        while(--x) adres = adres->nastepny;   //przechodzimy przez elementy az znajdziemy adres wybranego x
        return adres;                         // adres wybranego elementu
      }
    }

// wyświetla wszystkie elementy
    void wyswietl()
    {
      Element * p;
      if(!poczatek) cout <<endl<<endl<< "Lista jest pusta." << endl;
      else
      {
        p = poczatek;
        while(p)
        {
          cout << p->wartosc << " ";
          p = p->nastepny;
        }
        cout << endl;
      }
    }

// przesuwa element na początek i zwraca jego adres
    Element * na_poczatek(Element * przesuwany)  //wybrany element  
    {
      Element * adres;                          
      if(przesuwany == poczatek)                     //czy jest pierwszym na liscie
      return adres;                     //wywolanie funkcji gdy jest pierwszym elem
      else
      {
        adres = poczatek;                        //adres ustawiamy na poczatek
        while(adres->nastepny != przesuwany)        //dopuki adres jest rozny od adresu przesunietego
        adres = adres->nastepny;                 //adres to teraz nastepny adres
        adres->nastepny = przesuwany->nastepny;     //nastepny znalezionego adresu to nastepny przesuwany
        if(!(adres->nastepny))                   //czy nowy adres jest ostatnim elementem
        koniec = adres;                          //zapisuje adres jako koniec
        licznik--;                               //zmniejszamy liczbe elementow o 1
        dodaj_poczatek(przesuwany);             //dodaje element na poczatek 
        return adres;                          //zwraca adres przesunietego elementu
      }
    } 
};

//////////// Menu /////////////
void menu(Lista lista1, Element *p, int i)
{
  int ile;
  int ktory;
  int liczba;
    cout << "               Menu:"<<endl<<"0 - Wyswietl liste"<<endl<<"1 - Dodaj element na poczatek"<<endl<<"2 - Dodaj element w srodku"<<endl<<"3 - Dodaj element na koniec"<<endl<<"4 - Usun element z poczatku"<<endl<<"5 - Usun element ze srodka"<<endl<<"6 - Usun element z konca"<<endl<<"7 - Wyszukaj element z listy"<<endl<<"8 - Usun wszystkie elementy"<<endl<<"9 - Wyjdz"<<endl<<endl;
    cin >> liczba;
    switch( liczba )
{
  case 0:
   lista1.wyswietl();
   cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
   break;

   case 1:
// tworzymy elementy dodając je na początek listy
  cout<<endl<<"ile elementow chcesz dodac na poczatek listy"<<endl;
  cin>>ile;
  for(i = 1; i <= ile; i++)
  {
    p = new Element;
    p->wartosc = i;
    lista1.dodaj_poczatek(p);
  }

  cout << "Lista:  ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;

  case 3:
// tworzymy elementy dodając je na koniec listy
  cout<<endl<<"ile elementow chcesz dodac na poczatek listy"<<endl;
  cin>>ile;
  for(i = 1; i <= ile; i++)
  {
    p = new Element;
    p->wartosc = i;
    lista1.dodaj_koniec(p);
  }

  cout << "Lista:   ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;

case 4:
// usuwamy pierwszy element listy
  lista1.usun_poczatek();
  
  cout << "Lista:   ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;

  case 6:
// usuwamy ostatni element listy

  lista1.usun_koniec();
  
  cout << "Lista:  ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;
 
 case 5:
// usuwamy element z listy
cout<<endl<<"Ktory element chcesz usunac"<<endl;
cin>>ktory;
  delete lista1.usun_srodek(lista1.miejsce(ktory));
  
  cout << "Lista:  ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;

  case 2:
// Za elementem listy wstawiamy nowy element
  cout<<endl<<"Za ktorym elementem chcesz dodac nowy"<<endl;
  cin>>ktory;
  cout<<endl<<"jaka wartosc ma miec element: "<<endl;
  cin>>ile;
  p = new Element;
  p->wartosc=ile;
  lista1.dodaj_srodek(p,lista1.miejsce(ktory));
  
  cout << "Lista:  ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;

case 8:
// usuwamy wszystkie elementy z listy
  while(lista1.licznik) lista1.usun_poczatek();
  lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
  menu(lista1, p, i);
  break;

case 7:
// wyszukujemy element z listy
cout<<endl<<"Ktory element z listy chcesz wyszukac"<<endl;
cin>>ktory;
 lista1.na_poczatek(lista1.miejsce(ktory));
  
  cout << "Lista:  ";   lista1.wyswietl();
  cout<<endl<<"Potrzebujesz cos jeszcze?"<<endl;
    menu(lista1, p, i);
  break;

  case 9:
  cout<<"Koniec"<<endl;
  break;

  default:
        cout<<endl<<"Ups, cos poszlo nie tak, sprobuj ponownie "<<endl;
         menu(lista1, p, i);
        break;
}
  
  cout << endl; 

}

int main()
{
  Lista    listap;
  Element * f;
  int zmienna;
 listap.wyswietl();
 menu(listap, f, zmienna);
  return 0;
}
