// TP 2016/2017: LV 1, Zadatak 1
#include <cmath>
#include <iostream>

int main() {
  int duzina, sirina, dubina, d;

  std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
  std::cin >> duzina >> sirina >> dubina;

  std::cout << "\n"
            << "Unesite sirinu plocice u centimetrima: ";
  std::cin >> d;


    if((dubina*100)%d!=0){
            std::cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
    }

    if((sirina*100)%d!=0){
            std::cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
    }

    if((duzina*100)%d!=0){
            std::cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
    }




  int P_str_bazena1 = (duzina * 100) * (dubina * 100);
  int P_str_bazena2 = (sirina * 100) * (dubina * 100);
  int P_dno = (sirina * 100) * (duzina * 100);
  int P_plocice = d * d;
  int br_plocica = 0, temp = 0;



  while (temp != P_str_bazena1) {
    if (temp > P_str_bazena1) {
      break;
    }
    temp = temp + P_plocice;
    br_plocica++;
  }
  if (temp > P_str_bazena1) {
    std::cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
  }
  int plocice = 0;
  plocice = plocice + br_plocica * 2;
  temp = 0;
  br_plocica = 0;




  while (temp != P_str_bazena2) {
    if (temp > P_str_bazena2) {
      break;
    }
    temp = temp + P_plocice;
    br_plocica++;
  }

  if (temp > P_str_bazena2) {
    std::cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
  }

  plocice = plocice + br_plocica * 2;
  temp = 0;
  br_plocica = 0;




  while (temp != P_dno) {
    if (temp > P_dno) {
      break;
    }
    temp = temp + P_plocice;
    br_plocica++;
  }
  if (temp > P_dno) {
    std::cout << "\nPoplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
  }

  plocice = plocice + br_plocica;
  temp = 0;
  br_plocica = 0;

  std::cout << "\nZa poplocavanje bazena dimenzija " << duzina << "x" << sirina
            << "x" << dubina << "m sa plocicama dimenzija " << d << "x" << d
            << "cm\npotrebno je " << plocice << " plocica.";

  return 0;
}