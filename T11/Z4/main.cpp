#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Tim {
  char ime_tima[20];
  int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih,
      broj_primljenih, broj_poena;

public:
  Tim(const char ime[]) {
    if (strlen(ime) > 20)
      throw std::range_error("Predugacko ime tima");
    strncpy(ime_tima, ime, 20);
    broj_odigranih = 0;
    broj_pobjeda = 0;
    broj_nerijesenih = 0;
    broj_poraza = 0;
    broj_datih = 0;
    broj_primljenih = 0;
    broj_poena = 0;
  }
  void ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    if (broj_datih < 0 || broj_primljenih < 0)
      throw std::range_error("Neispravan broj golova");
    Tim::broj_datih += broj_datih;
    Tim::broj_primljenih += broj_primljenih;
    broj_odigranih++;
    if (broj_datih > broj_primljenih) {
      broj_pobjeda++;
      broj_poena += 3;
    } else if (broj_datih == broj_primljenih) {
      broj_nerijesenih++;
      broj_poena++;
    } else
      broj_poraza++;
  }
  const char *DajImeTima() const { return ime_tima; }
  int DajBrojPoena() const { return broj_poena; }
  int DajGolRazliku() const { return broj_datih - broj_primljenih; }
  void IspisiPodatke() const {
    std::cout << std::left << std::setw(20) << ime_tima << std::right
              << std::setw(4) << broj_odigranih << std::setw(4) << broj_pobjeda
              << std::setw(4) << broj_nerijesenih << std::setw(4) << broj_poraza
              << std::setw(4) << broj_datih << std::setw(4) << broj_primljenih
              << std::setw(4) << broj_poena << std::endl;
  }
};
class Liga {
  int broj_timova;
  const int max_br_timova;
  Tim **timovi;

public:
  explicit Liga(int velicina_lige)
      : broj_timova(0), max_br_timova(velicina_lige) {
    timovi = new Tim *[velicina_lige] {};
  }
  explicit Liga(std::initializer_list<Tim> lista_timova)
      : broj_timova(lista_timova.size()), max_br_timova(lista_timova.size()),
        timovi(new Tim *[lista_timova.size()] {}) {
    auto pocetak = lista_timova.begin();
    for (int i = 0; i < lista_timova.size(); i++) {
      try {
        timovi[i] = new Tim(*pocetak);
        pocetak++;
      } catch (...) {
        for (int i = 0; i < lista_timova.size(); i++) {
          delete timovi[i];
          timovi[i] = nullptr;
        }
        throw;
      }
    }
  }
  ~Liga() {
    if (timovi != nullptr) {
      for (int i = 0; i < max_br_timova; i++)
        delete timovi[i];
      delete[] timovi;
    }
  }
  Liga(const Liga &l)
      : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova) {
    timovi = new Tim *[l.max_br_timova] {};
    try {
      for (int i = 0; i < l.broj_timova; i++)
        timovi[i] = new Tim(*l.timovi[i]);
    } catch (...) {
      for (int i = 0; i < broj_timova; i++)
        delete timovi[i];
      delete[] timovi;
      throw;
    }
  }
  Liga(Liga &&l)
      : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova),
        timovi(l.timovi) {
    l.timovi = nullptr;
    l.broj_timova = 0;
  }

  Liga &operator=(Liga l) {
    if (max_br_timova != l.max_br_timova)
      throw std::logic_error("Nesaglasni kapaciteti liga");

    std::swap(timovi, l.timovi);
    std::swap(broj_timova, l.broj_timova);
    return *this;
  }

  /*
  Liga &operator=(const Liga &l) {
    if (max_br_timova != l.max_br_timova)
      throw std::logic_error("Nesaglasni kapaciteti liga");
    if (broj_timova < l.broj_timova) {
      try {
        for (int i = broj_timova; i < l.broj_timova; i++)
          timovi[i] = new Tim(*l.timovi[i]);
      } catch (...) {
        for (int i = broj_timova; i < l.broj_timova; i++) {
          delete timovi[i];
          timovi[i] = nullptr;
        }
        throw;
      }
    } else {
      for (int i = l.broj_timova; i < broj_timova; i++) {
        delete timovi[i];
        timovi[i] = nullptr;
      }
    }
    broj_timova = l.broj_timova;
    for (int i = 0; i < broj_timova; i++)
      *timovi[i] = *l.timovi[i];
    return *this;
  }
  Liga &operator=(Liga &&l) {
    if (max_br_timova != l.max_br_timova)
      throw std::logic_error("Nesaglasni kapaciteti liga");
    std::swap(broj_timova, l.broj_timova);
    std::swap(timovi, l.timovi);
    return *this;
  } */
  void DodajNoviTim(const char ime_tima[]) {
    if (strlen(ime_tima) > 20)
      throw std::logic_error("Predugacko ime tima");
    if (broj_timova >= max_br_timova)
      throw std::range_error("Liga popunjena");
    for (int i = 0; i < broj_timova; i++) {
      if (strcmp(timovi[i]->DajImeTima(), ime_tima) == 0)
        throw std::logic_error("Tim vec postoji");
    }
    timovi[broj_timova++] = new Tim(ime_tima);
  }
  void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1,
                           int rezultat_2) {
    bool nadjen1 = false, nadjen2 = false;
    for (int i = 0; i < broj_timova; i++)
      if (strcmp(timovi[i]->DajImeTima(), tim1) == 0)
        nadjen1 = true;
    for (int i = 0; i < broj_timova; i++)
      if (strcmp(timovi[i]->DajImeTima(), tim2) == 0)
        nadjen2 = true;
    if (!nadjen1 || !nadjen2)
      throw std::logic_error("Tim nije nadjen");
    if (rezultat_1 < 0 || rezultat_2 < 0)
      throw std::range_error("Neispravan broj golova");
    for (int i = 0; i < broj_timova; i++) {
      if (strcmp(timovi[i]->DajImeTima(), tim1) == 0)
        timovi[i]->ObradiUtakmicu(rezultat_1, rezultat_2);
      else if (strcmp(timovi[i]->DajImeTima(), tim2) == 0)
        timovi[i]->ObradiUtakmicu(rezultat_2, rezultat_1);
    }
  }
  void IspisiTabelu() {
    std::sort(timovi, timovi + broj_timova, [](Tim *tim1, Tim *tim2) -> bool {
      if (tim1->DajBrojPoena() != tim2->DajBrojPoena())
        return tim1->DajBrojPoena() > tim2->DajBrojPoena();
      else if (tim1->DajBrojPoena() == tim2->DajBrojPoena() &&
               tim1->DajGolRazliku() > tim2->DajGolRazliku())
        return tim1->DajGolRazliku() > tim2->DajGolRazliku();
      else if (tim1->DajBrojPoena() == tim2->DajBrojPoena() &&
               tim1->DajGolRazliku() == tim2->DajGolRazliku() &&
               strcmp(tim1->DajImeTima(), tim2->DajImeTima()) != 0) {
        if (strcmp(tim1->DajImeTima(), tim2->DajImeTima()) < 0)
          return true;
      }
      return false;
    });
    std::for_each(timovi, timovi + broj_timova,
                  [](Tim *tim) { tim->IspisiPodatke(); });
  }
};
int main() {
  Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo"};
  Liga l2{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Krupa"};

  try {
    l1 = std::move(l2);
  } catch (std::logic_error e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}