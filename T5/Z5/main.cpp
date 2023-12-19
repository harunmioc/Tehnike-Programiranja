//TP 2022/2023: LV 5, Zadatak 5
#include <iostream>
#include <cmath>
#include <iomanip>

const double Pi= 4*atan(1);


  double  TrapeznoPravilo(double fun(double), double a, double b, int n){
    double rezultat=0;

        rezultat=(0.5)*fun(a)  +  (0.5)*fun(b);

            for(int k=1; k<=n-1; k++){
                rezultat+=fun(a+(((b-a)/n)*k));
            }

        rezultat*= (b-a)/n;

     return rezultat;
    }



int main ()
{
    int n;
    std::cout<<"Unesite broj podintervala: ";
    std::cin>>n;

    std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose: ";
    std::cout<<std::fixed<<std::setprecision(5)<<"\n- Za funkciju sin x na intervalu (0,pi): "<<TrapeznoPravilo( std::sin,0, Pi, n );	
    
    std::cout<<std::fixed<<std::setprecision(2)<<"\n- Za funkciju x^3 na intervalu (0,10): "<<TrapeznoPravilo( [](double x){return x*x*x;}, 0, 10, n);

    std::cout<<std::fixed<<std::setprecision(5)<<"\n- Za funkciju 1/x na intervalu (1,2): "<<TrapeznoPravilo([] (double x){return 1./x;}, 1, 2, n);

    return 0;}
