//TP 2022/2023: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>


    class ApstraktnoVozilo{
        int tezina;
    public:
        ApstraktnoVozilo(int kg):tezina(kg){}
        int DajTezinu() const{ return tezina;}

        virtual int DajUkupnuTezinu() const =0;
        virtual void IspisiPodatke() const=0;
        virtual ~ApstraktnoVozilo() {}

        virtual ApstraktnoVozilo* DajKopiju() const=0;
    };


    class Automobil: public ApstraktnoVozilo{
        std::vector<int> putnici;
    public:

        Automobil(int kg, const std::vector<int> & putnici):ApstraktnoVozilo(kg),putnici(putnici){}
        int DajUkupnuTezinu() const override{
            int suma=0;
            for(int i=0; i<putnici.size();i++)
                suma+=putnici.at(i);
            return DajTezinu() + suma;
        }

        void IspisiPodatke() const override;
        Automobil* DajKopiju() const override {return new Automobil(*this);}

    };

void Automobil::IspisiPodatke() const  {
    std::cout<<"Vrsta vozila: Automobil\n Vlastita tezina: "<<DajTezinu()<<" kg\n";
    std::cout<<"Tezine putnika: ";
        for(int i=0; i<putnici.size();i++){
            std::cout<<putnici.at(i)<<" kg";
            if(i!=putnici.size()-1)std::cout<<", ";
        }
    std::cout<<"\nUkupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}   



    class Kamion: public ApstraktnoVozilo{
        int teret;
    public:
        Kamion (int kg, int kgteret): ApstraktnoVozilo(kg),teret(kgteret){}
        int DajUkupnuTezinu() const override{
            return DajTezinu() + teret;}
        void IspisiPodatke() const override;
        Kamion* DajKopiju() const override{ return new Kamion(*this);}
    };

void Kamion::IspisiPodatke() const{
    std::cout<<"Vrsta vozila: Kamion\nVlastita tezina: "<<DajTezinu()<<" kg";
    std::cout<<"\nTezina tereta: "<<teret<<" kg"<<"\nUkupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}




    class Autobus: public ApstraktnoVozilo{
        int BrojPutnika=0;
        double tezina;
    public:
        Autobus( int kg, int brpt, double aprxkg):ApstraktnoVozilo(kg), BrojPutnika(brpt), tezina(aprxkg){}
        int DajUkupnuTezinu() const override{return DajTezinu()+ BrojPutnika*tezina;}
        void IspisiPodatke() const override;
        Autobus * DajKopiju() const override{ return new Autobus(*this);}
    };

void Autobus::IspisiPodatke() const{
    std::cout<<"Vrsta vozila: Autobus\nVlastita tezina: "<<DajTezinu()<<" kg\n";
    std::cout<<"Broj putnika: "<<BrojPutnika<<"\nProsjecna tezina putnika: "<<tezina<<" kg\nUkupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}






    class Vozilo{
        ApstraktnoVozilo *pok_vozilo;
        void Test() const{ if( !pok_vozilo)  throw std::logic_error("Nespecificirano vozilo!");}
    public:
        Vozilo() :pok_vozilo(nullptr) {};
        ~Vozilo(){delete pok_vozilo;}

        Vozilo ( const ApstraktnoVozilo &vozilo) : pok_vozilo(vozilo.DajKopiju()){}
        Vozilo ( const Vozilo &vozilo){
            if( !vozilo.pok_vozilo) pok_vozilo=nullptr;
            else pok_vozilo = vozilo.pok_vozilo->DajKopiju();
        }
        Vozilo( Vozilo &&vozilo){pok_vozilo=vozilo.pok_vozilo; vozilo.pok_vozilo=nullptr;}


        Vozilo &operator =(const Vozilo &vozilo){
            ApstraktnoVozilo *p_novo=nullptr;
            if(vozilo.pok_vozilo!=nullptr) p_novo=vozilo.pok_vozilo->DajKopiju();
            delete pok_vozilo;
            pok_vozilo=p_novo;
            return *this;
        }
        Vozilo &operator =(Vozilo &&vozilo){
            std::swap(pok_vozilo, vozilo.pok_vozilo);
            return *this;
        }

        int DajTezinu() const{
            Test(); return pok_vozilo->DajTezinu();}
        int DajUkupnuTezinu() const{ Test(); return pok_vozilo->DajUkupnuTezinu();}
        void IspisiPodatke() const{ Test(); return pok_vozilo->IspisiPodatke();}
    };


int main ()
{
        bool DaLiJeTokOK=true;

    std::ifstream tok("VOZILA.TXT");

    if(!tok){ std::cout<<"Trazena datoteka ne postoji"; return 0;}

    std::vector<Vozilo> vec_vozila{};

        char slovo;



    while(tok>>slovo){
        int kg;
            
        tok>>kg;
        if(slovo=='A'){
            int BrojPutnika;
            tok>>BrojPutnika;

            std::vector<int> tezine(BrojPutnika);
                for(int i=0; i<BrojPutnika; i++)
                    tok>>tezine.at(i);
            vec_vozila.push_back(Automobil(kg,tezine));

        }else if(slovo=='K'){
            int teret;
            tok>>teret;
            vec_vozila.push_back(Kamion(kg, teret));

        }else if(slovo=='B'){
            int BrojPutnika;
            double tezina;
            tok>>BrojPutnika>>tezina;
            vec_vozila.push_back(Autobus(kg,BrojPutnika,tezina));
        }
    else{
        std::cout<<"Greska";

        return 0;
    }
    }
    tok.close();

    std::vector<int> tezine;
    for(int i=0; i<vec_vozila.size(); i++)
        tezine.push_back(vec_vozila.at(i).DajUkupnuTezinu());

std::sort(tezine.begin(), tezine.end(), std::less<int>());



    for(int i=0; i<vec_vozila.size(); i++){
        std::cout<<tezine.at(i)<<"\n";
    }

	return 0;
}
