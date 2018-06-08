/*!
    * \file automate.cpp
    * \brief Définition des fonctions de l'objet Automate
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 02 juin 2018
    *
    * \details Fichier pour définir les fonctions relatives à Automate non inline
    *
    */


#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include "automate.h"

using namespace std;

unsigned int Cell1D::nbDim=1;
unsigned int JeuDeLaVie::nbDim=2;

void Automate::appliquerTransition(const Etat& dep, Etat& dest) const {

}

Automate::Automate(const unsigned int nb, unsigned int** tab) :nbEtats(nb), regle(tab) {

}
//NOT
unsigned int** Cell1D::remplissageRegle(unsigned int** tab, const std::string regle) const{

}
//NOT
unsigned int** Cell1D::remplissageRegle(unsigned int** tab, unsigned int** regle) const{

}

Cell1D::Cell1D(const std::string regle) :Automate(2,remplissageRegle(createTabRegle(),regle)){

}

Cell1D::Cell1D(const Automate& a) :Automate(2, remplissageRegle(createTabRegle(), a.getRegle())) {

}

unsigned int** Cell1D::createTabRegle() const {
    unsigned int** tab = new unsigned int* [2];
    for(int i=0; i<2; ++i){
        tab[i] = new unsigned int [20+1];
    }
    return tab;
}
//NOT
unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, const std::string regle) const{

}
//NOT
unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, unsigned int** regle) const{

}

JeuDeLaVie::JeuDeLaVie(const std::string regle) :Automate(2,remplissageRegle(createTabRegle(),regle)) {

}

JeuDeLaVie::JeuDeLaVie(const Automate& a) :Automate(2, remplissageRegle(createTabRegle(), a.getRegle())) {

}

unsigned int** JeuDeLaVie::createTabRegle() const {
    unsigned int** tab = new unsigned int* [2];
    for(int i=0; i<2; ++i){
        tab[i] = new unsigned int [800+1];
    }
    return tab;
}
/*
Automate* FabriqueAutomate::createAutomate(const std::string idAutomate, const std::string regle) const {
    if(idAutomate== "Cell1D") return new Cell1D(regle);
    if(idAutomate== "JeuDeLaVie") return new JeuDeLaVie(regle);
    throw AutomateException("Automate Inexistant");
}

Automate* FabriqueAutomate::createAutomate(const Automate& a) const {
    if(typeid(a).name()=="Cell1D") return new Cell1D(a);
    if(typeid(a).name()=="JeuDeLaVie") return new JeuDeLaVie(a);
    throw AutomateException("Automate Inexistant");
}
*/
