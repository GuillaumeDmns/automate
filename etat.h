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
    * \details La classe gère les données relatives à la grille d'un automate
    *
    */
class Etat {
protected :
        unsigned int dimN; /*!< Dimension 1 de la grille*/
public :
    
    /*!
     * \brief Recupération de la dimension N
     *
     * \details Renvoie la dimension n de la grille
     *
     * \param 
     * \return dimN
     */
    unsigned int getdimN() const {return dimN;}
    
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Etat
     *
     * \param unsigned int n : valeur initiale de la dimension n
     *
     */
    Etat(unsigned int n): dimN(n){}
    virtual void fonctionVirtuelle() =0;
};


/*!
    * \class Etat1D
    * \brief classe pour les états en 1 dimension
    * 
    * \details La classe gère les données relatives à la grille d'un automate en 1 dimension
    *
    */
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
    Etat1D(Etat1D& e) : Etat(e.getdimN()){
            for (unsigned int i=0;i<getdimN();i++)
                    valeur[i]=e.valeur[i];
    }
    
    /*!
     * \brief Opérateur affectation
     *
     * \details Opérateur d'affectation de la classe Etat1D
     *
     * \param Etat1D& e : objet Etat1D à affecter
     * 
     */
    Etat1D& operator=(const Etat1D& e);

    /*!
     * \brief Recupération de la valeur d'une case de la grille
     *
     * \details Renvoie la valeur de la case (n)
     *
     * \param unsigned int n : indice de la case dans le tableau
     * \return valeur[n]
     */
    unsigned int getValue(unsigned int n) const {return valeur[n];}

    /*!
     * \brief Affectation d'une valeur
     *
     * \details Affecte une valeur à la case indiquée, dans la grille
     *
     * \param unsigned int n : indice de la case dans le tableau
     * \param unsigned int v : valeur à affecter à la case
     * \return
     */
    void setValue(unsigned int n, unsigned int v) const {valeur[n]=v;}
    void fonctionVirtuelle(){};
private :
    unsigned int* valeur; /*!< Tableau des valeurs de la grille*/
};



/*!
    * \class Etat2D
    * \brief classe pour les états en 2 dimensions
    * 
    * \details La classe gère les données relatives à la grille d'un automate en 2 dimensions
    *
    */
class Etat2D : public Etat{
private :
    unsigned int** valeur; /*!< Tableau des valeurs de la grille*/
    unsigned int dimM; /*!< Deuxième dimension de la grille*/
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
    Etat2D(unsigned int n,unsigned int m, unsigned int** t);
    
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
    Etat2D(Etat2D& e):Etat(e.getdimN()), dimM(e.getdimM()), valeur(new unsigned int*[e.getdimM()]){
            for (unsigned int i=0;i<dimN;i++)
                for (unsigned int j=0;j<dimM;j++)
                    valeur[i][j]=e.valeur[i][j];
    }
    
    /*!
     * \brief Opérateur affectation
     *
     * \details Opérateur d'affectation de la classe Etat2D
     *
     * \param Etat2D& e : objet Etat2D à affecter
     * 
     */
    Etat2D& operator=(const Etat2D& e);
    
    /*!
     * \brief Recupération de la valeur d'une case de la grille
     *
     * \details Renvoie la valeur de la case (n,m)
     *
     * \param unsigned int n : abscisse de la case sur la grille
     * \param unsigned int m : ordonnée de la case sur la grille
     * \return valeur[n][m]
     */
    unsigned int getValue(unsigned int n,unsigned int m) const {return valeur[n][m];}
    
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

    /*!
     * \brief Recupération de la dimension M
     *
     * \details Renvoie la dimension m de la grille
     *
     * \param
     * \return dimM
     */
    unsigned int getdimM() const {return dimM;}
    void fonctionVirtuelle(){};
};

/*!
    * \class FabriqueEtat
    * \brief Classe Fabrique pour les Etats
    *
    * \details La classe permet l'instanciation de la bonne classe fille d'Etat
    *
    */
class FabriqueEtat {
    friend class Simulateur;
protected :
    /*!
     * \brief createEtat
     *
     * \param const unsigned int dimN
     * \param const unsigned int dimN
     * \return Etat&
     */
    Etat* createEtat(unsigned int dimN, unsigned int* t) const;
    /*!
     * \brief createEtat
     *
     * \param const unsigned int dimN
     * \param const unsigned int dimN
     * \return Etat&
     */
    Etat* createEtat(unsigned int dimN, unsigned int dimM, unsigned int** t) const;
    /*!
     * \brief createEtat
     * \param const Etat& e
     * \return Etat&
     */
    Etat* createEtat(Etat* e) const;
    /*!
     * \brief deleteEtat
     * \param Etat* a
     * \return void
     */
    //void deleteEtat(Etat* e) const;

};

class EtatException {
private :
    std::string info; /*! Information sur l'exception*/
public :
    /*!
     * \brief EtatException
     * \param const string inf
     * \return
     */
    EtatException(std::string inf):info(inf) {};
    /*!
     * \brief getInfo
     * \return string
     */
    std::string getInfo() const {return info;};
};

#endif // ETAT_H
