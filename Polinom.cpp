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
