// TP 2022/2023: LV 8, Zadatak 1
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

struct Vrijeme {
  int sati, minute, sekunde;
};

void TestirajVrijeme(Vrijeme vrijeme) {

  if ((vrijeme.sati < 0 || vrijeme.sati > 23) ||
      (vrijeme.minute < 0 || vrijeme.minute > 59) ||
      (vrijeme.sekunde < 0 || vrijeme.sekunde > 59)) {
    throw std::domain_error("Neispravno vrijeme");
  }
}

void IspisiVrijeme(Vrijeme vrijeme) {
  try {
    TestirajVrijeme(vrijeme);
    std::cout << std::setw(2) <<std::setfill('0')<< vrijeme.sati << ":" << std::setw(2)<<vrijeme.minute << ":"
              << std::setw(2)<<vrijeme.sekunde;
  } catch (std::domain_error) {
    throw std::domain_error("Neispravno vrijeme");
  }
}

Vrijeme SaberiVrijeme(Vrijeme vrijeme1, Vrijeme vrijeme2) {
  Vrijeme vrijeme3{0, 0, 0};
  try {
    TestirajVrijeme(vrijeme1);
    TestirajVrijeme(vrijeme2);

    int temp = 0;

    temp = vrijeme3.sekunde = vrijeme1.sekunde + vrijeme2.sekunde;
    temp /= 60;
    vrijeme3.sekunde -= 60 * temp;
    vrijeme3.minute += temp;

    temp = vrijeme3.minute += vrijeme1.minute + vrijeme2.minute;
    temp /= 60;
    vrijeme3.minute -= 60 * temp;
    vrijeme3.sati += temp;

    temp = vrijeme3.sati += vrijeme1.sati + vrijeme2.sati;
    temp /= 24;
    vrijeme3.sati -= 24 * temp;

  } catch (std::domain_error) {
    throw std::domain_error("Neispravno vrijeme");
  }
  return vrijeme3;
}

int main() {
  Vrijeme vrijeme1, vrijeme2;
  try {
    std::cout << "Unesite prvo vrijeme (h m s): ";
    std::cin >> vrijeme1.sati >> vrijeme1.minute >> vrijeme1.sekunde;

    TestirajVrijeme(vrijeme1);

    std::cout << "\nUnesite drugo vrijeme (h m s): ";
    std::cin >> vrijeme2.sati >> vrijeme2.minute >> vrijeme2.sekunde;

    TestirajVrijeme(vrijeme2);

    std::cout << "\nPrvo vrijeme: ";
    IspisiVrijeme(vrijeme1);

    std::cout << "\nDrugo vrijeme: ";
    IspisiVrijeme(vrijeme2);

    std::cout << "\nZbir vremena: ";
    IspisiVrijeme(SaberiVrijeme(vrijeme1, vrijeme2));
  }

  catch (std::domain_error izuzetak) {
    std::cout << izuzetak.what();
  }

  return 0;
}
