/*!
    * \file main.c
    * \brief Test des automates
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 16 juin 2018
    *
    * \details Programme pour tester les fonctions de l'automate et l'affichage
    *
    */
    
#include "interface.h"
#include "simulateur.h"

/*!
    * \fn int main (int argc,char * argv[])
    * \brief Entrée du programme
    * 
    *
    * \param int argc : Nombre d'arguments donnés en entrée
    * \param char * argv[] : Arguments données en entrée
    *
    * \return 0 - Arrête normal du programme
    */
int main(int argc, char * argv[]) {
    _interface(argc, argv);
    return 0;
}
