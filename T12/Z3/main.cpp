// TP 2022/2023: LV 12, Zadatak 3

#include <iostream>
#include <ostream>
enum Dani { Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja };

Dani &operator++(Dani &dani) {
     return dani = Dani( (int(dani) + 1) % 7) ; }

Dani operator++(Dani &dani, int) {
  Dani pom(dani);
  ++dani;
  return pom;
}
std::ostream &operator<<(std::ostream &tok, const Dani &dani) {
  std::string naziv[] = {"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak",
                         "Petak", "Subota", "Nedjelja"};
  return tok << naziv[(dani)];
}
int main() {
  for (Dani d = Ponedjeljak; d <= Petak; d++)
    std::cout << d << std::endl;
  for (Dani i = Ponedjeljak; i <= Nedjelja; i++) {
    std::cout << i << std::endl;
    if (i == Nedjelja)
      break;
  }
  return 0;
}
