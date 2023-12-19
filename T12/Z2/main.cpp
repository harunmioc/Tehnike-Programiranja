
#include <iostream>
#include <set>




template <typename Tip>
std::set<Tip> &operator+=(std::set<Tip> &s1, std::set<Tip> s2) {

  typename std::set<Tip>::iterator p1(s1.begin()), k1(s1.end());
  typename std::set<Tip>::iterator p2(s2.begin()), k2(s2.end());
  std::set<Tip> pom;
  while (p1 != k1) {
    pom.insert(*p1);
    p1++;
  }
  while (p2 != k2) {
    pom.insert(*p2);
    p2++;
  }
  s1 = pom;
  return s1;
}

template <typename Tip>
std::set<Tip> operator+(std::set<Tip> s1, std::set<Tip> s2) {
  std::set<Tip> unija(s1 += s2);
  return unija;
}


template <typename Tip>
std::set<Tip> &operator*=(std::set<Tip> &s1, std::set<Tip> s2) {
  typename std::set<Tip>::iterator p1(s1.begin()), k1(s1.end()), p2(s2.begin()), k2(s2.end());

  std::set<Tip> pom;
  while (p1 != k1) {
    if (s2.find(*p1) != s2.end())
      pom.insert(*p1);
    p1++;
  }
  s1 = pom;
  return s1;
}

template <typename Tip>
std::set<Tip> operator*(std::set<Tip> s1, std::set<Tip> s2) {
  std::set<Tip> presjek(s1 *= s2);
  return presjek;
}
template <typename Tip1, typename Tip2>
std::set<std::pair<Tip1, Tip2>> operator%(std::set<Tip1> s1,
                                          std::set<Tip2> s2) {
  std::set<std::pair<Tip1, Tip2>> pom;
  typename std::set<Tip1>::iterator p1(s1.begin()), k1(s1.end());
  typename std::set<Tip2>::iterator p2(s2.begin()), k2(s2.end());
  while (p1 != k1) {
    while (p2 != k2) {
      pom.insert({*p1, *p2});
      p2++;
    }
    p2 = s2.begin();
    p1++;
  }
  return pom;
}
template <typename Tip>
std::ostream &operator<<(std::ostream &ispis, std::set<Tip> skup) {
  ispis << '{';
  auto p(skup.begin());
  if (skup.size() == 0)
    return ispis << '}';
  for (auto i = 0; i < skup.size() - 1; i++)
    ispis << *p++ << ",";
  ispis << *p << '}';
  return ispis;
}
template <typename Tip1, typename Tip2>
std::ostream &operator<<(std::ostream &ispis,
                         std::set<std::pair<Tip1, Tip2>> skup) {
  ispis << '{';
  auto p(skup.begin());
  if (skup.size() == 0)
    return ispis << "}";
  for (auto i = 0; i < skup.size() - 1; i++) {
    ispis << '(' << p->first << "," << p->second << ")"
          << ",";
    p++;
  }
  ispis << '(' << p->first << "," << p->second << ')' << "}";
  return ispis;
}
int main() {
  std::set<int> s1{3, 5, 1, 2, 8}, s2{7, 2, 8, 4};
  std::cout << s1 + s2 << std::endl;
  std::cout << s1 * s2 << std::endl;
  std::set<char> s3{'A', 'B'};
  std::set<int> s4{1, 2, 3};
  std::cout << s3 % s4 << std::endl;
  return 0;
}