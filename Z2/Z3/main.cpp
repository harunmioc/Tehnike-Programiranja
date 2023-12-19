// TP 2022/2023: Zadaća 2, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

std::string F(std::string a, std::string b) {
    return a + "+" + b;
}

std::string G(std::string a, std::string b) { return a + "*" + b; }

template <typename Tip, typename Tip2, typename fun1, typename fun2>
auto GeneraliziraniMatricniProizvod(std::vector<std::vector<Tip>> &mat1,
                                     std::vector<std::vector<Tip2>> &mat2,
                                    fun1 F, fun2 G){

  // bacanje errora

  if (mat1.at(0).size() != mat2.size()) {
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }

  for (int i = 1; i < mat1.size(); i++) {
    if (mat1.at(0).size() != mat1.at(i).size())
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }

  for (int i = 1; i < mat2.size(); i++) {
    if (mat2.at(0).size() != mat2.at(i).size())
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }

  // konstrukcija rezultantne matrice
  Tip a=Tip();
  Tip2 b=Tip2();

  //slucaj za prazne mat
if (mat1.size() == 0 || mat1.at(0).size() == 0 || mat2.size() == 0 ||
      mat2.at(0).size() == 0) {
            std::vector<std::vector<std::remove_reference_t<decltype(G(a, b))>>> rezultantnaMat2(
            mat1.size(), std::vector<std::remove_reference_t<decltype(G(a, b)) >> ({}) ) ;

    return rezultantnaMat2;
  }

  //ostale
  std::vector<std::vector<std::remove_reference_t<decltype(G(a, b))>>> rezultantnaMat( mat1.size(),
                                    std::vector<std::remove_reference_t<decltype(G(a, b))>> (mat2.at(0).size()));

  

  for (int i = 0; i < mat1.size(); i++) {         // kretanje po mat1
    for (int j = 0; j < mat2.at(0).size(); j++) { // kretanje po mat2
      for (int k = 0; k < mat2.size(); k++) {
        try {
          auto rezultat = G(mat1.at(i).at(k), mat2.at(k).at(j));
          if (k == 0) {
            rezultantnaMat.at(i).at(j) = rezultat;
          } else {
            rezultantnaMat.at(i).at(j) = F(rezultantnaMat.at(i).at(j), rezultat);
          }
        } catch (...) {
          throw std::runtime_error("Neocekivani problemi pri racunanju");
        }
      }
    }
  }

  return rezultantnaMat;
}

int main() {
  int red1, KolRed, kol2;

  std::cout << "\nUnesite broj redova prve matrice: ";
  std::cin >> red1;
  std::cout << "Unesite broj kolona prve matrice, ujedno broj redova druge "
               "matrice: ";
  std::cin >> KolRed;
  std::cout << "Unesite broj kolona druge matrice: ";
  std::cin >> kol2;

  std::vector<std::vector<std::string>> mat1(red1,
                                             std::vector<std::string>(KolRed));
  std::vector<std::vector<std::string>> mat2(KolRed,
                                             std::vector<std::string>(kol2));

  std::cout << "\nUnesite elemente prve matrice: ";
  for (int i = 0; i < red1; i++) {
    for (int j = 0; j < KolRed; j++) {
      std::cin >> mat1.at(i).at(j);
    }
  }

  std::cout << "\nUnesite elemente druge matrice: ";
  for (int i = 0; i < KolRed; i++) {
    for (int j = 0; j < kol2; j++) {
      std::cin >> mat2.at(i).at(j);
    }
  }

  auto pokF = F;
  auto pokG = G;
  try {

    auto mat = GeneraliziraniMatricniProizvod(mat1, mat2, pokF, pokG);
    int duzina = 0;
    for (int i = 0; i < red1; i++) {
      for (int j = 0; j < kol2; j++) {
        int temp = mat.at(i).at(j).length();
        if (temp > duzina)
          duzina = temp;
      }
    }
    std::cout << "\n\nMatricni proizvod:\n";
    for (int i = 0; i < red1; i++) {
      for (int j = 0; j < kol2; j++) {
        std::cout << std::left << std::setw(duzina + 2) << mat.at(i).at(j);
      }
      std::cout << "\n";
    }

  } catch (std::domain_error izuzetak) {
    std::cout << izuzetak.what() << "\n";
  } catch (std::runtime_error izuzetak) {
    std::cout << izuzetak.what() << "\n";
  }

  return 0;
}
