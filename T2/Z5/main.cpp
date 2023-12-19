//TP 2022/2023: LV 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <complex>
const double Pi= 4*atan(1);


int main ()
{



std::cout<<"Unesite broj elemenata: ";
        int n;
    std::cin>>n;

    std::complex<double>z_suma(0,0);
    std::cout<<"\n";


        for(int i=1;i<=n;i++){
        std::complex<double> zk;
        double Z, Fi;

        std::cout<<"Z"<<i<<" = ";
        std::cin>>Z;
        std::cout<<"fi"<<i<<" = ";
        std::cin>>Fi;
        Fi=Fi*(Pi/180 );
        
        zk=std::polar(Z,Fi);

        z_suma=z_suma+1./zk;

        std::cout<<"\n";
    }


        z_suma=1./z_suma;


    std::cout<<"Paralelna veza ovih elemenata ima Z = "<<std::abs(z_suma)<<" i fi = "<<(arg(z_suma)*(180/Pi))<<".";

	return 0;
}
