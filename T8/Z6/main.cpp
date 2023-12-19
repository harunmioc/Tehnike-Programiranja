// TP 2022/2023: LV 8, Zadatak 6
#include <cmath>
#include <iostream>

template <typename TipElemenata> struct Cvor {
  TipElemenata element;
  Cvor<TipElemenata> *veza;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni) {
  TipElemenata unos;
  Cvor<TipElemenata> *pocetak = nullptr;
  Cvor<TipElemenata> *prethodni = nullptr;
  while (1) {
    std::cin >> unos;
    if (unos == zavrsni)
      break;

    Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{unos, nullptr};
    if (pocetak == nullptr)
      pocetak = novi;
    else
      prethodni->veza = novi;
    prethodni = novi;
  }
  return pocetak;
}

template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak) {
  int brojac = 0;
  while (pocetak != nullptr) {
    brojac++;
    pocetak = pocetak->veza;
  }
  return brojac;
}

template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak) {
  TipElemenata suma{};

  while (pocetak != nullptr) {
    suma += pocetak->element;
    pocetak = pocetak->veza;
  }
  return suma;
}

template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag) {
  int brojac = 0;

  while (pocetak != nullptr) {
    if (pocetak->element > prag)
      brojac++;
    pocetak = pocetak->veza;
  }
  return brojac;
}

template <typename TipElemenata> void UnistiListu(Cvor<TipElemenata> *pocetak) {
  while (pocetak != nullptr) {
    Cvor<TipElemenata> *naredni = pocetak->veza;
    delete pocetak;
    pocetak = naredni;
  }
}

int main() {
  double broj;

  std::cout << "Unesite slijed brojeva (0 za kraj): ";

  Cvor<double> *pocetak = KreirajPovezanuListu(0.);

  int brojac =
      BrojVecihOd(pocetak, SumaElemenata(pocetak) / BrojElemenata(pocetak));

  UnistiListu(pocetak);

  std::cout << "\nU slijedu ima " << brojac
            << " brojeva vecih od njihove aritmeticke sredine";

  return 0;
}
