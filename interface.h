/*!
    * \file interface.h
    * \brief Déclaration des classes et fonctions de l'interface
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 16 juin 2018
    *
    * \details Fichier pour déclarer les fonctions et les classes relatives à l'interface graphique
    *
    */


#if !defined(INTERFACE_H)
#define INTERFACE_H

#include <QtWidgets>
#include "simulateur.h"


/*!
    * \class MainWindow
    * \brief Classe pour la fenêtre principale
    *
    * \details La classe gère les méthodes et attributs relatifs à l'affichage de la fenêtre principale
    *
    */
class MainWindow : public QWidget {
    Q_OBJECT /*! ATTRIBUT A DECRIRE*/
public slots:
    /*!
     * \brief Fonction afficheGrid de MainWindow
     *
     * \details Permet l'affichage de la grille
     *
     * \return void
     */
    void afficheGrid();

    /*!
     * \brief Fonction backToHome de MainWindow
     *
     * \details Permet le retour à la page d'Accueil
     *
     * \return void
     */
    void backToHome();

    /*!
     * \brief Fonction changeCell de MainWindow
     *
     * \details Permet de changer d'Automate
     *
     * \param int row : Nombre de lignes
     * \param int colomn : Nombre de colonnes
     * \return void
     */
    void changeCell(int row, int colomn);

    /*!
     * \brief Fonction changeForm de MainWindow
     *
     * \details Permet de changer l'affichage en fonctions des caractéristiques de l'automate simulé
     *
     * \param int index : Choix de l'automate à simuler
     * \return void
     */
    void changeForm(int index);

    /*!
     * \brief Fonction createGrid de MainWindow
     *
     * \details Permet la création de la grille
     *
     * \return void
     */
    void createGrid();

    /*!
     * \brief Fonction nextEtat de MainWindow
     *
     * \details Permet le passage à l'état suivant de l'automate simulé
     *
     * \return void
     */
    void nextEtat();

    /*!
     * \brief Fonction playGrid de MainWindow
     *
     * \details Permet de lancer la simulation de l'automate simulé
     *
     * \return void
     */
    void playGrid();

    /*!
     * \brief Fonction resetGrid de MainWindow
     *
     * \details Permet de revenir dans la situation initiale de la simulation
     *
     * \return void
     */
    void resetGrid();

    /*!
     * \brief Fonction setLoadedAutomate de MainWindow
     *
     * \details Permet de charger un automate pré-existant
     *
     * \return void
     */
    void setLoadedAutomate();

    /*!
     * \brief Fonction stopGrid de MainWindow
     *
     * \details Permet d'arrêter la simulation en cours
     *
     * \return void
     */
    void stopGrid();

    /*!
     * \brief Fonction checkRules de MainWindow
     *
     * \details Récupère les règles pour la simulation
     *
     * \return void
     */
    void checkRules();

    /*!
     * \brief Fonction saveSimu de MainWindow
     *
     * \details Permet de sauvegarder la simulation courante
     *
     * \return void
     */
    void saveSimu();

    /*!
     * \brief Fonction validAuto de MainWindow
     *
     * \details Crée l'automate pour la simulation
     *
     * \return void
     */
    void validAuto();
public:
    /*!
     * \brief Constructeur
     *
     * \details Constructeur de la classe MainWindow
     *
     */
    MainWindow();

    /*!
     * \brief Destructeur
     *
     * \details Destructeur de la classe MainWindow
     *
     */
    ~MainWindow();
private:

