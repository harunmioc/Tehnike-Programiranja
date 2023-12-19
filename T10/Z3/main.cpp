//TP 2022/2023: LV 10, Zadatak 3
#include <iostream>
#include <cmath>


class Vektor3d{
    double koordinate[3];
    mutable int brojacispisa=0;
public:
    Vektor3d(){for(int i{}; i<3; i++)koordinate[i]=0; brojacispisa=0;}
    Vektor3d(double a, double b, double c){ koordinate[0]=a; koordinate[1]=b; koordinate[2]=c; brojacispisa=0;}
    Vektor3d(const Vektor3d &v1){koordinate[0]=v1.DajX(); koordinate[1]=v1.DajY(); koordinate[2]=v1.DajZ(); /*brojacispisa=0;*/}
    Vektor3d &PoataviX(double br){
        koordinate[0]=br;
        return *this;
    }

    Vektor3d &PoataviY(double br){
        koordinate[1]=br;
        return *this;
    }
    Vektor3d &PostaviZ(double br){
        koordinate[2]=br;
        return *this;
    }

    void Postavi(double x, double y, double z){
        koordinate[0]=x; koordinate[1]=y; koordinate[2]=z;
    }

    void Ocitaj(double &x, double &y, double &z) const{
        x=koordinate[0]; y=koordinate[1]; z=koordinate[2];
    }

    void Ispisi() const{
        brojacispisa++;
        std::cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
    }
    int DajBrojIspisa() const{return brojacispisa;}
    double DajX() const{ return koordinate[0];}
    double DajY() const{ return koordinate[1];}
    double DajZ() const{ return koordinate[2];}

    double DajDuzinu() const{ return std::sqrt(koordinate[0]*koordinate[0] + koordinate[1]*koordinate[1] + koordinate[2]*koordinate[2]);}
    Vektor3d &PomnoziSaSkalarom (double skalar){
        koordinate[0]*=skalar;
        koordinate[1]*=skalar;
        koordinate[2]*=skalar;
        return *this;
    }

    Vektor3d &SaberiSa(const Vektor3d &v){
        koordinate[0]+=v.koordinate[0];
        koordinate[1]+=v.koordinate[1];
        koordinate[2]+=v.koordinate[2];
      return *this;
    }
    
    friend Vektor3d ZbirVektora( const Vektor3d &v1, const Vektor3d &v2);
};

    Vektor3d ZbirVektora( const Vektor3d &v1, const Vektor3d &v2){
        Vektor3d v3;
        v3.koordinate[0]=v1.DajX()+v2.DajX();
        v3.koordinate[1]=v1.DajY()+v2.DajY();
        v3.koordinate[2]=v1.DajZ()+v2.DajZ();
      return v3;
    }

int main ()
{


	return 0;
}
