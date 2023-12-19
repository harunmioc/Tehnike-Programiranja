// TP 2022/2023: Zadaća 4, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

const double pi = 4 * atan(1);

class NepreklapajuciKrug {
  static int brojac;
  double poluprecnik;
  std::pair<double, double> centar;

  NepreklapajuciKrug *prethodni = posljednji;
  // epsilon jednakost
  static bool BoolJednako(double a, double b) {
    double eps = 1e-10;
    double razlika = std::abs(a - b);
    double suma = std::abs(a) + std::abs(b);
    return razlika <= eps * suma;
  }
  // preklapanje kruznica
  bool DaLiSePreklapaju(const NepreklapajuciKrug &k) const {
    return RastojanjeCentara(k, *this) <= k.poluprecnik + poluprecnik;
  }
  // poziv provjere preklapanja sa prethodnim
  bool PreklapanjeSaSvim() const {
    const NepreklapajuciKrug *krugTRAZITELJ = posljednji;
    // petlja koja ide od zada i do pocetka i trazi da li se preklapa i sa
    // jednim postojecim osim onog kojeg provjeravamo;
    while (1) {
      if (brojac == 1)
        break;

      if (krugTRAZITELJ == this) {
        krugTRAZITELJ = krugTRAZITELJ->prethodni;
        continue;
      }

      if (DaLiSePreklapaju(*krugTRAZITELJ))
        return true;

      if (krugTRAZITELJ->prethodni == nullptr)
        break;

      krugTRAZITELJ = krugTRAZITELJ->prethodni;
    }

    return false;
  }
  static NepreklapajuciKrug *posljednji;

public:
  explicit NepreklapajuciKrug(double poluprecnik = 0);
  explicit NepreklapajuciKrug(const std::pair<double, double> &centar,
                              double poluprecnik = 0);
  std::pair<double, double> DajCentar() const;
  double DajPoluprecnik() const;
  double DajObim() const;
  double DajPovrsinu() const;
  NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar);
  NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik);
  void Ispisi() const;
  NepreklapajuciKrug &Transliraj(double delta_x, double delta_y);
  NepreklapajuciKrug &Rotiraj(double alpha);
  NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                              double alpha);
  static double RastojanjeCentara(const NepreklapajuciKrug &k1,
                                  const NepreklapajuciKrug &k2);
  bool DaLiSadrzi(const NepreklapajuciKrug &k) const;
  // branimo kompajleru da pravi svoje
  NepreklapajuciKrug(NepreklapajuciKrug const &) = delete;
  NepreklapajuciKrug operator=(NepreklapajuciKrug &) = delete;
};
NepreklapajuciKrug *NepreklapajuciKrug::posljednji = nullptr;
int NepreklapajuciKrug::brojac = 0;

//  konstuktor  //
NepreklapajuciKrug::NepreklapajuciKrug(double poluprecnik) {
  if (poluprecnik < 0)
    throw std::domain_error("Nedozvoljen poluprecnik");

  centar = std::make_pair(0, 0);
  NepreklapajuciKrug::poluprecnik = poluprecnik;
  brojac++;

  // provjerava preklapanje//
  if (brojac != 0 && PreklapanjeSaSvim()){
      brojac--;
    throw std::logic_error("Nedozvoljeno preklapanje");
  }
  if (brojac != 0)
    this->prethodni = posljednji;
  posljednji = this;
}

NepreklapajuciKrug::NepreklapajuciKrug(const std::pair<double, double> &centar,
                                       double poluprecnik) {

  if (poluprecnik < 0)
    throw std::domain_error("Nedozvoljen poluprecnik");
  NepreklapajuciKrug::centar = centar;
  NepreklapajuciKrug::poluprecnik = poluprecnik;
  // provjerava preklapanje 
   
   brojac++;
  if (brojac != 0 && PreklapanjeSaSvim()){
      brojac--;
    throw std::logic_error("Nedozvoljeno preklapanje");
  }
  if (brojac != 0)
    this->prethodni = posljednji;
  posljednji = this;
}
NepreklapajuciKrug &
NepreklapajuciKrug::PostaviCentar(const std::pair<double, double> &centar) {
  auto tempcentar = NepreklapajuciKrug::centar;
  NepreklapajuciKrug::centar = centar;
  if (brojac != 0 && PreklapanjeSaSvim()) {
    NepreklapajuciKrug::centar = tempcentar;
    throw std::logic_error("Nedozvoljeno preklapanje");
  }
  return *this;
}
NepreklapajuciKrug &NepreklapajuciKrug::PostaviPoluprecnik(double poluprecnik) {
  if (poluprecnik < 0)
    throw std::domain_error("Nedozvoljen poluprecnik");
  auto temppoluprecnik = NepreklapajuciKrug::poluprecnik;

  NepreklapajuciKrug::poluprecnik = poluprecnik;
  if (brojac != 0 && PreklapanjeSaSvim()) {
    NepreklapajuciKrug::poluprecnik = temppoluprecnik;
    throw std::logic_error("Nedozvoljeno preklapanje");
  }
  return *this;
}

