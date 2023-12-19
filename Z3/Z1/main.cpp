// TP 2022/2023: Zadaća 3, Zadatak 1
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

std::function<double(double)>
LagrangeovaInterpolacija(std::vector<std::pair<double, double>> cvorovi) {
  int duzina = cvorovi.size();
  // provjera ispravnih cvorova
  for (int i = 0; i < duzina; i++)
    for (int j = i + 1; j < duzina; j++)
      if (cvorovi.at(i).first == cvorovi.at(j).first)
        throw std::domain_error("Neispravni cvorovi");
  // funkcija proizvoda
  std::function<double(double, int)> fun = [cvorovi](double x, double j) {
    double product = 1;
    for (int i = 0; i < cvorovi.size(); i++) {
      if (i != j)
        product *= (x - cvorovi.at(i).first) /
                   (cvorovi.at(j).first - cvorovi.at(i).first);
    }
    return product;
  };

  std::function<double(double)> P = [fun, cvorovi](double x) {
    double rez = 0;
    for (int i = 0; i < cvorovi.size(); i++)
      rez += cvorovi.at(i).second * fun(x, i);

    return rez;
  };

  return P;
};

std::function<double(double)>
LagrangeovaInterpolacija(const std::function<double(double)> &funkcija,
                         double min, double max, double delta) {
  if (delta <= 0 || min > max)
    throw std::domain_error("Nekorektni parametri");

  std::vector<std::pair<double, double>> cvorovi;
  for (double x = min; x <= max; x += delta)
    cvorovi.push_back(std::make_pair(x, funkcija(x)));

  std::function<double(double)> lagrange = [cvorovi](double x) {
    double rez = 0;

    for (int i = 0; i < cvorovi.size(); i++) {
      double product = 1;
      for (int j = 0; j < cvorovi.size(); j++) {
          if(i==j)continue;
        product *= (x - cvorovi.at(j).first) /
                   (cvorovi.at(i).first - cvorovi.at(j).first);
      }
      rez += cvorovi.at(i).second * product;
    }
    return rez;
  };
  return lagrange;
};

int main() {
  int opcija;

  std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
  std::cin >> opcija;

  if (opcija == 1) {
    std::cout << "Unesite broj cvorova: ";
    int brojcv;
    std::cin >> brojcv;

    std::vector<std::pair<double, double>> cvorovi;
    std::cout<<"Unesite cvorove kao parove x y: ";
    for (int i = 0; i < brojcv; i++) {
      int x, y;
      std::cin >> x >> y;
      cvorovi.push_back(std::make_pair(x, y));

for (int i = 0; i < cvorovi.size(); i++)
    for (int j = i + 1; j < cvorovi.size(); j++)
      if (cvorovi.at(i).first == cvorovi.at(j).first){
        std::cout<<("Neispravni cvorovi");
        return 0;
      }

    }
          int min=cvorovi.begin()->first,max=cvorovi.begin()->first;
          for(int i{}; i<cvorovi.size(); i++){
              if(cvorovi.at(i).first>max) max= cvorovi.at(i).first;
              if(cvorovi.at(i).second>max) max= cvorovi.at(i).second;
              if(cvorovi.at(i).first<min) min= cvorovi.at(i).first;
              if(cvorovi.at(i).second<min) min= cvorovi.at(i).second;

          }

    while (1) {
      try {
          bool ekstrapolacija=false;
        std::cout << "\nUnesite argument (ili \"kraj\" za kraj): ";
        double x;
        std::cin >> x;
        if (std::cin) {
          auto P = LagrangeovaInterpolacija(cvorovi);
          double aprox = P(x);

          std::cout << "f(" << x << ") = " << aprox<<" ";
          //ekstrapolacija
          for(int i{}; i<cvorovi.size(); i++){
              if(x>max || x<min)
                ekstrapolacija=true;
          }
          if(ekstrapolacija==true){
              std::cout<<" [ekstrapolacija]";
              ekstrapolacija=false;
          }

        } else {
          break;
        }
      } catch (std::domain_error izuzetak) {
        std::cout << izuzetak.what();
        break;
      }
    }
  } else if (opcija == 2) {
    double min, max, delta;
    std::cout << "Unesite krajeve intervala i korak: ";
    std::cin >> min >> max >> delta;
    if(min>max || delta<=0){
        std::cout<<"Nekorektni parametri";
        return 0;
    }
    std::function<double(double)> funkc = [](double x) {
      return x * x + std::sin(x) + std::log(x + 1);
    };

    while (1) {
      try {
        std::cout << "\nUnesite argument (ili \"kraj\" za kraj): ";
        double x;
        std::cin >> x;

        if (!std::cin) {
          break;
        }

        auto P = LagrangeovaInterpolacija(funkc, min, max, delta);
        double approx = P(x);
        std::cout << "\nf(" << x << ") = " << funkc(x) << " P(" << x
                  << ") = " << approx;
        if(x<min || x>max)
            std::cout<<" [ekstrapolacija]";

      } catch (std::domain_error izuzetak) {
        std::cout << izuzetak.what();
        break;
      }
    }
  }

  return 0;
}
