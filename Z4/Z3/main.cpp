// TP 2022/2023: Zadaća 4, Zadatak 3
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <string>

class Polazak {
  std::string odrediste;
  std::string oznaka_voznje;
  int peron;
  int sati;
  int minute;
  int trajanje_voznje;
  int kasnjenje;

public:
  Polazak(std::string Odrediste, std::string Oznaka_voznje, int broj_perona,
          int sat_polaska, int minute_polaska, int Trajanje_voznje) {
    if (broj_perona < 1 || broj_perona > 15 || sat_polaska < 0 ||
        sat_polaska > 23 || minute_polaska < 0 || minute_polaska > 59 ||
        Trajanje_voznje < 1)
      throw std::domain_error("Neki od unosa nema smisla");
    odrediste = Odrediste;
    oznaka_voznje = Oznaka_voznje;
    peron = broj_perona;
    sati = sat_polaska;
    minute = minute_polaska;
    trajanje_voznje = Trajanje_voznje;
    kasnjenje = 0;
  }
  void PostaviKasnjenje(int kasnjenje);
  bool DaLiKasni() const;
  int DajTrajanje() const;
  void OcekivanoVrijemePolaska(int &sati, int &minute) const;
  void OcekivanoVrijemeDolaska(int &sati, int &minute) const;
  void Ispisi() const;
};

void Polazak::PostaviKasnjenje(int kasnjenje) {
  if (kasnjenje < 0)
    throw std::domain_error("Parametar nema smisla");
  Polazak::kasnjenje = kasnjenje;
}
bool Polazak::DaLiKasni() const {
  if (kasnjenje > 0) {
    return true;
  }
  return false;
}

int Polazak::DajTrajanje() const { return trajanje_voznje; }
void Polazak::OcekivanoVrijemePolaska(int &sati, int &minute) const {
  int min = Polazak::sati * 60 + Polazak::minute + kasnjenje;
  sati = min / 60;
  min -= sati * 60;
  minute = min;
  sati%=24;
  minute%=60;
}
void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const {

  int min = Polazak::sati * 60 + Polazak::minute + kasnjenje+trajanje_voznje;
  sati = min / 60;
  min -= sati * 60;
  minute = min;
  sati%=24;
  minute%=60;
}

void Polazak::Ispisi() const {
  if (kasnjenje == 0) {
    int h, m;
    OcekivanoVrijemeDolaska(h, m);
    //oznaka voznje
        std::cout<<std::setw(10)<<std::left<<oznaka_voznje;
    //odrediste
        std::cout<<std::left<<std::setw(30)<<odrediste;
    //polazak sati
        std::cout<<std::right<<std::setw(7)<<sati<<":";
    //polazak minute
        std::cout<<std::setw(2)<<std::setfill('0')<<minute;
    //dolazak sati
        std::cout<<std::setfill(' ')<<std::right<<std::setw(7)<<h<<":";
    //dolazak minute
        std::cout<<std::setw(2)<<std::setfill('0')<<m;
    //broj perona
        std::cout<<std::setfill(' ')<<std::setw(8)<<peron<<"\n";
  } else {
    int h, m;
    OcekivanoVrijemePolaska(h, m);
    std::cout << std::setw(10) << std::left << oznaka_voznje;
    std::cout << std::left << std::setw(30) << odrediste;
    std::cout<< std::setw(7) <<std::right<< h << ":";
    std::cout<< std::setw(2) << std::setfill('0') << m;

    std::cout<< std::setfill(' ') << " (Planirano " << sati << ":";
    std::cout<<std::setw(2)<< std::setfill('0') << minute << std::setfill(' ') << ", Kasni "
              << kasnjenje << " min)" << std::endl;
  }
}

