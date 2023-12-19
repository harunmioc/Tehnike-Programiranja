// TP 2022/2023: Zadaća 1, Zadatak 4
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string Cenzura(std::string s, std::vector<std::string> cenzurisane) {

  for (int i = 0; i < cenzurisane.size(); i++) {
    std::string rijec = cenzurisane.at(i);
    for (int j = 0; j < rijec.length(); j++) {
      if ((rijec.at(j) >= 'A') && (rijec.at(j) <= 'Z')) {
        rijec.at(j) += 32;
      }

      if (!((rijec.at(j) >= 'A') && (rijec.at(j) <= 'Z')) &&
          !((rijec.at(j) >= 'a') && (rijec.at(j) <= 'z')) &&
          !((rijec.at(j) >= '0') && (rijec.at(j) <= '9'))) {
        throw std::logic_error("Neispravna riječ");
      }
    }

    cenzurisane.at(i) = rijec;
  }

  int pocetakRijeci = 0;
  int duzinaStringa = s.length();
  for (int i = 0; i < duzinaStringa; i++) {
    std::string rijec;

    if (s.at(i) != ' ') {
      pocetakRijeci = i;
      while (i < duzinaStringa && ((s.at(i) >= 'A' && s.at(i) <= 'Z') ||
                                   (s.at(i) >= 'a' && s.at(i) <= 'z'))) {
        if ((s.at(i) >= 'A') && (s.at(i) <= 'Z')) {
          rijec.push_back(s.at(i) + 32);
        } else {
          rijec.push_back(s.at(i));
        }
        i++;
      }
    }
    for (std::string x : cenzurisane) {

      if (rijec == x) {
        for (int k = pocetakRijeci; k < i; k++) {
          s.at(k) = '*';
        }
      }
    }
  }

  return s;
}

int main() {

  std::cout << "Unesite recenicu: ";
  std::string s1;
  std::getline(std::cin, s1);
  try {
    std::cout << "\nUnesite zabranjene rijeci (. za kraj): ";

    std::string string;

    std::vector<std::string> cenzurisane;
    while (1) {
      std::cin >> string;

      if (string == ".") {
        break;
      }

      for (int i = 0; i < string.length(); i++) {
        if (!((string.at(i) >= 'A') && (string.at(i) <= 'Z')) &&
            !((string.at(i) >= 'a') && (string.at(i) <= 'z')) &&
            !((string.at(i) >= '0') && (string.at(i) <= '9'))) {
          std::cout << "\nGRESKA: Nelegalne zabranjene rijeci!";
          return 0;
        }
      }

      /*   for(int i=0;i<string.length();i++){
             if ((string.at(i) >= 'A') && (string.at(i) <= 'Z')) {
               string.at(i)+=32;
             }
         }*/
      cenzurisane.push_back(string);
    }

    std::string CenzurisanaRecenica = Cenzura(s1, cenzurisane);

    std::cout << "Cenzurisana recenica: " << CenzurisanaRecenica;
  } catch (std::logic_error izuzetak) {
    std::cout << izuzetak.what() << std::endl;
  }
  return 0;
}
