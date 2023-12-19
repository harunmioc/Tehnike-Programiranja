// TP 2022/2023: Zadaća 3, Zadatak 4
#include <cmath>
#include <iostream>
#include <list>

int Poglavica(int brojPunoljetnih, int korak, bool ispis = false) {
  std::list<int> lista{};
  for (int i = 1; i <= brojPunoljetnih; i++) {
    lista.push_back(i);
  }
  int brojElemenata = lista.size();
  int brojac = 1;
  auto it = lista.begin();
  //granicni uslovi
    if(korak==1){
        while(it!=lista.end())
            it++;
        return *it;
    }
    if(korak<=0 || brojPunoljetnih<1) return 0;

  while (brojElemenata > 1) {
    brojac++;
    if (brojac == korak) {
      brojac = 1;
      it++;
      if (it == lista.end())
        it = lista.begin();

    if (ispis)  
        std::cout << *it << ", ";

      it = lista.erase(it);
      if (it == lista.end())
        it = lista.begin();
      brojElemenata--;

    } else {
      it++;
      if (it == lista.end())
        it = lista.begin();
    }
  }
  return *it;
}

int SigurnoMjesto(int korak, int N1, int N2) {
    if(N2>N1) return 0;
    if(korak<=0) return 0;
  std::list<int> lista{};

  for (int i = N1; i <= N2; i++)
    lista.push_back(i);

  for (int i = N1; i <= N2; i++) {

    int poglavica = Poglavica(i, korak);
    auto it = lista.begin();

    while (it != lista.end()) {
      if (*it == poglavica && *it>0) {
        it = lista.erase(it);
        break;
      } else
        it++;
    }
  }
  if (lista.size() > 0){
      auto it=lista.begin();
      while(it!=lista.end()){
          if(*it>=0)
            return *it;
        it++;
      }
  }

  return 0;
}

int main() {
  int brPunoljetnih, korak, N1, N2;
  std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena "
               "Wabambe: ";
  std::cin >> brPunoljetnih;
  std::cout << "Unesite korak razbrajanja: ";
  std::cin >> korak;
  std::cout << "Unesite raspon za odabir (N1 i N2): ";
  std::cin >> N1 >> N2;
  std::cout << "Redni broj osobe koja postaje poglavica: "
            << Poglavica(brPunoljetnih, korak);
  int mjesto = SigurnoMjesto(korak, N1, N2);
  if (mjesto == 0)
    std::cout << "\nZao mi je Mbebe Mgogo, ali nema sigurnog mjesta.";
  else
    std::cout << "\nMbebe Mgogo, stani na sigurno mjesto " << mjesto
              << " da ne bi bio poglavica!";

  return 0;
}