/*!
    * \file automate.cpp
    * \brief Définition des fonctions des objets Automate
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
#include <math.h>
#include "automate.h"

using namespace std;

//DOCUMENTATION POUR INITIALISATION DES ATTRIBUTS STATIC ????

unsigned int Cell1D::nbDim=1;
unsigned int JeuDeLaVie::nbDim=2;
unsigned int FeuDeForet::nbDim=2;
unsigned int Cell1D::nbEtats=2;
unsigned int JeuDeLaVie::nbEtats=2;
unsigned int FeuDeForet::nbEtats=4;

    /*!
     * \fn void FabriqueAutomate::appliquerTransition(Etat& dep, Etat& dest, Automate& a) const
     * \brief Calcule l'état suivant d'un état donné
     *
     * \param Etat& dep : Référence sur l'état de départ sur lequel appliquer la transition
     * \param Etat& dest : Référence vers l'état résultant de la transition
     * \param Automate& a : Référence sur l'automate possédant les régles pour la transition
     * \return void
     */
void FabriqueAutomate::appliquerTransition(Etat& dep, Etat& dest, Automate& a) const {
    if(strcmp(typeid(dep).name(),typeid(dest).name())) throw AutomateException("Etats incompatibles");
    if(!strcmp(typeid(dep).name(),"6Etat1D")) {
        a.appliquerTransition(dynamic_cast<Etat1D&>(dep),dynamic_cast<Etat1D&>(dest));
        return;
    }
    if(!strcmp(typeid(dep).name(),"6Etat2D")) {
        a.appliquerTransition(dynamic_cast<Etat2D&>(dep),dynamic_cast<Etat2D&>(dest));
        return;
    }
    throw AutomateException("Etats non existants");
}


    /*!
     * \fn void Automate::appliquerTransition(const Etat1D& dep, Etat1D& dest) const
     * \brief Calcule l'état suivant d'un état donné
     *
     * \param Etat1D& dep : Référence sur l'état en 1D de départ sur lequel appliquer la transition
     * \param Etat1D& dest : Référence vers l'état en 1D résultant de la transition
     *
     * \return void
     */
void Automate::appliquerTransition(const Etat1D& dep, Etat1D& dest) const {
    if(getNbDim()!=1) throw AutomateException("Nombre de dimensions incorrect");
    if((dep.getdimN()!=dest.getdimN())) throw AutomateException("Etat dep et dest incompatibles");
    unsigned int v=0;
    unsigned int voisinage=0;
    for(unsigned int i=0; i<dep.getdimN(); ++i){
        voisinage=0;
        voisinage+=pow(10, dep.getValue((i-1+dep.getdimN())%dep.getdimN()));
        voisinage+=pow(10, dep.getValue((i+1+dep.getdimN())%dep.getdimN()));
        if(voisinage>getTailleRegle()) throw AutomateException("Etat avec trop d'etats pour l'Automate");
        v=regle[dep.getValue(i)][voisinage];
        dest.setValue(i,v);
    }
}


    /*!
     * \fn void Automate::appliquerTransition(const Etat2D& dep, Etat2D& dest) const
     * \brief Calcule l'état suivant d'un état donné
     *
     * \param Etat2D& dep : Référence sur l'état en 2D de départ sur lequel appliquer la transition
     * \param Etat2D& dest : Référence vers l'état en 2D résultant de la transition
     *
     * \return void
     */
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
                    voisinage+=pow(10, dep.getValue((k+dep.getdimN())%dep.getdimN(),(l+dep.getdimM())%dep.getdimM()));
                }
            }
            voisinage-=pow(10, dep.getValue(i,j));
            if(voisinage>getTailleRegle()) throw AutomateException("Etat avec trop d'etats pour l'Automate");
            v=regle[dep.getValue(i,j)][voisinage];
            dest.setValue(i,j,v);
        }
    }
}


    /*!
     * \fn Automate::Automate(unsigned int** tab)
     * \brief Constructeur de la classe Automate
     *
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     */
Automate::Automate(unsigned int** tab) :regle(tab) {
}


    /*!
     * \fn Automate::~Automate()
     * \brief Détruit un objet de type Automate
     *
     */
