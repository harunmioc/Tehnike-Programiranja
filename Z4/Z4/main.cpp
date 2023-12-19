// TP 2022/2023: Zadaća 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

class Korisnik {
  int clanski_broj;
  std::string ime_i_prezime;
  std::string adresa;
  std::string broj_telefona;

public:
  Korisnik(int broj, std::string imeprezime, std::string adress,
           std::string brmob)
      : clanski_broj(broj), ime_i_prezime(imeprezime), adresa(adress),
        broj_telefona(brmob) {}

  int DajClanskiBroj()const { return clanski_broj; }
  std::string DajImeIPrezime()const { return ime_i_prezime; }
  std::string DajAdresu()const { return adresa; }
  std::string DajTelefon()const { return broj_telefona; }

  void Ispisi()const {
    std::cout << "Clanski broj: " << clanski_broj
              << "\nIme i prezime: " << ime_i_prezime << "\nAdresa: " << adresa
              << "\nTelefon: " << broj_telefona << "\n";
  }
};

class Film {
  int evidencijski_broj;
  bool DVD;
  std::string ime_filma;
  std::string zanr;
  int godina_izdavanja;
  Korisnik *zaduznik;

public:
  Film(int br, bool trilidvd, const std::string &ime, const std::string &Zanr,
       int godina)
      : evidencijski_broj(br), DVD(trilidvd), ime_filma(ime), zanr(Zanr),
        godina_izdavanja(godina) {
    zaduznik = nullptr;
  }

  int DajEvidencijskiBroj() const { return evidencijski_broj; }
  std::string DajNaziv()const { return ime_filma; }
  std::string DajZanr() const { return zanr; }
  int DajGodinuProdukcije()const { return godina_izdavanja; }
  bool DaLiJeDVD() const{
    if (DVD)
      return true;
    return false;
  }

  void ZaduziFilm(Korisnik &Zaduznik);
  void RazduziFilm();
  bool DaLiJeZaduzen()const;
  Korisnik &DajKodKogaJe();
  Korisnik *DajPokKodKogaJe();

  void Ispisi()const {
    std::cout << "Evidencijski broj: " << evidencijski_broj << "\nMedij: ";
    if (DVD)
      std::cout << "DVD";
    else
      std::cout << "Video traka";
    std::cout << "\nNaziv filma: " << ime_filma << "\nZanr: " << zanr
              << "\nGodina produkcije: " << godina_izdavanja<<"\n";
  }
};

void Film::ZaduziFilm(Korisnik &Zaduznik) { zaduznik = &Zaduznik; }

void Film::RazduziFilm() { zaduznik = nullptr; }

bool Film::DaLiJeZaduzen()const {
  if (zaduznik != nullptr)
    return true;
  return false;
}

Korisnik &Film::DajKodKogaJe() {
  if (DaLiJeZaduzen() == false)
    throw std::domain_error("Film nije zaduzen");
  return *zaduznik;
}

Korisnik *Film::DajPokKodKogaJe() {
  if (DaLiJeZaduzen() == false)
    return nullptr;
  return zaduznik;
}

class Videoteka {
  std::map<int, std::shared_ptr<Korisnik>> mapa_korisnika;
  std::map<int, std::shared_ptr<Film>> mapa_filmova;

public:
  Videoteka() {}

  void RegistrirajNovogKorisnika(int clanski_brojj, const std::string &ime,
                                 const std::string &adress,
                                 const std::string &br);
  void RegistrirajNoviFilm(int evidencijski_br, bool dvd,
                           const std::string &ime, const std::string &Zanr,
                           int godina);
   Korisnik &NadjiKorisnika(int clanski_broj)const;
   Film &NadjiFilm(int evidencijski_broj)const ;
  void IzlistajKorisnike() const;
  void IzlistajFilmove() const;
  void ZaduziFilm(int evidencijski_br, int clanski_brojj);
  void RazduziFilm(int evidencijski_br);
  void PrikaziZaduzenja(int clanski_brojj) const;
  Videoteka (const Videoteka &videoteka);
  Videoteka (Videoteka &&videoteka);
  Videoteka &operator =(const Videoteka &videoteka);
  Videoteka &operator =(Videoteka &&videoteka);
};


    Videoteka::Videoteka(const Videoteka &videoteka){
        for(const auto &x:videoteka.mapa_korisnika)
            mapa_korisnika[x.first]=std::make_shared<Korisnik>(*x.second);
        
        for(const auto &x:videoteka.mapa_filmova)
            mapa_filmova[x.first]=std::make_shared<Film>(*x.second);
    }


    Videoteka& Videoteka::operator =(const Videoteka &videoteka){
        if(this==&videoteka)
            return *this;

        mapa_korisnika.clear();
        mapa_filmova.clear();

        for(const auto &x:videoteka.mapa_korisnika)
            mapa_korisnika[x.first]=std::make_shared<Korisnik>(*x.second);
        
        for(const auto &x:videoteka.mapa_filmova)
            mapa_filmova[x.first]=std::make_shared<Film>(*x.second);
        
        return *this;
    }

    Videoteka::Videoteka( Videoteka &&videoteka){
        mapa_filmova=std::move(videoteka.mapa_filmova);
        mapa_korisnika=std::move(videoteka.mapa_korisnika);
    }

    Videoteka& Videoteka::operator =( Videoteka &&videoteka){
        if(this==&videoteka)
            return *this;
        mapa_filmova=std::move(videoteka.mapa_filmova);
        mapa_korisnika=std::move(videoteka.mapa_korisnika);
        return *this;
    }

