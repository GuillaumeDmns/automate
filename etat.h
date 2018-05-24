#ifndef ETAT_H
#define ETAT_H
#include <iostream>
#include <string>
using namespace std;

class Etat {
private :
        unsigned int dimN;
public :
    const unsigned int getdimN() const {return dimN;}
    Etat(const unsigned int n): dimN(n){}
};

class Etat1D : public Etat{
public :
    Etat1D(unsigned int n,unsigned int* t);
    //~Etat1D();
    //Etat1D(const Etat1D& e);
    //Etat1D operator=(const Etat1D& e);
private :
    unsigned int* valeur;
};

class Etat2D : public Etat{
public :
    Etat2D(unsigned int n,unsigned int m,unsigned int** t);
    ~Etat2D();
    //Etat2D(const Etat2D& e);
    //Etat2D opertaor=(const Etat2D& e);
    const unsigned int getValue(unsigned int n,unsigned int m) const {return valeur[n][m];}
    void setValue(unsigned int n, unsigned int m, unsigned int v) const {valeur[n][m]=v;}
private :
    unsigned int** valeur;
    unsigned int dimM;
};


#endif // ETAT_H