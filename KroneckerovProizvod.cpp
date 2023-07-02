/*Kroneckerov (ili tenzorski) proizvod dva vektora a i b (u matematičkom smilslu) čiji su koeficijenti
a_ 𝑖, i = 1,2,…,𝑚 i b_j, 𝑗 = 1,2,…,𝑛, u oznaci ⊗ , predstavlja matricu formata 𝑚 × 𝑛 čiji su elementi
 (to je zapravo “tablica množenja” formirana od elemenata ova dva vektora). Napišite generičku
funkciju koja kao svoje parametre prihvata vektore i , pri čemu oni mogu biti smješteni u bilo
kojem kontejnerskom tipu podataka koji podržava indeksiranje i funkciju “size” (npr. mogu biti
smješteni u vektoru, ili u deku), pri čemu se tipovi kontejnera u kojima su smješteni elementi vektora
 i mogu razlikovati. Čak je dopušteno da se razlikuju i tipovi elemenata u ova dva kontejnera
(recimo, prvi parametar može biti dek cijelih brojeva, a drugi vektor realnih brojeva). Funkcija treba
da dinamički alocira matricu koju će popuniti elementima Kroneckerovog proizvoda vektora koji su
proslijeđeni kao parametri, i da vrati kao rezultat dvojni pokazivač pomoću kojeg se može pristupiti
elementima tako kreirane matrice. Tip elemenata matrice je onakav kakav je potreban da se smjesti
rezultat množenja elemenata iz ova dva vektora (npr. ako sadrži cijele a realne brojeve, matrica
treba sadržavati realne brojeve, jer se množenjem cijelog sa realnim brojem dobija realni broj).
Alokaciju treba izvesti postupkom kontinualne alokacije. U slučaju da alokacija ne uspije, treba baciti
izuzetak tipa “logic_error” uz prateći tekst “Alokacija nije uspjela”. Funkcija ne smije uzrokovati
curenje memorije ni pod kakvim okolnostima. Demonstrirajte napisanu funkciju u isječku programa
u kojem ćete kreirati Kroneckerov proizvod dva fiksna vektora cijelih brojeva, ispisati elemente
kreiranog Kroneckerovog proizvoda na ekran, i na kraju osloboditi svu alociranu memoriju. */

#include <deque>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

#include <algorithm>
#include <cctype>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

template <typename T> void OslobodiMemoriju(T **matrica, size_t m) {
  delete[] matrica[0];
  delete[] matrica;
}

template <typename Tip1, typename Tip2>
auto KroneckerovProizvod(Tip1 &blok1, Tip2 &blok2) {
  using TipEl = std::remove_reference_t<decltype(blok1[0], blok2[0])>;

  TipEl **elementi = nullptr;
  try {
    elementi = new TipEl *[blok1.size()];
    elementi[0] = new TipEl[blok1.size() * blok2.size()];

    for (int i = 1; i < blok1.size(); i++)
      elementi[i] = elementi[i - 1] + blok2.size();

    for (int i = 0; i < blok1.size(); i++) {
      for (int j = 0; j < blok2.size(); j++) {
        elementi[i][j] = blok1[i] * blok2[j];
      }
    }
  } catch (...) {
    OslobodiMemoriju(elementi, blok1.size());
    throw std::logic_error("Alokacija nije uspjela");
  }
  return elementi;
}

int main() {

  std::vector<int> vektor1 = {1, 2, 3, 4, 5};
  std::deque<double> vektor2 = {0.5, 1.5, 2.5};

  decltype(KroneckerovProizvod(vektor1, vektor2)) mat = nullptr;

    mat = KroneckerovProizvod(vektor1, vektor2);
    for (size_t i = 0; i < vektor1.size(); i++) {
      for (size_t j = 0; j < vektor2.size(); j++) {
        std::cout << mat[i][j] << ",  ";
      }
      std::cout << std::endl;
    }
    
    OslobodiMemoriju(mat, vektor1.size());


  return 0;
}
