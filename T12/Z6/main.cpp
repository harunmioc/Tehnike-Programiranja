#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <new>
#include <cstring>
#include <type_traits>

template <typename TipEl> 
class Matrica {
  int br_redova, br_kolona;  
  char ime_matrice;
  TipEl **elementi;  

  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elementi);

public:
  Matrica(int br_redova, int br_kolona, char ime = 0);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m);

  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica &&m);
  void Unesi();
  void Ispisi(int sirina_ispisa) const;

  template <typename Tip2>
  friend Matrica<Tip2> ZbirMatrica(const Matrica<Tip2> &m1,const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator+(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator-(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> &operator+=( Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> &operator-=( Matrica<Tip2> &m, const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> &operator*=( Matrica<Tip2> &m, const Matrica<Tip2> &m2);

  TipEl* &operator[](int indeks) {return elementi[indeks];}
  TipEl* operator[](int indeks) const { return elementi[indeks];}

  TipEl &operator()(int i, int j);
  TipEl operator()(int i, int j) const;
  operator std::string() const;

  template <typename Tip2>
  friend std::ostream &operator<<(std::ostream &os, const Matrica<Tip2> &matrica);
  template <typename Tip2>
  friend std::istream &operator>>(std::istream &is, Matrica<Tip2> &m);

  template <typename Tip2>
  friend Matrica<Tip2> operator*(int skalar, const Matrica<Tip2> &m);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &m, int skalar);
  template <typename Tip2>
  friend Matrica<Tip2> &operator*=( Matrica<Tip2> &m, int skalar);
};
//m1   +  m2
template <typename T>
 Matrica<T> operator+ (const Matrica<T> &m1, const Matrica<T> &m2){
    if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
      throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<T> rezultantna(m1.br_redova, m1.br_kolona);
    for(int i = 0; i< m1.br_redova; i++)
        for(int j = 0; j<m1.br_kolona; j++)
            rezultantna.elementi[i][j]=0;

    for(int i = 0; i< m1.br_redova; i++)
        for(int j = 0; j<m1.br_kolona; j++)
        	rezultantna.elementi[i][j]= m1.elementi[i][j] + m2.elementi[i][j];
    return rezultantna;
 }

//m1  -  m2
template <typename TipEl>
 Matrica <TipEl> operator- (const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
      throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> rezultantna(m1.br_redova, m2.br_kolona);
    for(int i = 0; i< m1.br_redova; i++)
        for(int j = 0; j<m1.br_kolona; j++)
            rezultantna.elementi[i][j]=0;

    for(int i = 0; i< m1.br_redova; i++)
        for(int j = 0; j<m1.br_kolona; j++)
        	rezultantna.elementi[i][j]= m1.elementi[i][j] - m2.elementi[i][j];
    return rezultantna;
 }

//m1   *   m2
template <typename TipEl>
 Matrica <TipEl> operator* (const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    if (m1.br_kolona != m2.br_redova)
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipEl> rezultantna(m1.br_redova, m2.br_kolona);
    for(int i = 0; i< m1.br_redova; i++)
        for(int j = 0; j<m1.br_kolona; j++)
            rezultantna.elementi[i][j]=0;

    for(int i = 0; i< m1.br_redova; i++)
        for(int j = 0; j<m2.br_redova; j++)
            for(int k=0; k< m1.br_kolona; k++)
        	rezultantna.elementi[i][j]+= m1.elementi[i][k] * m2.elementi[k][j];

    return rezultantna;
 }

//m1  +=   m2
template <typename TipEl>
    Matrica<TipEl> &operator+=( Matrica<TipEl> &m1,const Matrica<TipEl> &m2 ){
        if (m1.br_kolona != m2.br_redova || m2.br_redova != m1.br_redova)
            throw std::domain_error("Matrice nemaju jednake dimenzije!");
        for(int i=0; i<m1.br_redova; i++)
            for(int j=0; j<m1.br_kolona; j++)
                m1.elementi[i][j]+=m2.elementi[i][j];
    return m1;
    }


//m1  -=   m2
template <typename TipEl>
    Matrica<TipEl> &operator-=( Matrica<TipEl> &m1,const Matrica<TipEl> &m2 ){
        if (m1.br_kolona != m2.br_redova)
            throw std::domain_error("Matrice nemaju jednake dimenzije!");
        for(int i=0; i<m1.br_redova; i++)
            for(int j=0; j<m1.br_kolona; j++)
                m1.elementi[i][j]-=m2.elementi[i][j];
    return m1;
    }


//m1  *=  m2
template <typename TipEl>
 Matrica <TipEl> &operator*= ( Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    if (m1.br_kolona != m2.br_redova)
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipEl> rezultantna(m1.br_redova, m2.br_kolona);
    m1= m1*m2;
    return m1;
 }


template <typename TipEl>
TipEl &Matrica<TipEl>::operator() (int i, int j) {
    if(i<1 || j<1 || i>br_redova || j>br_kolona)
        throw std::range_error("Neispravan indeks");
    return elementi[i-1][j-1];
}

template <typename TipEl>
TipEl Matrica<TipEl>::operator() (int i, int j) const {
    if(i<1 || j<1 || i>br_redova || j>br_kolona)
        throw std::range_error("Neispravan indeks");
    return elementi[i-1][j-1];
}


    template <typename TipEl>
    Matrica<TipEl>::operator std::string()const{
        std::string string;
        string = string + '{';
        for (int i = 0; i < br_redova; i++) {
            string = string + "{";
            for (int j = 0; j < br_kolona; j++) {
            string = string + std::to_string(int(elementi[i][j]));
            if (j != br_kolona - 1)
                string = string + ",";
            }
            string = string + "}";
            if (i != br_redova - 1)
            string = string + ",";
        }
        string = string + "}";
        return string;
    }

    template <typename T>
   std::ostream &operator<<(std::ostream &tok , const Matrica<T> &matrica){
        int sirina = tok.width();

        for(int i=0; i< matrica.br_redova; i++){
            for( int j=0; j<matrica.br_kolona; j++)
                tok<< std::setw(sirina)<< matrica.elementi[i][j];
            tok<<std::endl;
        }
    return tok;
   }

    template <typename T>
    std::istream& operator>>(std::istream &tok, Matrica<T> &m){
        for(int i=0; i< m.br_redova; i++)
            for( int j=0; j<m.br_kolona; j++){
                std::cout<<m.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
                std::cin>>m.elementi[i][j];
            }
    return tok;
    }



  template <typename TipEl>
   Matrica<TipEl> operator*(const Matrica<TipEl> &m, int skalar){
    Matrica<TipEl> rezultantna(m.br_redova, m.br_kolona);
    for (int i = 0; i < rezultantna.br_redova; i++)
      for (int j = 0; j < rezultantna.br_kolona; j++)
        rezultantna.elementi[i][j] = 0;

    for(int i = 0; i< m.br_redova; i++)
        for(int j = 0; j<m.br_kolona; j++)
        	rezultantna.elementi[i][j]= m.elementi[i][j] *skalar;
    return rezultantna;
   }


  template <typename TipEl>
   Matrica<TipEl> &operator*=( Matrica<TipEl> &m, int skalar){

    for(int i = 0; i< m.br_redova; i++)
        for(int j = 0; j<m.br_kolona; j++)
        	m.elementi[i][j]*= skalar;
    return m;
   }


  template <typename TipEl>
   Matrica<TipEl> operator*(int skalar, const Matrica<TipEl> &m ){
    Matrica<TipEl> rezultantna(m.br_redova, m.br_kolona);
        for (int i = 0; i < rezultantna.br_redova; i++)
      for (int j = 0; j < rezultantna.br_kolona; j++)
        rezultantna.elementi[i][j] = 0;

    for(int i = 0; i< m.br_redova; i++)
        for(int j = 0; j<m.br_kolona; j++)
        	rezultantna.elementi[i][j]=  m.elementi[i][j]*skalar;
    return rezultantna;
   }




    template <typename TipEl>
    void Matrica<TipEl>::Unesi(){
        for(int i=0; i< br_redova; i++)
            for( int j=0; j<br_kolona; j++){
                std::cout<<ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
                std::cin>>elementi[i][j];
            }
    }
    template <typename TipEl>
    void Matrica<TipEl>::Ispisi(int sirina) const{
        for(int i=0; i< br_redova; i++)
            for( int j=0; j<br_kolona; j++){
                std::cout<<std::setw(sirina)<<elementi[i][j];
        std::cout<<std::endl;
    }
}

    template <typename TipEl>
    Matrica<TipEl> ZbirMatrica(const Matrica <TipEl> &m1, const Matrica <TipEl> &m2){
        if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
            throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
        for (int i = 0; i < m1.br_redova; i++)
            for (int j = 0; j < m1.br_kolona; j++)
                m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
    }


    template <typename TipEl>
    TipEl** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona){
        TipEl** elementi = new TipEl* [br_redova]{};
        try{
            for(int i=0; i< br_redova; i++)
                elementi[i]=new TipEl[br_kolona];
        }catch(...){
            DealocirajMemoriju(elementi,br_redova);
            throw;
        }
    return elementi;
    } 

    template <typename TipEl>
    void Matrica<TipEl>::DealocirajMemoriju (TipEl** elementi, int br_redova){
        for(int i=0; i<br_redova; i++)
            delete [] elementi[i];
        delete [] elementi; 
    }


    template <typename TipEl>
    Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime): br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime), elementi(AlocirajMemoriju(br_redova, br_kolona)){}

    template <typename TipEl>
    void Matrica<TipEl>::KopirajElemente(TipEl** elementi){
        for(int i=0; i<br_redova; i++)
            for( int j=0; j<br_kolona; j++)
                Matrica::elementi[i][j]=elementi[i][j];
    }

    template <typename TipEl>
    Matrica<TipEl>::Matrica(const Matrica<TipEl> &m):br_redova(m.br_redova),br_kolona(m.br_kolona),ime_matrice(m.ime_matrice),elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)){
        KopirajElemente(m.elementi);
    }

    template <typename TipEl>
    Matrica<TipEl>::Matrica(Matrica<TipEl> &&m):br_redova(m.br_redova),br_kolona(m.br_kolona),ime_matrice(m.ime_matrice),elementi(m.elementi){
        m.br_redova=0;
        m.br_kolona=0;
        m.elementi=nullptr;
    }

    template <typename TipEl>
    Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m){
    if(br_redova< m.br_redova || br_kolona<m.br_kolona){
        TipEl** novo=AlocirajMemoriju(m.br_redova,m.br_kolona);
        DealocirajMemoriju(elementi, br_redova);
        elementi=novo;

    }else if(br_redova >m.br_redova){
        for(int i=m.br_redova; i<br_redova; i++)
        delete elementi[i];
    }
        br_redova=m.br_redova;
        br_kolona=m.br_kolona;
        ime_matrice=m.ime_matrice;
        KopirajElemente(m.elementi);
        return *this;
    }


    template <typename TipEl>
    Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m){
        std::swap(br_redova, m.br_redova);
        std::swap(br_kolona,m.br_kolona);
        std::swap(elementi, m.elementi);
        std::swap(ime_matrice,m.ime_matrice);
    return *this;
    }



int main() {
  int m, n;
  std::cout << "Unesi broj redova i kolona za matrice:\n";
  std::cin >> m >> n;
  try {
    Matrica<double> a(m, n, 'A'), b(m, n, 'B');
    std::cout << "Unesi matricu A:\n";
    std::cin >> a;
    std::cout << "Unesi matricu B:\n";
    std::cin >> b;
    std::cout << "Zbir ove dvije matrice je:\n";
    std::cout << std::setw(7) <<a+b;

  } catch (std::bad_alloc & izuzetak) {
    std::cout << "Nema dovoljno memorije!\n";
  }
  return 0;
}
