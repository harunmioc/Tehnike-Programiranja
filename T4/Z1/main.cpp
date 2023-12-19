// TP 2022/2023: LV 4, Zadatak 1
#include <cmath>
#include <iostream>

int Cifre(long long int n, int &c_min, int &c_max) {

  int brojac = 0;
  int cifra = n % 10;
     c_min = abs(cifra);
    c_max = abs(cifra);

  if(n==0){return 1;}
  
  while (n != 0) {
    cifra = n % 10;
    if (abs(cifra) < c_min)
      c_min = abs(cifra);
    if (abs(cifra) > c_max)
      c_max = abs(cifra);
    n /= 10;
    brojac++;
  }

  return brojac;
}

int main() {
  long long int n;
  std::cout << "Unesite broj: ";
  std::cin >> n;

  int min, max, broj = Cifre(n, min, max);

  std::cout << "Broj " << n << " ima " << broj << " cifara, najveca je " << max
            << " a najmanja " << min << ".";
  return 0;
}
