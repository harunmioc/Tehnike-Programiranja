//TP 2022/2023: LV 2, Zadatak 4
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
        double Re, Im;

        std::cout<<"R"<<i<<" = ";
        std::cin>>Re;
        std::cout<<"X"<<i<<" = ";
        std::cin>>Im;

        z=std::complex<double>(Re,Im);

        z_suma=z_suma+ 1./z;
        std::cout<<"\n";
    }

    z_suma=1./z_suma;

    std::cout<<"Paralelna veza ovih elemenata ima R = "<<real(z_suma)<<" i X = "<<imag(z_suma)<<".";
	return 0;
}
