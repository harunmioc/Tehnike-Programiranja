// TP 2022/2023: Zadaća 1, Zadatak 1
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };

long long int MultiplikativniDigitalniKorijen(long long int broj, int baza) {
  long long int MDK = 9223372036854775807;
  int brojac = 0;

  if (broj < 0) {
    broj *= -1;
  }
  if (baza < 2) {
    throw std::domain_error("\nNeispravna baza");
  }
  if (broj == 0 && baza == 10) {
    return 0;
  }
  if (baza == 10) {
    while (MDK >= 10) {
      brojac = 0;
      while (broj != 0) {
        if (brojac == 0) {
          MDK = 1;
          brojac++;
        }
        MDK = MDK * (broj % baza);
        broj = broj / baza;
      }
      broj = MDK;
    }
    return MDK;
  }

  long long int ostatak = broj, rezultat = broj;
  int brojacZaOstatak = 0; // brojac sluzi da ostatak uzme MDK>=baza

  while (MDK >= baza) {
    if (brojacZaOstatak > 0) {
      ostatak = MDK;
    }

    MDK = 1;

    while (ostatak > 0) {
      rezultat = ostatak % baza;
      ostatak = ostatak / baza;
      MDK = MDK * rezultat;
    }

    brojacZaOstatak = 1;
  }
  return MDK;
}

std::array<std::vector<long long int>, 10>
RazvrstajBrojeve(std::vector<long long int> v, TretmanNegativnih x) {
  std::array<std::vector<long long int>, 10> mm;

  for (int i = 0; i < v.size(); i++) {
    if (x == TretmanNegativnih::IgnorirajZnak && v.at(i) < 0) {
      v.at(i) *= -1;
    } else if (x == TretmanNegativnih::Odbaci && v.at(i) < 0) {
      throw v.at(i);
    } else if (v.at(i) < 0) {
      throw std::domain_error(
          "Nije predvidjeno razvrstavanje negativnih brojeva");
    }
    int mdkBroja = MultiplikativniDigitalniKorijen(v.at(i), 10);
    mm.at(mdkBroja).push_back(v.at(i));
  }

  return mm;
}

int main() {

  std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
  std::vector<long long int> v;

  for (;;) {
    long long int a;
    std::cin >> a;
    if (a < 0) {
      std::cout << "Nije podrzano razvrstavanje negativnih brojeva!";
      return 0;
    }
    if (std::cin) {
      v.push_back(a);
    } else {
      break;
    }
  }

  std::cout << "\n";
  std::cout
      << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu:\n";
  try {
    std::array<std::vector<long long int>, 10> NIZ =
        RazvrstajBrojeve(v, TretmanNegativnih::IgnorirajZnak);
    for (int i = 0; i < 10; i++) {
      if (NIZ.at(i).size() != 0) {
        std::cout << i << ": ";
        for (int j = 0; j < NIZ.at(i).size(); j++) {
          std::cout << NIZ.at(i).at(j) << " ";
        }
        std::cout << "\n";
      } else {
        continue;
      }
    }
  } catch (const char poruka[]) {
    std::cout << poruka;
  } catch (std::domain_error izuzetak) {
    std::cout << izuzetak.what();
  } catch (long long int broj) {
  } catch (...) {
  }

  return 0;
}
