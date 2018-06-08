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
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param
     * \return
     */
    virtual unsigned int** remplissageRegle(unsigned int** tab, const std::string regle) const =0;
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param
     * \return
     */
    virtual unsigned int** remplissageRegle(unsigned int** tab, unsigned int** regle) =0;
public :
    /*!
     * \brief Accesseur regle
     *
     * \details Retourne l'attribut regle
     *
     * \param
     * \return unsigned int**
     */
    unsigned int** getRegle() const {return regle;};
    /*!
     * \brief Accesseur nbEtats
     *
     * \details Retourne l'attribut nbEtats
     *
     * \param
     * \return unsigned int
     */
    unsigned int getNbEtats() const {return nbEtats;};
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
     * \brief creation tableau de règles
     *
     * \details Crée un tableau de règles vide aux bonnes dimensions
     *
     * \param
     * \return unsigned int**
     */
    virtual unsigned int** createTabRegle() const =0;
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Automate
     *
     * \param const unsigned int nb
     * \return
     */
    Automate(const unsigned int nb, unsigned int** regle);
};

/*!
    * \class Cell1D
    * \brief Classe Automate Cellulaire 1D 2e
    *
    * \details La classe gére les données relatives à un automate cellulaire 1D à 2 états
    *
    */
class Cell1D : public Automate {
private :
    static unsigned int nbDim; /*! nombre de dimensions de l'automate */
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param
     * \return
     */
    unsigned int** remplissageRegle(unsigned int** tab, const std::string regle) const;
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param
     * \return
     */
    unsigned int** remplissageRegle(unsigned int** tab, unsigned int** regle) const;
public :
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Cell1D
     *
     * \param
     * \return
     */
    Cell1D(const std::string regle);
    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Cell1D
     *
     * \param const Automate& a
     * \return
     */
    Cell1D(const Automate& a);
    /*!
     * \brief creation tableau de règles
     *
     * \details Crée un tableau de règles vide aux bonnes dimensions
     *
     * \param
     * \return unsigned int**
     */
    unsigned int** createTabRegle() const;
};

/*!
    * \class JeuDeLaVie
    * \brief Classe Jeu de la vie
    *
    * \details La classe gère les données relatives à un automate Jeu de la vie
    *
    */
class JeuDeLaVie : public Automate {
private :
    static unsigned int nbDim; /*! nombre de dimensions de l'automate */
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param
     * \return
     */
    unsigned int** remplissageRegle(unsigned int** tab, std::string regle) const;
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param
     * \return
     */
    unsigned int** remplissageRegle(unsigned int** tab, unsigned int**) const;
public :
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Cell1D
     *
     * \param
     * \return
     */
    JeuDeLaVie(const std::string regle);
    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Cell1D
     *
     * \param const Automate& a
     * \return
     */
    JeuDeLaVie(const Automate& a);
    /*!
     * \brief creation tableau de règles
     *
     * \details Crée un tableau de règles vide aux bonnes dimensions
     *
     * \param
     * \return unsigned int**
     */
    unsigned int** createTabRegle() const;
};

/*!
    * \class FabriqueAutomate
    * \brief Classe Fabrique pour les Automates
    *
    * \details La classe permet l'instanciation de la bonne classe fille d'automate
    *
    */
class FabriqueAutomate {
public :
    /*!
     * \brief createAutomate
     * \param const string idAutomate
     * \param const unsigned int dim
     * \return Automate1D&
     */
    inline Automate* createAutomate(const std::string idAutomate, const std::string regle) const;
    /*!
     * \brief createAutomate
     * \param const Automate& a
     * \return Automate&
     */
    inline Automate* createAutomate(const Automate& a) const;
};

/*!
    * \class AutomateException
    * \brief Classe d'exception pour les automates
    *
    * \details La classe est retournée en cas d'exception concernant un automate
    *
    */
class AutomateException {
private :
    std::string info; /*! Information sur l'exception*/
public :
    /*!
     * \brief AutomateException
     * \param const string inf
     * \return
     */
    AutomateException(const std::string inf):info(inf) {};
    /*!
     * \brief getInfo
     * \return string
     */
    std::string getInfo() const {return info;};
};

#endif // AUTOMATE_H
