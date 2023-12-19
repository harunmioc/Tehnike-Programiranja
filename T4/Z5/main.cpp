//TP 2022/2023: LV 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <string>
#include <vector>


template <typename Tip>

std::vector<Tip> Presjek(std::vector<Tip> v1, std::vector<Tip> v2){
    std::vector<Tip> v3;
    int duzina1=v1.size(), duzina2=v2.size();

    for(int i=0;i<duzina1;i++){
        Tip element=v1.at(i);
        for(int j=0;j<duzina2;j++){                
            int brojac=0;
            if(element==v2.at(j)){

                for(int k=0;k<v3.size();k++){           //provjerava ponavljanje 
                    if(element==v3.at(k)){
                        brojac++;
                    }
                }
                if(brojac!=0){
                    break;}
                else{
                    v3.push_back(element);
                }
            }
        }
    }


    return v3;
}


int main ()
{


    std::cout<<"Test za brojeve...\n";
int brEl1;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>brEl1;
std::vector<double> v1(brEl1);
    std::cout<<"\nUnesite elemente prvog vektora: ";
    for(int i=0;i<brEl1;i++){
        std::cin>>v1.at(i);
    }

    std::cout<<"\nUnesite broj elemenata drugog vektora: ";
int brEl2;
    std::cin>>brEl2;
std::vector<double> v2(brEl2);
    std::cout<<"\nUnesite elemente drugog vektora: ";
    for(int i=0;i<brEl1;i++){
        std::cin>>v1.at(i);
    }

std::vector<double> v3=Presjek(v1, v2);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0;i<v3.size();i++){
        std::cout<<v3.at(i);
    }
//SSSSTRRRRRRINNNNNNNNNGGGGGGGGGGGGGGGGGG

    std::cout<<"\n\nTest za stringove...\nUnesite broj elemenata prvog vektora: ";
    int brEl3;
    std::cin>>brEl3;
    std::cout<<"\nUnesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    std::vector<std::string> v4(brEl3);

    for(int i=0;i<brEl3;i++){
        std::getline(std::cin,v4.at(i));
    }

    std::cout<<"\nUnesite elemente drugog vektora: ";
    int brEl4;
        std::cout<<"\nUnesite elemente drugog vektora (ENTER nakon svakog unosa): ";
        std::vector<std::string> v5(brEl4);

    for(int i=0;i<brEl4;i++){
        std::getline(std::cin,v5.at(i));
    }

    std::vector<std::string> v6=Presjek(v4, v5);

    std::cout<<"Zajednicki elementi su: ";
    for(int i=0;i<v6.size();i++){
        std::cout<<v6.at(i);
    }



	return 0;
}
