#include "simulateur.h"
#include <string.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "automate.h"

//OSCAR IL FAUT SIMULATEUR FRIEND AVEC AUTOMATEEEEE

/*
Simulateur::Simulateur(const string typeautomate, const unsigned int regles[], const string choixdepart, const unsigned int n, const unsigned int m=0) : numEtat(0) {
    automate=FabriqueAutomate::createAutomate(typeautomate,regles);
    unsigned int i,j;
    unsigned int* tab;
    if (m==0)
    {
        tab=new unsigned int[n];
        if (choixdepart.std::compare('aleatoire')==0){
            for (i=0;i<n;i++)
                tab[i]=rand()%2;
        }
        else {
            if (strcmp(choixdepart,'symetrique')==0){
                for (i=0;i<(floor(n/2)+1);i++)
                    {
                        tab[i]=rand()%2;
                        tab[n-1-i]=tab[i];
                    }
            }
            else {
                if (strcmp(choixdepart,'vide')==0){
                    for (i=0;i<n;i++)
                            tab[i]=0;
                }
                else
                    throw "erreur : choix de départ inconnu\n";
            }
        }
    }
    else {
        tab=new unsigned int[n][m];
        if (strcmp(choixdepart,'aleatoire')==0){
            for (i=0;i<n;i++)
                for (j=0;j<m;j++)
                    tab[i][j]=rand()%2;
        }
        else {
            if (strcmp(choixdepart,'symetrique')==0){
                for (i=0;i<(floor(n/2)+1);i++)
                    for (j=0;j<m;j++)
                    {
                        tab[i][j]=rand()%2;
                        tab[n-1-i][j]=tab[i][j];
                    }
            }
            else {
                if (strcmp(choixdepart,'vide')==0){
                    for (i=0;i<n;i++)
                        for (j=0;j<m;j++)
                            tab[i][j]=0;
                }
                else
                    throw "erreur : choix de départ inconnu\n"
            }
        }
    }
    if (m==0){
        depart=Etat1D(n,tab);
        current=Etat1D(depart);
    }
    else {
        depart=Etat2D(n,m,tab);
        current=Etat2D(depart);
    }
}
*/
