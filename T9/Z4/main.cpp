//TP 2022/2023: LV 9, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

    class Sat{
        int sati, minute, sekunde;

    public:
        //zasto static
        static bool DaLiJeIspravno (int sati, int minute, int sekunde);

        void Postavi(int h, int min, int sec){
                if(Sat::DaLiJeIspravno(h, min, sec)==false){
                    throw std::domain_error ("Neispravno vrijeme");
                }
                sati=h; minute=min; sekunde=sec;
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

            sati=h; minute=min; sekunde=sec;
        }

        Sat &Sljedeci() {
            sekunde++;
            PostaviNormalizirano(sati, minute, sekunde);
            return *this;
        }

        Sat &Prethodni() {
            sekunde--;
            PostaviNormalizirano(sati, minute, sekunde);
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
            std::cout<<std::setw(2)<<std::setfill('0')<<sati<<":"<<std::setw(2)<<minute<<":"<<std::setw(2)<<sekunde;
        }

        int DajSate() const{
            return sati;
        }

        int DajMinute() const{
            return minute;
        }

        int DajSekunde() const{
            return sekunde;
        }

        friend int BrojSekundiIzmedju(const Sat &vrijeme1, const Sat &vrijeme2);
        static int Razmak(const Sat &vrijeme1, const Sat &vrijeme2){
            return BrojSekundiIzmedju(vrijeme1, vrijeme2);
        }
    };

        int BrojSekundiIzmedju(const Sat &vrijeme1, const Sat &vrijeme2){
            return (vrijeme1.sati*3600+vrijeme1.minute*60+vrijeme1.sekunde)-(vrijeme2.sati*3600+vrijeme2.minute*60+vrijeme2.sekunde);
        }


     bool Sat::DaLiJeIspravno (int sati, int minute, int sekunde){
            if(sati<0 || sati>23 || minute<0 || minute>59 || sekunde<0 || sekunde>59) return false;
            return true;
        }



int main ()
{
    

	return 0;
}
