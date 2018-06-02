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
    void appliquerTransition(const Etat& dep, Etat& dest) const;

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Automate
     *
     * \param const Automate& a
     * \return
     */
    virtual Automate(const Automate& a) =0;

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Automate
     *
     * \param
     * \return
     */
    virtual ~Automate() =0;
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
     * \return
     */
    Automate(const unsigned int dim);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Automate1D
     *
     * \param const Automate& a
     * \return
     */
    Automate(const Automate& a);

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Automate1D
     *
     * \param
     * \return
     */
    ~Automate();
};

/*!
    * \class Automate2D
    * \brief Classe mère pour les automates 2D
    *
    * \details La classe gére les données relatives aux à un automate 2D
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
     * \return
     */
    Automate(const unsigned int dimM, const unsigned int dimN);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Automate2D
     *
     * \param const Automate& a
     * \return
     */
    Automate(const Automate& a);

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Automate1D
     *
     * \param
     * \return
     */
    ~Automate();
};

#endif // AUTOMATE_H
