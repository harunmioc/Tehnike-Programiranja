// TP 2022/2023: Zadaća 1, Zadatak 2
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef std::vector<std::vector<double>> Matrica;

Matrica KreirajMatricu(int red, int kolona) {
  return std::vector<std::vector<double>> (red,std::vector<double>(kolona));
}

Matrica UsrednjavajuciFilter(Matrica mat, int RED_N) {

  if (RED_N < 0) {
    throw std::domain_error("Neispravan red filtriranja");
  }

  int brojRedova = mat.size();

  Matrica FiltriranaMatrica = KreirajMatricu(brojRedova, 0);
  double suma = 0;
  int k = RED_N, brojac = 0;

  for (int i = 0; i < brojRedova; i++) {
    int brojKolona = mat.at(i).size();

    for (int j = 0; j < brojKolona; j++) {

      for (int kretacRED = i - k; kretacRED <= i+k; kretacRED++) {
        // kretanje po redovimam matrice N reda
        if (kretacRED < 0 || kretacRED >= brojRedova){continue;}  
        int brojKolona2=mat.at(kretacRED).size();                        //iskljucuje redove koji nisu u opsegu
          for (int kretacKOLONA = j - k; kretacKOLONA <= j+k; kretacKOLONA++) {
            // kretanje po kolonama matrice N reda
            if(kretacKOLONA<0 || kretacKOLONA>=brojKolona2){continue;}
                suma += mat.at(kretacRED).at(kretacKOLONA);
                brojac++;
        }
      }
      double rezultat = suma / double(brojac);
      FiltriranaMatrica.at(i).push_back(rezultat);
      brojac = 0;
      suma = 0;
    }
  }
  /**
for (int i = 0; i < brojRedova; i++) {
  int brojKolona = mat.at(i).size();

  for (int j = 0; j < brojKolona; j++) {

    double suma = 0;
    int brojac = 0, brojacReda = 0;
//lijevo od broja
    for (int lijevo = j; lijevo >= 0; lijevo--) {
      if (brojacReda == RED_N + 1) {
        break;
      }
      suma += mat.at(i).at(lijevo);
      brojac++;
      brojacReda++;
    }

    brojacReda = 0;
//desno od broja
    for (int desno = j; desno < mat.at(i).size(); desno++) {
      if (brojacReda == RED_N + 1) {
        break;
      }
      suma += mat.at(i).at(desno);
      brojac++;
      brojacReda++;
    }

    brojacReda = 0;
//gore od broja
    for (int gore = i; gore >= 0; gore--) {
      if (brojacReda == RED_N + 1) {
        break;
      }
      suma += mat.at(gore).at(j);
      brojac++;
      brojacReda++;
    }

    brojacReda = 0;
//dolje od broja
    for (int dolje = i; dolje < mat.size(); dolje++) {
      if (brojacReda == RED_N + 1) {
        break;
      }
      suma += mat.at(dolje).at(j);
      brojac++;
      brojacReda++;
    }

//gore desno od broja
int k=1;
while(k<=RED_N){
  if(( i-k>0 && i-k<mat.size() )  &&  (j+k>0 && j+k<mat.at(i).size()) ){
          suma + =mat.at(i-k).at(j+k);
          k++;
  }
}

    suma = suma - 3*mat.at(i).at(j);
    brojac=brojac-3;
    FiltriranaMatrica.at(i).push_back(suma / brojac);
    suma = 0;
    brojac = 0;
  }
}
**/
  return FiltriranaMatrica;
}

int main() {
  int red=0, kolona=0;
  
    std::cout << "Unesite broj redova i kolona matrice: ";
    std::cin >> red >> kolona;

    std::cout << "Unesite elemente matrice: ";
    Matrica mat = KreirajMatricu(red, kolona);

    for (int i = 0; i < red; i++) {
      for (int j = 0; j < kolona; j++) {
        std::cin >> mat.at(i).at(j);
      }
    }
  /*
  std::vector<std::vector<double>> mat = {{2, 3, 3, 1, 2, 3},
                                          {1, 2, 4, 3, 4, 4},
                                          {2, 3, 4, 5, 3, 2},
                                          {3, 4, 3, 4, 4, 2},
                                            {1, 2, 3, 3, 4, 3}};  */
  int n;

  std::cout << "Unesite red filtriranja: ";
  std::cin >> n;
  try {
    Matrica FiltriranaMatrica = UsrednjavajuciFilter(mat, n);

    std::cout << "\nMatrica nakon filtriranja:\n";
    for (int i = 0; i < red; i++) {
      for (int j = 0; j < kolona; j++) {
        std::cout << std::fixed << std::setprecision(2) << std::setw(7)
                  << FiltriranaMatrica.at(i).at(j);
      }
      std::cout << "\n";
    }

  }

  catch (std::domain_error izuzetak) {
std::cout <<"\nGRESKA: "<< izuzetak.what() <<"!"<< std::endl;
  }

  return 0;
}
