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
    Simulateur(const string typeautomate, const string regles, const string choixdepart, const unsigned int n, const unsigned int m);
    //Simulateur(const Automate& a, );
    void reset(); //copie etat de depart vers courant et remet a zero
    void setEtat(Etat& e); //on doit être dans état 0
    void next();
    //void run(); //run execute par interface
    //const Etat& dernier() const;
    //unsigned int getRangDernier() const;
    ~Simulateur();
private:
    const Automate& automate; /*!< Automate simulé par le simulateur*/
    Etat& depart; /*!< Etat de départ pour la simulation*/
    Etat& current; /*!< Etat courant de la simulation*/
    unsigned int numEtat; /*!< rang de l'Etat current dans la simulation*/
};




#endif // SIMULATEUR_H
