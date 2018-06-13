/*!
    * \file automate.h
    * \brief Déclaration des objets Automate
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
    * \details La classe gère les données relatives à un automate
    *
    */
class Automate {
    friend class FabriqueAutomate;
protected :
    unsigned int** regle; /*!< Règles de transition*/

    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
    virtual unsigned int** remplissageRegle(unsigned int** tab, const unsigned int regle[]) const =0;

    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
    virtual unsigned int** remplissageRegle(unsigned int** tab, unsigned int** regle) const =0;

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Automate
     *
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     */
    Automate(unsigned int** regle);

public :
    /*!
     * \brief Accesseur des régles
     *
     * \details Permet la récupération des régles
     *
     * \return unsigned int** regle
     */
    unsigned int** getRegle() const {return regle;};

    /*!
     * \brief Accesseur du nombre d'Etats
     *
     * \details Permet la récupération de la valeur de l'attribut nbEtats
     *
     * \return unsigned int
     */
    virtual unsigned int getNbEtats() const =0;

    /*!
     * \brief Accesseur du nombre de dimensions
     *
     * \details Permet la récupération du nombre de dimensions de l'automate
     *
     * \param
     * \return unsigned int
     */
    virtual unsigned int getNbDim() const =0;

    /*!
     * \brief Calcul la taille du tableau de régles
     *
     * \details Permet la récupération de la taille que devra faire le tableau de régles
     *
     * \return unsigned int
     */
    virtual unsigned int getTailleRegle() const =0;

    /*!
     * \brief Transition d'état
     *
     * \details Calcule l'état suivant d'un état donné
     *
     * \param Etat1D& dep : Référence sur l'état en 1D de départ sur lequel appliquer la transition
     * \param Etat1D& dest : Référence vers l'état en 1D résultant de la transition
     *
     * \return void
     */
    void appliquerTransition(const Etat1D& dep, Etat1D& dest) const;

    /*!
     * \brief Transition d'état
     *
     * \details Calcule l'état suivant d'un état donné
     *
     * \param Etat2D& dep : Référence sur l'état en 2D de départ sur lequel appliquer la transition
     * \param Etat2D& dest : Référence vers l'état en 2D résultant de la transition
     *
     * \return void
     */
    void appliquerTransition(const Etat2D& dep, Etat2D& dest) const;

    /*!
     * \brief Création du tableau des règles
     *
     * \details Crée un tableau de règles vide aux bonnes dimensions
     *
     * \return unsigned int**
     */
    virtual unsigned int** createTabRegle() const =0;

    /*!
     * \brief Destructeur d'Automate
     *
     * \details Détruit un objet de type Automate
     *
     */
    virtual ~Automate();
};

#include "simulateur.h"

/*!
    * \class Cell1D
    * \brief Classe Automate Cellulaire 1D 2e
    *
    * \details La classe gère les données relatives à un automate cellulaire 1D à 2 états
    *
    */
class Cell1D : public Automate {
    friend class FabriqueAutomate;
private :
    static unsigned int nbDim; /*! Nombre de dimensions de l'automate */
    static unsigned int nbEtats; /*!< Nombre d'états acceptés par l'automate*/
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
    unsigned int** remplissageRegle(unsigned int** tab, const unsigned int regle[]) const;
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
    unsigned int** remplissageRegle(unsigned int** tab, unsigned int** regle) const;
protected :
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Cell1D
     *
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     */
    Cell1D(const unsigned int regle[]);
    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe Cell1D
     *
     * \param const Automate& a : Objet Automate à recopier
     */
    Cell1D(const Automate& a);
public :
    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Cell1D
     *
     */
    ~Cell1D();

    /*!
     * \brief Création du tableau de règles
     *
     * \details Crée un tableau de règles vide aux bonnes dimensions
     *
     * \return unsigned int**
     */
    unsigned int** createTabRegle() const;

    /*!
     * \brief Accesseur du nombre d'Etats
     *
     * \details Permet la récupération de la valeur de l'attribut nbEtats
     *
     * \return unsigned int
     */
    unsigned int getNbEtats() const;

    /*!
     * \brief Calcul la taille du tableau de régles
     *
     * \details Permet la récupération de la taille que devra faire le tableau de régles
     *
     * \return unsigned int
     */
    unsigned int getTailleRegle() const;

    /*!
     * \brief Accesseur du nombre de dimensions
     *
     * \details Permet la récupération du nombre de dimensions de l'automate
     *
     * \param
     * \return unsigned int
     */
    unsigned int getNbDim() const;
};