Automate::~Automate(){}


    /*!
     * \fn unsigned int** Cell1D::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const
     * \brief Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
unsigned int** Cell1D::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const{
    if(regle[0]||regle[3]!=1||regle[1]>2||regle[2]>2||regle[4]>2||regle[5]>2) throw AutomateException("Regle incorrecte");
    if(regle[1]>regle[2]||regle[4]>regle[5]) throw AutomateException("Regle incorrecte");
    for(unsigned int i=0; i<=Cell1D::getTailleRegle();++i){
        tab[0][i]=0;
        tab[1][i]=0;
        if((i/10+i%10)==2) {
            if((i/10>=regle[1])&&(i/10<=regle[2])) tab[0][i]=1;
            if((i/10>=regle[4])&&(i/10<=regle[5])) tab[1][i]=1;
        }
    }
    return tab;
}

    /*!
     * \fn unsigned int** Cell1D::remplissageRegle(unsigned int** tab, unsigned int** regle) const
     * \brief Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
unsigned int** Cell1D::remplissageRegle(unsigned int** tab, const unsigned int** regle) const{
    for(unsigned int i=0; i<nbEtats; ++i){
        for(unsigned int j=0; j<=Cell1D::getTailleRegle(); ++j){
            tab[i][j] = regle[i][j];
        }
    }
    return tab;
}

    /*!
     * \fn Cell1D::Cell1D(const unsigned int regle[])
     * \brief Constructeur de la classe Cell1D
     *
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     */
Cell1D::Cell1D(const unsigned int regle[]) :Automate(Cell1D::remplissageRegle(Cell1D::createTabRegle(),regle)){
}

    /*!
     * \fn Cell1D::Cell1D(const Automate& a)
     * \brief Constructeur par recopie de la classe Cell1D
     *
     * \param const Automate& a : Objet Automate à recopier
     */
Cell1D::Cell1D(const Automate& a) :Automate(Cell1D::remplissageRegle(Cell1D::createTabRegle(), const_cast<const unsigned int**>(a.getRegle()))) {
}

    /*!
     * \fn Cell1D::~Cell1D()
     * \brief Destructeur de la classe Cell1D
     *
     */
Cell1D::~Cell1D(){
    for(unsigned int i=0; i<nbEtats; ++i) delete[] regle[i];
    delete[] regle;
}

    /*!
     * \fn unsigned int** Cell1D::createTabRegle() const
     * \brief Crée un tableau de règles vide aux bonnes dimensions
     *
     * \return unsigned int**
     */
unsigned int** Cell1D::createTabRegle() const {
    unsigned int** tab = new unsigned int* [nbEtats];
    for(unsigned int i=0; i<nbEtats; ++i){
        tab[i] = new unsigned int[Cell1D::getTailleRegle()+1];
    }
    return tab;
}

    /*!
     * \fn unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const
     * \brief Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const{
    if(regle[0]||regle[3]!=1||regle[1]>8||regle[2]>8||regle[4]>8||regle[5]>8) throw AutomateException("Regle incorrecte");
    if(regle[1]>regle[2]||regle[4]>regle[5]) throw AutomateException("Regle incorrecte");
    for(unsigned int i=0; i<=JeuDeLaVie::getTailleRegle();++i){
        tab[0][i]=0;
        tab[1][i]=0;
        if((i/10+i%10)==8) {
            if((i/10>=regle[1])&&(i/10<=regle[2])) tab[0][i]=1;
            if((i/10>=regle[4])&&(i/10<=regle[5])) tab[1][i]=1;
        }
    }
    return tab;
}

    /*!
     * \fn unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, const unsigned int** regle) const
     * \brief Remplissage du tableau des règles pour automate
     *
     * \param unsigned int** tab : Tableau contenant les différentes régles
     * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
     * \return unsigned int**
     */
unsigned int** JeuDeLaVie::remplissageRegle(unsigned int** tab, const unsigned int** regle) const{
    for(unsigned int i=0; i<nbEtats; ++i){
        for(unsigned int j=0; j<=JeuDeLaVie::getTailleRegle(); ++j){
            tab[i][j] = regle[i][j];
        }
    }
    return tab;
}

    /*!
     * \fn JeuDeLaVie::JeuDeLaVie(const unsigned int regle[])
     * \brief Constructeur de la classe Jeu de la Vie
     *
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
     */
JeuDeLaVie::JeuDeLaVie(const unsigned int regle[]) :Automate(JeuDeLaVie::remplissageRegle(JeuDeLaVie::createTabRegle(),regle)) {
}

    /*!
     * \fn JeuDeLaVie::JeuDeLaVie(const Automate& a)
     * \brief Constructeur par recopie de la classe JeuDeLaVie
     *
     * \param const Automate& a : Objet Automate à recopier
     */
JeuDeLaVie::JeuDeLaVie(const Automate& a) :Automate(JeuDeLaVie::remplissageRegle(JeuDeLaVie::createTabRegle(), const_cast<const unsigned int**>(a.getRegle()))) {
}

    /*!
     * \fn JeuDeLaVie::~JeuDeLaVie()
     * \brief Destructeur de la classe JeuDeLaVie
     *
     */
JeuDeLaVie::~JeuDeLaVie(){
    for(unsigned int i=0; i<nbEtats; ++i) delete[] regle[i];
    delete[] regle;
}

    /*!
     * \fn unsigned int** JeuDeLaVie::createTabRegle() const
     * \brief Crée un tableau de règles vide aux bonnes dimensions
     *
     * \return unsigned int**
     */
