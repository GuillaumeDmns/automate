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
#include "string.h"
#include "automate.h"

using namespace std;

unsigned int Cell1D::nbDim=1;
unsigned int JeuDeLaVie::nbDim=2;
unsigned int Cell1D::nbEtats=2;
unsigned int JeuDeLaVie::nbEtats=2;


void Automate::appliquerTransition(const Etat1D& dep, Etat1D& dest) const {
    if(getNbDim()!=1) throw AutomateException("Nombre de dimensions incorrect");
    if((dep.getdimN()!=dest.getdimN())) throw AutomateException("Etat dep et dest incompatibles");
    unsigned int v=0;
    unsigned int voisinage=0;
    for(unsigned int i=0; i<dep.getdimN(); ++i){
        voisinage=0;
        voisinage+=10^dep.getValue((i-1)%dep.getdimN());
        voisinage+=10^dep.getValue((i+1)%dep.getdimN());
        if(voisinage>getTailleRegle()) throw AutomateException("Etat avec trop d'etats pour l'Automate");
        v=regle[dep.getValue(i)][voisinage];
        dest.setValue(i,v);
    }
}

void Automate::appliquerTransition(const Etat2D& dep, Etat2D& dest) const {
    if(getNbDim()!=2) throw AutomateException("Nombre de dimensions incorrect");
    if((dep.getdimM()!=dest.getdimM())||(dep.getdimN()!=dest.getdimN())) throw AutomateException("Etat dep et dest incompatibles");
    unsigned int v=0;
    unsigned int voisinage=0;
    for(unsigned int i=0; i<dep.getdimN(); ++i){
        for(unsigned int j=0; j<dep.getdimM(); ++j){
            voisinage=0;
            for(int k=i-1; k<=static_cast<int>(i+1); ++k){
                for(int l=j-1; l<=static_cast<int>(j+1); ++l){
                    voisinage+=10^dep.getValue(k%dep.getdimN(),l%dep.getdimM());
                }
            }
            voisinage-=dep.getValue(i,j);
            if(voisinage>getTailleRegle()) throw AutomateException("Etat avec trop d'etats pour l'Automate");
            v=regle[dep.getValue(i,j)][voisinage];
            dest.setValue(i,j,v);
        }
    }
}

Automate::Automate(unsigned int** tab) :regle(tab) {

}

unsigned int** Cell1D::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const{
    if(regle[0]||regle[3]!=1||regle[1]>2||regle[2]>2||regle[4]>2||regle[5]>2) throw AutomateException("Regle incorrecte");
    if(regle[1]>regle[2]||regle[4]>regle[5]) throw AutomateException("Regle incorrecte");
    for(unsigned int i=0; i<getTailleRegle();++i){
        tab[0][i]=0;
        tab[1][i]=0;
        if((i/10+i%10)==2) {
            if((i/10>=regle[1])&&(i/10<=regle[2])) tab[0][i]=1;
            if((i/10>=regle[4])&&(i/10<=regle[5])) tab[1][i]=1;
        }
    }
    return tab;
}
unsigned int** Cell1D::remplissageRegle(unsigned int** tab, unsigned int** regle) const{
    for(unsigned int i=0; i<nbEtats; ++i){
        for(unsigned int j=0; j<=getTailleRegle(); ++j){
            tab[i][j] = regle[i][j];
        }
    }
    return tab;
}

Cell1D::Cell1D(const unsigned int regle[]) :Automate(remplissageRegle(createTabRegle(),regle)){

}

Cell1D::Cell1D(const Automate& a) :Automate(remplissageRegle(createTabRegle(), a.getRegle())) {

}

Cell1D::~Cell1D() {
    for(unsigned int i=0; i<nbEtats; ++i) delete[] regle[i];
    delete[] regle;
}

unsigned int** Cell1D::createTabRegle() const {
    unsigned int** tab = new unsigned int* [nbEtats];
    for(unsigned int i=0; i<nbEtats; ++i){
        tab[i] = new unsigned int [getTailleRegle()+1];
    }
    return tab;
}

unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const{
    if(regle[0]||regle[3]!=1||regle[1]>8||regle[2]>8||regle[4]>8||regle[5]>8) throw AutomateException("Regle incorrecte");
    if(regle[1]>regle[2]||regle[4]>regle[5]) throw AutomateException("Regle incorrecte");
    for(unsigned int i=0; i<getTailleRegle();++i){
        tab[0][i]=0;
        tab[1][i]=0;
        if((i/10+i%10)==8) {
            if((i/10>=regle[1])&&(i/10<=regle[2])) tab[0][i]=1;
            if((i/10>=regle[4])&&(i/10<=regle[5])) tab[1][i]=1;
        }
    }
    return tab;
}

unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, unsigned int** regle) const{
    for(unsigned int i=0; i<nbEtats; ++i){
        for(unsigned int j=0; j<=getTailleRegle(); ++j){
            tab[i][j] = regle[i][j];
        }
    }
    return tab;
}

JeuDeLaVie::JeuDeLaVie(const unsigned int regle[]) :Automate(remplissageRegle(createTabRegle(),regle)) {

}

JeuDeLaVie::JeuDeLaVie(const Automate& a) :Automate(remplissageRegle(createTabRegle(), a.getRegle())) {

}

JeuDeLaVie::~JeuDeLaVie() {
    for(unsigned int i=0; i<nbEtats; ++i) delete[] regle[i];
    delete[] regle;
}

unsigned int** JeuDeLaVie::createTabRegle() const {
    unsigned int** tab = new unsigned int* [nbEtats];
    for(unsigned int i=0; i<nbEtats; ++i){
        tab[i] = new unsigned int [getTailleRegle()+1];
    }
    return tab;
}

Automate& FabriqueAutomate::createAutomate(const std::string idAutomate, const unsigned int regle[]) const {
    if(idAutomate== "Cell1D") return *(new Cell1D(regle));
    if(idAutomate== "JeuDeLaVie") return *(new JeuDeLaVie(regle));
    throw AutomateException("Automate Inexistant");
}

Automate& FabriqueAutomate::createAutomate(const Automate& a) const {
    if(!strcmp(typeid(a).name(),"Cell1D")) return *(new Cell1D(a));
    if(!strcmp(typeid(a).name(),"JeuDeLaVie")) return *(new JeuDeLaVie(a));
    throw AutomateException("Automate Inexistant");
}

unsigned int Cell1D::getNbEtats() const{
    return nbEtats;
}

unsigned int Cell1D::getTailleRegle() const{
    return ((3^nbDim)-1)*10^(nbEtats-1);
}

unsigned int Cell1D::getNbDim() const{
    return nbDim;
}

unsigned int JeuDeLaVie::getNbEtats() const{
    return nbEtats;
}

unsigned int JeuDeLaVie::getTailleRegle() const{
    return ((3^nbDim)-1)*10^(nbEtats-1);
}

unsigned int JeuDeLaVie::getNbDim() const{
    return nbDim;
}
