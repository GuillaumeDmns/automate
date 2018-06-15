/*!
    * \file main.c
    * \brief Test des automates
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
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
    * \return 0 - Arrête normal du programme
    *
    */

int main(int argc, char * argv[]) {
    try {
    _interface(argc, argv);
    }
    catch (AutomateException::AutomateException a);
    cout<<"exception : "<<a.getInfo()<<"\n";
    /*unsigned int tab[6] = {0, 3, 5, 1, 3, 5};
    Simulateur simu("Cell1D", tab, "symetrique", 10, 0);
    Etat* e = simu.getCurrent();*/
    //std::cout << dynamic_cast<Etat1D*>(e)->getValue(2) << std::endl;
    return 0;
}

/*
int main(){
    FabriqueAutomate fabA;
    unsigned int tab[6]={0,0,1,1,1,2};
    Automate* a = FabriqueAutomate::createAutomate("Cell1D", tab);
}
*/