unsigned int** JeuDeLaVie::createTabRegle() const {
    unsigned int** tab = new unsigned int* [nbEtats];
    for(unsigned int i=0; i<nbEtats; ++i){
        tab[i] = new unsigned int [JeuDeLaVie::getTailleRegle()+1];
    }
    return tab;
}

    /*!
     * \fn Automate* FabriqueAutomate::createAutomate(std::string idAutomate, const unsigned int regle[]) const
     * \brief Permet l'instanciation de l'Automate souhaité
     *
     * \param string idAutomate : Chaîne de caractères correspondant au type d'automate souhaité
     * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles de transition
     *
     * \return Automate*
     */
Automate* FabriqueAutomate::createAutomate(std::string idAutomate, const unsigned int regle[]) const {
    if(idAutomate== "Vie 1D") return (new Cell1D(regle));
    if(idAutomate== "Vie 2D") return (new JeuDeLaVie(regle));
    if(idAutomate== "Feu de forêt") return (new FeuDeForet(regle));
    throw AutomateException("Automate Inexistant");
}

    /*!
     * \fn Automate* FabriqueAutomate::createAutomate(const Automate* a) const
     * \brief Permet l'instanciation de l'Automate souhaité par recopie
     *
     * \param const Automate* a : Pointeur vers l'automate qu'on souhaite dupliquer
     *
     * \return Automate*
     */
Automate* FabriqueAutomate::createAutomate(const Automate* a) const {
    if(!strcmp(typeid(*a).name(),"6Cell1D")) return (new Cell1D(*a));
    if(!strcmp(typeid(*a).name(),"10JeuDeLaVie")) return (new JeuDeLaVie(*a));
    if(!strcmp(typeid(*a).name(),"10FeuDeForet")) return (new FeuDeForet(*a));
    throw AutomateException("Automate Inexistant");
}

    /*!
     * \fn void FabriqueAutomate::deleteAutomate(Automate* a) const
     * \brief Permet la destruction de l'automate en fonction de son type
     *
     * \param Automate* a : Pointeur vers l'Automate que l'on souhaite détruire
     * \return void
     */
void FabriqueAutomate::deleteAutomate(Automate* a) const{
    if(!strcmp(typeid(*a).name(),"6Cell1D")) delete dynamic_cast<Cell1D*>(a);
    else{
        if(!strcmp(typeid(*a).name(),"10JeuDeLaVie")) delete dynamic_cast<JeuDeLaVie*>(a);
        else{
            if(!strcmp(typeid(*a).name(),"10FeuDeForet")) delete dynamic_cast<FeuDeForet*>(a);
            else throw AutomateException("AutomateInexistant");
        }
    }
}

    /*!
     * \fn unsigned int Cell1D::getNbEtats() const
     * \brief Permet la récupération de la valeur de l'attribut nbEtats
     *
     * \return unsigned int
     */
unsigned int Cell1D::getNbEtats() const{
    return nbEtats;
}

    /*!
     * \fn unsigned int Cell1D::getTailleRegle() const
     * \brief Permet la récupération de la taille que devra faire le tableau de régles
     *
     * \return unsigned int
     */
unsigned int Cell1D::getTailleRegle() const{
    return ((pow(3, nbDim)-1)*pow(10, nbEtats-1));
}

    /*!
     * \fn unsigned int Cell1D::getNbDim() const
     * \brief Permet la récupération du nombre de dimensions de l'automate
     *
     * \param
     * \return unsigned int
     */
unsigned int Cell1D::getNbDim() const{
    return nbDim;
}

    /*!
     * \fn unsigned int JeuDeLaVie::getNbEtats() const
     * \brief Permet la récupération de la valeur de l'attribut nbEtats
     *
     * \return unsigned int
     */
unsigned int JeuDeLaVie::getNbEtats() const{
    return nbEtats;
}

    /*!
     * \fn unsigned int JeuDeLaVie::getTailleRegle() const
     * \brief Permet la récupération de la taille que devra faire le tableau de régles
     *
     * \return unsigned int
     */
unsigned int JeuDeLaVie::getTailleRegle() const{
    return (pow(3, nbDim)-1)*pow(10, nbEtats-1);
}

    /*!
     * \fn unsigned int JeuDeLaVie::getNbDim() const
     * \brief Permet la récupération du nombre de dimensions de l'automate
     *
     * \param
     * \return unsigned int
     */
unsigned int JeuDeLaVie::getNbDim() const{
    return nbDim;
}

/*!
 * \fn unsigned int** FeuDeForet::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const
 * \brief Remplissage du tableau des règles pour automate
 *
 * \param unsigned int** tab : Tableau contenant les différentes régles
 * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
 * \return unsigned int**
 */
