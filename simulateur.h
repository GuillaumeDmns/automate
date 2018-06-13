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
#include <typeinfo>
#include <string>
#include "etat.h"
#include "automate.h"

using namespace std;

/*!
    * \class Simulateur
    * \brief Classe définissant un Simulateur
    *
    * \details La classe gère les données relatives à la création d'un simulateur
    *
    */
class Simulateur {
public:
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Simulateur
     *
     * \param string typeautomate : Choix du type d'automate
     * \param unsigned int regles[] : Régles choisies pour l'automate
     * \param string choixdepart : Choix de configuration pour l'état de départ
     * \param unsigned int n : Dimension n de la grille
     * \param unsigned int m : Dimension m de la grille
     *
     */
    Simulateur(string typeautomate, unsigned int regles[], string choixdepart, unsigned int n, unsigned int m =0);

    /*!
     * \brief Fonction reset du Simulateur
     *
     * \details Permet la mise en place d'un nouvel état de départ et la remise à zéro de la simulation
     *
     *
     */
    void reset() {
            this->current=this->depart;
            this->numEtat=0;
    }


    /*!
     * \brief Fonction setEtat du Simulateur
     *
     * \details Permet la mise en place d'un nouvel état de départ
     *
     * \param Etat& e : Référence sur l'état à mettre en état de départ
     *
     */
    void setEtat(Etat* e) {
        if (typeid(this->depart) != typeid(e))
            throw "erreur : pas meme type de grille\n";
        else {
                this->depart=e;
                this->reset();
        }
    }

    /*!
     * \brief Fonction next du Simulateur
     *
     * \details Permet le passage d'un état à son état suivant en fonction des régles de transition
     *
     *
     */
    void next();

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Simulateur
     *
     */
    ~Simulateur();

private:
    Automate* automate; /*!< Automate simulé par le simulateur*/
    Etat* depart; /*!< Etat de départ pour la simulation*/
    Etat* current; /*!< Etat courant de la simulation*/
    unsigned int numEtat; /*!< Rang de l'Etat courant dans la simulation*/
};




#endif // SIMULATEUR_H
