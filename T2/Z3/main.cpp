//TP 2022/2023: LV 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <complex>

int main ()
{

    std::cout<<"Unesite broj elemenata: ";
        int n;
    std::cin>>n;

    std::complex<double>z_suma(0,0);
    std::cout<<"\n";

    for(int i=1;i<=n;i++){
        std::complex<double> z;

        std::cout<<"Z_"<<i<<" = ";
        std::cin>>z;

        z_suma=z_suma+ 1./z;

    }
        std::cout<<"\nParalelna veza ovih elemenata ima impedansu Z_ = "<<1./z_suma<<".";


	return 0;
}
