// TP 2022/2023: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>
#include <utility>

const double pi = 4 * atan(1);

class Krug {
  double poluprecnik;
  std::pair<double, double> centar;
  static bool BoolJednako(double a, double b) {
    double eps = 1e-10;
    double razlika = std::abs(a - b);
    double suma = std::abs(a) + std::abs(b);
    return razlika <= eps * suma;
  }

public:
  explicit Krug(double poluprecnik = 0);
  explicit Krug(const std::pair<double, double> &centar,
                double poluprecnik = 0);
  std::pair<double, double> DajCentar() const;
  double DajPoluprecnik() const;
  double DajObim() const;
  double DajPovrsinu() const;
  Krug &PostaviCentar(const std::pair<double, double> &centar);
  Krug &PostaviPoluprecnik(double poluprecnik);
  void Ispisi() const;
  Krug &Transliraj(double delta_x, double delta_y);
  Krug &Rotiraj(double alpha);
  Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
  static double RastojanjeCentara(const Krug &k1, const Krug &k2);
  static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2);
  static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2);
  static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2);
  static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2);
  static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2);
  static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2);
  static bool DaLiSeSijeku(const Krug &k1, const Krug &k2);
  bool DaLiSadrzi(const Krug &k) const;
  friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
  friend Krug RotiraniKrug(const Krug &k, double alpha);
  friend Krug RotiraniKrug(const Krug &k,
                           const std::pair<double, double> &centar_rotacije,
                           double alpha);
};

Krug::Krug(double poluprecnik) {
  if (poluprecnik < 0)
    throw std::domain_error("Nedozvoljen poluprecnik");
  centar = std::make_pair(0, 0);
  Krug::poluprecnik = poluprecnik;
}

Krug::Krug(const std::pair<double, double> &centar, double poluprecnik) {
  if (poluprecnik < 0)
    throw std::domain_error("Nedozvoljen poluprecnik");
  Krug::centar = centar;
  Krug::poluprecnik = poluprecnik;
}

std::pair<double, double> Krug::DajCentar() const { return centar; }
double Krug::DajPoluprecnik() const { return poluprecnik; }
double Krug::DajObim() const { return (2 * poluprecnik * pi); }
double Krug::DajPovrsinu() const { return (poluprecnik * poluprecnik * pi); }
Krug &Krug::PostaviCentar(const std::pair<double, double> &centar) {
  Krug::centar = centar;
  return *this;
}
Krug &Krug::PostaviPoluprecnik(double poluprecnik) {
  if (poluprecnik < 0)
    throw std::domain_error("Nedozvoljen poluprecnik");
  Krug::poluprecnik = poluprecnik;
  return *this;
}

void Krug::Ispisi() const {
  std::cout << "{(" << centar.first << "," << centar.second << "),"
            << poluprecnik << "}";
}

Krug &Krug::Transliraj(double delta_x, double delta_y) {
  centar.first += delta_x;
  centar.second += delta_y;
  return *this;
}

Krug &Krug::Rotiraj(double alpha) {
  if (alpha == 0)
    return *this;
  double x = centar.first;
  centar.first = x * std::cos(alpha) - centar.second * std::sin(alpha);
  centar.second = x * std::sin(alpha) + centar.second * std::cos(alpha);
  return *this;
}

Krug &Krug::Rotiraj(const std::pair<double, double> &centar_rotacije,
                    double alpha) {
  double x = centar.first;
  double y = centar.second;
  centar.first = centar_rotacije.first +
                 (x - centar_rotacije.first) * std::cos(alpha) -
                 (y - centar_rotacije.second) * std::sin(alpha);
  centar.second = centar_rotacije.second +
                  (x - centar_rotacije.first) * std::sin(alpha) +
                  (y - centar_rotacije.second) * std::cos(alpha);
  return *this;
}

double Krug::RastojanjeCentara(const Krug &k1, const Krug &k2) {
  return (std::sqrt(std::pow((k2.centar.first - k1.centar.first), 2) +
                    std::pow((k2.centar.second - k1.centar.second), 2)));
}

bool Krug::DaLiSuIdenticni(const Krug &k1, const Krug &k2) {
  return (BoolJednako(k1.centar.first, k2.centar.first) &&
          BoolJednako(k1.centar.second, k2.centar.second) &&
          BoolJednako(k1.poluprecnik, k2.poluprecnik));
}

bool Krug::DaLiSuPodudarni(const Krug &k1, const Krug &k2) {
  return BoolJednako(k1.poluprecnik, k2.poluprecnik);
}

bool Krug::DaLiSuKoncentricni(const Krug &k1, const Krug &k2) {
  return BoolJednako(k1.centar.first, k2.centar.first) &&
         BoolJednako(k1.centar.second, k2.centar.second);
}
// rastojanje centara==sumi poluprecnika
bool Krug::DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2) {
  return BoolJednako(RastojanjeCentara(k1, k2),
                     k1.poluprecnik + k2.poluprecnik);
}
// rastojanje centara==razlici poluprecnika
bool Krug::DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2) {
  return BoolJednako(RastojanjeCentara(k1, k2),
                     std::abs(k1.poluprecnik - k2.poluprecnik));
}
// da li imaju zajednickih tacaka unutar kruznice
bool Krug::DaLiSePreklapaju(const Krug &k1, const Krug &k2) {
  return (RastojanjeCentara(k1, k2) < (k1.poluprecnik + k2.poluprecnik));
}
// 2 presjecne tacke
bool Krug::DaLiSeSijeku(const Krug &k1, const Krug &k2) {
   if( (( RastojanjeCentara(k1, k2) - std::fabs(k1.poluprecnik-k2.poluprecnik)) >1e-10) && ((k1.poluprecnik+k2.poluprecnik-RastojanjeCentara(k1, k2)) > 1e-10) ) return true;
   return false;
}

