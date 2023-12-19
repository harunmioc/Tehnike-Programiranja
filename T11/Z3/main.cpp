//TP 2022/2023: LV 11, Zadatak 3
#include <iostream>
#include <cmath>
#include <string.h>
#include <stdexcept>
#include <iomanip>



class Tim{
    char ime_tima[20];
    int broj_odigranih;
    int broj_pobjeda;
    int broj_nerijesenih;
    int broj_poraza;
    int broj_datih;
    int broj_primljenih;
    int broj_poena;

public:
    Tim(const char ime[]);
    void ObradiUtakmicu( int broj_datih, int broj_primjlenih);
    const char *DajImeTima() const{ return ime_tima;}
    int DajBrojPoena() const{return broj_poena;}
    int DajGolRazliku() const{return broj_datih-broj_primljenih;}
    void IspisiPodatke() const;
};

Tim::Tim(const char ime[]){
    if(strlen(ime)>20)
        throw std::range_error("Predugacko ime tima");
    strcpy(ime_tima,ime);
    broj_datih=0; broj_nerijesenih=0; broj_odigranih=0; broj_poena=0;
    broj_pobjeda=0; broj_poraza=0; broj_primljenih=0;
}

void Tim::ObradiUtakmicu( int dati, int primljeni){
    if(dati<0 || primljeni<0)   
        throw std::range_error("Neispravan broj golova");
        broj_odigranih++;
        broj_datih+=dati;
        broj_primljenih+=primljeni;
        if(dati>primljeni){
            broj_pobjeda++;
            broj_poena+=3;
        }
        else if(primljeni==dati){
            broj_nerijesenih++;
            broj_poena++;
        }
        else
            broj_poraza++;
}

void Tim::IspisiPodatke() const{
    std::cout<<std::setw(20)<<std::left<<ime_tima<<
                std::setw(4)<<std::right<<broj_odigranih<<
                std::setw(4)<<broj_pobjeda<<
                std::setw(4)<<broj_nerijesenih<<
                std::setw(4)<<broj_poraza<<
                std::setw(4)<<broj_datih<<
                std::setw(4)<<broj_primljenih<<
                std::setw(4)<<broj_poena<<std::endl;
}




int main ()
{
    Tim t1("FK Rudar");
    Tim t2("FK Mladost");
    t1.ObradiUtakmicu(1,0);
    t2.ObradiUtakmicu(0,1);
    t1.IspisiPodatke();
    t2.IspisiPodatke();

	return 0;
}
