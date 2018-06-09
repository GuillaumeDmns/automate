#include "simulateur.h"
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "automate.h"

/*
Simulateur::Simulateur(const string typeautomate, const string regles=0, const string choixdepart, const unsigned int n, const unsigned int m=0) : numEtat(0) {
    //automate=FabriqueAutomate::createAutomate(typeautomate,regles);
    unsigned int i,j;
    if (m==0)
    {
        tab=new unsigned int[n];
        if (strcmp(choixdepart,'aleatoire')==0){
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
                    throw "erreur : choix de départ inconnu\n"
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
}
*/
