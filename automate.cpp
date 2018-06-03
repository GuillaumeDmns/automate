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
#include "automate.h"

using namespace std;

Automate1D* FabriqueAutomate::createAutomate(const std::string idAutomate, const unsigned int dim) const {
    if(idAutomate=="Cell1D") return new Cell1D(dim);
    throw AutomateException("Automate 1D "+idAutomate+" Inexistant");
}

Automate2D* FabriqueAutomate::createAutomate(const std::string idAutomate, const unsigned int dimM, const unsigned int dimN) const {
    if(idAutomate=="JeuDeLaVie") return new JeuDeLaVie(dimM,dimN);
    throw AutomateException("Automate 2D "+idAutomate+" Inexistant");
}

//NON FONCTIONNELLE MANQUE COMMENT RECUPERER QUELLE CLASSE FILLE EST a
Automate* FabriqueAutomate::createAutomate(const Automate &a) const {
    return new Automate1D(a);
}
/*
//FONCTIONS SUIVANTES NON FONCTIONNELLES
Automate1D::Automate1D(const unsigned int dim, const unsigned int nb):nbEtats(nb),dim(dim) {

}

Automate1D::Automate1D(const Automate& a) {

}

Automate1D::~Automate1D() {

}

void Automate1D::appliquerTransition(const Etat& dep, Etat& dest) const {

}

Automate2D::Automate2D(const unsigned int dimM, const unsigned int dimN, const unsigned int nb):nbEtats(nb),dimM(dimM),dimN(dimN) {

}

Automate2D::Automate2D(const Automate& a) {

}

Automate2D::~Automate2D() {

}

void Automate2D::appliquerTransition(const Etat& dep, Etat& dest) const {

}

Cell1D::Cell1D(const unsigned int dim):Automate1D(dim,2) {

}

Cell1D::Cell1D(const Automate& a) {

}

JeuDeLaVie::JeuDeLaVie(const unsigned int dimM, const unsigned int dimN):Automate2D(dimM,dimN,2){

}

JeuDeLaVie::JeuDeLaVie(const Automate& a) {

}
*/
