//TP 2016/2017: LV 1, Zadatak 3
#include <ios>
#include <iostream>
#include <cmath>
#include <iomanip>



int main (){
    int a,b;

    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;



//linija
    std::cout<<"\n+";
    for(int i=1;i<=44;i++){
        if(i==10 || i==21 || i==32 || i==44 ){
            std::cout<<"+";
        }
        else{
            std::cout<<"-";
        }
    }


    std::cout<<"\n";
    std::cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |\n";

//linija

    std::cout<<"+";
    for(int i=1;i<=44;i++){
        if(i==10 || i==21 || i==32 || i==44 ){
            std::cout<<"+";
        }
        else{
            std::cout<<"-";
        }
    }    
    std::cout<<"\n";



    for(int i=a;i<=b;i++){
        double temp=i;
        std::cout<<"| "<<std::left<<std::setw(8)<<i<<"|";
        std::cout<<std::right<<std::setw(9)<<i*i<<" |";                 //kvadrat
        
        std::cout<<std::right<<std::fixed<<std::setprecision(3)<<std::setw(9)<<std::sqrt(temp)<<" |";       //korijen
        std::cout<<std::setw(10)<<std::fixed<<std::setprecision(5)<<std::log(i)<<" |\n";                  //logaritam
        
    }

//linija

 std::cout<<"+";
    for(int i=1;i<=44;i++){
        if(i==10 || i==21 || i==32 || i==44 ){
            std::cout<<"+";
        }
        else{
            std::cout<<"-";
        }
    }

    

	return 0;
}