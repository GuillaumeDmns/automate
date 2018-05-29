DOCUMENTATION DOXYGEN

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

/*!
    * \fn Etat1D::Etat1D (unsigned int n,unsigned int* t=0)
    * \brief Constructeur de la classe Etat1D
    * 
    * \param unsigned int n : dimension de la grille
    * \param unsigned int* t : tableau des valeurs (par défaut =0)
    * \return 
    *
    */


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
};