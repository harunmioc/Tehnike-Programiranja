#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <new>
#include <cstring>
#include <type_traits>
#include <fstream>


template <typename TipEl> 
class Matrica {
  int br_redova, br_kolona;  
  char ime_matrice;
  TipEl **elementi;  

  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elementi);

public:

    Matrica(const std::string &ImeDatoteke, bool TiliB);


  Matrica(int br_redova, int br_kolona, char ime = 0);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m);

  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  //Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica m);
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


    void SacuvajUTekstualnuDatoteku( std::string ImeDatoteke);
    void SacuvajUBinarnuDatoteku ( std::string ImeDatoteke);
    void ObnoviIzTekstualneDatoteke( std::string ImeDatoteke);
    void ObnoviIzBinarneDatoteke( std::string ImeDatoteke);

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
   std::ostream& operator<<(std::ostream &tok , const Matrica<T> &matrica){
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

  /*  template <typename TipEl>
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
    } */


    template <typename TipEl>
    Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> m){
        std::swap(br_redova, m.br_redova);
        std::swap(br_kolona,m.br_kolona);
        std::swap(elementi, m.elementi);
        std::swap(ime_matrice,m.ime_matrice);
    return *this;
    }




    template <typename TipEl>
    void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(std::string ImeDatoteke){
        std::ofstream tok(ImeDatoteke);

        if(!tok){
            throw std::logic_error("Problemi sa upisom u datoteku");}
 else{
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<br_kolona; j++){
                if(j!= br_kolona-1)
                    tok<<elementi[i][j]<<",";
                        if(!tok)throw std::logic_error("Problemi sa upisom u datoteku");
                else
                    tok<< elementi[i][j];
                        if(!tok)throw std::logic_error("Problemi sa upisom u datoteku");
            }
        tok<<std::endl;
        }}

    if( !tok)
        throw std::logic_error("Problemi sa upisom u datoteku");
    }


    template <typename TipEl>
    void Matrica<TipEl>::SacuvajUBinarnuDatoteku(std::string ImeDatoteke){
        std::ofstream tok(ImeDatoteke, std::ios::binary);

        if(!tok)
            throw std::logic_error("Problemi sa upisom u datoteku");

        tok.write( reinterpret_cast<const char*>(this), sizeof *this);

            for(int i=0; i<br_redova; i++){
                tok.write(reinterpret_cast<char*>(elementi[i]), sizeof(TipEl)*br_kolona);
                    if(!tok)throw std::logic_error("Problemi sa upisom u datoteku");
            }

    if(!tok)throw std::logic_error("Problemi sa upisom u datoteku");    
}


    template <typename TipEl>
    void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(std::string ImeDatoteke){
        
        std::ifstream tok (ImeDatoteke);
        if(!tok) throw std::logic_error("Trazena datoteka ne postoji");

    bool boolTok=false;
    int brojac=0, broj_kolona=0, broj_redova=0;
    std::string red;
//test grbava
        std::getline(tok, red);
        for(auto slovo: red) 
            if(slovo==',') 
                broj_kolona++;
        broj_redova++;
    while(std::getline(tok, red)){
        int temp=0;
        for(auto slovo: red)
            if(slovo==',') temp++;
        if(temp!=broj_kolona)
            throw std::logic_error("Datoteka sadrzi besmislene podatke");
        broj_redova++;
    }

    	if(tok.eof())
            boolTok=true;
        else if( tok.bad() )
            throw std::logic_error("Datoteka sadrzi besmislene podatke");
        else
            throw std::logic_error("Porblemi pri citanju datoteke");
        

        tok.close();
        tok.open(ImeDatoteke);
        
        TipEl ClanMatrice;
        char c;
        bool Greska=false;
//test na smislenost datoteke
    for( int i =0 ; i<=broj_kolona; i++){
        if(!tok) break;
        if(i!=br_kolona){
            tok>> ClanMatrice;
                if(!tok) { Greska=true; break;}
        }else{
            tok>>ClanMatrice>>c;
                if(!tok) { Greska=true; break;}
        }
        if(tok.eof())
            break;
    }

    if(Greska || tok.bad())
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    else if(tok.eof())
        return;
    else
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

    tok.close();
    tok.open(ImeDatoteke);

//obnavljanje matrice

    for(int i=0; i< br_redova; i++){
        delete [] elementi[i];
        elementi[i]=nullptr;
    }
    delete[] elementi;
    elementi=nullptr;


    elementi= AlocirajMemoriju(br_redova, br_kolona+1);
    br_redova=broj_redova;
    br_kolona=broj_kolona+1;

    for(int i=0; i<broj_redova; i++){
        for(int j=0; j<broj_kolona+1; j++){

        if(!tok) break;

        if(j==broj_kolona){
            tok>>ClanMatrice;
            if(!tok){Greska=true; break;}
        this->elementi[i][j]=ClanMatrice;
        }
        else{
            tok>>ClanMatrice>>c;
            if(!tok){Greska=true; break;}
        this->elementi[i][j]=ClanMatrice;
        }
    if(!tok){Greska=true; break;}
    }
if(!tok){Greska=true; break;}
if(tok.eof())break;

}
if(tok.eof())return;
else if(tok.bad())
    throw std::logic_error("Datoteka sadrzi besmislene podatke");
else
    throw std::logic_error("Problemi p ir citanju datoteke");
}





    template <typename TipEl>
    void Matrica<TipEl>::ObnoviIzBinarneDatoteke(std::string ImeDatoteke){
        std::ifstream tok(ImeDatoteke, std::ios::binary);
        if(!tok)
            throw std::logic_error("Trazena datoteka ne postoji");
        
        for(int i=0; i<br_redova; i++){
            delete [] elementi[i]; 
            elementi=nullptr;   
        }
    delete[] elementi;
    elementi=nullptr;


tok.read(reinterpret_cast<char*>(this), sizeof *this);

    if(!tok)
        throw std::logic_error("Problemi pri citanju iz datotetek");
    elementi = AlocirajMemoriju(br_redova, br_kolona);

    for(int i=0; i<br_redova; i++){
        tok.read(reinterpret_cast<char*>(elementi[i]), sizeof (TipEl)*br_kolona);
    if(!tok)
        throw std::logic_error("Problemi pri citanju iz datotetek");
    }
}


    template <typename TipEl>
    Matrica<TipEl>::Matrica(const std::string &ImeDatoteke, bool TiliB){
        if(!TiliB){
       
            std::ifstream tok(ImeDatoteke);
            if(!tok)throw std::logic_error("Trazena datoteka ne postoji");

            int brojac=0,broj_redova=0, broj_kolona=0;
            bool boollll=true;
            TipEl ElementMatrice;

            while(true){
                if(!tok) break;
                while(true){
                    if(!tok) break;

                        tok>>ElementMatrice;
                        if(tok.peek()==','){
                            tok.get();
                            broj_kolona++;
                        }
    //biljeska sebi (mozda samo bez \n)
                        else if(tok.peek()=='\n'){
                            broj_kolona++; break;
                        }
                }
        if(!tok) break;
        broj_redova++;
        if(boollll){
            brojac=broj_kolona;
            broj_kolona=0;
            boollll=false;
        }
        else{
            if(broj_kolona!=brojac) throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
    }
    if(!tok && tok.bad())throw std::logic_error("Problem pri citanju datoteke");
    if(!tok && !tok.eof())throw std::logic_error("Datoteka sadrzi besmislene podatke");
    else if(!tok && tok.eof()) tok.clear();
    tok.close();
    tok.open(ImeDatoteke);

    br_kolona=brojac;
    br_redova=broj_redova+1;


      elementi= AlocirajMemoriju(br_redova, br_kolona);

      for(int i=0; i<br_redova; i++){
        for(int j=0; j<br_redova; j++){
            tok>>elementi[i][j];
            if(j<br_kolona-1) tok.get();
        }
      }
}
    else {
            std::ifstream tok(ImeDatoteke, std::ios::binary);
            if(!tok)throw std::logic_error("Trazena datoteka ne postoji");
tok.read(reinterpret_cast<char*>(this),   sizeof(*this));
    elementi=AlocirajMemoriju(br_redova, br_kolona);
    for(int i=0; i<br_redova; i++){
        tok.read(reinterpret_cast<char*>(elementi[i]), sizeof(TipEl)*br_kolona);
    }

        }
    }





int main() {





  return 0;
}
