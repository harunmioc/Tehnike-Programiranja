// TP 2022/2023: LV 8, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

std::string
ZamijeniPremaRjecniku(std::string s,
                      std::map<std::string, std::string> moj_rjecnik) {

  for (int i = 0; i < s.length(); i++) {
    std::string rijec{};

    if (s.at(i) >= 'a' && s.at(i) <= 'z') {
      auto p3 = s.at(i);
      while (s.at(i) != ' ' && i != s.length() - 1) {
        rijec.push_back(s.at(i));
        i++;
      }

      for (auto it = moj_rjecnik.begin(); it != moj_rjecnik.end(); it++) {
        if (rijec == it->first) {
            s.replace(i-rijec.length(), rijec.length(), it->second);
            i-=rijec.length();
            i+=it->second.length();
        }
      }
    }
  }
  return s;
}

int main() {

}
