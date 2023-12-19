//TP 2022/2023: LV 11, Zadatak 1
#include <iostream>
#include <cmath>


    class NeobicnaKlasa{
        
        public:
        NeobicnaKlasa(const int &br){std::cout<<"Kopirajuca inicijalizacija\n";}        
        explicit NeobicnaKlasa(int &&broj){std::cout<<"Direktna inicijalizacija\n";}
     /*  explicit NeobicnaKlasa ( const NeobicnaKlasa &broj){std::cout<<"brbrbbr";}
       NeobicnaKlasa(NeobicnaKlasa &&br){std::cout<<"\nsqrt";} //move konstruktor
*/

    };

int main (){
    int broj=5;
    //NeobicnaKlasa k1(broj);
    //NeobicnaKlasa k2=5;
    NeobicnaKlasa k3(5);
    //NeobicnaKlasa k4(k3);
    NeobicnaKlasa k5=std::move(3);
	return 0;
}
