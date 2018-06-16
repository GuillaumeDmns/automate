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
#include <fstream>
#include <iostream>

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
     * \param unsigned int regles[] : règles choisies pour l'automate
     * \param string choixdepart : Choix de configuration pour l'état de départ
     * \param unsigned int n : Dimension n de la grille
     * \param unsigned int m : Dimension m de la grille
     * \param unsigned int age : Valeur de numEtat du simulateur
     *
     */
    Simulateur(string typeautomate, unsigned int regles[], string choixdepart, unsigned int n, unsigned int m =1, unsigned int age =0);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Simulateur
     *
     * \param string typeautomate : Choix du type d'automate
     * \param unsigned int regles** : règles choisies pour l'automate
     * \param string choixdepart : Choix de configuration pour l'état de départ
     * \param unsigned int n : Dimension n de la grille
     * \param unsigned int age : Valeur de numEtat du simulateur
     * \param const unsigned int* dep : Etat de départ à donner au Simulateur
     * \param const unsigned int* cur : Etat courant à donner au Simulateur
     *
     */
    Simulateur(string typeautomate, const unsigned int** regles, unsigned int n, unsigned int age, const unsigned int* dep, const unsigned int* cur);

    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe Simulateur
     *
     * \param string typeautomate : Choix du type d'automate
     * \param unsigned int regles** : règles choisies pour l'automate
     * \param string choixdepart : Choix de configuration pour l'état de départ
     * \param unsigned int n : Dimension n de la grille
     * \param unsigned int m : Dimension m de la grille
     * \param unsigned int age : Valeur de numEtat du simulateur
     * \param const unsigned int* dep : Etat de départ à donner au Simulateur
     * \param const unsigned int* cur : Etat courant à donner au Simulateur
     *
     */
    Simulateur(string typeautomate, const unsigned int** regles, unsigned int n, unsigned int m, unsigned int age, const unsigned int** dep, const unsigned int** cur);


    /*!
     * \brief Fonction reset du Simulateur
     *
     * \details Permet la mise en place d'un nouvel état de départ et la remise à zéro de la simulation
     *
     * \return void
     */
    void reset() {
            FabriqueEtat fabEtat;
            fabEtat.copyEtat(depart,current);
            numEtat=0;
    }

    /*!
     * \brief Fonction setEtat du Simulateur
     *
     * \details Permet la mise en place d'un nouvel état de départ
     *
     * \param Etat* e : Pointeur sur l'état à mettre en état de départ
     * \return void
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
     * \details Permet le passage d'un état à son état suivant en fonction des règles de transition
     *
     * \return void
     */
    void next();

    /*!
     * \brief Fonction getCurrent du Simulateur
     *
     * \details Récupère un pointeur vers l'état courant du simulateur
     *
     * \return Etat*
     */
    Etat* getCurrent() const { return current; }

    /*!
     * \brief Fonction getValueCurrent du Simulateur
     *
     * \details Récupère une valeur de l'état courant
     *
     * \param unsigned int n : Abscisse de la case dont on veut la valeur
     * \param unsigned int m : Ordonnée de la case dont on veut la valeur
     * \return unsigned int
     */
    unsigned int getValueCurrent(unsigned int n, unsigned int m) const;

    /*!
     * \brief Fonction getNumEtat du Simulateur
     *
     * \details Donne la valeur de l'attribut numEtat du Simulateur
     *
     * \return unsigned int
     */
    unsigned int getNumEtat() const { return numEtat; }

    /*!
     * \brief Fonction setValueDepart du Simulateur
     *
     * \details Donne une nouvelle valeur à l'état de départ
     *
     * \param unsigned int n : Abscisse de la case
     * \param unsigned int m : Ordonnée de la case
     * \param unsigned int v : Valeur à attribuer à la case
     * \return void
     */
    void setValueDepart(unsigned int n, unsigned int m =0, unsigned int v=0);

    /*!
     * \brief Fonction getAutomate du Simulateur
     *
     * \details Donne un pointeur vers l'automate concerné par la simulation
     *
     * \return Automate*
     */
    Automate* getAutomate() const { return automate; }

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe Simulateur
     *
     */
    ~Simulateur();

    /*!
     * \brief Fonction save du Simulateur
     *
     * \details Permet de sauvegarder les informations du simulateur
     *
     * \param string filename : Nom du fichier dans lequel réaliser la sauvegarde
     * \return void
     */
    void save(string filename) const;

private:
    Automate* automate; /*!< Automate simulé par le simulateur*/
    Etat* depart; /*!< Etat de départ pour la simulation*/
    Etat* current; /*!< Etat courant de la simulation*/
    unsigned int numEtat; /*!< Rang de l'Etat courant dans la simulation*/
};




#endif // SIMULATEUR_H
