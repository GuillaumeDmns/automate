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
    void setLoadedAutomate();
public:
    MainWindow();
private:
    QComboBox *typeAutomate, *generation;
    //QFileDialog *loadOtherAutomate;
    QFormLayout *newAutomate;
    QGridLayout *display, *mainLayout;
    QHBoxLayout *dimensions, *header;
    QLabel *displayTitle, *timesDimensions, *generalTitle, *toolsInfo;
    QPushButton *submit, *submit2, *loadLastAutomate, *loadOtherAutomate, *quit;
    QSpinBox *dimensionH, *dimensionL;
    QStackedLayout *disp;
    QTextEdit *rules;
    QVBoxLayout *loadAutomate, *tools;
    QWidget *home;
};

int _interface(int argc, char* argv[]);

#endif
