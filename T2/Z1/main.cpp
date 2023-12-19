// TP 2022/2023: LV 2, Zadatak 1
#include <cmath>
#include <iostream>
#include <vector>

bool DaLiJeProst(int a) {

  if (a <= 1) {
    return false;
  }

  if (a <= 3) {
    return true;
  }

  if (a % 2 == 0 || a % 3 == 0) {
    return false;
  }

  for (int i = 5; i <= floor(std::sqrt(a)); i += 6) {
    if (a % i == 0 || a % (i + 2) == 0) {

      return false;
    }
  }

  return true;
}

/*
bool DaLiJeProst(int a){

    if(a==2 || a==3){
        return true;
    }

    if(a<=1 || a%2==0 || a%3==0){
        return false;
    }

    for(int i=5;i*i<=a;i+=6){
        if(a%i==0 || a%(i+2)==0){
            return false;
        }
    }
    return true;
}
*/

std::vector<int> ProstiBrojeviUOpsegu(int a, int b) {

  std::vector<int> prosti;
  int temp=a, br=0;
// dolazi do prekoracenja max int vrijednosti 2147... i nakon i++ desava se -2147... sto dovodi u beskonacnu petlju
 for(;;){
     if(br==1){break;}

     if(temp==b){
         br=1;
     }

    if (DaLiJeProst(temp) == true) {
      prosti.push_back(temp);
    }
        
    temp++;
    
 }
/*
  for (int i = a; i <= b; i++) {
    if (DaLiJeProst(i) == true) {
      prosti.push_back(i);
    }
  }
*/
  return prosti;
}

int main() {
  int a, b;

  std::cout << "Unesite pocetnu i krajnju vrijednost: ";
  std::cin >> a >> b;

  std::vector<int> prosti = ProstiBrojeviUOpsegu(a, b);

  if (prosti.size() == 0) {
    std::cout << "Nema prostih brojeva u rasponu od " << a << " do " << b
              << "!";
  }

  else {
    std::cout << "Prosti brojevi u rasponu od " << a << " do " << b << " su:";
    for (int i = 0; i < prosti.size(); i++) {

      if (i == prosti.size() - 1) {
        std::cout << " " << prosti[i];
      } else {
        std::cout << " " << prosti[i] << ",";
      }
    }
    std::cout << "\n";
  }

  return 0;
}
