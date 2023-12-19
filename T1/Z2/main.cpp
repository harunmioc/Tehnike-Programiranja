//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>

const double Pi=4*std::atan(1);

int main (){

    double a,b,c;

    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;

    if(a<=0 || b<=0 || c<=0){
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 0;
    }

    if(c>=a+b){
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 0;
    }

    if(a>=b+c){
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 0;
    }

    if(b>=a+c){
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 0;
    }


    double s=(a+b+c)/2;
    double P=std::sqrt(s*(s-a)*(s-b)*(s-c));
    double O=s*2;

    std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<O<<".";
    std::cout<<"\nNjegova povrsina iznosi "<<P<<".";

    double A=std::acos((b*b+c*c-a*a)/(2*b*c));   //a^2= b^2+c^2 - 2bc*cosA
    double B=std::acos((a*a+c*c-b*b)/(2*a*c));   //b^2= c^2+a^2 - 2ac*cosB
    double G=std::acos((a*a+b*b-c*c)/(2*a*b));   //c^2= a^2+b^2 - 2ab*cosC


    double Alfa=A*(180/Pi);
    double Beta=B*(180/Pi);
    double Gama=G*(180/Pi);

    double NajmanjiUgao;

    if(Alfa<=Beta && Alfa<=Gama){
        NajmanjiUgao=Alfa;            
    }

    else if(Beta<=Alfa && Beta<=Gama){
        NajmanjiUgao=Beta;
    }

    else if(Gama<=Alfa && Gama<=Beta){
        NajmanjiUgao=Gama;
    }


    int stepeni=std::floor(NajmanjiUgao);
    double minute=(NajmanjiUgao - std::floor(NajmanjiUgao)) * 60;
    double sekunde=(minute - std::floor(minute)) * 60;

    std::cout<<"\nNjegov najmanji ugao ima "<<stepeni<<" stepeni, "<<(int)minute<<" minuta i "<<(int)sekunde<<" sekundi.";

	return 0;
}