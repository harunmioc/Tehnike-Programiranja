// TP 2022/2023: LV 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <vector>

bool TestPerioda(std::vector<double> v, int period) {

  if (period == 0 || period >= v.size()) {
    return false;
  }

  for (int i = 0; i <= v.size() - period; i++) {
    if (v.size() > i + period) {

      if (v.at(i) != v.at(i + period)) {
        return false;
      }
    } else
      return true;
  }

  return true;
}

int OdrediOsnovniPeriod(std::vector<double> v) {

  for (int i = 1; i <= v.size() - 1; i++) {
    if (TestPerioda(v, i)) {
      return i;
    }
  }

  return 0;
}

int main() {
  std::vector<double> v;

  std::cout << "Unesite slijed brojeva (0 za kraj): ";

  double n;

  while (std::cin >> n) {
    if (n == 0) {
      break;
    }

    v.push_back(n);
  }

  if (OdrediOsnovniPeriod(v) == 0) {
    std::cout << "Slijed nije periodican!";
  } else {
    std::cout << "Slijed je periodican sa osnovnim periodom "
              << OdrediOsnovniPeriod(v) << ".";
  }

  return 0;
}
