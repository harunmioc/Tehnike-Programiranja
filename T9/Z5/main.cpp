//TP 2022/2023: LV 9, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

    class Sat{
        int sekunde;

    public:
        //zasto static
        static bool DaLiJeIspravno (int sati, int minute, int sekunde){
            if(sati<0 || sati>23 || minute<0 || minute>59 || sekunde<0 || sekunde>59) return false;
            return true;
        }

        void Postavi(int h, int min, int sec){
                if(DaLiJeIspravno(h, min, sec)==false){
                    throw std::domain_error ("Neispravno vrijeme");
                }
                sekunde=sec+min*60+h*3600;
           
        }

        void PostaviNormalizirano(int h, int min, int sec){
            
        while(sec<0){
            sec+=60;
            min--;
        }
        while(min<0){
            min+=60;
            h--;
        }
        while(h<0) h+=24;

        while(sec>59){
            sec-=60;
            min++;
        }

        while(min>59){
            min-=60;
            h++;
        }

        while(h>23) h-=24;

            sekunde=sec+min*60+h*3600;
        }

        Sat &Sljedeci() {
            sekunde++;
            PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde());
            return *this;
        }

        Sat &Prethodni() {
            sekunde--;
            PostaviNormalizirano(DajSate() , DajMinute(), DajSekunde());
            return *this;
        }

        Sat &PomjeriZa(int sec){
            if(sec>0)
                for(int i=0; i<sec; i++)
                    Sljedeci();
            else
                for(int i=0; i>sec; i--)
                    Prethodni();

            return *this;
        }

        void Ispisi() const{
            int sati=DajSate(), minute=DajMinute();
            std::cout<<std::setw(2)<<std::setfill('0')<<sati<<":"<<std::setw(2)<<minute<<":"<<std::setw(2)<<DajSekunde();
        }

        int DajSate() const{
            return sekunde/3600;;
        }

        int DajMinute() const{
            return (sekunde-DajSate()*3600)/60;
        }

        int DajSekunde() const{
            return sekunde-DajSate()*3600-DajMinute()*60;
        }

        friend int BrojSekundiIzmedju(const Sat &vrijeme1, const Sat &vrijeme2);
        static int Razmak(const Sat &vrijeme1, const Sat &vrijeme2){
            return BrojSekundiIzmedju(vrijeme1, vrijeme2);
        }
    };

        int BrojSekundiIzmedju(const Sat &vrijeme1, const Sat &vrijeme2){
            return (vrijeme1.DajSate()*3600+vrijeme1.DajMinute()*60+vrijeme1.DajSekunde())-(vrijeme2.DajSate()*3600+vrijeme2.DajMinute()*60+vrijeme2.DajSekunde());
        }





int main ()
{


	return 0;
}
