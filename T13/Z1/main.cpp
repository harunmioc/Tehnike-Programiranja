// TP 2022/2023: LV 13, Zadatak 1
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

const double pi = 4 * atan(1);

class Lik {
public:
  virtual void IspisiSpecificnosti() const = 0;
  virtual double DajObim() const = 0;
  virtual double DajPovrsinu() const = 0;
  void Ispisi() {
    IspisiSpecificnosti();
    std::cout << "Obim: " << DajObim() << " Povrsina: " << DajPovrsinu()
              << std::endl;
  }
  virtual ~Lik(){};
};

class Krug : public Lik {
protected:
  double poluprecnik;

public:
  Krug(double poluprecnik) {
    if (poluprecnik <= 0)
      throw std::domain_error("Neispravni parametri");
    Krug::poluprecnik = poluprecnik;
  }
  void IspisiSpecificnosti() const {
    std::cout << "Krug poluprecnika " << poluprecnik << std::endl;
  }
  double DajObim() const { return 2 * poluprecnik * pi; }
  double DajPovrsinu() const { return poluprecnik * poluprecnik * pi; }
};

class Pravougaonik : public Lik {
protected:
  double a, b;

public:
  Pravougaonik(double a, double b) {
    if (a <= 0 || b <= 0)
      throw std::domain_error("Neispravni parametri");
    Pravougaonik::a = a;
    Pravougaonik::b = b;
  }
  void IspisiSpecificnosti() const {
    std::cout << "Pravougaonik sa stranicama duzine " << a << " i " << b
              << std::endl;
  }
  double DajObim() const { return 2 * a + 2 * b; }
  double DajPovrsinu() const { return a * b; }
};

class Trougao : public Lik {
protected:
  double a, b, c;

public:
  Trougao(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
      throw std::domain_error("Neispravni parametri");
    else if (a + b <= c || a + c <= b || b + c <= a)
      throw std::domain_error("Neispravni parametri");
    Trougao::a = a;
    Trougao::b = b;
    Trougao::c = c;
  }
  void IspisiSpecificnosti() const {
    std::cout << "Trougao sa stranicama duzine " << a << ", " << b << " i " << c
              << std::endl;
  }
  double DajObim() const { return a + b + c; }
  double DajPovrsinu() const {
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
  }
};

int main() {

  int n;
  std::vector<std::shared_ptr<Lik>> likovi;
  std::cout << "Koliko zelite likova: ";
  std::cin >> n;

  int i = 0;
  std::cin.clear();
  std::cin.ignore(10000, '\n');

char tip;
double a, b, c;
  while (i < n) {
    std::cout << "Lik " << i + 1 << ": ";
    std::cin >> tip;
    if (tip == 'P') {
      std::cin >> a;
      if (std::cin.fail()) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      char c;
      std::cin >> c;
      if (c != ',') {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      std::cin >> b;
      if (std::cin.fail()) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      try {
        Pravougaonik p(a, b);
        auto pok = std::make_shared<Pravougaonik>(p);
        likovi.push_back(pok);
      } catch (...) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        if (std::cin.peek() != EOF) {
          std::cin.clear();
          std::cin.ignore(10000, '\n');
        }
        continue;
      }
    } 
    
    
    
    else if (tip == 'K') {
      std::cin >> a;
      if (std::cin.fail()) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      } else {
        auto c = std::getchar();
        if (c != 10) {
          std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          continue;
        }
      }
      try {
        Krug k(a);
        auto pok = std::make_shared<Krug>(k);
        likovi.push_back(pok);
      } catch (...) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        continue;
      }
    } 
    
    
    else if (tip == 'T') {
      std::cin >> a;
      if (std::cin.fail()) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      char d;
      std::cin >> d;
      if (d != ',') {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      std::cin >> b;
      if (std::cin.fail()) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      std::cin >> d;
      if (d != ',') {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      std::cin >> c;
      if (std::cin.fail()) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      try {
        Trougao t(a, b, c);
        auto pok = std::make_shared<Trougao>(t);
        likovi.push_back(pok);
      } catch (...) {
        std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
        if (std::cin.peek() != EOF) {
          std::cin.clear();
          std::cin.ignore(10000, '\n');
        }
        continue;
      }
    } else {
      i--;
      std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
    i++;
  }

  for (int i = 0; i < likovi.size(); i++) {
    likovi.at(i)->Ispisi();
  }

  return 0;
}