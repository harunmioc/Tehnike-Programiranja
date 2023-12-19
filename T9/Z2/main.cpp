//TP 2022/2023: LV 9, Zadatak 2
#include <iostream>
#include <cmath>


    class Vektor3d {
        double koordinate[3];

    public:
        void Postavi(double x, double y, double z){
           koordinate[0]=x; koordinate[1]=y; koordinate[2]=z;
        }
        void PostaviX( double x){
           koordinate[0]=x;
        }
        void PostaviY( double y){
            koordinate[1]=y;
        }
        void PostaviZ( double z){
            koordinate[2]=z;
        }

        void Ocitaj (double &x, double &y, double &z) const {
            x=koordinate[0]; y=koordinate[1]; z=koordinate[2];}
        void Ispisi() const { std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}"; }
        double DajX() const { return koordinate[0]; }
        double DajY() const { return koordinate[1]; }
        double DajZ() const { return koordinate[2]; }
        double DajDuzinu() const { return std::sqrt(koordinate[0] * koordinate[0] + koordinate[1] * koordinate[1] + koordinate[2] * koordinate[2]); }
        Vektor3d &PomnoziSaSkalarom(double s) { koordinate[0] *= s; koordinate[1] *= s; koordinate[2] *= s; 
        return *this; }
        Vektor3d &SaberiSa(const Vektor3d &v) { koordinate[0] += v.koordinate[0]; koordinate[1] += v.koordinate[1]; koordinate[2] += v.koordinate[2]; return *this;}

        friend Vektor3d ZbirVektora (const Vektor3d &v1, const Vektor3d &v2){
            Vektor3d v3;
            v3.koordinate[0]=v1.koordinate[0]+v2.koordinate[0] ; v3.koordinate[1]= v1.koordinate[1]+v2.koordinate[1]; v3.koordinate[2]=v1.koordinate[2]+v2.koordinate[2];
            return v3;
        }
    };



int main ()
{
    Vektor3d v1, v2, v3;
    double x,y,z;

    std::cout<<"Unesi koordinate prvog vektora: ";
    std::cin>>x>>y>>z;

    v1.Postavi(x, y, z);

    std::cout<<"Unesi koordinate prvog vektora: ";
    std::cin>>x>>y>>z;

    v2.Postavi(x, y, z);

    v3=ZbirVektora(v1.SaberiSa(v2),v2.PomnoziSaSkalarom(10));

    v1.Ispisi();v2.Ispisi();v3.Ispisi();


	return 0;
}