unsigned int** FeuDeForet::remplissageRegle(unsigned int** tab, const unsigned int regle[]) const{
if(regle[0]) throw AutomateException("Regle incorrecte");
    for(unsigned int i=0; i<=FeuDeForet::getTailleRegle();++i){
        tab[0][i]=0;
        tab[1][i]=0;
        tab[2][i]=0;
        tab[3][i]=0;
        if(((i/1000)+(i/100)%10+(i/10)%10+i%10)==8) {
            tab[2][i]=3;
            tab[3][i]=3;
            if((i/100)%10>0) tab[1][i]=2; else tab[1][i]=1;
        }
    }
    return tab;
}

/*!
 * \fn unsigned int** FeuDeForet::remplissageRegle(unsigned int** tab, const unsigned int** regle) const
 * \brief Remplissage du tableau des règles pour automate
 *
 * \param unsigned int** tab : Tableau contenant les différentes régles
 * \param const unsigned int regle** : Tableau contenant les informations pour générer les régles
 * \return unsigned int**
 */
unsigned int** FeuDeForet::remplissageRegle(unsigned int** tab, const unsigned int** regle) const{
    for(unsigned int i=0; i<nbEtats; ++i){
        for(unsigned int j=0; j<=getTailleRegle(); ++j){
            tab[i][j] = regle[i][j];
        }
    }
    return tab;
}

/*!
 * \fn FeuDeForet::FeuDeForet(const unsigned int regle[])
 * \brief Constructeur de la classe Feu De Foret
 *
 * \param const unsigned int regle[] : Tableau contenant les informations pour générer les régles
 */
FeuDeForet::FeuDeForet(const unsigned int regle[]) : Automate(FeuDeForet::remplissageRegle(FeuDeForet::createTabRegle(),regle)) {
}

/*!
 * \fn FeuDeForet::FeuDeForet(const Automate& a)
 * \brief Constructeur par recopie de la classe Feu De Foret
 *
 * \param const Automate& a : Objet Automate à recopier
 */
FeuDeForet::FeuDeForet(const Automate& a) : Automate(FeuDeForet::remplissageRegle(FeuDeForet::createTabRegle(), const_cast<const unsigned int**>(a.getRegle()))) {
}

/*!
 * \fn FeuDeForet::~FeuDeForet()
 * \brief Destructeur de la classe Feu De Foret
 *
 */
FeuDeForet::~FeuDeForet(){
    for(unsigned int i=0; i<nbEtats; ++i) delete[] regle[i];
    delete[] regle;
}

/*!
 * \fn unsigned int** FeuDeForet::createTabRegle() const
 * \brief Crée un tableau de règles vide aux bonnes dimensions
 *
 * \return unsigned int**
 */
unsigned int** FeuDeForet::createTabRegle() const {
    unsigned int** tab = new unsigned int* [nbEtats];
    for(unsigned int i=0; i<nbEtats; ++i){
        tab[i] = new unsigned int [FeuDeForet::getTailleRegle()+1];
    }
    return tab;
}

/*!
 * \fn unsigned int FeuDeForet::getNbEtats() const
 * \brief Permet la récupération de la valeur de l'attribut nbEtats
 *
 * \return unsigned int
 */
unsigned int FeuDeForet::getNbEtats() const{
    return nbEtats;
}

/*!
 * \fn unsigned int FeuDeForet::getTailleRegle() const
 * \brief Permet la récupération de la taille que devra faire le tableau de régles
 *
 * \return unsigned int
 */
unsigned int FeuDeForet::getTailleRegle() const{
    return (pow(3, nbDim)-1)*pow(10, nbEtats-1);
}

/*!
 * \fn unsigned int FeuDeForet::getNbDim() const
 * \brief Permet la récupération du nombre de dimensions de l'automate
 *
 * \return unsigned int
 */
unsigned int FeuDeForet::getNbDim() const{
    return nbDim;
}

Automate* FabriqueAutomate::createAutomate(std::string idAutomate, const unsigned int** regle) const{
    if(!idAutomate.compare("6Cell1D")) return (new Cell1D(regle));
    if(!idAutomate.compare("10JeuDeLaVie")) return (new JeuDeLaVie(regle));
    if(!idAutomate.compare("10FeuDeForet")) return (new FeuDeForet(regle));
    throw AutomateException("Automate Inexistant");
}

Cell1D::Cell1D(const unsigned int** regle) :Automate(Cell1D::remplissageRegle(Cell1D::createTabRegle(), regle)) {
}

JeuDeLaVie::JeuDeLaVie(const unsigned int** regle) :Automate(JeuDeLaVie::remplissageRegle(JeuDeLaVie::createTabRegle(), regle)) {
}

FeuDeForet::FeuDeForet(const unsigned int** regle) :Automate(FeuDeForet::remplissageRegle(FeuDeForet::createTabRegle(), regle)) {
}
