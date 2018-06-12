/*!
    * \file etat.cpp
    * \brief Définition des fonctions de l'objet Etat
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Fichier pour définir les fonctions relatives à Etat non inline
    *
    */


#include <stdio.h>
#include <iostream>
#include "etat.h"
#include <typeinfo>
#include "string.h"

using namespace std;

/*!
    * \fn Etat1D::Etat1D (unsigned int n,unsigned int* t=0)
    * \brief Constructeur de la classe Etat1D
    *
    * \param unsigned int n : dimension de la grille
    * \param unsigned int* t : tableau des valeurs (par défaut =0)
    * \return
    *
    */
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

/*!
     * \fn Etat1D::~Etat1D()
     * \brief Destructeur
     *
     *
     *
     * \return
     */
Etat1D::~Etat1D(){
    delete[] valeur;
}


/*!
     * \fn Etat1D::operator=(const Etat1D& e)
     * \brief Opérateur affectation
     *
     *
     * \param Etat1D& e : objet Etat1D à affecter
     * \return
     */
Etat1D& Etat1D::operator=(const Etat1D& e){
    if (getdimN()!=e.getdimN())
        throw "erreur : taille des grilles incompatibles";
    else {
    for (unsigned int i=0;i<getdimN();i++)
                valeur[i]=e.valeur[i];
    }
    return *this;
}

/*!
    * \fn Etat2D::Etat2D (unsigned int n,unsigned int m,unsigned int** t=0)
    * \brief Constructeur de la classe Etat2D
    *
    * \param unsigned int n : dimension N de la grille
    * \param unsigned int m : dimension M de la grille
    * \param unsigned int** t : tableau des valeurs (par défaut =0)
    * \return
    *
    */
Etat2D::Etat2D(unsigned int n,unsigned int m,unsigned int** t):Etat(n),dimM(m),valeur(new unsigned int*[n]){
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

/*!
    * \fn Etat2D::~Etat2D()
    * \brief Destructeur de la classe Etat2D
    *
    *
    * \return
    *
    */
Etat2D::~Etat2D(){
    for (unsigned int i=0;i<this->getdimN();i++)
        {
            delete valeur[i];
        }
    delete[] valeur;
}


Etat2D& Etat2D::operator=(const Etat2D& e){
    if (dimM!=e.dimM || getdimN()!=e.getdimN())
        throw "erreur : tailles des grilles incompatibles";
    else {
    for (unsigned int i=0;i<getdimN();i++)
        for (unsigned int j=0;j<dimM;j++)
                valeur[i][j]=e.valeur[i][j];
    }
    return *this;
}

Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int* t) const {
    if(!dimN) throw EtatException("Incorrect Etat");
    return new Etat1D(dimN,t);
}

Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int dimM, unsigned int** t) const {
    if((!dimN)||(!dimM)) throw EtatException("Incorrect Etat");
    return new Etat2D(dimN, dimM, t);
}

Etat* FabriqueEtat::createEtat(Etat* e) const{
    if(!strcmp(typeid(*e).name(),"Etat1D")) return (new Etat1D(*dynamic_cast<Etat1D*>(e)));
    if(!strcmp(typeid(*e).name(),"Etat2D")) return (new Etat2D(*dynamic_cast<Etat2D*>(e)));
    throw EtatException("Etat inexistant");
}

void FabriqueEtat::deleteEtat(Etat* e) const{
    if(!strcmp(typeid(*e).name(),"Etat1D")) delete dynamic_cast<Etat1D*>(e);
    if(!strcmp(typeid(*e).name(),"Etat2D")) delete dynamic_cast<Etat2D*>(e);
    throw EtatException("Etat non existant");
}

