// TP 2022/2023: Zadaća 1, Zadatak 3
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

typedef std::vector<std::vector<int>> Matrica;

int Duzina(int br){
    int brojac=0;
    if(br==0){return 1;}
    while(br!=0){
        br=br/10;
        brojac++;
    }
return brojac;
}


int NajvecaSirina(Matrica mat){
    int sirina=0,MAXsirina=0;

    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            sirina =Duzina(mat[i][j]);

            if(mat[i][j]<0){
                sirina++;
            }

            if(sirina>MAXsirina){
                MAXsirina=sirina;
            }

        }
    }
return MAXsirina;
}


Matrica KreirajMatricu(int red, int kolona) {
  return Matrica(red, std::vector<int>(kolona));
}


Matrica KreirajSpiralnuMatricu(int red, int kolona, int k, bool DiliL) {

    if(red<=0 || kolona<=0){
        return KreirajMatricu(0, 0);
    }

  Matrica mat = KreirajMatricu(red, kolona);

  int brojacRED = 0, brojacKOLONA = 0, maxRedova = red - 1,
      maxKolona = kolona - 1;
  int broj = k;

  if (DiliL == true) {

    while (k <= (broj + (red * kolona) - 1)) {

      for (int j = brojacKOLONA; j <= maxKolona; j++) {
        mat.at(brojacRED).at(j) = k;
        k++;
      }
      brojacRED++;
        if(k > (broj + (red * kolona) - 1)){break;}

      for (int i = brojacRED; i <= maxRedova; i++) {
        mat.at(i).at(maxKolona) = k;
        k++;
      }
      maxKolona--;
        if(k > (broj + (red * kolona) - 1)){break;}

      for (int j = maxKolona; j >= brojacKOLONA; j--) {
        mat.at(maxRedova).at(j) = k;
        k++;
      }
      maxRedova--;
        if(k > (broj + (red * kolona) - 1)){break;}

      for (int i = maxRedova; i >= brojacRED; i--) {
        mat.at(i).at(brojacKOLONA) = k;
        k++;
      }
      brojacKOLONA++;
              if(k > (broj + (red * kolona) - 1)){break;}

    }
  }

  else{

      while(k<=(broj+(red*kolona)-1)){

          for(int i=brojacRED;i<=maxRedova;i++){
              mat.at(i).at(brojacRED)=k;
              k++;
          }

        brojacKOLONA++;
              if(k > (broj + (red * kolona) - 1)){break;}

        for(int j=brojacKOLONA;j<=maxKolona;j++){
            mat.at(maxRedova).at(j)=k;
            k++;
        }

        maxRedova--;
              if(k > (broj + (red * kolona) - 1)){break;}

        for(int i=maxRedova;i>=brojacRED;i--){
            mat.at(i).at(maxKolona)=k;
            k++;
        }

        maxKolona--;
              if(k > (broj + (red * kolona) - 1)){break;}

        for(int j=maxKolona;j>=brojacKOLONA;j--){
            mat.at(brojacRED).at(j)=k;
            k++;
        }
        brojacRED++;
              if(k > (broj + (red * kolona) - 1)){break;}
      }
     
  }

  return mat;
}

    bool DaLiJeSpiralnaMatrica(Matrica mat){
        int k=mat.at(0).at(0);
        int br_redova=mat.size();
        int br_kolona=mat.at(0).size();
        bool DiliL=true;

        if( k > ( k + (br_redova*br_kolona) - 1)){
            return false;
        }
        if(mat.at(1).at(0)==k+1){
            DiliL=false;
        }


        Matrica PravilnaMatrica=KreirajSpiralnuMatricu(br_redova, br_kolona, k, DiliL);
int brojacTacnosti=0;
        for(int i=0;i<br_redova;i++){
            if(mat.at(i)==PravilnaMatrica.at(i)){
                brojacTacnosti++;
            }
        }

        if(brojacTacnosti==br_redova){
            return true;
        }
        else{return false;}
    }


int main() {
  int red, kolona, k;
  char slovo;

  std::cout << "Unesite broj redova i kolona matrice: ";
  std::cin >> red >> kolona;

  std::cout << "Unesite pocetnu vrijednost: ";
  std::cin >> k;

  std::cout << "Unesite L za lijevu, a D za desnu spiralnu matricu: ";
  std::cin >> slovo;

  bool DiliL = true;
  if (slovo == 'L') {
    DiliL = false;
  }

  Matrica mat = KreirajSpiralnuMatricu(red, kolona, k, DiliL);

  std::cout << "\nKreirana spiralna matrica:\n";
int SirinaIspisa=NajvecaSirina(mat);
  for (int i = 0; i < red; i++) {
    for (int j = 0; j < kolona; j++) {
      std::cout <<std::left<<std::setw(SirinaIspisa+1)<<mat.at(i).at(j);
    }
    std::cout << "\n";
  }

  return 0;
}
