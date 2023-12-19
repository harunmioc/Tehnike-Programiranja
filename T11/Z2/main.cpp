//TP 2022/2023: LV 11, Zadatak 2
#include <cmath>
#include <iostream>
#include <sched.h>
#include <stdexcept>

class StedniRacun {
  double stanje;
  static int brojKreiranih;
  static int brojAktivnih;

public:
//konstruktori

  explicit StedniRacun(double x = 0) {
    if (x < 0) {
      throw std::logic_error("Nedozvoljeno pocetno stanje");
    }
    stanje = x;
    brojAktivnih++;
    brojKreiranih++;
  }

    StedniRacun(const StedniRacun &stedniracun){
        if(stedniracun.DajStanje()<0)        
            throw std::logic_error("Nedozvoljeno pocetno stanje");
        else{
            stanje=stedniracun.DajStanje();
            brojKreiranih++;
            brojAktivnih++;
        }
    }


  //desteruktor
  ~StedniRacun(){brojAktivnih--;}

  StedniRacun &Ulozi(const double &x) {
    if (x < 0 && std::abs(x) > stanje)
      throw std::logic_error("Transakcija odbijena");
    stanje += x;
    return *this;
  }
  StedniRacun &Podigni(const double &x) {
    if (x > stanje)
      throw std::logic_error("Transakcija odbijena");
    stanje -= x;
    return *this;
  }

  double DajStanje() const { return stanje; };

  StedniRacun &ObracunajKamatu(const double &x) {
    if (x < 0)
      throw std::logic_error("Nedozvoljena kamatna stopa");
    stanje += stanje * x / 100;
    return *this;
  }

    static int DajBrojAktivnih(){
        return brojAktivnih;
    }
    static int DajBrojKreiranih(){
        return brojKreiranih;
    }

};

int StedniRacun::brojKreiranih=0;
int StedniRacun::brojAktivnih=0;

int main() { 
    StedniRacun s1, s2(100);
    {
        StedniRacun s3(50);
    }
    std::cout<<StedniRacun::DajBrojKreiranih()<<" "<<StedniRacun::DajBrojAktivnih();
    
    
    
    return 0; }

