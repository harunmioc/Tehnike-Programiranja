// TP 2022/2023: LV 10, Zadatak 1
#include <cmath>
#include <iostream>
#include <stdexcept>

class StedniRacun {
  double stanje;

public:
  StedniRacun(double x = 0) {
    if (x < 0) {
      throw std::logic_error("Nedozvoljeno pocetno stanje");
    }
    stanje = x;
  }

  StedniRacun &Ulozi(const double &x) {
    if (x < 0 && std::abs(x) > stanje)
      throw std::logic_error("Transakcija odbijena");
    stanje += x;
    return *this;
  }
  
  StedniRacun &Podigni(const double &x) {
    if (x > stanje)
      throw std::logic_error("Transakcija odbijena");
    stanje -= x;
    return *this;
  }

  double DajStanje() const { return stanje; };

  StedniRacun &ObracunajKamatu(const double &x) {
    if (x < 0)
      throw std::logic_error("Nedozvoljena kamatna stopa");
    stanje += stanje * x / 100;
    return *this;
  }
};

int main() { return 0; }