NepreklapajuciKrug &NepreklapajuciKrug::Transliraj(double delta_x,
                                                   double delta_y) {
  centar.first += delta_x;
  centar.second += delta_y;
  if (brojac != 0 && PreklapanjeSaSvim()) {
    centar.first -= delta_x;
    centar.second -= delta_y;
    throw std::logic_error("Nedozvoljeno preklapanje");
  }
  return *this;
}

NepreklapajuciKrug &NepreklapajuciKrug::Rotiraj(double alpha) {
  alpha *= pi / 180;
  double x = centar.first;
  double y = centar.second;
  centar.first = x * std::cos(alpha) - centar.second * std::sin(alpha);
  centar.second = x * std::sin(alpha) + centar.second * std::cos(alpha);
  if (brojac != 0 && PreklapanjeSaSvim()) {
    NepreklapajuciKrug::centar.first = x;
    NepreklapajuciKrug::centar.second = y;
    throw std::domain_error("Nedozvoljeno preklapanje");
  }
  return *this;
}

NepreklapajuciKrug &
NepreklapajuciKrug::Rotiraj(const std::pair<double, double> &centar_rotacije,
                            double alpha) {
  alpha *= pi / 180;
  double x = centar.first;
  double y = centar.second;
  centar.first = centar_rotacije.first +
                 (x - centar_rotacije.first) * std::cos(alpha) -
                 (y - centar_rotacije.second) * std::sin(alpha);
  centar.second = centar_rotacije.second +
                  (x - centar_rotacije.first) * std::sin(alpha) +
                  (y - centar_rotacije.second) * std::cos(alpha);
  if (brojac != 0 && PreklapanjeSaSvim()) {
    NepreklapajuciKrug::centar.first = x;
    NepreklapajuciKrug::centar.second = y;
    throw std::logic_error("Nedozvoljeno preklapanje");
  }
  return *this;
}

std::pair<double, double> NepreklapajuciKrug::DajCentar() const {
  return centar;
}
double NepreklapajuciKrug::DajPoluprecnik() const { return poluprecnik; }
double NepreklapajuciKrug::DajObim() const { return (2 * poluprecnik * pi); }
double NepreklapajuciKrug::DajPovrsinu() const {
  return (poluprecnik * poluprecnik * pi);
}
void NepreklapajuciKrug::Ispisi() const {
  std::cout << "{(" << centar.first << "," << centar.second << "),"
            << poluprecnik << "}\n";
}

double NepreklapajuciKrug::RastojanjeCentara(const NepreklapajuciKrug &k1,
                                             const NepreklapajuciKrug &k2) {
  return (std::sqrt(std::pow((k2.centar.first - k1.centar.first), 2) +
                    std::pow((k2.centar.second - k1.centar.second), 2)));
}

bool NepreklapajuciKrug::DaLiSadrzi(const NepreklapajuciKrug &k) const {
  return RastojanjeCentara(*this, k) + k.poluprecnik <=
         NepreklapajuciKrug::poluprecnik;
}

int main() {

  int n;
  std::cout << "Unesite broj krugova: ";
  while (1) {
    std::cin >> n;
    if (n <= 0)
      std::cout << "Neispravan broj krugova, unesite ponovo! ";
    else
      break;
  }

  std::vector<std::shared_ptr<NepreklapajuciKrug>> krugovi;
  for (int i = 0; i < n; i++) {
    bool Unos = false;
    int brojac = 0;
    double x, y, r;
    while (!Unos) {
      int temp = krugovi.size();
      try {
        if (brojac == 0 || brojac == 2) {
          if (brojac == 0)
            std::cout << "Unesite centar za " << i + 1 << ". krug: ";
          if (brojac == 2)
            std::cout << "Unesite ponovo centar za " << i + 1 << ". krug: ";

          std::cin >> x >> y;
          if (!std::cin) {
            std::cout << "Neispravan centar!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            brojac = 2;
            continue;
          }
          std::cout << "Unesite poluprecnik: ";
          std::cin >> r;
          if (!std::cin || r < 0) {
            std::cout << "Neispravan poluprecnik!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            brojac = 1;
            continue;
          }

          std::shared_ptr<NepreklapajuciKrug> krug =
              std::make_shared<NepreklapajuciKrug>(std::make_pair(x, y), r);
          krugovi.push_back(krug);
        } else if (brojac == 1) {
          std::cout << "Unesite ponovo poluprecnik za " << i + 1 << ". krug: ";
          std::cin >> r;
          if (!std::cin)
            continue;
          std::shared_ptr<NepreklapajuciKrug> krug =
              std::make_shared<NepreklapajuciKrug>(std::make_pair(x, y), r);
          krugovi.push_back(krug);
        }

      } catch (std::domain_error izuzetak) {
        std::cout << "Neispravan poluprecnik!" << std::endl;
        brojac = 1;
      } catch (std::logic_error izuzetak) {
        std::cout << izuzetak.what() << std::endl;
      }

      if (krugovi.size() != temp)
        Unos = true;
    }
  }

  std::sort(krugovi.begin(), krugovi.end(), [](const auto &k1, const auto &k2) {
    return k1->DajPovrsinu() >=
           k2->DajPovrsinu(); //>= da zadrzi redoslijed ako su isti
  });

  std::cout << "Krugovi nakon obavljenog sortiranja:\n";

  for (int i = 0; i < krugovi.size(); i++) {
    krugovi.at(i)->Ispisi();
  }
  return 0;
}
