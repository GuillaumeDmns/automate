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
     * \param const string typeautomate : choix du type d'automate
     * \param const unsigned int regles[] : régles choisies pour l'automate
     * \param const string choixdepart : choix de configuration pour l'état de départ
     * \param const unsigned int n : dimension n de la grille
     * \param const unsigned int m : dimension m de la grille
     * \return
     */

Simulateur::Simulateur(const std::string typeautomate, const unsigned int regles[], const std::string choixdepart, const unsigned int n, const unsigned int m) : numEtat(0) {
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
        depart = new Etat1D(n,tab);
        current = new Etat1D(n, tab);
    }
    else {
        unsigned int** tab=new unsigned int*[n];
        if (choixdepart.compare("aleatoire")==0){
            for (i=0;i<n;i++)
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
        depart = new Etat2D(n,m,tab);
        current = new Etat2D(n,m,tab);
    }
}
