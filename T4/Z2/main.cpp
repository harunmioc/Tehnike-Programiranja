//TP 2022/2023: LV 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>
    
    void IzvrniString(std::string &s){
        int duzina=s.length();
  
            for(int i=0;i<duzina/2;i++){
                char temp=s.at(i);
                s.at(i)=s.at(duzina-i-1);
                s.at(duzina-i-1)=temp;
            }

        }
        
int main ()
{

    std::string s;

    std::cout<<"Unesi string: ";
    std::getline(std::cin,s);
    IzvrniString(s);
    std::cout<<"Izvrnuti string je: "<<s;

	return 0;
}
