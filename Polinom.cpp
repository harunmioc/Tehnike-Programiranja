/*Napravite funkciju “Polinom” koja kao parametar prima vektor realnih brojeva koji predstavljaju
koeficijente nekog polinoma (prvi element vektora je slobodni član, drugi element je član uz prvi
stepen promjenljive polinoma, i tako dalje ka rastućim stepenima promjenljive polinoma), a koja kao
rezultat vraća funkciju koja računa vrijednost tog polinoma u tački koja se zadaje kao argument te
funkcije. */



#include <iostream>
#include <vector>
#include <functional>

    std::function<double(double)> Polinom (const std::vector<double>& v){
        
        return [=](double x){
            double rez=0;
            int stepen=1;
            for(int i=0; i<v.size(); i++){
                rez+=v.at(i)*stepen;
                stepen*=x;
            }

            return rez;
        };
}

int main (){

    auto poli = Polinom({2, 3, 0, -1, 4});
        std::cout << poli(5);

	return 0;
}
