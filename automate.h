/*!
    * \file automate.h
    * \brief Déclaration de l'objet Automate
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 02 juin 2018
    *
    * \details Fichier pour créer les classes et fonctions relatives à Automate
    *
    */


#ifndef AUTOMATE_H
#define AUTOMATE_H
#include <iostream>
#include <string>
#include "etat.h"
using namespace std;


/*!
    * \class Automate
    * \brief Classe mère pour les automates
    *
    * \details La classe gére les données relatives aux à un automate
    *
    */
class Automate {
private :
        unsigned int** regle; /*!< Règles de transition*/
        unsigned int nbEtats; /*!< Nombre d'états de l'automate*/
public :

    /*!
     * \brief Transition d'état
     *
     * \details Calcule l'état suivant d'un état donné
     *
     * \param const Etat& dep
     * \param Etat& dest
     * \return void
     */
    virtual void appliquerTransition(const Etat& dep, Etat& dest) const =0;
};

/*!
    * \class Automate1D
    * \brief Classe mère pour les automates 1D
    *
    * \details La classe gére les données relatives à un automate 1D
    *
    */
class Automate1D : public Automate {
private :
        unsigned int dim; /*!< Dimension de l'automate*/
public :
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Automate1D
     *
     * \param const unsigned int dim
     * \param const unsigned int nb
     * \return
     */
    Automate1D(const unsigned int dim, const unsigned int nb);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Automate1D
     *
     * \param const Automate& a
     * \return
     */
    Automate1D(const Automate& a);

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Automate1D
     *
     * \param
     * \return
     */
    ~Automate1D();

    /*!
     * \brief Transition d'état
     *
     * \details Calcule l'état suivant d'un état donné
     *
     * \param const Etat& dep
     * \param Etat& dest
     * \return void
     */
    void appliquerTransition(const Etat& dep, Etat& dest) const;
};

/*!
    * \class Automate2D
    * \brief Classe mère pour les automates 2D
    *
    * \details La classe gére les données relatives à un automate 2D
    *
    */
class Automate2D : public Automate {
private :
        unsigned int dimM; /*!< Dimension de l'automate largeur*/
        unsigned int dimN; /*!< Dimension de l'automate hauteur*/
public :

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Automate2D
     *
     * \param const unsigned int dimM
     * \param const unsigned int dimN
     * \param const unsigned int nb
     * \return
     */
    Automate2D(const unsigned int dimM, const unsigned int dimN, const unsigned int nb);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Automate2D
     *
     * \param const Automate& a
     * \return
     */
    Automate2D(const Automate& a);

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Automate1D
     *
     * \param
     * \return
     */
    ~Automate2D();

    /*!
     * \brief Transition d'état
     *
     * \details Calcule l'état suivant d'un état donné
     *
     * \param const Etat& dep
     * \param Etat& dest
     * \return void
     */
    void appliquerTransition(const Etat& dep, Etat& dest) const;
};

/*!
    * \class Cell1D
    * \brief Classe Automate Cellulaire 1D 2e
    *
    * \details La classe gére les données relatives à un automate cellulaire 1D à 2 états
    *
    */
class Cell1D : public Automate1D {
public :

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Cell1D
     *
     * \param const unsigned int dim
     * \return
     */
    Cell1D(const unsigned int dim):Automate1D(dim,2);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Cell1D
     *
     * \param const Automate& a
     * \return
     */
    Cell1D(const Automate& a):Automate(a);

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Cell1D
     *
     * \param
     * \return
     */
    ~Cell1D();
};

/*!
    * \class JeuDeLaVie
    * \brief Classe Jeu de la vie
    *
    * \details La classe gére les données relatives à un automate du jeu de la vie
    *
    */
class JeuDeLaVie : Automate2D {
public :
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe JeuDeLaVie
     *
     * \param const unsigned int dimM
     * \param const unsigned int dimN
     * \return
     */
    JeuDeLaVie(const unsigned int dimM, const unsigned int dimN):Automate2D(dimM,dimN,2);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe JeuDeLaVie
     *
     * \param const Automate& a
     * \return
     */
    JeuDeLaVie(const Automate& a):Automate2D(a);

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe JeuDeLaVie
     *
     * \param
     * \return
     */
    ~JeuDeLaVie();
};

#endif // AUTOMATE_H