void Videoteka::RegistrirajNovogKorisnika(int clanski_brojj,
                                          const std::string &ime,
                                          const std::string &adress,
                                          const std::string &br) {
  if (mapa_korisnika.count(clanski_brojj) != 0)
    throw std::logic_error("Vec postoji korisnik s tim clanskim brojem\n");

  std::shared_ptr<Korisnik> korisnik =
      std::make_shared<Korisnik>(clanski_brojj, ime, adress, br);
  mapa_korisnika[clanski_brojj] = korisnik;
}

void Videoteka::RegistrirajNoviFilm(int evidencijski_br, bool dvd,
                                    const std::string &ime,
                                    const std::string &Zanr, int godina) {
  if (mapa_filmova.count(evidencijski_br) != 0)
    throw std::logic_error("Film s tim evidencijskim brojem vec postoji\n");
  std::shared_ptr<Film> film =
      std::make_shared<Film>(evidencijski_br, dvd, ime, Zanr, godina);
  mapa_filmova[evidencijski_br] = film;
}

 Korisnik &Videoteka::NadjiKorisnika(int clanski_broj) const{
  if (mapa_korisnika.count(clanski_broj) == 0)
    throw std::logic_error("Korisnik nije nadjen");
  return *mapa_korisnika.at(clanski_broj);
}
 Film &Videoteka::NadjiFilm(int evidencijski_broj)const {
  if (mapa_filmova.count(evidencijski_broj) == 0)
    throw std::logic_error("Film nije nadjen");
  return *mapa_filmova.at(evidencijski_broj);
}

void Videoteka::IzlistajKorisnike() const {
  for (const auto &x : mapa_korisnika) {
    x.second->Ispisi();
    std::cout << "\n\n";
  }
}

void Videoteka::IzlistajFilmove() const {
  for (const auto &x : mapa_filmova) {
    x.second->Ispisi();
    if (x.second->DaLiJeZaduzen())
      std::cout << "\nZaduzen kod korisnika: "
                << x.second->DajPokKodKogaJe()->DajImeIPrezime() << " ("
                << x.second->DajPokKodKogaJe()->DajClanskiBroj() << ")";
    std::cout << "\n\n";
  }
}

void Videoteka::ZaduziFilm(int evidencijski_br, int clanski_brojj) {
  if (mapa_filmova.count(evidencijski_br) == 0)
    throw std::logic_error("Film nije nadjen");

  if (mapa_korisnika.count(clanski_brojj) == 0)
    throw std::logic_error("Korisnik nije nadjen");

  Film &film = *mapa_filmova[evidencijski_br];
  Korisnik &korisnik = *mapa_korisnika[clanski_brojj];

  if (film.DaLiJeZaduzen())
    throw std::logic_error("Film vec zaduzen");

  film.ZaduziFilm(korisnik);
}

void Videoteka::RazduziFilm(int evidencijski_br) {
  if (mapa_filmova.count(evidencijski_br) == 0)
    throw std::logic_error("Film nije nadjen");

  Film &film = *mapa_filmova[evidencijski_br];

  if (!film.DaLiJeZaduzen())
    throw std::logic_error("Film nije nadjen");

  film.RazduziFilm();
}

void Videoteka::PrikaziZaduzenja(int clanski_brojj) const{
  if (mapa_korisnika.count(clanski_brojj) == 0)
    throw std::logic_error("Korisnik nije nadjen");

  bool DaLiImaZaduzenja = false;

  for (const auto &x : mapa_filmova) {
    if (x.second->DaLiJeZaduzen() &&
        (*x.second).DajKodKogaJe().DajClanskiBroj() == clanski_brojj) {
      DaLiImaZaduzenja = true;
      x.second->Ispisi();
    }
  }

  if (!DaLiImaZaduzenja)
    std::cout << "Korisnik nema zaduzenja";
}


int main() {

  return 0;
}
