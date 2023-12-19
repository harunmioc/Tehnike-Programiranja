// TP 2022/2023: LV 13, Zadatak 3
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class ApstraktniStudent {
  std::string ime, prezime;
  int indeks, polozeni_ispiti;
  double prosjek;

public:
  ApstraktniStudent(std::string ime, std::string prezime, int indeks) {
    ApstraktniStudent::ime = ime;
    ApstraktniStudent::prezime = prezime;
    ApstraktniStudent::indeks = indeks;
    polozeni_ispiti = 0;
    prosjek = 5;
  }
  virtual ~ApstraktniStudent() {}
  std::string DajIme() const { return ime; }
  std::string DajPrezime() const { return prezime; }
  int DajBrojIndeksa() const { return indeks; }
  int DajBrojPolozenih() const { return polozeni_ispiti; }
  double DajProsjek() const { return prosjek; }
  void RegistrirajIspit(int nova) {
    if (nova < 5 || nova > 10)
      throw std::domain_error("Neispravna ocjena");
    if (nova != 5) {
      double pom = prosjek * polozeni_ispiti;
      polozeni_ispiti++;
      prosjek = (pom + nova) / polozeni_ispiti;
    }
  }
  void PonistiOcjene() {
    polozeni_ispiti = 0;
    prosjek = 5;
  }
  virtual void IspisiPodatke() const = 0;
  virtual ApstraktniStudent *DajKopiju() const = 0;
};


class StudentBachelor : public ApstraktniStudent {
public:
  StudentBachelor(std::string ime, std::string prezime, int indeks)
      : ApstraktniStudent(ime, prezime, indeks) {}
  void IspisiPodatke() const {
    std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime()
              << ", sa brojem indeksa " << DajBrojIndeksa() << "," << std::endl;
    std::cout << "ima prosjek " << DajProsjek() << "." << std::endl;
  }
  StudentBachelor *DajKopiju() const { return new StudentBachelor(*this); }
};



class StudentMaster : public ApstraktniStudent {
  int godina;

public:
  StudentMaster(std::string ime, std::string prezime, int indeks, int godina)
      : ApstraktniStudent(ime, prezime, indeks), godina(godina) {}
  void IspisiPodatke() const {
    std::cout << "Student master studija " << DajIme() << " " << DajPrezime()
              << ", sa brojem indeksa " << DajBrojIndeksa() << "," << std::endl;
    std::cout << "zavrsio bachelor studij godine " << godina << ",ima prosjek "
              << DajProsjek() << "." << std::endl;
  }
  StudentMaster *DajKopiju() const { return new StudentMaster(*this); }
};



class Fakultet {
  std::vector<ApstraktniStudent *> v;

public:
  Fakultet() {}
  ~Fakultet() {
    for (int i = 0; i < v.size(); i++) {
      delete v[i];
      v[i] = nullptr;
    }
  }
  Fakultet(const Fakultet &f) : v(f.v) {
    for (int i = 0; i < f.v.size(); i++) {
      v[i] = f.v[i]->DajKopiju();
    }
  }

  Fakultet &operator=(const Fakultet &f) {
    std::vector<ApstraktniStudent *> pomocni(f.v.size());
    try {
      for (int i = 0; i < pomocni.size(); i++) {
        pomocni[i] = f.v[i]->DajKopiju();
      }
    } catch (...) {
      throw;
    }
    for (int i = 0; i < v.size(); i++) {
      delete v[i];
      v[i] = nullptr;
    }
    v = pomocni;
    return *this;
  }
  Fakultet(Fakultet &&f) : v(f.v.size()) {
      
    for (int i = 0; i < v.size(); i++)
      delete v[i];
    v.resize(f.v.size());
    try {
      for (int i = 0; i < v.size(); i++) {
        v[i] = f.v[i]->DajKopiju();
      }
    } catch (...) {
      throw;
    }
    for (int i = 0; i < f.v.size(); i++) {
      delete f.v[i];
      f.v[i] = nullptr;
    }
    f.v.resize(0);
  }
  Fakultet &operator=(Fakultet &&f) {
    for (int i = 0; i < v.size(); i++)
      delete v[i];
    v.resize(f.v.size());
    try {
      for (int i = 0; i < v.size(); i++) {
        v[i] = f.v[i]->DajKopiju();
      }
    } catch (...) {
      throw;
    }
    for (int i = 0; i < f.v.size(); i++) {
      delete f.v[i];
      f.v[i] = nullptr;
    }
    f.v.resize(0);
    return *this;
  }
  void UpisiStudenta(std::string ime, std::string prezime, int indeks) {
    for (int i = 0; i < v.size(); i++) {
      if (indeks == v[i]->DajBrojIndeksa())
        throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    }
    ApstraktniStudent *pomoc = new StudentBachelor(ime, prezime, indeks);
    v.push_back(pomoc);
  }
  void UpisiStudenta(std::string ime, std::string prezime, int indeks,
                     int godina) {
    for (int i = 0; i < v.size(); i++) {
      if (indeks == v[i]->DajBrojIndeksa())
        throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    }
    ApstraktniStudent *pomoc = new StudentMaster(ime, prezime, indeks, godina);
    v.push_back(pomoc);
  }
  void ObrisiStudenta(int indeks) {
    for (int i = 0; i < v.size(); i++) {
      if (indeks == v[i]->DajBrojIndeksa())
        break;
      if (i == v.size() - 1 && indeks != v[i]->DajBrojIndeksa())
        throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    }
    int mjesto(0);
    for (int i = 0; i < v.size(); i++) {
      if (v[i]->DajBrojIndeksa() == indeks) {
        delete v[i];
        mjesto = i;
        break;
      }
    }
    v.erase(v.begin() + mjesto);
  }
  const ApstraktniStudent &operator[](int indeks) const {
    for (int i = 0; i < v.size(); i++) {
      if (indeks == v[i]->DajBrojIndeksa())
        break;
      if (i == v.size() - 1 && indeks != v[i]->DajBrojIndeksa())
        throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    }
    int pom = 0;
    for (int i = 0; i < v.size(); i++) {
      if (v[i]->DajBrojIndeksa() == indeks)
        pom = i;
    }
    return *v[pom];
  }
  ApstraktniStudent &operator[](int indeks) {
    for (int i = 0; i < v.size(); i++) {
      if (indeks == v[i]->DajBrojIndeksa())
        break;
      if (i == v.size() - 1 && indeks != v[i]->DajBrojIndeksa())
        throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    }
    int pom = 0;
    for (int i = 0; i < v.size(); i++) {
      if (v[i]->DajBrojIndeksa() == indeks)
        pom = i;
    }
    return *v[pom];
  }
  void IspisiSveStudente() const {
    auto pomocni = v;
    std::sort(pomocni.begin(), pomocni.end(),
              [](ApstraktniStudent *s1, ApstraktniStudent *s2) {
                if (s1->DajProsjek() == s2->DajProsjek())
                  return s1->DajBrojIndeksa() < s2->DajBrojIndeksa();
                return s1->DajProsjek() > s2->DajProsjek();
              });
    for (int i = 0; i < pomocni.size(); i++)
      pomocni[i]->IspisiPodatke();
  }
};
int main() {
  Fakultet f;
  f.UpisiStudenta("Dalila", "Krslak", 18906);
  f.UpisiStudenta("Faris", "Tahirovic", 21011);
  f.IspisiSveStudente();
  return 0;
}