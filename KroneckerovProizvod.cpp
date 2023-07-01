#include <deque>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename Tip1, typename Tip2>
auto KroneckerovProizvod(Tip1 &blok1, Tip2 &blok2) {
  using TipEl = std::remove_reference_t<decltype(blok1[0], blok2[0])>;

  TipEl **elementi = nullptr;
  try {
    elementi = new TipEl *[blok1.size()];
    for (int i = 0; i < blok1.size(); i++)
      elementi[i] = new TipEl[blok2.size()];

    for (int i = 0; i < blok1.size(); i++) {
      for (int j = 0; j < blok2.size(); j++) {
        elementi[i][j] = blok1[i] * blok2[j];
      }
    }
  } catch (...) {
    for (int i = 0; i < blok2.size(); i++)
      delete[] elementi[i];
    delete[] elementi;
    throw std::logic_error("Alokacija nije uspjela");
  }
  return elementi;
}

template <typename T> void OslobodiMemoriju(T **matrica, size_t m) {
  for (size_t i = 0; i < m; i++) {
    delete[] matrica[i];
  }
  delete[] matrica;
}

int main() {

  std::vector<int> vektor1 = {1, 2, 3, 4, 5};
  std::deque<double> vektor2 = {0.5, 1.5, 2.5};

  decltype(KroneckerovProizvod(vektor1, vektor2)) mat = nullptr;
  try {
    auto mat = KroneckerovProizvod(vektor1, vektor2);
    for (size_t i = 0; i < vektor1.size(); i++) {
      for (size_t j = 0; j < vektor2.size(); j++) {
        std::cout << mat[i][j] << ",  ";
      }
      std::cout << std::endl;
    }
  } catch (...) {
    OslobodiMemoriju(mat, vektor1.size());
  }

  OslobodiMemoriju(mat, vektor1.size());

  return 0;
}
