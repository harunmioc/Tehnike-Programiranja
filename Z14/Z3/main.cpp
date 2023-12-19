//TP 2022/2023: LV 14, Zadatak 3
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>

class Tim {
  char ime_tima[20];
  int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza;
  int broj_datih, broj_primljenih, broj_poena;

public:
  Tim() = default;
  Tim(const char ime[]);
  void ObradiUtakmicu(int broj_datih, int broj_primljenih);
  const char *DajImeTima() const { return ime_tima; }
  int DajBrojPoena() const { return broj_poena; }
  int DajGolRazliku() const { return broj_datih - broj_primljenih; }
  void IspisiPodatke() const;
};

class Liga {
  int broj_timova;
  const int max_br_timova;
  Tim **timovi;
  void SortirajTabelu();

public:
  explicit Liga(int velicina_lige);
  explicit Liga(std::initializer_list<Tim> lista_timova);
  explicit Liga(const std::string &ime);
  ~Liga();
  Liga(const Liga &l);
  Liga(Liga &&l);
  Liga &operator=(const Liga &l);
  Liga &operator=(Liga &&l);
  void DodajNoviTim(const char ime_tima[]);
  void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1,
                           int rezultat_2);
  void IspisiTabelu() const;

  void ObrisiSve();
  void SacuvajStanje(const std::string &ime) const;
  void AzurirajIzDatoteke(const std::string &ime);
};

Tim::Tim(const char ime[]) {
  if (std::strlen(ime) >= 20)
    throw std::range_error("Predugacko ime tima");
  std::strcpy(ime_tima, ime);
  broj_odigranih = broj_pobjeda = broj_nerijesenih = broj_poraza = broj_datih =
      broj_primljenih = broj_poena = 0;
}
void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
  if (broj_datih < 0 || broj_primljenih < 0)
    throw std::range_error("Neispravan broj golova");

  broj_odigranih++;
  Tim::broj_datih += broj_datih;
  Tim::broj_primljenih += broj_primljenih;

  if (broj_datih > broj_primljenih) {
    broj_pobjeda++;
    broj_poena += 3;
  } else if (broj_datih == broj_primljenih) {
    broj_nerijesenih++;
    broj_poena++;
  } else
    broj_poraza++;
}
void Tim::IspisiPodatke() const {
  std::cout << std::setw(20) << std::left << ime_tima;
  std::cout << std::setw(4) << std::right << broj_odigranih;
  std::cout << std::setw(4) << std::right << broj_pobjeda;
  std::cout << std::setw(4) << std::right << broj_nerijesenih;
  std::cout << std::setw(4) << std::right << broj_poraza;
  std::cout << std::setw(4) << std::right << broj_datih;
  std::cout << std::setw(4) << std::right << broj_primljenih;
  std::cout << std::setw(4) << std::right << broj_poena << std::endl;
}

