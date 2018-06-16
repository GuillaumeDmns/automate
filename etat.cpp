/*!
    * \file etat.cpp
    * \brief Définition des fonctions des objets Etat
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 16 juin 2018
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
    * \fn Etat1D::Etat1D (unsigned int n, const unsigned int* t)
    * \brief Constructeur de la classe Etat1D
    *
    * \param unsigned int n : Dimension de la grille
    * \param const unsigned int* t : Tableau des valeurs
    *
    */
Etat1D::Etat1D (unsigned int n, const unsigned int* t): Etat(n), valeur(new unsigned int[n]){
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
     * \fn void Etat1D::copyEtat(const Etat1D* source)
     * \brief Remplace l'état par un état donné en paramètre de la classe Etat1D
     *
     *
     * \param const Etat1D* source : Objet Etat1D à affecter
     * \return void
     */
void Etat1D::copyEtat(const Etat1D* source){
    if (source->getdimN()!=dimN)
        throw "erreur : taille des grilles incompatibles";
    else {
    for (unsigned int i=0;i<dimN;++i)
                valeur[i]=source->getValue(i);
    }
}

/*!
    * \fn Etat2D::Etat2D (unsigned int n,unsigned int m, const unsigned int** t)
    * \brief Constructeur de la classe Etat2D
    *
    * \param unsigned int n : Dimension N de la grille
    * \param unsigned int m : Dimension M de la grille
    * \param const unsigned int** t : Tableau des valeurs
    *
    */
Etat2D::Etat2D(unsigned int n,unsigned int m, const unsigned int** t):Etat(n),dimM(m),valeur(new unsigned int*[n]){
    for (unsigned int i=0;i<(n);i++)
        {
        valeur[i]=new unsigned int [m];
        for (unsigned int j=0;j<m;j++)
            valeur[i][j]=t[i][j];
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
 * \fn void Etat2D::copyEtat(const Etat2D* source)
 * \brief Remplace l'état par un état donné en paramètre, de la classe Etat2D
 *
 * \param const Etat2D* source : Objet Etat2D à affecter à l'objet courant
 * \return void
 */
void Etat2D::copyEtat(const Etat2D* source){
    if (source->getdimM()!=dimM || source->getdimN()!=dimN)
        throw "erreur : tailles des grilles incompatibles";
    else {
    for (unsigned int i=0;i<dimN;i++)
        for (unsigned int j=0;j<dimM;j++)
                valeur[i][j]=source->getValue(i,j);
    }
}


    /*!
     * \fn Etat* FabriqueEtat::createEtat(unsigned int dimN, const unsigned int* t) const
     * \brief Fabrique un état avec deux paramètres, en 1D
     *
     * \param unsigned int dimN : Taille pour la première dimension
     * \param const unsigned int* t : Valeurs à placer dans la grille
     * \return Etat*
     */
Etat* FabriqueEtat::createEtat(unsigned int dimN, const unsigned int* t) const {
    if(!dimN) throw EtatException("Incorrect Etat");
    return new Etat1D(dimN,t);
}

    /*!
     * \fn Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int dimM, const unsigned int** t) const
     * \brief Fabrique un état avec trois paramètres, en 2D
     *
     * \param unsigned int dimN : Taille pour la première dimension
     * \param unsigned int dimM : Taille pour la deuxième dimension
     * \param const unsigned int** t : Valeurs à placer dans la grille
     * \return Etat*
     */
Etat* FabriqueEtat::createEtat(unsigned int dimN, unsigned int dimM, const unsigned int** t) const {
    if((!dimN)||(!dimM)) throw EtatException("Incorrect Etat");
    return new Etat2D(dimN, dimM, t);
}

    /*!
     * \fn Etat* FabriqueEtat::createEtat(Etat* e) const
     * \brief Fabrique un état par recopie d'un état existant
     *
     * \param Etat* e : Etat existant à dupliquer
     * \return Etat*
     */
Etat* FabriqueEtat::createEtat(Etat* e) const{
    if(!strcmp(typeid(*e).name(),"6Etat1D")) return (new Etat1D(*dynamic_cast<Etat1D*>(e)));
    if(!strcmp(typeid(*e).name(),"6Etat2D")) return (new Etat2D(*dynamic_cast<Etat2D*>(e)));
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
    if(!strcmp(typeid(*e).name(),"6Etat1D")) delete dynamic_cast<Etat1D*>(e); else
    if(!strcmp(typeid(*e).name(),"6Etat2D")) delete dynamic_cast<Etat2D*>(e); else
    throw EtatException("Etat non existant");
}

    /*!
     * \fn void FabriqueEtat::setValue(unsigned int n, unsigned int m, unsigned int v, Etat *e)
     * \brief Donne une valeur v à la case (n,m) de l'état e
     *
     * \param unsigned int n : Abscisse de la case à affecter
     * \param unsigned int m : Ordonnée de la case à affecter
     * \param unsigned int v : Valeur à affecter
     * \param Etat* e : Etat auquel affecter la valeur
     * \return void
     */
void FabriqueEtat::setValue(unsigned int n, unsigned int m, unsigned int v, Etat *e){
    if(n>=e->getdimN()) throw EtatException("Dimension incorrecte");
    if(!strcmp(typeid(*e).name(),"6Etat1D")){
        if(m==0) dynamic_cast<Etat1D*>(e)->setValue(n,v); else throw EtatException("Dimension incorrecte");
        return;
    }
    if(!strcmp(typeid(*e).name(),"6Etat2D")){
        if(m<dynamic_cast<Etat2D*>(e)->getdimM()) dynamic_cast<Etat2D*>(e)->setValue(n,m,v); else throw EtatException("Dimension incorrecte");
        return;
    }
    throw EtatException("Etat non existant");
}

    /*!
     * \fn unsigned int FabriqueEtat::getValue(unsigned int n, unsigned int m, Etat *e) const
     * \brief Retourne la valeur affectée à une case
     *
     * \param unsigned int n : Abscisse de la case à retourner
     * \param unsigned int m : Ordonnée de la case à retourner
     * \param Etat* e : Etat dont on veut récupérer une valeur
     * \return unsigned int
     */
unsigned int FabriqueEtat::getValue(unsigned int n, unsigned int m, Etat *e) const {
    if(n>=e->getdimN()) throw EtatException("Dimension incorrecte");
    if(!strcmp(typeid(*e).name(),"6Etat1D")){
        if(m==0) return dynamic_cast<Etat1D*>(e)->getValue(n);
        else throw EtatException("Dimension incorrecte");
    }
    if(!strcmp(typeid(*e).name(),"6Etat2D")){
        if(m<dynamic_cast<Etat2D*>(e)->getdimM()) return dynamic_cast<Etat2D*>(e)->getValue(n,m);
        else throw EtatException("Dimension incorrecte");
    }
    throw EtatException("Etat non existant");
}

    /*!
     * \fn void FabriqueEtat::copyEtat(Etat* source, Etat* dest) const
     * \brief Remplace l'état par un état donné en paramètre, selon le type d'état
     *
     * \param Etat* source : Objet Etat à affecter à l'objet courant
     * \param Etat* dest : Etat de destination de l'affectation
     * \return void
     */
void FabriqueEtat::copyEtat(Etat* source, Etat* dest) const {
    if(strcmp(typeid(*source).name(),typeid(*dest).name())) throw EtatException("Etats incompatibles");
    else {
        if(!strcmp(typeid(*source).name(),"6Etat1D")) dynamic_cast<Etat1D*>(dest)->copyEtat(dynamic_cast<Etat1D*>(source));
        else {
            if(!strcmp(typeid(*source).name(),"6Etat2D")) dynamic_cast<Etat2D*>(dest)->copyEtat(dynamic_cast<Etat2D*>(source));
            else throw EtatException("Etat non existant");
        }
    }

}
