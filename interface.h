/*!
    * \file interface.h
    * \brief Déclaration des classes et fonctions de l'interface
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Programme pour déclarer les fonctions et les classes relatives à l'interface graphique
    *
    */


#if !defined(INTERFACE_H)
#define INTERFACE_H

#include <QtWidgets>

class MainWindow: public QWidget {
    Q_OBJECT
public slots:
    void createGrid();
    void backToHome();
public:
    MainWindow();
private:
    QLabel *displayTitle, *timesDimensions, *generalTitle, *toolsInfo;
    QComboBox *typeAutomate, *generation;
    QSpinBox *dimensionH, *dimensionL;
    QHBoxLayout *dimensions, *header;
    QTextEdit *rules;
    QFormLayout *newAutomate;
    QPushButton *submit, *submit2, *loadLastAutomate, *loadOtherAutomate, *quit;
    QVBoxLayout *loadAutomate, *tools;
    QGridLayout *display, *mainLayout;
    QWidget *home;
    QStackedLayout *disp;
};

int _interface(int argc, char* argv[]);

#endif