class Polasci {
  Polazak **polasci_niz = nullptr;
  int broj_polazaka = 0;
  int max_polazaka;

public:
  explicit Polasci(int max_broj_polazaka) : max_polazaka(max_broj_polazaka) {
    broj_polazaka = 0;
    polasci_niz = new Polazak *[max_broj_polazaka];
  }
  Polasci(std::initializer_list<Polazak> lista_polazaka);
  ~Polasci() {
    for (int i = 0; i < broj_polazaka; i++)
      delete polasci_niz[i];
    delete[] polasci_niz;
    broj_polazaka = 0;
  }
  Polasci(const Polasci &polasci);
  Polasci(Polasci &&polasci);
  Polasci &operator=(const Polasci &polasci);
  Polasci &operator=(Polasci &&polasci);
  void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje,
                          int broj_perona, int sat_polaska, int minute_polaska,
                          int trajanje_voznje);
  void RegistrirajPolazak(Polazak *polazak);
  int DajBrojPolazaka() const;
  int DajBrojPolazakaKojiKasne() const;
  Polazak &DajPrviPolazak();
  Polazak DajPrviPolazak() const;
  Polazak &DajPosljednjiPolazak();
  Polazak DajPosljednjiPolazak() const;
  void Ispisi() const;
  void IsprazniKolekciju();
};

Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka)
    : max_polazaka(lista_polazaka.size()) {
  polasci_niz = new Polazak *[max_polazaka] {};
  for (const Polazak &x : lista_polazaka) {
    polasci_niz[broj_polazaka] = new Polazak(x);
    broj_polazaka++;
  }
}

Polasci::Polasci(const Polasci &polasci) {
  max_polazaka = polasci.max_polazaka;
  broj_polazaka = polasci.broj_polazaka;
  polasci_niz = new Polazak *[max_polazaka] {};
  for (int i = 0; i < broj_polazaka; i++)
    polasci_niz[i] = new Polazak(*polasci.polasci_niz[i]);
}

Polasci::Polasci(Polasci &&polasci) {
  polasci_niz = polasci.polasci_niz;
  max_polazaka = polasci.max_polazaka;
  broj_polazaka = polasci.broj_polazaka;
  polasci.polasci_niz = nullptr;
  polasci.broj_polazaka = 0;
  polasci.max_polazaka = 0;
}

Polasci &Polasci::operator=(const Polasci &polasci) {
  if (&polasci != this) {
    for (int i = 0; i < max_polazaka; i++)
      delete polasci_niz[i];
    delete[] polasci_niz;
    max_polazaka = polasci.max_polazaka;
    broj_polazaka = polasci.broj_polazaka;
    polasci_niz = new Polazak *[max_polazaka] {};
    for (int i = 0; i < broj_polazaka; i++)
      polasci_niz[i] = new Polazak(*polasci.polasci_niz[i]);
  }
  return *this;
}

Polasci &Polasci::operator=(Polasci &&polasci) {
  if (&polasci != this) {
    for (int i = 0; i < max_polazaka; i++)
      delete polasci_niz[i];
    delete[] polasci_niz;

    polasci_niz = polasci.polasci_niz;
    max_polazaka = polasci.max_polazaka;
    broj_polazaka = polasci.broj_polazaka;
    polasci.polasci_niz = nullptr;
    polasci.broj_polazaka = 0;
    polasci.max_polazaka = 0;
  }
  return *this;
}

void Polasci::RegistrirajPolazak(std::string odrediste,
                                 std::string oznaka_voznje, int broj_perona,
                                 int sat_polaska, int minute_polaska,
                                 int trajanje_voznje) {
  if (broj_polazaka >= max_polazaka)
    throw std::range_error("Dostignut maksimalni broj polazaka");

  polasci_niz[broj_polazaka] =
      new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska,
                  minute_polaska, trajanje_voznje);
  broj_polazaka++;
}

void Polasci::RegistrirajPolazak(Polazak *polazak) {
  if (broj_polazaka >= max_polazaka)
    throw std::range_error("Dostignut maksimalni broj polazaka");
  polasci_niz[broj_polazaka] = polazak;
  broj_polazaka++;
}

int Polasci::DajBrojPolazaka() const { return broj_polazaka; }

