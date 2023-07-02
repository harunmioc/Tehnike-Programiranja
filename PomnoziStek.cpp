/*Napišite funkciju koja kao jedan parametar prima neki stek realnih brojeva, a kao drugi parametar
neki realni broj. Funkcija kao rezultat treba da vrati novi stek realnih brojeva čiji su elementi jednaki
elementima izvornog steka pomnoženi sa zadanim brojem. Na primjer, ukoliko se u steku koji je
proslijeđen kao parametar nalaze brojevi 2, 5, 3 i 4 (tim redom), i ukoliko se kao drugi parametar
proslijedi broj 3, stek vraćen kao rezultat treba da sadrži brojeve 6, 15, 9 i 12 (tim redom). Podsjetimo
se da je stek kontejnerska struktura koja ne podržava ništa drugo osim operacija “push” (dodaj novi
element na vrh steka), “top” (daj element koji je na vrhu steka), “pop” (ukloni element sa vrha steka),
“size” (daj broj elemenata u steku) i “empty” (daj informaciju da li je stek prazan ili ne). Za realizaciju
ove funkcije ne smijete koristiti nikakvu pomoćnu funkciju, osim eventualno jednog pomoćnog steka
ukoliko smatrate da Vam je potreban. */

#include <iostream>
#include <stack>

std::stack<double> PomnoziStek(std::stack<double> &stek, double broj) {
  std::stack<double> rezultantni;

  while (!stek.empty()) {
    double element = stek.top();
    stek.pop();
    rezultantni.push(element * broj);
  }

  return rezultantni;
}



int main() {
  std::stack<double> stek;
  stek.push(2);
  stek.push(5);
  stek.push(3);
  stek.push(4);

  double faktor = 3;
  std::stack<double> rezultat = PomnoziStek(stek, faktor);

  while (!rezultat.empty()) {
    std::cout << rezultat.top() << " ";
    rezultat.pop();
  }
  return 0;
}
