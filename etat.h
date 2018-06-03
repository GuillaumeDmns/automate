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
    ~Etat1D();
    
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
    operator=(const Etat1D& e);
    
private :
    unsigned int* valeur; /*!< Tableau des valeurs de la grille*/
};

class Etat2D : public Etat{
public :

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat2D
     *
     * \param unsigned int n : valeur initiale de la dimension n
     * \param unsigned int m : valeur initiale de la dimension m
     * \param unsigned int** t : tableau des valeurs de la grille
     */
    Etat2D(unsigned int n,unsigned int m,unsigned int** t);
    
    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Etat2D
     *
     * 
     */
    ~Etat2D();
    
    /*!
     * \brief Constructeur par recopie
     *
     * \details Constructeur par recopie de la classe Etat2D
     *
     * \param Etat2D& e : objet Etat2D à recopier
     * 
     */
    //Etat2D(const Etat2D& e);
    
    /*!
     * \brief Opérateur affectation
     *
     * \details Opérateur d'affectation de la classe Etat2D
     *
     * \param Etat2D& e : objet Etat2D à affecter
     * 
     */
    operator=(const Etat2D& e);
    
    /*!
     * \brief Recupération de la valeur d'une case de la grille
     *
     * \details Renvoie la valeur de la case (n,m)
     *
     * \param unsigned int n : abscisse de la case sur la grille
     * \param unsigned int m : ordonnée de la case sur la grille
     * \return valeur[n][m]
     */
    const unsigned int getValue(unsigned int n,unsigned int m) const {return valeur[n][m];}
    
    /*!
     * \brief Affectation d'une valeur
     *
     * \details Affecte une valeur à la case indiquée, dans la grille
     *
     * \param unsigned int n : abscisse de la case sur la grille
     * \param unsigned int m : ordonnée de la case sur la grille
     * \param unsigned int v : valeur à affecter à la case
     * \return 
     */
    void setValue(unsigned int n, unsigned int m, unsigned int v) const {valeur[n][m]=v;}
    
private :
    unsigned int** valeur; /*!< Tableau des valeurs de la grille*/
    unsigned int dimM; /*!< Deuxième dimension de la grille*/
};


#endif // ETAT_H