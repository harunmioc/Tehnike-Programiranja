//TP 2022/2023: LV 3, Zadatak 8
#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>

    std::string IzdvojiRijec( std::string s, int n){
        if(n<=0){
            throw std::domain_error("IZUZETAK: Pogresan redni broj rijeci!");
        }
    int br=0;
    std::string rijec;

    for(int i=0; i<s.length(); i++){

        if(s.at(i)!=' '){
            br++;
            while(s.at(i)!=' ' && i<s.length()){
                if(br==n){
                    rijec.push_back(s.at(i));
                }
                i++;
            }
        }

    if(br==n) 
        return rijec;
    }
    
    
    throw std::domain_error("IZUZETAK: Pogresan redni broj rijeci!");
}



int main ()
{

try{
    std::cout<<"Unesite redni broj rijeci: ";
        int n;
    std::cin>>n;
    std::cin.ignore(10000, '\n');
    std::cout<<"Unesite recenicu: ";
        std::string s;
    std::getline(std::cin,s);

    std::string izdvojenaRijec=IzdvojiRijec(s,n);

    std::cout<<"Rijec na poziciji "<<n<<" je "<<izdvojenaRijec;

}
catch(std::domain_error izuzetak){
    std::cout<<izuzetak.what()<<std::endl;
}
	return 0;
}
