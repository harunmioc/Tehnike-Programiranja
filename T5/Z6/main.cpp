//TP 2022/2023: LV 5, Zadatak 6
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>


    int SumaCifara(int broj){
        if (broj==0){
            return 0;
        }
        return broj%10+SumaCifara(broj/10);
    }



int main ()
{

    std::cout<<"Unesite broj elemenata: ";
int n;
    std::cin>>n;

    std::cout<<"\nUnesite elemente: ";
std::vector<int> v;

    std::for_each(v.begin(), v.end(), [] (int &a) { std::cin>>a;});


    std::sort(v.begin(),v.end(), [] (int a, int b){
        int suma_a=SumaCifara(abs(a));
        int suma_b=SumaCifara(abs(b));

        if(suma_a>suma_b) return false;

        else if(suma_a< suma_b) return true;

        else if(suma_a==suma_b && a>b ) return false;

        else return true;
    });



    std::cout<<"\nNiz sortiran po sumi cifara glasi: ";
    std::for_each(v.begin(), v.end(), [](int a){std::cout<<" "<<a;});
    
    std::cout<<"\nUnesite broj koji trazite: ";
int broj;
    std::cin>>broj;

    std::cout<<"\nTrazeni broj se nalazi na poziciji "<<std::lower_bound(v.begin(),v.end(), broj);


	return 0;
}
