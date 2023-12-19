// TP 2022/2023: Zadaća 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <vector>

bool DaLiJeProst(int a) {
  if (a <= 1) {
    return false;
  }
  if (a <= 3) {
    return true;
  }
  if (a % 2 == 0 || a % 3 == 0) {
    return false;
  }

  for (int i = 5; i <= std::floor(std::sqrt(a)); i += 6) {
    if (a % i == 0 || a % (i + 2) == 0)
      return false;
  }
  return true;
}

void RastavaBroja(int broj, int &p, int &q) {
  int br = broj;
  p = 1;
  q = 1;
  if (broj < 0)
    p *= -1;

  broj = std::abs(broj);

  if (broj == 0)
    p = 0;

  int BROJ = 0;
  int tempBR = broj;

    if(DaLiJeProst(broj)){
        p=br;
        q=1;
    }
    
else{


  for (int i = 2; i <= broj; i++) {

    /* if (DaLiJeProst(tempBR)) {
       p *= tempBR;
       break;
     }
     */

    if (DaLiJeProst(i) && tempBR % i == 0) {

      int j = i;
      int brojac = 0;

      while (tempBR % j == 0) {
        tempBR = tempBR / j;
        brojac++;
      }
      if (brojac > 0) {
        // svrstavanje u p i q
        if (brojac > 0 && brojac % 2 == 0) {
          for (int k = 1; k <= brojac; k++) {
            q *= j;
          }
        } else {
          for (int k = 1; k <= brojac - 1; k++) {
            q *= j;
          }
          p *= j;
        }
      }
      BROJ = p * q;
      if (BROJ == br) {
        break;
      }
    }
    if (i == broj)
      break;
  }
}


}

int main() {
  long long int broj;
  std::cout << "Unesi broj:";
  std::cin >> broj;

  int p = 1, q = 1;

  RastavaBroja(broj, p, q);

  std::cout << "\n" << broj << " = " << p << "*" << std::sqrt(q) << "^2";
  return 0;
}