bool Krug::DaLiSadrzi(const Krug &k) const {
  return RastojanjeCentara(*this, k) + k.poluprecnik <= Krug::poluprecnik;
}

Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y) {
  Krug novi_krug = k;
  novi_krug.Transliraj(delta_x, delta_y);
  return novi_krug;
}

Krug RotiraniKrug(const Krug &k, double alpha) {
  Krug novi_krug = k;
  novi_krug.Rotiraj(alpha);
  return novi_krug;
}

Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rot,
                  double alpha) {
  Krug novi = k;
  novi.Rotiraj(centar_rot, alpha);
  return novi;
}

int main() {
  int n;
  std::cout << "Unesite broj krugova: ";
  std::cin >> n;
  if (n <= 0) {
    std::cout << "\nUneseni broj nije prirodan!";
    return 0;
  }
Krug **krugovi=nullptr;
try{
  Krug **krugovi = new Krug *[n];
  int UspjesnoKreirani = 0;
  for (int i = 0; i < n; i++) {

    bool Unos = false;
    int brojac = 1;
    double x = 0, y = 0, r;

    while (!Unos) {
      int temp = UspjesnoKreirani;
      try {

        std::cout << "Unesite centar " << i + 1 << ". kruga: ";

        std::cin >> x >> y;
        if (!std::cin) {
          std::cout << "Neispravne koordinate centra! Pokusajte ponovo: \n";
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          continue;
        }
        std::cout << "Unesite poluprecnik " << i + 1 << ". kruga: ";
        std::cin >> r;
        if (!std::cin) {
          std::cout << "Nedozvoljen poluprecnik! Pokusajte ponovo:\n";
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          continue;
        }
        // pravi tu
        krugovi[i] = new Krug(std::make_pair(x, y), r);
        UspjesnoKreirani++;

      } catch (std::domain_error izuzetak) {
        std::cout << "Neispravan poluprecnik! Pokusajte ponovo: \n";
      } catch (std::bad_alloc izuzetak) {
        std::cout << "Nedovoljno memorije!";
        for (int j = 0; j < n; j++)
          delete krugovi[j];
        delete[] krugovi;
      }
      if (temp != UspjesnoKreirani)
        Unos = true;
    }
  }



  double delta_x, delta_y, alpha;
  std::cout << "Unesite parametre translacije (delta_x,delta_y): ";
  std::cin >> delta_x >> delta_y;
  std::cout << "Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
  std::cin >> alpha;

  std::transform(krugovi, krugovi + n, krugovi, [delta_x, delta_y](Krug *krug) {
    krug->Transliraj(delta_x, delta_y);
    return krug;
  });
alpha*=pi/180;
  std::transform(krugovi, krugovi + n, krugovi, [alpha](Krug *krug) {
    krug->Rotiraj(alpha);
    return krug;
  });

  std::sort(krugovi, krugovi + n, [](Krug *krug1, Krug *krug2) {
    return krug1->DajPovrsinu() < krug2->DajPovrsinu();
  });

  std::cout << "Parametri krugova nakon obavljene transformacije su: ";
  for (int i = 0; i < n; i++) {
    std::cout << std::endl;
    krugovi[i]->Ispisi();
  }

  Krug *najveciObim =
      *std::max_element(krugovi, krugovi + n, [](Krug *krug1, Krug *krug2) {
        return krug1->DajObim() < krug2->DajObim();
      });

  std::cout << "\nKrug sa najvecim obimom je: ";
  najveciObim->Ispisi();

  int brojacIspisa = 0, brbr=0;

  std::for_each(krugovi, krugovi + n, [&brbr,krugovi, n, &brojacIspisa](Krug *k1) {
      brbr++;
    std::for_each(krugovi+brbr, krugovi + n, [&brbr,k1, &brojacIspisa](Krug *k2) {
      if ((Krug::DaLiSeSijeku(*k1, *k2)  || Krug::DaLiSeDodirujuIznutri(*k1, *k2)) && k1!=k2) {
        std::cout << "\nPresjecaju se krugovi:\n";
        k1->Ispisi();
        std::cout << " i ";
        k2->Ispisi();
        brojacIspisa++;
      }
    });
  });
  if (brojacIspisa == 0)
    std::cout << "\nNe postoje krugovi koji se presjecaju!";

  for (int i = 0; i < n; i++)
    delete krugovi[i];
  delete[] krugovi;
}catch(std::bad_alloc izuzetak){
    std::cout<<"Problemi sa alokacijom memorije!";
    delete [] krugovi;
 }
  return 0;
}