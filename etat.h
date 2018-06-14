/*!
    * \file etat.h
    * \brief Déclaration des objets Etat
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
    * \brief Classe mère pour les états
    * 
    * \details La classe gère les données relatives à la grille d'un automate
    *
    */
class Etat {
protected :
    unsigned int dimN; /*!< Dimension 1 de la grille*/

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat
     *
     * \param unsigned int n : Valeur initiale de la dimension n
     *
     */
    Etat(unsigned int n): dimN(n){}
public :
    
    /*!
     * \brief Récupération de la dimension N
     *
     * \details Renvoie la dimension n de la grille
     *
     * \return dimN
     */
    unsigned int getdimN() const {return dimN;}

//FONCTION NON DOCUMENTEE
    virtual void fonctionVirtuelle() =0;
};


    /*!
    * \class Etat1D
    * \brief Classe pour les états en 1 dimension
    * 
    * \details La classe gère les données relatives à la grille d'un automate en 1 dimension
    *
    */
class Etat1D : public Etat{
    friend class FabriqueEtat;
    friend class Automate;
protected:

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat1D
     *
     * \param unsigned int n : Valeur initiale de la dimension n
     * \param unsigned int* t : Tableau des valeurs de la grille
     */
    Etat1D(unsigned int n,unsigned int* t);
    
    /*!
     * \brief Constructeur par recopie
     *
     * \details Constructeur par recopie de la classe Etat1D
     *
     * \param Etat1D& e : Ojet Etat1D à recopier
     * 
     */
    Etat1D(Etat1D& e) : Etat(e.getdimN()){
            for (unsigned int i=0;i<getdimN();i++)
                    valeur[i]=e.valeur[i];
    }
    
    /*!
     * \brief Opérateur d'affectation
     *
     * \details Opérateur d'affectation de la classe Etat1D
     *
     * \param Etat1D& e : Objet Etat1D à affecter à l'objet courant
     * 
     */
    Etat1D& operator=(const Etat1D& e);

    /*!
     * \brief Affectation d'une valeur
     *
     * \details Affecte une valeur à la case indiquée dans la grille
     *
     * \param unsigned int n : Indice de la case dans le tableau
     * \param unsigned int v : Valeur à affecter à la case
     */
    void setValue(unsigned int n, unsigned int v) {valeur[n]=v;}

public:
    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Etat1D
     *
     *
     */
    ~Etat1D();

    /*!
     * \brief Récupération de la valeur d'une case de la grille
     *
     * \details Renvoie la valeur de la case (n)
     *
     * \param unsigned int n : Indice de la case dans le tableau
     * \return valeur[n]
     */
    unsigned int getValue(unsigned int n) const {return valeur[n];}

//FONCTION NON DOCUMENTEE
    void fonctionVirtuelle(){};
private :
    unsigned int* valeur; /*!< Tableau des valeurs de la grille*/
};



/*!
    * \class Etat2D
    * \brief Classe pour les états en 2 dimensions
    * 
    * \details La classe gère les données relatives à la grille d'un automate en 2 dimensions
    *
    */
class Etat2D : public Etat{
    friend class FabriqueEtat;
    friend class Automate;
private :
    unsigned int dimM; /*!< Deuxième dimension de la grille*/
    unsigned int** valeur; /*!< Tableau des valeurs de la grille*/
protected:

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat2D
     *
     * \param unsigned int n : Valeur initiale de la dimension n
     * \param unsigned int m : Valeur initiale de la dimension m
     * \param unsigned int** t : Tableau des valeurs de la grille
     */
    Etat2D(unsigned int n,unsigned int m, unsigned int** t);
    
    /*!
     * \brief Constructeur par recopie
     *
     * \details Constructeur par recopie de la classe Etat2D
     *
     * \param Etat2D& e : Objet Etat2D à recopier
     * 
     */
    Etat2D(Etat2D& e):Etat(e.getdimN()), dimM(e.getdimM()), valeur(new unsigned int*[e.getdimM()]){
            for (unsigned int i=0;i<dimN;i++)
                for (unsigned int j=0;j<dimM;j++)
                    valeur[i][j]=e.valeur[i][j];
    }
    
