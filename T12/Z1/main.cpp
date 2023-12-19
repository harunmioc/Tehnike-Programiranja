#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>

class Sat {
  int sati, minute, sekunde;

public:
  Sat() : sati(0), minute(0), sekunde(0){};
  Sat(int h, int min, int sek) : sati(0), minute(0), sekunde(0) {
    PostaviNormalizirano(h, min, sek);
  }
  static bool DaLiJeIspravno(int h, int min, int s) {
    if (h < 0 || h > 23 || min < 0 || min > 59 || s < 0 || s > 59)
      return false;
    return true;
  }
  void Postavi(int h, int min, int s) {
    if (!DaLiJeIspravno(h, min, s))
      throw std::domain_error("Neispravno vrijeme");
    sati = h;
    minute = min;
    sekunde = s;
  }
  void PostaviNormalizirano(int h, int min, int s) {
    if (!DaLiJeIspravno(h, min, s)) {
      while (s < 0) {
        s += 60;
        min--;
      }
      while (s > 59) {
        s -= 60;
        min++;
      }
      while (min < 0) {
        min += 60;
        h--;
      }
      while (min > 59) {
        min -= 60;
        h++;
      }
      while (h < 0)
        h += 24;
      while (h > 23)
        h -= 24;
    }
    sati = h;
    minute = min;
    sekunde = s;
  }
  friend Sat operator++(Sat &s, int);
  friend Sat &operator++(Sat &s);
  friend Sat operator--(Sat &s, int);
  friend Sat &operator--(Sat &s);
  friend Sat &operator+=(Sat &s, int p);
  friend Sat &operator-=(Sat &s, int p);
  int DajSate() const { return sati; }
  int DajMinute() const { return minute; }
  int DajSekunde() const { return sekunde; }
  friend std::ostream &operator<<(std::ostream &ispis, const Sat &s);
  friend Sat operator-(const Sat &s, int p);
  friend int operator-(const Sat &s1, const Sat &s2);
  friend Sat operator+(const Sat &s, int p);
  friend int operator+(const Sat &s1, const Sat &s2);
};
Sat operator++(Sat &s, int) {
  Sat pom(s.sati, s.minute, s.sekunde);
  ++s;
  return pom;
}
Sat &operator++(Sat &s) {
  if (++s.sekunde == 60) {
    s.minute++;
    s.sekunde = 0;
  }
  if (s.minute == 60) {
    s.sati++;
    s.minute = 0;
  }
  if (s.sati == 24)
    s.sati = 0;
  return s;
}
Sat operator--(Sat &s, int) {
  Sat pom(s.sati, s.minute, s.sekunde);
  --s;
  return pom;
}
Sat &operator--(Sat &s) {
  if (--s.sekunde < 0) {
    s.sekunde = 59;
    s.minute--;
  }
  if (s.minute < 0) {
    s.minute = 59;
    s.sati--;
  }
  if (s.sati < 0)
    s.sati = 23;
  return s;
}
Sat &operator+=(Sat &s, int p) {
  s.sekunde += p;
  s.PostaviNormalizirano(s.sati, s.minute, s.sekunde);
  return s;
}
Sat &operator-=(Sat &s, int p) {
  s.sekunde -= p;
  s.PostaviNormalizirano(s.sati, s.minute, s.sekunde);
  return s;
}

std::ostream &operator<<(std::ostream &ispis, const Sat &s) {
  ispis << std::setfill('0') << std::setw(2) << s.sati << ":"
        << std::setfill('0') << std::setw(2) << s.minute << ":"
        << std::setfill('0') << std::setw(2) << s.sekunde;
  return ispis;
}
Sat operator-(const Sat &s, int p) {
  Sat pom;
  pom.sati = s.sati;
  pom.minute = s.minute;
  pom.sekunde = s.sekunde;
  pom.sekunde -= p;
  pom.PostaviNormalizirano(pom.sati, pom.minute, pom.sekunde);
  return pom;
}
int operator-(const Sat &s1, const Sat &s2) {
  Sat pom;
  pom.sati = s1.sati - s2.sati;
  pom.minute = s1.minute - s2.minute;
  pom.sekunde = s1.sekunde - s2.sekunde;
  pom.PostaviNormalizirano(pom.sati, pom.minute, pom.sekunde);
  int sekunde = pom.sati * 3600 + pom.minute * 60 + pom.sekunde;
  return sekunde;
}
Sat operator+(const Sat &s, int p) {
  Sat pom;
  pom.sati = s.sati;
  pom.minute = s.minute;
  pom.sekunde = s.sekunde;
  pom.sekunde += p;
  pom.PostaviNormalizirano(pom.sati, pom.minute, pom.sekunde);
  return pom;
}
int operator+(const Sat &s1, const Sat &s2) {
  Sat pom;
  pom.sati = s1.sati + s2.sati;
  pom.minute = s1.minute + s2.minute;
  pom.sekunde = s1.sekunde + s2.sekunde;
  pom.PostaviNormalizirano(pom.sati, pom.minute, pom.sekunde);
  int sekunde = pom.sati * 3600 + pom.minute * 60 + pom.sekunde;
  return sekunde;
}
int main() {
  try {
    Sat s1, s2;
    s1.Postavi(4, 11, 18);
    s2.PostaviNormalizirano(23, 11, 2);
    s1++;
    s2--;
    std::cout << s1 << std::endl;
    std::cout << s2.DajSate() << ":" << s2.DajMinute() << ":" << s2.DajSekunde()
              << std::endl;
    std::cout << "Broj sekundi izmedju: " << std::endl << s1 - s2 << std::endl;
    s2 += 21;
  } catch (...) {
    std::cout << "Greska!";
  }
  return 0;
}