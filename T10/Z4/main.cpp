
#include <cmath>
#include <iomanip>
#include <iostream>

const double PI = 4 * std::atan(1);
class Ugao {
  double ugao;

public:
  Ugao(double radijani = 0) { Postavi(radijani); }
  Ugao(int stepeni, int minute, int sekunde) {
    Postavi(stepeni, minute, sekunde);
  }
  void Postavi(double radijani) {
    while (radijani < 0)
      radijani += 2 * PI;
    while (radijani >= 2 * PI)
      radijani -= 2 * PI;
    ugao = radijani;
  }
  void Postavi(int stepeni, int minute, int sekunde) {
    double kut = (sekunde / 3600. + minute / 60. + stepeni) * (PI / 180.) +
                 std::pow(10, -16);
    while (kut < 0)
      kut += 2 * PI;
    while (kut >= 2 * PI)
      kut -= 2 * PI;
    ugao = kut;
  }
  double DajRadijane() const { return ugao; }
  void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {
    stepeni = DajStepene();
    minute = DajMinute();
    sekunde = DajSekunde();
  }
  int DajStepene() const { return ugao * 180 / PI; }
  int DajMinute() const {
    double pom = ugao * 180 / PI;
    int stepeni = pom;
    pom = (pom - stepeni) * 60;
    return pom;
  }
  int DajSekunde() const {
    double pom = ugao * 180 / PI;
    int stepeni = pom;
    pom = (pom - stepeni) * 60;
    int minute = pom;
    pom = (pom - minute) * 60;
    return pom;
  }
  void Ispisi() const {
    std::cout << std::fixed << std::setprecision(5) << DajRadijane();
  }
  void IspisiKlasicno() const {
    std::cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde()
              << "sec ";
  }
  Ugao &SaberiSa(const Ugao &u) {
    ugao += u.ugao;
    Postavi(ugao);
    return *this;
  }
  Ugao &PomnoziSa(double x) {
    ugao *= x;
    Postavi(ugao);
    return *this;
  }
  friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2) {
    return Ugao(u1.ugao + u2.ugao);
  }
  friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x) {
    return u.DajRadijane() * x;
  }
};

int main() {
  Ugao u1;
  u1.Ispisi();
  std::cout << std::endl;
  Ugao u2(23, 11, 01);
  u2.IspisiKlasicno();
  std::cout << std::endl;
  u1.SaberiSa(u2);
  std::cout << "radijani: " << u1.DajRadijane() << ", " << u1.DajStepene()
            << "deg " << u1.DajMinute() << "min " << u1.DajSekunde() << "sec"
            << std::endl;
  Ugao u3 = ZbirUglova(u1, u2);
  u3.Ispisi();
  std::cout << std::endl;
  u3.Postavi(411);
  u3.IspisiKlasicno();
  std::cout << std::endl;
  int stepeni, minute, sekunde;
  u3.OcitajKlasicneJedinice(stepeni, minute, sekunde);
  std::cout << "stepeni: " << stepeni << ", minute: " << minute
            << ", sekunde: " << sekunde << std::endl;
  u3.PomnoziSa(2);
  u3.Ispisi();
  std::cout << std::endl;




  
  Ugao u4 = ProduktUglaSaBrojem(u3, 2);
  u1=ProduktUglaSaBrojem(u3,2);
  std::cout<<"\nispis u4:";
  u4.Ispisi();
  std::cout<<"\nispis u1 isti kao u4: ";
  u1.Ispisi();
  return 0;
}