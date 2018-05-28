/*!
    * \file etat.h
    * \brief Déclaration de l'objet Etat
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Fichier pour créer les classes et fonctions relatives à Etat
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
    * \details La classe gére les données relatives à la grille d'un automate
    *
    */
class Etat {
private :
        unsigned int dimN; /*!< Dimension 1 de la grille*/
public :
    
    /*!
     * \brief Recupération de la dimension
     *
     * \details Renvoie la dimension n de la grille
     *
     * \param 
     * \return dimN
     */
    const unsigned int getdimN() const {return dimN;}
    
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat
     *
     * \param unsigned int n : valeur initiale de la dimension n
     *
     */
    Etat(const unsigned int n): dimN(n){}
};

class Etat1D : public Etat{
public :

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat1D
     *
     * \param unsigned int n : valeur initiale de la dimension n
     * \param unsigned int* t : tableau des valeurs de la grille
     */
    Etat1D(unsigned int n,unsigned int* t);
    
    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Etat1D
     *
     * 
     */
    //~Etat1D();
    
    /*!
     * \brief Constructeur par recopie
     *
     * \details Constructeur par recopie de la classe Etat1D
     *
     * \param Etat1D& e : objet Etat1D à recopier
     * 
     */
    //Etat1D(const Etat1D& e);
    
    /*!
     * \brief Opérateur affectation
     *
     * \details Opérateur d'affectation de la classe Etat1D
     *
     * \param Etat1D& e : objet Etat1D à affecter
     * 
     */
    //Etat1D operator=(const Etat1D& e);
    
private :
    unsigned int* valeur; /*!< Tableau des valeurs de la grille*/
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