// TP 2022/2023: LV 3, Zadatak 5
#include <cmath>
#include <deque>
#include <iostream>

std::deque<int> Obrni(std::deque<int> v) {
  int brel = v.size();

  if (brel % 2 == 0) {
    for (int i = 0; i < (brel / 2); i++) {
      int temp = v[i];
      v[i] = v[brel - (i + 1)];
      v[(brel - (i + 1))] = temp;
    }

  }

  else {
    for (int i = 0; i < std::floor(brel / 2); i++) {
      int temp = v[i];
      v[i] = v[(brel - (i + 1))];
      v[(brel - (i + 1))] = temp;
    }
  }

  return v;
}

std::deque<int> IzdvojiElemente(std::deque<int> v, bool Y_N) {

  std::deque<int> v2;

  if (Y_N == true) {

    for (int x : v) {
      int suma = 0;

      int temp = x;
      while (temp != 0) {
        suma = suma + temp;
        temp = temp / 10;
      }

      if (suma % 2 == 0) {
        v2.push_front(x);
      }
    }

  }

  else {
    for (int x : v) {
      int suma = 0;

      int temp = x;
      while (temp != 0) {
        suma = suma + temp;
        temp = temp / 10;
      }

      if (suma % 2 != 0) {
        v2.push_front(x);
      }
    }
  }

  return Obrni(v2);
}

int main() {
  int n;
  std::deque<int> v;

  std::cout << "Koliko zelite unijeti elemenata: ";
  std::cin >> n;
  if (n <= 0) {
    std::cout << "Broj elemenata mora biti veci od 0!";
    return 0;
  }
  std::cout << "Unesite elemente: ";

  for (int i = 0; i < n; i++) {
    int br;
    std::cin >> br;
    v.push_back(br);
  }

  // parni
  std::deque<int> b = IzdvojiElemente(v, true);
  // neparni
  std::deque<int> c = IzdvojiElemente(v, false);

  for (int i = 0; i < b.size(); i++) {
    if (i == b.size() - 1) {
      std::cout << b[i];
      break;
    }
    std::cout << b[i] << ",";
  }

  std::cout << "\n";

  for (int i = 0; i < c.size(); i++) {
    if (i == c.size() - 1) {
      std::cout << c[i];
      break;
    }
    std::cout << c[i] << ",";
  }

  return 0;
}
