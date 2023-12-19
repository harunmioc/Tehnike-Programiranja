// TP 2022/2023: Zadaća 3, Zadatak 5
#include <cmath>
#include <iostream>
#include <list>

struct Cvor {
  int redni_broj;
  Cvor *sljedeci;
};

int Poglavica(int brojPunoljetnih, int korak, bool ispis = false) {
    if(korak<=0 || brojPunoljetnih<1) return 0;

  Cvor *pocetak = nullptr;
  Cvor *prethodni = nullptr;


  // kreiranje liste
  for (int i = 1; i <= brojPunoljetnih; i++) {
    Cvor *novi = new Cvor{i, nullptr};

    if (pocetak == nullptr)
      pocetak = novi;
    else
      prethodni->sljedeci = novi;
    prethodni = novi;
  }

  prethodni->sljedeci = pocetak;
  int brojElemenata = brojPunoljetnih;
  int brojac = 0;

  Cvor *trenutni = pocetak;
  Cvor *prethodniTrenutnog = nullptr;

  while (brojElemenata > 1) {
    brojac++;
    if (brojac == korak) {
      brojac = 0;
      if (ispis)
        std::cout << trenutni->redni_broj << ", ";

      if (prethodniTrenutnog == nullptr)
        pocetak = trenutni->sljedeci;
      else
        prethodniTrenutnog->sljedeci = trenutni->sljedeci;

      Cvor *zaBrisanje = trenutni;
      trenutni = trenutni->sljedeci;
      delete zaBrisanje;
      brojElemenata--;

    } else {
      prethodniTrenutnog = trenutni;
      trenutni = trenutni->sljedeci;
    }
  }

  int poglavica = trenutni->redni_broj;
  delete trenutni;
  prethodniTrenutnog=nullptr;
  delete prethodniTrenutnog;
  return poglavica;
}

int SigurnoMjesto(int korak, int N1, int N2) {
    if(N2<N1) return 0;
  if (korak <= 0) return 0;
  std::list<int> lista{};
  for (int i = N1; i <= N2; i++)
    lista.push_back(i);

  for (int i = N1; i <= N2; i++) {
    int poglavica = Poglavica(i, korak);
    auto it = lista.begin();

    while (it != lista.end()) {
      if (*it == poglavica && *it > 0) {
        it = lista.erase(it);
        break;
      } else
        it++;
    }
  }
  if (lista.size() > 0) {
    auto it = lista.begin();
    while (it != lista.end()){
      if (*it >= 0)
        return *it;
    it++;
    }
  }
  return 0;
}

int main() {
  int brojPunoljetnih, korak, N1, N2;

  std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena "
               "Wabambe: ";
  std::cin >> brojPunoljetnih;
  std::cout << "Unesite korak razbrajanja: ";
  std::cin >> korak;
  std::cout << " Unesite raspon za odabir (N1 i N2): ";
  std::cin >> N1 >> N2;
  std::cout << "Redni broj osobe koja postaje poglavica: "
            << Poglavica(brojPunoljetnih, korak);
  int mjesto = SigurnoMjesto(korak, N1, N2);
  if (mjesto == 0)
    std::cout << "\nZao mi je Mbebe Mgogo, ali nema sigurnog mjesta.";
  else
    std::cout << "\nMbebe Mgogo, stani na sigurno mjesto " << mjesto
              << " da ne bi bio poglavica!";

  return 0;
}
