// TP 2022/2023: LV 3, Zadatak 6
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrica;

int Duzina(int br) {
  int brojac = 0;
    
    if(br==0){
        return brojac=1;
    }

  while (br !=  0) {
    br = br / 10;
    brojac++;
  }

  return brojac;
}

int NajvecaSirina(Matrica mat) {
  int sirina = 0, MAXsirina = 0;

  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[i].size(); j++) {

      sirina = Duzina(mat[i][j]);

      if (mat[i][j] < 0) {
        sirina += 1;
      }

      if (sirina > MAXsirina) {
        MAXsirina = sirina;
      }
    }
  }

  return MAXsirina;
}

Matrica KroneckerovProizvod(std::vector<int> v1, std::vector<int> v2) {
  int redovi = v1.size(), kolone = v2.size();

  Matrica mat(redovi, std::vector<int>(kolone));

  for (int i = 0; i < redovi; i++) {

    for (int j = 0; j < kolone; j++) {

      mat[i][j] = v1[i] * v2[j];
    }
  }

  return mat;
}

int main() {
  int n, m;

  std::cout << "Unesite broj elemenata prvog vektora: ";
  std::cin >> n;

  std::vector<int> v1;

  std::cout << "Unesite elemente prvog vektora: ";

  for (int i = 0; i < n; i++) {
    int br;
    std::cin >> br;
    v1.push_back(br);
  }

  std::cout << "Unesite broj elemenata drugog vektora: ";
  std::cin >> m;

  std::vector<int> v2;

  std::cout << "Unesite elemente drugog vektora: ";

  for (int i = 0; i < m; i++) {
    int br;
    std::cin >> br;
    v2.push_back(br);
  }

  Matrica mat = KroneckerovProizvod(v1, v2);

  int SirinaIspisa = NajvecaSirina(mat);

  std::cout << "\n";

  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[i].size(); j++) {
      std::cout << std::right << std::setw(SirinaIspisa+ 1) << mat[i][j];
    }
    std::cout << "\n";
  }

  return 0;
}
