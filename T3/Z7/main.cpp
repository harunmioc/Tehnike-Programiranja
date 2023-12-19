// TP 2022/2023: LV 3, Zadatak 7
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>

typedef std::vector<std::vector<int>> Matrica;

int Duzina(int br) {
  int brojac = 0;

  if (br == 0) {
    return brojac = 1;
  }

  while (br != 0) {
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

      if (sirina > MAXsirina) {
        MAXsirina = sirina;
      }
    }
  }

  return MAXsirina;
}

Matrica PascalovTrougao(int n) {

    if(n==0){
        Matrica mat;
        return mat;
    }

    if(n<0){
        throw std::domain_error("Broj redova ne smije biti negativan");
    }

                                    //Pravlljenje grbave matrice 
  Matrica mat;
  mat.resize(n);
  for (int i = 0; i < n; i++) {
    mat[i].resize(i + 1);
  }

  for (int i = 0; i < n; i++) {
    int k = i + 1;
    for (int j = 0; j < k; j++) {

      if (j == 0) {
        mat[i][j] = 1;
      }

      else if (j == k - 1) {
        mat[i][j] = 1;
      }

      else {
        mat[i][j] = mat[i - 1][j] + mat[i - 1][j - 1];
      }
    }
  }

  return mat;
}

int main() {
  int n;

  std::cout << "Unesite broj redova: ";
  std::cin >> n;
try{
  Matrica mat = PascalovTrougao(n);

  int sirina = NajvecaSirina(mat);

  for (int i = 0; i < n; i++) {
    int k = i+1;
    for (int j = 0; j < k; j++) {
      std::cout << std::right << std::setw(sirina + 1) << mat[i][j];
    }
    std::cout << "\n";
  }
}

catch(std::domain_error izuzetak){
    std::cout<<izuzetak.what()<<std::endl;
}

  return 0;
}
