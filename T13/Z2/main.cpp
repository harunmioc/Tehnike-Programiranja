// TP 2022/2023: LV 13, Zadatak 2
#include <cmath>
#include <iostream>
#include <string>

class ApstraktniStudent {
  std::string ime, prezime;
  int broj_indeksa;
  int broj_polozenih;
  double prosjek;

public:
  ApstraktniStudent() = default;
  ApstraktniStudent(std::string ime, std::string prezime, int broj_ind)
      : ime(ime), prezime(prezime), broj_indeksa(broj_ind), broj_polozenih(0),
        prosjek(5) {}
  std::string DajIme() const { return ime; }
  std::string DajPrezime() const { return prezime; }
  int DajBrojIndeksa() const { return broj_indeksa; }
  int DajBrojPolozenih() const { return broj_polozenih; }
  double DajProsjek() const { return prosjek; }
  void RegistrirajIspit(int ocjena) {
    if (ocjena < 5 || ocjena > 10)
      throw std::domain_error("Neispravna ocjena");
    if (ocjena != 5) {
      broj_polozenih++;
      if (prosjek == 5)
        prosjek = ocjena;
      else {
        prosjek = prosjek + (ocjena - prosjek) / broj_polozenih;
      }
    }
  }
  void PonistiOcjene() {
    prosjek = 5;
    broj_polozenih = 0;
  }
    virtual void IspisiPodatke() const = 0;
    virtual ApstraktniStudent *DajKopiju() const = 0;
  virtual ~ApstraktniStudent(){};
};



class StudentBachelor : public ApstraktniStudent {
public:
  StudentBachelor(std::string ime, std::string prezime, int broj_ind)
      : ApstraktniStudent(ime, prezime, broj_ind) {}

  void IspisiPodatke() const override {
    std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime()
              << ", sa brojem indeksa " << DajBrojIndeksa() << ",\n"
              << "ima prosjek " << DajProsjek() << "." << std::endl;
  }

  StudentBachelor *DajKopiju() const override {
    return new StudentBachelor(*this);
  }
};

class StudentMaster : public ApstraktniStudent {
protected:
  int godina_zavrsetka;

public:
  StudentMaster(std::string ime, std::string prezime, int broj_ind, int godina)
      : ApstraktniStudent(ime, prezime, broj_ind), godina_zavrsetka(godina) {}

  void IspisiPodatke() const override {
    std::cout << "Student master studija " << DajIme() << " " << DajPrezime()
              << ", sa brojem indeksa " << DajBrojIndeksa() << ",\n"
              << "zavrsio bachelor studij godine " << godina_zavrsetka
              << ",ima prosjek " << DajProsjek() << "." << std::endl;
  }

  StudentMaster *DajKopiju() const override { return new StudentMaster(*this); }
};

int main() {

  ApstraktniStudent *pok;
  pok = new StudentBachelor("Dusko", "Dugousko", 1234);
  pok->RegistrirajIspit(7);
  pok->RegistrirajIspit(6);
  pok->RegistrirajIspit(5);
  pok->RegistrirajIspit(10);
  pok->RegistrirajIspit(7);
  std::cout << pok->DajIme() << " " << pok->DajPrezime() << " "
            << pok->DajBrojIndeksa() << " " << pok->DajBrojPolozenih() << " "
            << pok->DajProsjek() << std::endl;
  pok->IspisiPodatke();
  delete pok;
  pok = new StudentMaster("Paja", "Patak", 4312, 2015);
  pok->RegistrirajIspit(7);
  pok->RegistrirajIspit(6);
  pok->RegistrirajIspit(5);
  pok->RegistrirajIspit(10);
  pok->RegistrirajIspit(7);
  std::cout << pok->DajIme() << " " << pok->DajPrezime() << " "
            << pok->DajBrojIndeksa() << " " << pok->DajBrojPolozenih() << " "
            << pok->DajProsjek() << std::endl;
  pok->IspisiPodatke();
  delete pok;
  return 0;
}