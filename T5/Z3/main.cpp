//TP 2022/2023: LV 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <algorithm>

    void Unos(int &a){
        std::cin>>a;
    }

    bool PotpuniKvadrati(int n){
           int k=std::sqrt(n);
        return (k*k==n);
    }

    bool BrojCifara(int x, int y){
        return floor(log10(std::fabs(x))+1) < std::floor(log10(std::fabs(y))+1);
    }

    int NeTrocifreni(int n){
       int x=std::floor(log10(std::fabs(n))+1);
        if(x!=3){
            std::cout<<" "<<n;
        }
        return 0;
    }

   

int main ()
{
    int a,n[1000];
    std::cout<<"Unesite broj elemenata (max. 1000): ";
    std::cin>>a;
    std::cout<<"Unesite elemente: ";
    auto pokUnos = Unos;
    std::for_each(n, n+a, pokUnos);


    std::cout<<"Najveci element niza je "<<*std::max_element(n,n+a);


    std::cout<<" \nNajmanji element niza se pojavljuje "<< std::count(n, n+a, *std::min_element(n,n+a))<<" puta u nizu";

        auto pok2=PotpuniKvadrati;
   std::cout<<"\nU nizu ima "<<std::count_if(n, n+a, pok2)<<" brojeva koji su potpuni kvadrati";
        bool (*poknaBrojCifara)(int, int)=&BrojCifara;
   std::cout<<"\nPrvi element sa najmanjim brojem cifara je "<<*std::min_element(n,n+a,poknaBrojCifara);

        auto poknaNeTrocifreni=NeTrocifreni;
        int n2[1000];
       
    std::cout<<"\nElementi koji nisu trocifreni su:";
    std::transform(n,n+a,n2,poknaNeTrocifreni);


	return 0;
}
