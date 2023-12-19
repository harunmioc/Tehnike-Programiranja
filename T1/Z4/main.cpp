//TP 2016/2017: LV 1, Zadatak 4
#include <iostream>
#include <cmath>
int main (){
    double n;
    

while(1){
    
    std::cout<<"Unesite prirodan broj ili 0 za kraj: ";

   

    for(;;){
        std::cin>>n;

        if(std::cin && n>0 && (n-floor(n)==0)){
            break;
        }

        if(std::cin && n==0){               //ne moze samo sa n==0, vjerovatno pretpostavi da je n==0 jer se nije desilo..?
            std::cout<<"Dovidjenja!";
            return 0;
    }
        std::cout<<"Niste unijeli prirodan broj!\n";
        std::cout<<"Unesite prirodan broj ili 0 za : ";        
        std::cin.clear();
        std::cin.ignore(10000,'\n');
    }



int suma=0;

    for(int i=1;i<n;i++){
        if(int(n)%i==0){
            suma=suma+i;
        }
    }

    if(suma<n){
        std::cout<<"Broj "<<n<<" je manjkav!\n";
    }
    else if(suma>n){
        std::cout<<"Broj "<<n<<" je obilan!\n";
    }
    else if(suma==n){
            std::cout<<"Broj "<<n<<" je savrsen!\n";
    }


}

	return 0;
}