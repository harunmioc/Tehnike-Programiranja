// TP 2022/2023: LV 5, Zadatak 2
#include <cmath>
#include <iostream>
#include <type_traits>

template <typename pok1, typename pok2>
pok2 RazmijeniBlokove(pok1 pocetak, pok1 iza_kraja, pok2 odrediste) {

  while (pocetak != iza_kraja) {
    auto temp = *pocetak;
    *pocetak = *odrediste;
    *odrediste = temp;
    pocetak++;
    odrediste++;
  }
 
  return odrediste;
}

int main() {
    
    int br1,niz[1000];

    std::cout<<"Unesite broj elemenata niza: ";
    std::cin>>br1;
    std::cout<<"\nUnesite elemente prvog niza: ";
int *p;
p=niz;
    for(int i=0;i<br1;i++){
        int broj;
        std::cin>>broj;
        *p=broj;
        p++;
    }

    std::cout<<"\nUnesite elemente drugog niza: ";
int niz2[1000];
p=niz2;

for(int i=0;i<br1;i++){
        int broj;
        std::cin>>broj;
        *p=broj;
        p++;
    }

RazmijeniBlokove(niz, niz+br1, niz2);
p=niz;
std::cout<<"Nakon razmjene blokova ovako izgledaju nizovi: \nPrvi niz:";
    for(int i=0;i<br1;i++){
        std::cout<<" "<<*p;
        p++;
    }
    
    std::cout<<"\nDrugi niz:";
    p=niz2;
    for(int i=0;i<br1;i++){
        std::cout<<" "<<*p;
        p++;
    }


  return 0;
}
