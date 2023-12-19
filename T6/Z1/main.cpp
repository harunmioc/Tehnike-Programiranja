//TP 2022/2023: LV 6, Zadatak 1
#include <iostream>
#include <cmath>
#include <exception>
#include <new>
#include <limits>
#include <stdexcept>


    template<typename Tip>
       Tip *GenerirajStepeneDvojke(int n){

            if(n<=0){
                throw std::domain_error("Broj elemenata mora biti pozitivan");
            }
        Tip *niz;
        try{
            niz=new Tip[n];
            }
       catch(std::bad_alloc){
                throw std::runtime_error("Alokacija nije uspjela");
            }

        
            Tip broj=1;
            for(int i=0;i<n;i++){
                if(broj> (std::numeric_limits<Tip>::max())  || broj<=0){
                    delete [] niz;
                    throw std::overflow_error("Prekoracen dozvoljeni opseg");
            }
            niz[i]=broj;
            broj*=2;
    }
    
        return niz;
    }




int main ()
{

    int n;
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;

    unsigned long long int *niz;

    try{
        niz=GenerirajStepeneDvojke<unsigned long long int>(n);

        for(int i=0;i<n;i++){
            std::cout<<niz[i]<<" ";
        }
        std::cout<<"\n";
        delete [] niz;

    }
catch(std::overflow_error izuzetak){
    std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
}
catch(std::runtime_error izuzetak){
    std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
}
catch(std::domain_error izuzetak){
    std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
}
	return 0;
}