int Polasci::DajBrojPolazakaKojiKasne() const {
  /* int broj=0;
   for(int i=0; i<broj_polazaka; i++)
       if(polasci_niz[i]->DaLiKasni())
           broj++;
   return broj; */
  return std::count_if(
      polasci_niz, polasci_niz + broj_polazaka,
      [](const Polazak *polazak) { return polazak->DaLiKasni(); });
}

Polazak &Polasci::DajPrviPolazak() {
  return **std::min_element(
      polasci_niz, polasci_niz + broj_polazaka,
      [](const Polazak *polazak1, const Polazak *polazak2) {
        int h1, h2, min1, min2, ukupno1, ukupno2;
        polazak1->OcekivanoVrijemePolaska(h1, min1);
        polazak2->OcekivanoVrijemeDolaska(h2, min2);
        ukupno1 = h1 * 60 + min1;
        ukupno2 = h2 * 60 + min2;
        return ukupno1 < ukupno2;
      });
}

Polazak Polasci::DajPrviPolazak() const {
  return **std::min_element(
      polasci_niz, polasci_niz + broj_polazaka,
      [](const Polazak *polazak1, const Polazak *polazak2) {
        int h1, h2, min1, min2, ukupno1, ukupno2;
        polazak1->OcekivanoVrijemePolaska(h1, min1);
        polazak2->OcekivanoVrijemeDolaska(h2, min2);
        ukupno1 = h1 * 60 + min1;
        ukupno2 = h2 * 60 + min2;
        return ukupno1 < ukupno2;
      });
}

Polazak &Polasci::DajPosljednjiPolazak() {
  return **std::max_element(
      polasci_niz, polasci_niz + broj_polazaka,
      [](const Polazak *polazak1, const Polazak *polazak2) {
        int h1, h2, min1, min2, ukupno1, ukupno2;
        polazak1->OcekivanoVrijemePolaska(h1, min1);
        polazak2->OcekivanoVrijemeDolaska(h2, min2);
        ukupno1 = h1 * 60 + min1;
        ukupno2 = h2 * 60 + min2;
        return ukupno1 < ukupno2;
      });
}

Polazak Polasci::DajPosljednjiPolazak() const {
  return **std::max_element(
      polasci_niz, polasci_niz + broj_polazaka,
      [](const Polazak *polazak1, const Polazak *polazak2) {
        int h1, h2, min1, min2, ukupno1, ukupno2;
        polazak1->OcekivanoVrijemePolaska(h1, min1);
        polazak2->OcekivanoVrijemeDolaska(h2, min2);
        ukupno1 = h1 * 60 + min1;
        ukupno2 = h2 * 60 + min2;
        return ukupno1 < ukupno2;
      });
}

void Polasci::Ispisi() const {
  std::sort(polasci_niz, polasci_niz + broj_polazaka,
            [](Polazak *polazak1, Polazak *polazak2) {
              int h1, h2, min1, min2, ukupno1, ukupno2;
              polazak1->OcekivanoVrijemePolaska(h1, min1);
              polazak2->OcekivanoVrijemeDolaska(h2, min2);
              ukupno1 = h1 * 60 + min1;
              ukupno2 = h2 * 60 + min2;
              return ukupno1 < ukupno2;
            });

  std::cout << std::setw(10) << std::right << "Voznja" << std::setw(30)<<std::right
            << "Odrediste" << std::setw(10) << "Polazak" <<std::setw(10)<<"Dolazak" <<std::setw(8)
            << "Peron" << std::endl;
  std::cout << "---------------------------------------------------------------"
               "-------\n";
  for (int i = 0; i < broj_polazaka; i++)
    if (polasci_niz[i] != nullptr)
      polasci_niz[i]->Ispisi();
}


void Polasci::IsprazniKolekciju(){
    for(int i=0; i<broj_polazaka; i++)
      if(polasci_niz!=nullptr)
        delete polasci_niz[i];

broj_polazaka=0;
}





int main() {

    

  return 0;
}
