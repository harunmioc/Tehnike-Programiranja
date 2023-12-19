// TP 2022/2023: Zadaća 3, Zadatak 2
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>>
    IndeksPojmova;

IndeksPojmova KreirajIndeksPojmova(Knjiga tekst_koji_analiziramo) {
  IndeksPojmova indeks;
  int stranica = 1;

  for (auto it = tekst_koji_analiziramo.begin();
       it != tekst_koji_analiziramo.end(); it++) {
    std::string poglavlje = it->first;
    stranica = 1;
    for (auto it_stranica = it->second.begin(); it_stranica != it->second.end();
         it_stranica++) {
      std::string StranicaPoglavlja = *it_stranica;
      int kursor = 0;

      while (kursor < StranicaPoglavlja.length()) {
        // provjerava da li je !slovo/broj i preskace sve sto nije slovo/broj
        while (kursor<StranicaPoglavlja.length() &&
                !(StranicaPoglavlja.at(kursor) >= 'a' &&
                 StranicaPoglavlja.at(kursor) <= 'z') &&
               !(StranicaPoglavlja.at(kursor) >= 'A' &&
                 StranicaPoglavlja.at(kursor) <= 'Z') &&
               !(StranicaPoglavlja.at(kursor) >= '0' &&
                 StranicaPoglavlja.at(kursor) <= '9')) {
       
          kursor++;
        }

        if (kursor >= StranicaPoglavlja.length())
          break;

        // trazimo rijec
       
        int duzinaRijeci = 0;
        while (kursor + duzinaRijeci < StranicaPoglavlja.length() &&
               ((StranicaPoglavlja.at(kursor + duzinaRijeci) >= 'a' &&
                 StranicaPoglavlja.at(kursor + duzinaRijeci) <= 'z') ||
                (StranicaPoglavlja.at(kursor + duzinaRijeci) >= 'A' &&
                 StranicaPoglavlja.at(kursor + duzinaRijeci) <= 'Z') ||
                (StranicaPoglavlja.at(kursor + duzinaRijeci) >= '0' &&
                 StranicaPoglavlja.at(kursor + duzinaRijeci) <= '9'))) {
          duzinaRijeci++;
        }

        std::string rijec = StranicaPoglavlja.substr(kursor, duzinaRijeci);

        // pretvaramo velika u mala slova
        for (int brojac = 0; brojac < rijec.length(); brojac++) {
          if (rijec.at(brojac) >= 'A' && rijec.at(brojac) <= 'Z')
            rijec.at(brojac) += 32;
        }

        // ubacujemo u mapu IndeksPojmova kljucnu rijec i ostale informacije
        
        indeks[rijec].insert(make_tuple(poglavlje, stranica, kursor));
        kursor += duzinaRijeci;
      
      }
      stranica++;
    }
  }
  return indeks;
}

std::set<std::tuple<std::string, int, int>>
PretraziIndeksPojmova(std::string rijec, IndeksPojmova MapaPojmova) {

  if (MapaPojmova.count(rijec) == 0)
    throw std::logic_error("Pojam nije nadjen");

  return MapaPojmova.at(rijec);
}

void IspisiIndeksPojmova(const IndeksPojmova &indeks) {

  for (auto it = indeks.begin(); it != indeks.end(); it++) {
    std::cout << it->first << ": ";
    std::set<std::tuple<std::string, int, int>> skup = it->second;

    for (auto itttt = skup.begin(); itttt != skup.end(); itttt++) {
      std::string poglavlje;
      int stranica, pozicija;
      std::tie(poglavlje, stranica, pozicija) = *itttt;

      std::cout << poglavlje << "/" << stranica << "/" << pozicija;
      if (itttt != std::prev(skup.end()))
        std::cout << ", ";
    }
    if (it != --indeks.end())
      std::cout << std::endl;
  }
}

int main() {

  Knjiga k;
  std::string poglavlje;

  while (1) {
    std::cout << "\nUnesite naziv poglavlja: ";
    std::getline(std::cin, poglavlje);
    if (poglavlje == ".")
      break;
    int stranica = 1;

    std::string tekst;
    while (1) {
      std::cout << "\nUnesite sadrzaj stranice " << stranica++ << ": ";
      std::getline(std::cin, tekst);
      if (tekst == ".")
        break;
      k[poglavlje].push_back(tekst);
    }
  }

  IndeksPojmova indeks = KreirajIndeksPojmova(k);
  std::cout << "\nKreirani indeks pojmova:\n";
  IspisiIndeksPojmova(indeks);

  while (1) {

    std::cout << "\nUnesite rijec: ";
    std::getline(std::cin, poglavlje);
    if (poglavlje == ".")
      break;
    try {
      // velika u mala slova
      for (int i = 0; i < poglavlje.length(); i++) {
        if (poglavlje.at(i) >= 'A' && poglavlje.at(i) <= 'Z')
          poglavlje.at(i) += 32;
      }

      std::set<std::tuple<std::string, int, int>> MapaPojmova =
          PretraziIndeksPojmova(poglavlje, indeks);
      std::cout << "\n";
      for (const auto &it : MapaPojmova) {
        std::cout << std::get<0>(it) << "/" << std::get<1>(it) << "/"
                  << std::get<2>(it) << " ";
      }
    } catch (std::logic_error izuzetak) {
      std::cout << "\nUnesena rijec nije nadjena!";
    }
  }

  return 0;
}