    QComboBox *typeAutomate; /*! Liste déroulante pour le choix de l'automate */
    QComboBox *generation; /*! Liste déroulante pour le choix du type de génération de grille  */
    QFormLayout *newAutomate; /*! Layout contenant le formulaire */
    QGridLayout *display; /*! Layout unique de home */
    QGridLayout *mainLayout; /*! Layout principal de l'interface */
    QHBoxLayout *dimensions; /*! Layout horizontal contenant des widgets de paramétrage des dimensions de la grille*/
    QHBoxLayout *header; /*! Layout de la banderolle d'affichage du gros titre */
    QHBoxLayout *rulesRenait; /*! Layout horizontal contenant des widgets de paramétrage pour renaître */
    QHBoxLayout *rulesVit; /*! Layout horizontal contenant des widgets de paramétrage pour rester en vie */
    QLabel *displayTitle; /*! Texte créer un automate */
    QLabel *timesDimensions; /*! Texte "x" entre les deux dimensions dans le formulaire */
    QLabel *generalTitle; /*! Texte AUTOCELL */
    QLabel *toolsInfo; /*! Texte présentation Cell1D */
    QLabel *toolsInfo2; /*! Texte présentation JeuDeLaVie */
    QLabel *toolsInfo3; /*! Texte présentation FeuDeForet */
    QLabel *counter; /*! Texte affichant le numéro de la génération */
    QLabel *counterLabel; /*! Texte affichant "génération" */
    QLabel *minR; /*! Texte minimum pour renaître */
    QLabel *maxR; /*! Texte maximum pour renaître */
    QLabel *minV; /*! Texte minimum pour rester en vie */
    QLabel *maxV; /*! Texte maximum pour rester en vie */
    QPushButton *submit; /*! Bouton valider */
    QPushButton *backHomeButton; /*! Bouton retour */
    QPushButton *loadOtherAutomate; /*! Bouton charger un automate */
    QPushButton *quit; /*! Bouton quitter */
    QPushButton *next; /*! Bouton next */
    QPushButton *reset; /*! Bouton reset */
    QPushButton *save; /*! Bouton sauvegarder */
    QPushButton *stop; /*! Bouton stop */
    QPushButton *play; /*! Bouton play */
    Simulateur* simu; /*! Instance de Simulateur */
    QSpinBox *dimensionH; /*! Zone de saisie de la hauteur de la grille */
    QSpinBox *dimensionL; /*! Zone de saisie de la largeur de la grille */
    QSpinBox *minRenait; /*! Zone de saisie du minimum de voisins d'une cellule pour renaître */
    QSpinBox *maxRenait; /*! Zone de saisie du maximum de voisins d'une cellule pour renaître */
    QSpinBox *minVit; /*! Zone de saisie du minimum de voisins d'une cellule pour rester en vie */
    QSpinBox *maxVit; /*! Zone de saisie du maximum de voisins d'une cellule pour rester en vie */
    QStackedLayout *disp; /*! Layout de l'affichage de la grille ou du formulaire */
    QStackedLayout *toolsStacked; /*! Layout de l'affichage du chargement d'automate ou des outils de simulation */
    static int Gridsize; /*! Paraètre de taille de la grille */
    QTableWidget *grid; /*! Grille */
    QTimer *timer; /*! Objet de temps pour le timing entre l'affichage de deux états */
    QVBoxLayout *toolsHome; /*! Layout unique de toolsWidgetHome*/
    QVBoxLayout *toolsRun; /*! Layaout unique de toolsWidgetRun */
    QVBoxLayout *bigGridLayout; /*! Layaout unique de gridWidget */
    QWidget *home; /*! Widget de la partie accueil */
    QWidget *gridWidget; /*! Widget de la partie grille */
    QWidget *toolsWidgetHome; /*! Widget de la partie description automate + charger + quitter */
    QWidget *toolsWidgetRun; /*! Widget de la partie outil lors de la simulation */
    QSlider *speedtime; /*! Barre de réglage de la vitesse */
};

/*!
    * \brief _interface
    * \details Programme d'affichage de l'interface
    *
    * \param int argc : Nombre d'arguments donnés en entrée
    * \param char * argv[] : Arguments données en entrée
    *
    * \return int
    */
int _interface(int argc, char* argv[]);

#endif
