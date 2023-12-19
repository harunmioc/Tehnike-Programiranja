// TP 2022/2023: LV 10, Zadatak 2
#include <cmath>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

const double pi=std::acos(-1);



class Krug {
  double poluprecnik;

public:

    explicit Krug(const int &r):poluprecnik(r){
        if (r <= 0)
      throw std::domain_error("Neispravan poluprecnik");
    }

    explicit Krug(const double &r):poluprecnik(r) {
    if (r <= 0)
      throw std::domain_error("Neispravan poluprecnik");
  }

  void Postavi(double r) {
    if (r <= 0)
      throw std::domain_error("Neispravan poluprecnik");
    poluprecnik = r;
  }

  double DajPoluprecnik() const { return poluprecnik; }
  double DajObim() const { return poluprecnik * 2 * pi; }
  double DajPovrsinu() const { return poluprecnik * poluprecnik  * pi; }

  void Skaliraj(double br) {
    if (br <= 0)
      throw std::domain_error("Neispravan faktor skaliranja");
    poluprecnik *= br;
  }

  void Ispisi() const {
    std::cout<<std::setprecision(5)<<std::fixed << "R=" << poluprecnik << " O=" << DajObim()
              << " P=" << DajPovrsinu();
  }  
};



class Valjak{
    Krug baza;
    double visina;
public:

    explicit Valjak(double r, double h):baza(r),visina(h){
        if(r<=0) throw std::domain_error("Neispravan poluprecnik");
        if(h<=0) throw std::domain_error("Neispravna visina");
    }
    


    void Postavi( double r, double h){
        if(r<=0) throw std::domain_error("Neispravan poluprecnik");
        if(h<=0) throw std::domain_error("Neispravna visina");
    baza.Postavi(r);
    visina=h;
    }

    Krug DajBazu() const{return baza;}
    double DajPoluprecnikBaze() const{return baza.DajPoluprecnik();}
    double DajVisinu() const{return visina;}
    double DajPovrsinu() const{
        return 2*baza.DajPovrsinu()+ baza.DajObim()*visina;
    }
    double DajZapreminu() const{
        return baza.DajPovrsinu()*visina;
    }

    void Skaliraj (double faktor){
        if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
        baza.Skaliraj(faktor);
        visina*=faktor;
    }

    void Ispisi() const{
        std::cout<<std::setprecision(5)<<std::fixed<<"R="<<baza.DajPoluprecnik()<<" H="<<visina<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();

    }

};

int main() { return 0; }
