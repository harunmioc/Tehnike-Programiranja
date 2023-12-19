//TP 2022/2023: LV 6, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>




    template<typename Pok>
   auto KreirajIzvrnutiNiz(Pok pocetak, Pok kraj) -> typename std::remove_reference<decltype(*pocetak)>::type *{

       typedef typename std::remove_reference<decltype(*pocetak)>::type Tip;

    Pok pok;
    pok=pocetak;
        int n=0;
    while(pok!=kraj){
        n++;
        pok++;
    }

    try{
        Tip *niz= new Tip [n]{};
        Tip *temp=niz+n-1;

        while(kraj!=pocetak){
            *temp=*pocetak;
            temp--;
            pocetak++;
        }

        return niz;
    }

    catch(...){
        throw;
    }

  
}

   






int main (){

    int n;
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;
try{
    std::vector<double> vec(n);

    std::cout<<"Unesite elemente: ";


    for(int i=0;i<n;i++){
        std::cin>>vec.at(i);
    }

    
        auto niz=KreirajIzvrnutiNiz(vec.begin(),vec.end());

        std::cout<<"Kreirani niz: ";
        for(int i=0;i<n;i++){
            std::cout<< niz[i]<<" ";
        }

        delete [] niz;

    }

    catch(std::bad_alloc){
        std::cout<<"Nedovoljno memorije!";
    }



	return 0;
}
