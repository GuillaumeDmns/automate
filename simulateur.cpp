/*!
    * \file simulateur.cpp
    * \brief Définition des fonctions des objets Simulateur
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 2 juin 2018
    *
    * \details Fichier pour définir les fonctions relatives à Simulateur non inline
    *
    */

#include "simulateur.h"
#include <string.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "automate.h"


    /*!
     * \fn Simulateur::Simulateur(const string typeautomate, const unsigned int regles[], const string choixdepart, const unsigned int n, const unsigned int m=0)
     * \brief Constructeur de la classe Simulateur
     *
     * \param string typeautomate : choix du type d'automate
     * \param unsigned int regles[] : régles choisies pour l'automate
     * \param string choixdepart : choix de configuration pour l'état de départ
     * \param unsigned int n : dimension n de la grille
     * \param unsigned int m : dimension m de la grille
     */
Simulateur::Simulateur(std::string typeautomate, unsigned int regles[], std::string choixdepart, unsigned int n, unsigned int m) : numEtat(0) {
    FabriqueAutomate fabAutomate;
    FabriqueEtat fabEtat;
    automate=fabAutomate.createAutomate(typeautomate,regles);
    unsigned int i,j;
    if (m==0)
    {
        unsigned int* tab=new unsigned int[n];
        if (choixdepart.compare("aleatoire")==0){
            for (i=0;i<n;i++)
                tab[i]=rand()%2;
        }
        else {
            if (choixdepart.compare("symetrique")==0){
                for (i=0;i<(floor(n/2)+1);i++)
                    {
                        tab[i]=rand()%2;
                        tab[n-1-i]=tab[i];
                    }
            }
            else {
                if (choixdepart.compare("vide")==0){
                    for (i=0;i<n;i++)
                            tab[i]=0;
                }
                else
                    throw "erreur : choix de départ inconnu\n";
            }
        }
        depart = fabEtat.createEtat(n, tab);
        current = fabEtat.createEtat(n,tab);
    }
    else {
        unsigned int** tab=new unsigned int*[n];
        if (choixdepart.compare("aleatoire")==0){
            for (i=0;i<n;i++)
                tab[i] = new unsigned int[m];
                for (j=0;j<m;j++)
                    tab[i][j]=rand()%2;
        }
        else {
            if (choixdepart.compare("symetrique")==0){
                for (i=0;i<(floor(n/2)+1);i++)
                    for (j=0;j<m;j++)
                    {
                        tab[i][j]=rand()%2;
                        tab[n-1-i][j]=tab[i][j];
                    }
            }
            else {
                if (choixdepart.compare("vide")==0){
                    for (i=0;i<n;i++)
                        for (j=0;j<m;j++)
                            tab[i][j]=0;
                }
                else
                    throw "erreur : choix de départ inconnu\n";
            }
        }
        depart = fabEtat.createEtat(n,m,tab);
        current = fabEtat.createEtat(n,m,tab);
    }
}

    /*!
     * \fn void Simulateur::next()
     * \brief Permet le passage d'un état à son état suivant en fonction des régles de transition
     *
     * \return void
     */
void Simulateur::next(){
    FabriqueEtat fabEtat;
    FabriqueAutomate fabAutomate;
    Etat* suivant = fabEtat.createEtat(current);
    fabAutomate.appliquerTransition(*current,*suivant,*automate);
    *current=*suivant;
    fabEtat.deleteEtat(suivant);
}

    /*!
     * \fn Simulateur::~Simulateur()
     * \brief Destructeur de la classe Simulateur
     *
     */
Simulateur::~Simulateur() {
    FabriqueAutomate fabAutomate;
    FabriqueEtat fabEtat;
    fabAutomate.deleteAutomate(automate);
    fabEtat.deleteEtat(depart);
    fabEtat.deleteEtat(current);
}
