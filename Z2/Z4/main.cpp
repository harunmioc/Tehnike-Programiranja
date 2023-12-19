// TP 2022/2023: Zadaća 2, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename TipVar> auto Product(std::vector<TipVar> vec) {
  TipVar product;
  product = 1;
  for (auto &element : vec) {
    product *= element;
  }
  return product;
}
template <typename TipVar>
bool Kriterij(std::vector<TipVar> x, std::vector<TipVar> y) {
  if (x.size() == 0 || y.size() == 0) {
    return false;
  }

  if (Product(x) == Product(y)) {
    return x < y;
  }
  return Product(x) <= Product(y);
}

template <typename TipVar>
void SortirajPoProizvoduRedova(std::vector<std::vector<TipVar>> &matrica) {
  std::sort(matrica.begin(), matrica.end(), Kriterij<TipVar>);
}

int main() {
  int broj, brojac = 0;
  std::vector<int> vec;
  std::vector<std::vector<int>> matrica;
  std::cout
      << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): ";
  int uslov = 0;
  for (;;) {

if(std::cin)
    std::cin >> broj;

    if (std::cin)
      uslov++;

    if (!std::cin && uslov == 0) {
      std::cin.clear();
      std::cin.ignore(100000, '\n');
      break;
    } else if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(100000, '\n');
      matrica.push_back(vec);
      vec = {};
      uslov = 0;
    }
    if (std::cin && uslov!=0)
      vec.push_back(broj);
  }

  SortirajPoProizvoduRedova(matrica);
  std::cout << "\nMatrica nakon sortiranja:\n";
  for (int i = 0; i < matrica.size(); i++) {
    for (int j = 0; j < matrica.at(i).size(); j++) {
      std::cout << matrica.at(i).at(j) << " ";
    }
    std::cout << "\n";
  }

  std::cout << "Unesite elemente sekvence koja se trazi (* za kraj reda): ";

  for (;;) {
    std::cin >> broj;

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
      break;
    }
    vec.push_back(broj);
  }

  auto p = std::lower_bound(matrica.begin(), matrica.end(), vec, Kriterij<int>);
  if (p != matrica.end() && *p == vec) {
    int redni = p - matrica.begin();
    std::cout << "Trazena sekvenca se nalazi u " << redni + 1
              << ". redu (nakon sortiranja)";
  } else {
    std::cout << "Trazena sekvenca se ne nalazi u matrici";
  }

  return 0;
}