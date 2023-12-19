// TP 2022/2023: LV 12, Zadatak 5

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::cout << "Koliko zelite elemenata: ";
  int n;
  std::cin >> n;
  std::cout << "Unesite elemente: ";
  std::vector<double> v(n);
  for (double &pom : v)
    std::cin >> pom;

  std::transform(v.begin(), v.end(), v.begin(),
                 std::bind(std::divides<double>(), 1, std::placeholders::_1));
                 
  std::cout << "Transformirani elementi: ";
  for (int i = 0; i < n; i++)
    std::cout << v.at(i) << " ";
  return 0;
}