    /*!
     * \brief Opérateur d'affectation
     *
     * \details Opérateur d'affectation de la classe Etat2D
     *
     * \param Etat2D& e : Objet Etat2D à affecter à l'objet courant
     * 
     */
    Etat2D& operator=(const Etat2D& e);

    /*!
     * \brief Affectation d'une valeur
     *
     * \details Affecte une valeur à la case indiquée dans la grille
     *
     * \param unsigned int n : Abscisse de la case sur la grille
     * \param unsigned int m : Ordonnée de la case sur la grille
     * \param unsigned int v : Valeur à affecter à la case
     * \return
     */
    void setValue(unsigned int n, unsigned int m, unsigned int v) {valeur[n][m]=v;}
public:
    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Etat2D
     *
     *
     */
    ~Etat2D();

    /*!
     * \brief Récupération de la valeur d'une case de la grille
     *
     * \details Renvoie la valeur de la case (n,m)
     *
     * \param unsigned int n : Abscisse de la case sur la grille
     * \param unsigned int m : Ordonnée de la case sur la grille
     * \return valeur[n][m]
     */
    unsigned int getValue(unsigned int n,unsigned int m) const {return valeur[n][m];}

    /*!
     * \brief Récupération de la dimension M
     *
     * \details Renvoie la dimension m de la grille
     *
     * \return dimM
     */
    unsigned int getdimM() const {return dimM;}

//FONCTION NON DOCUMENTEE
    void fonctionVirtuelle(){};
};

/*!
    * \class FabriqueEtat
    * \brief Classe correspondant à une Factory pour les Etats
    *
    * \details La classe permet l'instanciation de la bonne classe fille d'Etat
    *
    */
class FabriqueEtat {
    friend class Simulateur;
protected :
    /*!
     * \brief createEtat
     * \details Fabrique un état avec deux paramètres, en 1D
     *
     * \param unsigned int dimN : Taille pour la première dimension
     * \param unsigned int* t : Valeurs à placer dans la grille
     * \return Etat*
     */
    Etat* createEtat(unsigned int dimN, unsigned int* t) const;

    /*!
     * \brief createEtat
     * \details Fabrique un état avec trois paramètres, en 2D
     *
     * \param unsigned int dimN : Taille pour la première dimension
     * \param unsigned int dimM : Taille pour la deuxième dimension
     * \param unsigned int** t : Valeurs à placer dans la grille
     * \return Etat*
     */
    Etat* createEtat(unsigned int dimN, unsigned int dimM, unsigned int** t) const;


    /*!
     * \brief createEtat
     * \details Fabrique un état par recopie d'un état existant
     *
     * \param const Etat& e : Etat existant à dupliquer
     * \return Etat&
     */
    Etat* createEtat(Etat* e) const;

    /*!
     * \brief deleteEtat
     * \details Détruit un état fourni en paramètre
     *
     * \param Etat* e : Etat à supprimer
     * \return void
     */
    void deleteEtat(Etat* e) const;

    void setValue(unsigned int n, unsigned int m, unsigned int v, Etat* e);

    unsigned int getValue(unsigned int n, unsigned int m, Etat* e) const;
};


/*!
    * \class EtatException
    * \brief Classe d'Exception pour les Etats
    *
    * \details La classe permet de gérer les exceptions relatives aux classes Etats
    *
    */
class EtatException {
private :
    std::string info; /*!< Chaîne de caractères contenant les informations sur l'exception*/
public :
    /*!
     * \brief Constructeur
     * \details Constructeur de la classe EtatException
     *
     * \param string inf : Chaîne de caractères portant les informations sur l'exception
     */
    EtatException(std::string inf):info(inf) {};

    /*!
     * \brief Récupération de l'attribut info
     * \details Retourne la chaîne de caractères liée à l'exception déclenchée
     *
     * \return string
     */
    std::string getInfo() const {return info;};
};

#endif // ETAT_H