/*!
    * \class JeuDeLaVie
    * \brief Classe Jeu de la vie
    *
    * \details La classe gère les données relatives à un automate Jeu de la Vie
    *
    */
class JeuDeLaVie : public Automate {
    friend class FabriqueAutomate;
private :
    static unsigned int nbDim; /*! Nombre de dimensions de l'automate */
    static unsigned int nbEtats; /*! Nombre d'états acceptés par l'automate */
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
    unsigned int** remplissageRegle(unsigned int** tab, const unsigned int regle[]) const;
    /*!
     * \brief Remplissage des règles
     *
     * \details Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
    unsigned int** remplissageRegle(unsigned int** tab, unsigned int**) const;
protected :
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Jeu de la Vie
     *
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     */
    JeuDeLaVie(const unsigned int regle[]);
    /*!
     * \brief Constructeur
     *
     * \details Constructeur par recopie de la classe JeuDeLaVie
     *
     * \param const Automate& a : Objet Automate à recopier
     */
    JeuDeLaVie(const Automate& a);
public :
    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe JeuDeLaVie
     *
     */
    ~JeuDeLaVie();


    /*!
     * \brief Création du tableau de règles
     *
     * \details Crée un tableau de règles vide aux bonnes dimensions
     *
     * \return unsigned int**
     */
    unsigned int** createTabRegle() const;
    /*!
     * \brief Accesseur du nombre d'Etats
     *
     * \details Permet la récupération de la valeur de l'attribut nbEtats
     *
     * \return unsigned int
     */
    unsigned int getNbEtats() const;
    /*!
     * \brief Calcul la taille du tableau de régles
     *
     * \details Permet la récupération de la taille que devra faire le tableau de régles
     *
     * \return unsigned int
     */
    unsigned int getTailleRegle() const;
    /*!
     * \brief Accesseur du nombre de dimensions
     *
     * \details Permet la récupération du nombre de dimensions de l'automate
     *
     * \param
     * \return unsigned int
     */
    unsigned int getNbDim() const;
};

/*!
    * \class FabriqueAutomate
    * \brief Classe correspondant à une Factory pour les Automates
    *
    * \details La classe permet l'instanciation de la bonne classe fille d'automate
    *
    */
class FabriqueAutomate {
    friend class Simulateur;
protected :
    /*!
     * \brief Transition d'état
     *
     * \details Calcule l'état suivant d'un état donné
     *
     * \param Etat& dep : Référence sur l'état de départ sur lequel appliquer la transition
     * \param Etat& dest : Référence vers l'état résultant de la transition
     * \param Automate& a : Référence sur l'automate possédant les régles pour la transition
     * \return void
     */
    void appliquerTransition(Etat& dep, Etat& dest, Automate& a) const;
    /*!
     * \brief Création d'un Automate
     *
     * \details Permet l'instanciation de l'Automate souhaité
     *
     * \param string idAutomate : Chaîne de caractères correspondant au type d'automate souhaité
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles de transition
     *
     * \return Automate*
     */
    Automate* createAutomate(std::string idAutomate, const unsigned int regle[] =0) const;
    /*!
     * \brief Création d'un Automate
     *
     * \details Permet l'instanciation de l'Automate souhaité par recopie
     *
     * \param const Automate* a : Pointeur vers l'automate qu'on souhaite dupliquer
     *
     * \return Automate*
     */
    Automate* createAutomate(const Automate* a) const;
    /*!
     * \brief Destruction d'un automate
     *
     * \details Permet la destruction de l'automate en fonction de son type
     *
     * \param Automate* a : Pointeur vers l'Automate que l'on souhaite détruire
     * \return void
     */
    void deleteAutomate(Automate* a) const;
};


/*!
    * \class AutomateException
    * \brief Classe d'Exception pour les automates
    *
    * \details La classe permet de gérer les exceptions relatives aux classes Automates
    *
    */
class AutomateException {
private :
    std::string info; /*! Chaîne de caractères contenant les informations sur l'exception*/
public :
    /*!
     * \brief Constructeur
     * \details Constructeur de la classe AutomateException
     *
     * \param string inf : Chaîne de caractères portant les informations sur l'exception
     */
    AutomateException(std::string inf):info(inf) {};

    /*!
     * \brief Récupération de l'attribut info
     * \details Retourne la chaîne de caractères liée à l'exception déclenchée
     *
     * \return string
     */
    std::string getInfo() const {return info;};
};

#endif // AUTOMATE_H
