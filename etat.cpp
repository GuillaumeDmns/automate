/*!
    * \file etat.cpp
    * \brief Définition des fonctions des objets Etat
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
    * \param unsigned int n : Dimension de la grille
    * \param unsigned int* t : Tableau des valeurs (par défaut =0)
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
     * \brief Destructeur de la classe Etat1D
     *
     */
Etat1D::~Etat1D(){
    delete[] valeur;
}


/*!
     * \fn Etat1D& Etat1D::operator=(const Etat1D& e)
     * \brief Opérateur d'affectation de la classe Etat1D
     *
     *
     * \param const Etat1D& e : Objet Etat1D à affecter
     * \return Etat1D&
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
    * \param unsigned int n : Dimension N de la grille
    * \param unsigned int m : Dimension M de la grille
    * \param unsigned int** t : Tableau des valeurs (par défaut =0)
    *
    */
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

/*!
    * \fn Etat2D::~Etat2D()
    * \brief Destructeur de la classe Etat2D
    *
    */
Etat2D::~Etat2D(){
    for (unsigned int i=0;i<this->getdimN();i++)
        {
            delete valeur[i];
        }
    delete[] valeur;
}

/*!
     * \fn Etat2D& Etat2D::operator=(const Etat2D& e)
     * \brief Opérateur d'affectation de la classe Etat2D
     *
     *
     * \param const Etat2D& e : Objet Etat2D à affecter
     * \return Etat2D&
     */
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


    /*!
     * \fn Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int* t) const
     * \brief Fabrique un état avec deux paramètres, en 1D
     *
     * \param unsigned int dimN : Taille pour la première dimension
     * \param unsigned int* t : Valeurs à placer dans la grille
     * \return Etat*
     */
Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int* t) const {
    if(!dimN) throw EtatException("Incorrect Etat");
    return new Etat1D(dimN,t);
}

    /*!
     * \fn Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int dimM, unsigned int** t) const
     * \brief Fabrique un état avec trois paramètres, en 2D
     *
     * \param unsigned int dimN : Taille pour la première dimension
     * \param unsigned int dimM : Taille pour la deuxième dimension
     * \param unsigned int** t : Valeurs à placer dans la grille
     * \return Etat*
     */
Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int dimM, unsigned int** t) const {
    if((!dimN)||(!dimM)) throw EtatException("Incorrect Etat");
    return new Etat2D(dimN, dimM, t);
}

    /*!
     * \fn Etat* FabriqueEtat::createEtat(Etat* e) const
     * \brief Fabrique un état par recopie d'un état existant
     *
     * \param const Etat& e : Etat existant à dupliquer
     * \return Etat&
     */
Etat* FabriqueEtat::createEtat(Etat* e) const{
    if(!strcmp(typeid(*e).name(),"Etat1D")) return (new Etat1D(*dynamic_cast<Etat1D*>(e)));
    if(!strcmp(typeid(*e).name(),"Etat2D")) return (new Etat2D(*dynamic_cast<Etat2D*>(e)));
    throw EtatException("Etat inexistant");
}

    /*!
     * \fn void FabriqueEtat::deleteEtat(Etat* e) const
     * \brief Détruit un état fourni en paramètre
     *
     * \param Etat* e : Etat à supprimer
     * \return void
     */
void FabriqueEtat::deleteEtat(Etat* e) const{
    if(!strcmp(typeid(*e).name(),"Etat1D")) delete dynamic_cast<Etat1D*>(e);
    if(!strcmp(typeid(*e).name(),"Etat2D")) delete dynamic_cast<Etat2D*>(e);
    throw EtatException("Etat non existant");
}

void FabriqueEtat::setValue(unsigned int n, unsigned int m, unsigned int v, Etat *e){
    if(n>=e->getdimN()) throw EtatException("Dimension incorrecte");
    if(!strcmp(typeid(*e).name(),"Etat1D")){
        if(m==0) dynamic_cast<Etat1D*>(e)->setValue(n,v); else throw EtatException("Dimension incorrecte");
    }
    if(!strcmp(typeid(*e).name(),"Etat2D")){
        if(m<dynamic_cast<Etat2D*>(e)->getdimM()) dynamic_cast<Etat2D*>(e)->setValue(n,m,v); else throw EtatException("Dimension incorrecte");
    }
    throw EtatException("Etat non existant");
}

unsigned int FabriqueEtat::getValue(unsigned int n, unsigned int m, Etat *e) const {
    if(n>=e->getdimN()) throw EtatException("Dimension incorrecte");
    if(!strcmp(typeid(*e).name(),"6Etat1D")){
        if(m==0) return dynamic_cast<Etat1D*>(e)->getValue(n);
        else throw EtatException("Dimension incorrecte");
    }
    if(!strcmp(typeid(*e).name(),"Etat2D")){
        if(m<dynamic_cast<Etat2D*>(e)->getdimM()) return dynamic_cast<Etat2D*>(e)->getValue(n,m); else throw EtatException("Dimension incorrecte");
    }
    throw EtatException("Etat non existant");
}
