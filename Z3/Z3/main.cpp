//TP 2022/2023: Zadaća 3, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <new>
#include <iomanip>



template <typename TipElemenata>
  struct Matrica{
    char ime_matrice;
    int br_redova, br_kolona;
    TipElemenata **elementi=nullptr;
 };

template <typename TipElemenata>
  void UnistiMatricu (Matrica<TipElemenata> &mat){
      if(!mat.elementi)return;
      for(int i{}; i<mat.br_redova; i++) delete [] mat.elementi[i];
      delete [] mat.elementi;
      mat.elementi=nullptr;
  }

template <typename TipElemenata>
  Matrica<TipElemenata> StvoriMatricu (int br_redova, int br_kolona, char ime=0){
      Matrica<TipElemenata> mat;
      mat.br_redova=br_redova;
      mat.br_kolona=br_kolona;
      mat.ime_matrice = ime;
      mat.elementi = new TipElemenata*[br_redova]{};
      try{
          for( int i=0; i<br_redova; i++)
            mat.elementi[i] = new TipElemenata[br_kolona];
      }
      catch(...){
          UnistiMatricu(mat);
          throw;
      }
      return mat;
  }

template <typename TipElemenata>
  void UnesiMatricu(Matrica<TipElemenata> &mat){
      for(int i=0; i<mat.br_redova; i++)
        for(int j=0; j<mat.br_kolona; j++){
            std::cout<< mat.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
            std::cin>>mat.elementi[i][j];
        }
  }

template <typename TipElemenata>
  void IspisiMatricu (const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false){
      for(int i=0; i<mat.br_redova; i++){
          for(int j=0; j<mat.br_kolona; j++)
            std::cout<<std::setw(sirina_ispisa)<<std::setprecision(preciznost)<<mat.elementi[i][j];
        std::cout<<std::endl;
      }
      if(treba_brisati){
        auto brisimat=mat;
        UnistiMatricu(brisimat);
      }
  }

template <typename TipElemenata>
  Matrica<TipElemenata> ZbirMatrica (const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2){
      if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije");
    
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i=0;i<m1.br_redova; i++)
        for(int j=0; j<m1.br_kolona; j++)
            m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
    return m3;
  }

template <typename TipElemenata>
  void PomnoziMatricuSaSkalarom (Matrica<TipElemenata> &m1, double skalar){
      for(int i{};i<m1.br_redova; i++){
          for( int j{}; j<m1.br_kolona; j++){
              m1.elementi[i][j] = m1.elementi[i][j]*skalar;
          }
      }
  }


template <typename TipElemenata>
  Matrica<TipElemenata> ProduktMatrica (const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2){
      if(m1.br_kolona != m2.br_redova )
        throw std::domain_error("Matrice nisu saglasne za mnozenje");

    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);

    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m2.br_kolona; j++){
            TipElemenata suma=0;
            for(int k=0; k<m1.br_kolona; k++){
                suma+=m1.elementi[i][k]*m2.elementi[k][j];
            }
            m3.elementi[i][j]=suma;
        }
    }
    return m3;
  }


  template <typename TipElemenata>
    Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &A, int n){
    //izuzetci
        if(A.br_redova != A.br_kolona)
            throw std::domain_error("Matrica nije kvadratna");
        if(n<0)
            throw std::domain_error("Pogresan parametar n");

//racunanje polinoma
    Matrica<TipElemenata> temp;
    temp.elementi=nullptr;
    Matrica<TipElemenata> rez;
    rez.elementi=nullptr;
    Matrica<TipElemenata> matricaProdukt;
    matricaProdukt.elementi=nullptr;
    Matrica<TipElemenata> matricaSkalar;
    matricaSkalar.elementi=nullptr;

    try{
        rez=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
        matricaProdukt=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
        matricaSkalar=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);

        for(int i{}; i<A.br_redova; i++){
            for(int j{}; j<A.br_kolona; j++){
                rez.elementi[i][j]=0;
                matricaProdukt.elementi[i][j]=A.elementi[i][j];
            }
        }

//mnozenje
        for(int i=1;i<=n; i++){

//duboka kopija produkta u skalar
            for(int i{}; i<A.br_redova; i++){
                for(int j{}; j<A.br_kolona; j++){
                    matricaSkalar.elementi[i][j]=matricaProdukt.elementi[i][j];
            }
        }

            PomnoziMatricuSaSkalarom(matricaSkalar, 1./i);
            for(int i{}; i<A.br_redova; i++){
                for(int j{}; j<A.br_kolona; j++){
                    rez.elementi[i][j]+=matricaSkalar.elementi[i][j];
            }
        }

            temp=ProduktMatrica(matricaProdukt, A);

            for(int i{}; i<A.br_redova; i++){
                for(int j{}; j<A.br_kolona; j++){
                    matricaProdukt.elementi[i][j]=temp.elementi[i][j];
            }
        }
        UnistiMatricu(temp);
        }

        UnistiMatricu(matricaProdukt);
        UnistiMatricu(matricaSkalar);
        UnistiMatricu(temp);
        return rez;
    }
    catch(...){
        UnistiMatricu(temp);
        UnistiMatricu(matricaProdukt);
        UnistiMatricu(matricaSkalar);
        UnistiMatricu(rez);
        throw;
    }
   }






int main ()
{

    int dimenzija, redPol;
    std::cout<<"Unesite dimenziju kvadratne matrice: ";
    std::cin>>dimenzija;
try{
    Matrica<double> A(StvoriMatricu<double>(dimenzija, dimenzija));
    std::cout<<"\nUnesite elemente matrice A: ";
    for(int i{}; i<dimenzija; i++){
        for(int j{}; j<dimenzija; j++){
            double broj;
            std::cout<<"\nA("<<i+1<<","<<j+1<<") = ";
            std::cin>>broj;
            A.elementi[i][j]=broj;
        }
    }

    std::cout<<"\nUnesite red polinoma: ";
    std::cin>>redPol;

    std::cout<<"\nMatricni harmonijski polinom:\n";

    IspisiMatricu(MatricniHarmonijskiPolinom(A,redPol), 10, 6, true);
    UnistiMatricu(A);

}
catch(...){

}

	return 0;
}
