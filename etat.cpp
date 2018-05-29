/*!
    * \file etat.cpp
    * \brief Définition des fonctions de l'objet Etat
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Fichier pour définir les fonctions relatives à Etat non inline
    *
    */


#include <stdio.h>
#include <iostream>
#include "etat.h"

using namespace std;

/*!
    * \fn Etat1D::Etat1D (unsigned int n,unsigned int* t=0)
    * \brief Constructeur de la classe Etat1D
    * 
    * \param unsigned int n : dimension de la grille
    * \param unsigned int* t : tableau des valeurs (par défaut =0)
    * \return 
    *
    */
Etat1D::Etat1D (unsigned int n,unsigned int* t=0): Etat(n), valeur(new unsigned int[n]){
    if(t)
    {
        for (unsigned int i=0;i<n;i++)
            valeur[i]=t[i];
    }
    else {
        for (unsigned int i=0;i<n;i++)
            valeur[i]=0;
    }
}

/*!
    * \fn Etat2D::Etat2D (unsigned int n,unsigned int m,unsigned int** t=0)
    * \brief Constructeur de la classe Etat2D
    * 
    * \param unsigned int n : dimension N de la grille
    * \param unsigned int m : dimension M de la grille
    * \param unsigned int** t : tableau des valeurs (par défaut =0)
    * \return 
    *
    */
Etat2D::Etat2D(unsigned int n,unsigned int m,unsigned int** t=0):Etat(n),dimM(m),valeur(new unsigned int*[n]){
    if (t){
        for (unsigned int i=0;i<(n);i++)
            {
            valeur[i]=new unsigned int [m];
            for (unsigned int j=0;j<m;j++)
                valeur[i][j]=0;
            }
    }
    else {
        for (unsigned int i=0;i<(n);i++)
            {
            valeur[i]=new unsigned int [m];
            for (unsigned int j=0;j<m;j++)
                valeur[i][j]=t[i][j];
            }
    }
}

/*!
    * \fn Etat2D::~Etat2D()
    * \brief Destructeur de la classe Etat2D
    * 
    * 
    * \return 
    *
    */
Etat2D::~Etat2D(){
    for (unsigned int i=0;i<this->getdimN();i++)
        {
            delete valeur[i];
        }
    delete[] valeur;
}
