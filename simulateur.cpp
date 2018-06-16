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
#include <iostream>
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
Simulateur::Simulateur(std::string typeautomate, unsigned int regles[], std::string choixdepart, unsigned int n, unsigned int m, unsigned int age) : numEtat(age) {
    FabriqueAutomate fabAutomate;
    FabriqueEtat fabEtat;
    automate=fabAutomate.createAutomate(typeautomate,regles);
    unsigned int i,j;
    if (m==1)
    {
        unsigned int* tab=new unsigned int[n];
        if (choixdepart.compare("Remplissage aléatoire")==0){
            for (i=0;i<n;i++)
                tab[i]=rand()%2;
        }
        else {
            if (choixdepart.compare("Remplissage symétrique")==0){
                for (i=0;i<(floor(n/2)+1);i++)
                    {
                        tab[i]=rand()%2;
                        tab[n-1-i]=tab[i];
                    }
            }
            else {
                if (choixdepart.compare("Grille vide")==0){
                    for (i=0;i<n;i++)
                            tab[i]=0;
                }
                else
                    throw "erreur : choix de départ inconnu\n";
            }
        }
        depart = fabEtat.createEtat(n, tab);
        current = fabEtat.createEtat(n, tab);
        delete tab;
    }
    else {
        unsigned int** tab=new unsigned int*[n];
        if (choixdepart.compare("Remplissage aléatoire")==0){
            for (i=0;i<n;++i) {
                tab[i] = new unsigned int[m];
                for (j=0;j<m;++j) {
                    tab[i][j]=rand()%2;
                }
            }
        }
        else {
            if (choixdepart.compare("Remplissage symétrique")==0){
                for (i=0;i<n;++i) {
                    tab[i] = new unsigned int[m];
                }
                for (i=0;i<(n/2)+1;++i) {
                    for (j=0;j<m;++j)
                    {
                        tab[i][j]=rand()%2;
                        tab[n-1-i][j]=tab[i][j];
                    }
                }
            }
            else {
                if (choixdepart.compare("Grille vide")==0){
                    for (i=0;i<n;++i) {
                        tab[i] = new unsigned int[m];
                        for (j=0;j<m;++j) {
                            tab[i][j]=0;
                        }
                    }

                }
                else
                    throw "erreur : choix de départ inconnu\n";
            }
        }
        if (typeautomate.compare("Feu de forêt") == 0) {

            tab[rand()%n][rand()%m] = 2;
        }
        depart = fabEtat.createEtat(n,m,const_cast<const unsigned int**>(tab));
        current = fabEtat.createEtat(n,m,const_cast<const unsigned int**>(tab));
        for(unsigned int i=0; i<n; ++i) delete tab[i];
        delete tab;
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
    fabEtat.copyEtat(suivant,current);
    fabEtat.deleteEtat(suivant);
    numEtat++;
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

    /*!
     * \fn void Simulateur::setValueCurrent(unsigned int n, unsigned int m, unsigned int v
     * \brief Donne une valeur de l'état courant
     *
     * \param unsigned int n : Abscisse de la case dont on veut la valeur
     * \param unsigned int m : Ordonnée de la case dont on veut la valeur
     * \param unsigned int v : Valeur à attribuer à la case
     * \return void
     */
void Simulateur::setValueDepart(unsigned int n, unsigned int m, unsigned int v){
    FabriqueEtat fabEtat;
    fabEtat.setValue(n,m,v,depart);
    reset();
}

    /*!
     * \fn unsigned int Simulateur::getValueCurrent(unsigned int n, unsigned int m) const
     * \brief Récupère une valeur de l'état courant
     *
     * \param unsigned int n : Abscisse de la case dont on veut la valeur
     * \param unsigned int m : Ordonnée de la case dont on veut la valeur
     * \return unsigned int
     */
unsigned int Simulateur::getValueCurrent(unsigned int n, unsigned int m) const {
    FabriqueEtat fabEtat;
    return fabEtat.getValue(n,m,getCurrent());
}

void Simulateur::save(string filename) const {
    ofstream file;
    file.open(filename);
    file << numEtat <<endl;
    file << typeid(*automate).name()<<endl;
    file << automate->getNbEtats() <<";"<<automate->getTailleRegle()<<endl;
    for(unsigned int i=0; i<automate->getNbEtats(); ++i){
        for(unsigned int j=0; j<=automate->getTailleRegle(); ++j){
            file << automate->getRegle()[i][j] <<";";
        }
        file << endl;
    }
    file << typeid(*depart).name()<<endl;
    if(!strcmp(typeid(*depart).name(),"6Etat1D")){
        file<<depart->getdimN()<<";"<<0<<endl;
        for(unsigned int i=0; i<depart->getdimN(); ++i){
            file << dynamic_cast<Etat1D*>(depart)->getValue(i) <<";";
        }
        file<<endl<<endl;
        for(unsigned int i=0; i<current->getdimN(); ++i){
            file << dynamic_cast<Etat1D*>(current)->getValue(i) <<";";
        }
    }else{
        file<<depart->getdimN()<<";"<<dynamic_cast<Etat2D*>(depart)->getdimM()<<endl;
        for(unsigned int i=0; i<depart->getdimN(); ++i){
            for(unsigned int j=0; j<dynamic_cast<Etat2D*>(depart)->getdimM(); ++j){
                file << dynamic_cast<Etat2D*>(depart)->getValue(i,j) <<";";
            }
            file<<endl;
        }
        file<<endl;
        for(unsigned int i=0; i<depart->getdimN(); ++i){
            for(unsigned int j=0; j<dynamic_cast<Etat2D*>(current)->getdimM(); ++j){
                file << dynamic_cast<Etat2D*>(current)->getValue(i,j) <<";";
            }
            file<<endl;
        }
    }
    file<<endl;
    file.close();
}

Simulateur::Simulateur(std::string typeautomate, const unsigned int** regles, unsigned int n, unsigned int age, const unsigned int* dep, const unsigned int* cur) : numEtat(age) {
    FabriqueAutomate fabAutomate;
    FabriqueEtat fabEtat;
    automate=fabAutomate.createAutomate(typeautomate,regles);
    depart = fabEtat.createEtat(n, dep);
    current = fabEtat.createEtat(n, cur);
}

Simulateur::Simulateur(std::string typeautomate, const unsigned int** regles, unsigned int n, unsigned int m, unsigned int age, const unsigned int** dep, const unsigned int** cur) : numEtat(age) {
    FabriqueAutomate fabAutomate;
    FabriqueEtat fabEtat;
    automate=fabAutomate.createAutomate(typeautomate,regles);
    depart = fabEtat.createEtat(n, m, dep);
    current = fabEtat.createEtat(n, m, cur);
}
