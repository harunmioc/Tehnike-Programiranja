//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <complex>
#include <tuple>


const double pi= atan(1)*4;

class Sinusoida{
    double amplituda;
    double frekvencija;
    double fi;

    void normiraj(){
        if(amplituda<0){
            amplituda=std::abs(amplituda);
            fi+=pi;
        }
        if(frekvencija<0){
            frekvencija=std::abs(frekvencija);
            fi=-fi+pi;
        }
        while(fi <-pi)
            fi+=2*pi;
        while(fi >pi)
            fi-=2*pi;
    }


public:
    Sinusoida(double ampl, double frekv, double F);
        double DajAmplitudu() const {return amplituda;}
        double DajFrekvenciju() const {return frekvencija;}
        double DajFazu() const{return fi;}
        std::tuple<double, double, double> DajParametre() const{
                return std::make_tuple(amplituda, frekvencija, fi);
        }

    Sinusoida& PostaviAmplitudu(double ampl);
    Sinusoida& PostaviFrekvenciju( double frekv);
    Sinusoida& PostaviFazu( double F);
    Sinusoida& PostaviParametre( std::tuple<double,double,double> tapl);
    friend Sinusoida operator -(Sinusoida &s);
    friend Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida operator *(const Sinusoida &s1, double skalar);
    friend Sinusoida operator /(const Sinusoida &s1, double skalar);

    friend Sinusoida operator *(const double skalar, const Sinusoida &s);
    friend Sinusoida operator /(const double skalar,const Sinusoida &s);

    friend Sinusoida &operator +=( Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida &operator -=( Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida &operator *=( Sinusoida &s1, double skalar);
    friend Sinusoida &operator /=( Sinusoida &s1, double skalar);

    double operator [](const std::string &parametar) const;
    double &operator [](const std::string &sparametar);

    double operator ()(double t)const;
};

    Sinusoida::Sinusoida(double A, double frekv, double F):amplituda(A), frekvencija(frekv), fi(F){
        normiraj();
    }

    Sinusoida& Sinusoida::PostaviAmplitudu(double ampl){
        amplituda=ampl;
        normiraj();
        return *this;
    }

    Sinusoida& Sinusoida::PostaviFrekvenciju(double frekv){
        frekvencija=frekv;
        normiraj();
        return *this;
    }

    Sinusoida& Sinusoida::PostaviFazu(double F){
        fi=F;
        normiraj();
        return *this;
    }

    Sinusoida& Sinusoida::PostaviParametre(std::tuple<double, double, double> tapl){
       std::tie(amplituda, frekvencija, fi) = tapl;
       normiraj();
        return *this;
    }
//???????????????
    Sinusoida operator -(Sinusoida &s){
        Sinusoida rez(-s.amplituda, s.frekvencija, s.fi);
        s.normiraj();
        rez.normiraj();
        return rez;
    }

    
    Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2){
        if(std::abs(s1.frekvencija-s2.frekvencija)>0)
            throw std::domain_error("Razlicite frekvencije");
        std::complex<double> sinusoida1 (s1.amplituda*std::cos(s1.fi), s1.amplituda * std::sin(s1.fi));
        std::complex<double> sinusoida2 (s2.amplituda*std::cos(s2.fi), s2.amplituda * std::sin(s2.fi));

        std::complex<double> s3=sinusoida1+sinusoida2;
        Sinusoida rez(std::abs(s3), s1.frekvencija ,std::arg(s3));
        rez.normiraj();
        return rez;
    }

    Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2){
        if(std::abs(s1.frekvencija-s2.frekvencija)>0)
            throw std::domain_error("Razlicite frekvencije");

        std::complex<double> sinusoida1 (s1.amplituda*std::cos(s1.fi), s1.amplituda * std::sin(s1.fi));
        std::complex<double> sinusoida2 (s2.amplituda*std::cos(s2.fi), s2.amplituda * std::sin(s2.fi));

        std::complex<double> s3=sinusoida1 - sinusoida2;
        Sinusoida rez (std::abs(s3), s1.frekvencija ,std::arg(s3));
        rez.normiraj();

        return rez;
    }


    Sinusoida operator *(const Sinusoida &s, double skalar){
        Sinusoida rez(s.amplituda*skalar, s.frekvencija, s.fi);
        rez.normiraj();
        return rez;
    }
    Sinusoida operator /(const Sinusoida &s, double skalar){
    
    Sinusoida rez(s.amplituda/skalar, s.frekvencija, s.fi);
    rez.normiraj();
    return rez;    
    }

    Sinusoida& operator +=( Sinusoida &s1, const Sinusoida &s2){
        Sinusoida rez=s1+s2;
        rez.normiraj();
        s1=rez;
        return s1;
    }
    Sinusoida& operator -=( Sinusoida &s1, const Sinusoida &s2){
        Sinusoida rez=s1-s2;
        rez.normiraj();
        s1=rez;
        return s1;
    }
    Sinusoida& operator *=( Sinusoida &s1, double skalar){
        s1= s1*skalar;
        s1.normiraj();
        return s1;
    }
    Sinusoida& operator /=( Sinusoida &s1, double skalar){
        s1= s1/skalar;
        s1.normiraj();
        return s1;
    }

    double Sinusoida::operator [](const std::string &parametar) const{
        if(parametar=="A")
            return amplituda;
        else if(parametar=="w" || parametar=="omega")
            return frekvencija;
        else if(parametar=="fi" || parametar=="phi")
            return fi;
        else
            throw std::domain_error("Neispravan naziv parametra");
    }

    double &Sinusoida::operator [](const std::string &parametar){
        if(parametar=="A")
            return amplituda;
        else if(parametar=="w" || parametar=="omega")
            return frekvencija;
        else if(parametar=="fi" || parametar=="phi")
            return fi;
        else
            throw std::domain_error("Neispravan naziv parametra");
    }

    double Sinusoida::operator ()(double t)const{
        return amplituda* std::sin(frekvencija*t + fi);
    }



    Sinusoida operator *(const double skalar, const Sinusoida &s){
        Sinusoida rez(s.amplituda*skalar, s.frekvencija, s.fi);
        rez.normiraj();
        return rez;

    }
    Sinusoida operator /(const double skalar,const Sinusoida &s){
    
    Sinusoida rez(s.amplituda/skalar, s.frekvencija, s.fi);
    rez.normiraj();
    return rez;    

    }




int main ()
{


	return 0;
}
