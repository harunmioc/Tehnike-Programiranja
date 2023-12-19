//TP 2022/2023: LV 6, Zadatak 5
#include <iostream>
#include <cmath>
#include <type_traits>
#include <vector>
#include <deque>

        template <typename tip>
        auto KreirajDinamickuKopiju2D(tip mat) -> typename std::remove_reference<decltype(mat.at(0).at(0))>::type **{

                int br_redova=mat.size();
            
            typename std::remove_reference<decltype(mat.at(0).at(0))>::type ** dinMat=nullptr;

            try{

               dinMat= new typename std::remove_reference < decltype( mat[0][0]) >::type *[br_redova]{};

                    for(int i=0;i<br_redova;i++){
                        dinMat[i]=new typename std::remove_reference<decltype(mat[0][0])>::type [mat[i].size()];
                            for(int j=0;j<mat[i].size();j++){
                                dinMat[i][j]=mat[i][j];

                            }
                    }


            }
        catch(...){
            delete [] dinMat[0];
            delete [] dinMat;
            throw;
        }
        return dinMat;


        }



int main ()
{

int **mat=nullptr;
int n;

        try{
            std::cout<<"Unesite broj redova kvadratne matrice: ";
            std::cin>>n;
            std::vector<std::deque<int>> matttttt (n,std::deque<int>(n));

            std::cout<<"Unesite elemente matrice: ";

            for( int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    std::cin>>matttttt.at(i).at(j);
                }
            }


            mat=KreirajDinamickuKopiju2D(matttttt);

            for(int i=0;i<n;i++){
                for(int j=0; j<n;j++){
                    std::cout<<mat[i][j];
                    if(j<n-1) std::cout<<" ";
                }
                std::cout<<"\n";
            }


        for(int i=0;i<n;i++){
            delete [] mat[i];
        }
        delete [] mat;
        }
        catch(...){
            std::cout<<"Nedovoljno memorije"<<"\n";
        }



	return 0;
}
