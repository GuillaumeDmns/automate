#include <stdio.h>
#include <iostream>
#include "etat.h"

using namespace std;

Etat1D::Etat1D (unsigned int n,unsigned int* t=0): Etat(n), valeur(new unsigned int[n]){
    if(t)
    {
        for (unsigned int i=0;i<n;i++)
            valeur[i]=t[i];
    }
    else {
        for (unsigned int i=0;i<n;i++)
            valeur[i]=0;
    }
}

Etat2D::Etat2D(unsigned int n,unsigned int m,unsigned int** t=0):Etat(n),dimM(m),valeur(new unsigned int*[n]){
    if (t){
        for (unsigned int i=0;i<(n);i++)
            {
            valeur[i]=new unsigned int [m];
            for (unsigned int j=0;j<m;j++)
                valeur[i][j]=0;
            }
    }
    else {
        for (unsigned int i=0;i<(n);i++)
            {
            valeur[i]=new unsigned int [m];
            for (unsigned int j=0;j<m;j++)
                valeur[i][j]=t[i][j];
            }
    }
}

Etat2D::~Etat2D(){
    for (unsigned int i=0;i<this->getdimN();i++)
        {
            delete valeur[i];
        }
    delete[] valeur;
}
