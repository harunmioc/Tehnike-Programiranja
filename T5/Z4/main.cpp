//TP 2022/2023: LV 5, Zadatak 4
#include <iostream>
#include <cmath>
#include <deque>
#include <algorithm>

    void Unos(int &a){
        std::cin>>a;
    }


int main ()
{

    int a;
    
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>a;
    std::cout<<"Unesite elemente: ";
    std::deque<int> n(a);
        auto pokUnos=Unos;
    std::for_each(n.begin(),n.end() , pokUnos);

    std::cout<<"Najveci element deka je "<<*std::max_element(n.begin(),n.end());
    std::cout<<"\nNajmanji element deka se pojavljuje "<< std::count(n.begin(), n.end(), *std::min_element(n.begin(),n.end()))<<" puta u deku";
   std::cout<<"\nU deku ima "<<std::count_if(n.begin(), n.end(), [](int n) {return ( std::sqrt(n) == int(std::sqrt(n)) ); })<<" brojeva koji su potpuni kvadrati"<<std::endl;
   std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(n.begin(),n.end(), [] (int x, int y) ->bool { return int(std::log10(std::fabs(x))+1) < int (  std::log10(    std::fabs(y)) +1); });       
    std::cout<<"\nElementi koji nisu trocifreni su:";
    std::for_each(n.begin(),n.end(), [] (int n){ int x=int(std::log10(std::fabs(n))+1); if(x!=3){  std::cout<<" "<<n; }   }   );;




	return 0;
}
