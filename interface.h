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

class MainWindow : public QWidget {
    Q_OBJECT
public slots:
    void changeForm(int index);
    void createGrid();
    void backToHome();
    void setLoadedAutomate();
    void nextEtat();
    void afficheGrid();
public:
    MainWindow();
    ~MainWindow();
private:
    Simulateur* simu;
    static int Gridsize;
    QComboBox *typeAutomate, *generation;
    //QFileDialog *loadOtherAutomate;
    QFormLayout *newAutomate;
    QGridLayout *display, *mainLayout;
    QHBoxLayout *dimensions, *header;
    QHeaderView *VHeader, *HHeader;
    QLabel *displayTitle, *timesDimensions, *generalTitle, *toolsInfo;
    QPushButton *submit, *backHomeButton, *loadOtherAutomate, *quit, *next, *reset, *save;
    QSpinBox *dimensionH, *dimensionL;
    QStackedLayout *disp;
    QTableWidget *grid;
    QTextEdit *rules;
    QVBoxLayout *tools, *bigGridLayout;
    QWidget *home, *gridWidget;
    QCheckBox *play;
};

/*!
    * \brief _interface
    * \details Programme d'affichage de l'interface
    *
    * \param int argc :
    * \param char* argv[] :
    *
    * \return int
    */
int _interface(int argc, char* argv[]);

#endif
