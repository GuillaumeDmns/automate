/*!
    * \file etat.h
    * \brief Déclaration de l'objet Etat
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    *
    * Fichier pour créer les classes et fonctions relatives à Etat
    *
    */


#ifndef ETAT_H
#define ETAT_H
#include <iostream>
#include <string>
using namespace std;


/*!
    * \class Etat
    * \brief classe mère pour les états
    * 
    * La classe gére les données relatives à la grille d'un automate
    *
    */
class Etat {
private :
        unsigned int dimN; /*!< Dimension 1 de la grille*/
public :
    
    /*!
     * \brief Recupération de la dimension
     *
     * Renvoie la dimension n de la grille
     */
    const unsigned int getdimN() const {return dimN;}
    
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Etat
     *
     * \param n : valeur initiale de la dimension n
     *
     */
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