// TP 2022/2023: Zadaća 3, Zadatak 6
#include <cmath>
#include <iostream>
#include <list>
#include <memory>

struct Cvor {
  int redni_broj;
  std::shared_ptr<Cvor> sljedeci;
};

int Poglavica(int brPunoljetnih, int korak, bool ispis = false) {
    if(korak<=0 || brPunoljetnih<1) return 0;
  std::shared_ptr<Cvor> pocetak = nullptr;
  std::shared_ptr<Cvor> prethodni = nullptr;

  for (int i = 1; i <= brPunoljetnih; i++) {
    std::shared_ptr<Cvor> novi = std::make_shared<Cvor>();
    novi->redni_broj = i;
    novi->sljedeci = nullptr;

    if (pocetak == nullptr)
      pocetak = novi;
    else
      prethodni->sljedeci = novi;
    prethodni = novi;
  }

  prethodni->sljedeci = pocetak;
  int brojElemenata = brPunoljetnih;
  int brojac = 0;

  std::shared_ptr<Cvor> trenutni = pocetak;
  std::shared_ptr<Cvor> prethodniTrenutnog = nullptr;

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

      trenutni = trenutni->sljedeci;
      brojElemenata--;
    } else {
      prethodniTrenutnog = trenutni;
      trenutni = trenutni->sljedeci;
    }
  }
  int poglavica = trenutni->redni_broj;
  trenutni->sljedeci = nullptr;
  return poglavica;
}

int SigurnoMjesto(int korak, int N1, int N2) {
    if(N2<N1) return 0;
  if (korak <= 0)
    return 0;

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
    while (it != lista.end()) {
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
  std::cout << "Unesite raspon za odabir (N1 i N2): ";
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
