/*!
    * \file interface.h
    * \brief Déclaration des classes et fonctions de l'interface
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
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

    QComboBox *typeAutomate; /*! */
    QComboBox *generation; /*! */
    QFormLayout *newAutomate; /*! */
    QGridLayout *display; /*! */
    QGridLayout *mainLayout; /*! */
    QHBoxLayout *dimensions; /*! */
    QHBoxLayout *header; /*! */
    QHBoxLayout *rulesRenait; /*! */
    QHBoxLayout *rulesVit; /*! */
    QHeaderView *VHeader; /*! */
    QHeaderView *HHeader; /*! */
    QLabel *displayTitle; /*! */
    QLabel *timesDimensions; /*! */
    QLabel *generalTitle; /*! */
    QLabel *toolsInfo; /*! */
    QLabel *toolsInfo2; /*! */
    QLabel *toolsInfo3; /*! */
    QLabel *counter; /*! */
    QLabel *counterLabel; /*! */
    QLabel *minR; /*! */
    QLabel *maxR; /*! */
    QLabel *minV; /*! */
    QLabel *maxV; /*! */
    QPushButton *submit; /*! Bouton valider*/
    QPushButton *backHomeButton; /*! Bouton retour*/
    QPushButton *loadOtherAutomate; /*! Bouton charger un automate*/
    QPushButton *quit; /*! Bouton quitter*/
    QPushButton *next; /*! Bouton next*/
    QPushButton *reset; /*! Bouton reset*/
    QPushButton *save; /*! Bouton sauvegarder*/
    QPushButton *stop; /*! Bouton stop*/
    QPushButton *play; /*! Bouton play*/
    Simulateur* simu; /*! */
    QSpinBox *dimensionH; /*! */
    QSpinBox *dimensionL; /*! */
    QSpinBox *minRenait; /*! */
    QSpinBox *maxRenait; /*! */
    QSpinBox *minVit; /*! */
    QSpinBox *maxVit; /*! */
    QStackedLayout *disp; /*! */
    QStackedLayout *toolsStacked; /*! */
    static int Gridsize; /*! */
    QTableWidget *grid; /*! */
    QTimer *timer; /*! */
    QVBoxLayout *toolsHome; /*! */
    QVBoxLayout *toolsRun; /*! */
    QVBoxLayout *bigGridLayout; /*! */
    QWidget *home; /*! Partie principale de la fenêtre d'Accueil*/
    QWidget *gridWidget; /*! Partie grille de la fenêtre de simulation*/
    QWidget *toolsWidgetHome; /*! Partie choix de la fenêtre d'Accueil*/
    QWidget *toolsWidgetRun; /*! Partie réglages de la simulation de la fenêtre de simulation*/
    QSlider *speedtime; /*! Barre de réglage de la vitesse*/
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
