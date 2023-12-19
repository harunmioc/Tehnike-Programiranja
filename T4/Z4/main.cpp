// TP 2022/2023: LV 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <string>

template <typename br> void UnosBroja(std::string s1, std::string s2, br &n) {

  for (;;) {
    std::cout << s1;

    if (!(std::cin >> n) || std::cin.peek() != '\n') {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << s2<<"\n";
    } else {
      break;
    }
  }
}

int main() {
  double baza;
  int eksp;
  UnosBroja("Unesite bazu: ", "\nNeispravan unos, pokusajte ponovo...", baza);
  std::cout<<"\n";
  UnosBroja("Unesite cjelobrojni eksponent: \n",
            "Neispravan unos, pokusajte ponovo...", eksp);

  std::cout<<"\n" << baza << " na " << eksp << " iznosi " << pow(baza, eksp);

  return 0;
}
