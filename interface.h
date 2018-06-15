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
    void afficheGrid();
    void backToHome();
    void changeCell(int row, int colomn);
    void changeForm(int index);
    void createGrid();
    void nextEtat();
    void playGrid();
    void resetGrid();
    void setLoadedAutomate();
    void stopGrid();
public:
    MainWindow();
    ~MainWindow();
private:

    QComboBox *typeAutomate, *generation;
    //QFileDialog *loadOtherAutomate;
    QFormLayout *newAutomate;
    QGridLayout *display, *mainLayout;
    QHBoxLayout *dimensions, *header;
    QHeaderView *VHeader, *HHeader;
    QLabel *displayTitle, *timesDimensions, *generalTitle, *toolsInfo, *toolsInfo2, *toolsInfo3, *counter, *counterLabel;
    QPushButton *submit, *backHomeButton, *loadOtherAutomate, *quit, *next, *reset, *save, *stop, *play;
    Simulateur* simu;
    QSpinBox *dimensionH, *dimensionL;
    QStackedLayout *disp;
    static int Gridsize;
    QTableWidget *grid;
    QTextEdit *rules;
    QVBoxLayout *tools, *bigGridLayout;
    QWidget *home, *gridWidget;

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
