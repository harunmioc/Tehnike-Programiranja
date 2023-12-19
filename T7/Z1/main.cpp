//TP 2022/2023: LV 7, Zadatak 1
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
int main ()
{

    try{
        std::cout<<"Koliko zelite recenica: ";
        int broj_recenica;
        std::cin>>broj_recenica;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite recenice:"<<std::endl;

        char **recenice=new char*[broj_recenica];
        
        for(int i=0; i<broj_recenica; i++){
            
            char radni_prostor[1000];
            std::cin.getline(radni_prostor, sizeof radni_prostor);
            try{
                recenice[i]=new char[std::strlen(radni_prostor)+1];
                std::strcpy(recenice[i], radni_prostor);
            }

        catch(std::bad_alloc){
                for(int j=0; j<i; j++) delete[] recenice[j];
                delete[] recenice;
                throw;
            }
        }
        

        std::sort(recenice, recenice + broj_recenica, [](const char* a, const char* b) {
            return std::strcmp(a, b) < 0;
        });



    /*    for(int i=0; i<broj_recenica; i++){
            for(int j=i+1; j<broj_recenica; j++){
                if(std::strcmp(recenice[i], recenice[j])>0){
                    char *temp=recenice[i];
                    recenice[i]=recenice[j];
                    recenice[j]=temp;
                }
            }
        }*/
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0; i<broj_recenica; i++) std::cout<<recenice[i]<<std::endl;
        for(int i=0; i<broj_recenica; i++) delete[] recenice[i];
        delete[] recenice;
    
    
    }
catch(...){
    std::cout<<"Problemi s memorijom!";

}

	return 0;
}