Liga::Liga(int velicina_lige) : broj_timova(0), max_br_timova(velicina_lige) {
  timovi = new Tim* [max_br_timova] {};
}
Liga::Liga(std::initializer_list<Tim> lista_timova) : broj_timova(0), max_br_timova(lista_timova.size()) {
  timovi = new Tim* [max_br_timova] {};
  for (const auto &tim : lista_timova)
    DodajNoviTim(tim.DajImeTima());
}
Liga::Liga(const std::string &ime) : max_br_timova() {

  std::ifstream ulaz(ime, std::ios::binary);

  if (!ulaz) throw std::logic_error("Datoteka ne postoji");

  ulaz.read(reinterpret_cast<char*>(this), sizeof this);
  if (broj_timova > max_br_timova) throw std::logic_error("Datoteka sadrzi fatalne greske");
  timovi = new Tim*[max_br_timova]{};
  try {
    for (int i{}; i < broj_timova; i++) {
      timovi[i] = new Tim;
      ulaz.read(reinterpret_cast<char*>(timovi[i]), sizeof (Tim));
    }
    if (!ulaz) throw std::logic_error("Problemi pri citanju datoteke");
  }
  catch(...) {
    ObrisiSve();
    throw;
  }
}
Liga::~Liga() {
  if (!timovi)
    return;
  for (int i{}; i < broj_timova; i++)
    delete timovi[i];
  delete[] timovi;
}
Liga::Liga(const Liga &l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova) {
  timovi = new Tim* [max_br_timova] {};
  for (int i{}; i < broj_timova; i++)
    timovi[i] = new Tim(*(l.timovi[i]));
}
Liga::Liga(Liga &&l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova), timovi(l.timovi) {
  l.timovi = nullptr;
}
Liga &Liga::operator=(const Liga &l) {
  if (this == &l)
    return *this;
  if (max_br_timova != l.max_br_timova)
    throw std::logic_error("Nesaglasni kapaciteti liga");

  for (int i = 0; i < broj_timova; i++)
    delete timovi[i];
  delete[] timovi;

  broj_timova = l.broj_timova;
  timovi = new Tim *[max_br_timova];

  for (int i = 0; i < broj_timova; i++)
    timovi[i] = new Tim(*l.timovi[i]);

  return *this;
}
Liga &Liga::operator=(Liga &&l) {
  if (this == &l)
    return *this;
  if (max_br_timova != l.max_br_timova)
    throw std::logic_error("Nesaglasni kapaciteti liga");

  std::swap(broj_timova, l.broj_timova);
  std::swap(timovi, l.timovi);
  l.timovi = nullptr;
  return *this;
}
void Liga::DodajNoviTim(const char ime_tima[]) {
  if (std::strlen(ime_tima) > 19)
    throw std::range_error("Predugacko ime tima");
  if (broj_timova == max_br_timova)
    throw std::range_error("Liga popunjena");
  for (int i{}; i < broj_timova; i++)
    if (std::strcmp(timovi[i]->DajImeTima(), ime_tima) == 0)
      throw std::logic_error("Tim vec postoji");

  timovi[broj_timova++] = new Tim(ime_tima);
}
void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[],
                               int rezultat_1, int rezultat_2) {
  Tim *t1{}, *t2{};
  for (int i{}; i < broj_timova; i++) {
    if (std::strcmp(timovi[i]->DajImeTima(), tim1) == 0)
      t1 = timovi[i];
    if (std::strcmp(timovi[i]->DajImeTima(), tim2) == 0)
      t2 = timovi[i];
  }

  if (t1 == nullptr || t2 == nullptr)
    throw std::logic_error("Tim nije nadjen");

  t1->ObradiUtakmicu(rezultat_1, rezultat_2);
  t2->ObradiUtakmicu(rezultat_2, rezultat_1);
}
void Liga::IspisiTabelu() const {
  Liga nova = *this;
  nova.SortirajTabelu();
  for (int i{}; i < broj_timova; i++)
    nova.timovi[i]->IspisiPodatke();
}
void Liga::SortirajTabelu() {
  std::sort(timovi, timovi + broj_timova, [](const Tim *t1, const Tim *t2) {
    if (t1->DajBrojPoena() != t2->DajBrojPoena())
      return t1->DajBrojPoena() > t2->DajBrojPoena();
    else if (t1->DajGolRazliku() != t2->DajGolRazliku())
      return t1->DajGolRazliku() > t2->DajGolRazliku();
    else
      return std::strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0;
  });
}
void Liga::ObrisiSve() {
  if (!timovi) return;
  for (int i{}; i < broj_timova; i++) {
    delete[] timovi[i];
    timovi[i] = nullptr;
  }
  delete[] timovi;
  timovi = nullptr;
  broj_timova = 0;
}
void Liga::SacuvajStanje(const std::string &ime) const {
  std::ofstream izlaz(ime, std::ios::binary);
  izlaz.write(reinterpret_cast<const char*>(this), sizeof this);
  for (int i{}; i < broj_timova; i++)
    izlaz.write(reinterpret_cast<char*>(timovi[i]), sizeof *timovi[i]);
  if (!izlaz) throw std::logic_error("Nesto nije uredu sa upisom!");
}
void Liga::AzurirajIzDatoteke(const std::string &ime) {
  std::ifstream ulaz(ime);
  if (!ulaz) throw std::logic_error("Datoteka ne postoji");
  std::string tim1, tim2;
  int rez1, rez2;
  while(std::getline(ulaz, tim1) && std::getline(ulaz, tim2)) {
      ulaz >> rez1;
    ulaz.get(); // preskoci ':'
    ulaz >> rez2;
    if (!ulaz || rez1 < 0 || rez2 < 0) throw std::logic_error("Problemi pri citanju datoteke");
    try { DodajNoviTim(tim1.c_str()); }
    catch(...) {}
    try { DodajNoviTim(tim2.c_str()); }
    catch(...) {}
    RegistrirajUtakmicu(tim1.c_str(), tim2.c_str(), rez1, rez2); 
    ulaz.get(); //preskoci '\n'
  }
}

int main() {
  std::fstream ulaz("LIGA.DAT", std::ios::binary | std::ios::in | std::ios::out);
  if (ulaz) { 
    Liga l("LIGA.DAT");
    l.RegistrirajUtakmicu("Celik", "Borac", 0, 0);
    l.DodajNoviTim("Noviiii");
    l.RegistrirajUtakmicu("Noviiii", "Sarajevo", 10, 10);
    l.SacuvajStanje("LIGA.DAT");
  }
  else {
    ulaz.clear();
    Liga l{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo"};
    try {
      l.DodajNoviTim("FK Borac Banja Luka");
    } catch (std::range_error e) {
      std::cout << e.what() << std::endl;
    }
    catch(std::logic_error e) {
      std::cout << e.what() << std::endl;
    }
    ulaz.close();
    l.SacuvajStanje("LIGA.DAT");
  }

  return 0;
}