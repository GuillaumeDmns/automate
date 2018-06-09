/*!
    * \file simulateur.h
    * \brief Déclaration de l'objet Simulateur
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Fichier pour créer les classes et fonctions relatives à Simulateur
    *
    */


#ifndef SIMULATEUR_H
#define SIMULATEUR_H
#include <iostream>
#include <string>

#include "automate.h"

using namespace std;


/*!
    * \class Simulateur
    * \brief classe définissant les simulateurs
    *
    * \details La classe gère les données relatives à la création d'un simulateur
    *
    */
class Simulateur {
public:
    Simulateur(const Automate& a,unsigned int buf=2);
    Simulateur(const Automate& a, const Etat& dep, unsigned int buf=2);
    void reset();
    void setEtatDepart(const Etat& e);
    void next();
    void run(unsigned int nbStep=1);
    const Etat& dernier() const;
    unsigned int getRangDernier() const;
    ~Simulateur();
private:
    const Automate& automate; /*!< Automate simulé par le simulateur*/
    const Etat* depart; /*!< Etat de départ pour la simulation*/
    unsigned int nbMaxEtats; /*!< nombre maximum d'états stockés*/
    Etat** etats; /*!< tableau des états générés par le simulateur*/
};




#endif // SIMULATEUR_H
