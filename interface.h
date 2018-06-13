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

class MainWindow : public QWidget {
    Q_OBJECT
public slots:
    void changeForm(int index);
    void createGrid();
    void backToHome();
    void setLoadedAutomate();
public:
    MainWindow();
    ~MainWindow();
private:
    int Cellsize;
    QComboBox *typeAutomate, *generation;
    //QFileDialog *loadOtherAutomate;
    QFormLayout *newAutomate;
    QGridLayout *display, *mainLayout;
    QHBoxLayout *dimensions, *header;
    QHeaderView *VHeader, *HHeader;
    QLabel *displayTitle, *timesDimensions, *generalTitle, *toolsInfo;
    QPushButton *submit, *backHomeButton, *loadOtherAutomate, *quit;
    QSpinBox *dimensionH, *dimensionL;
    QStackedLayout *disp;
    QTableWidget *grid;
    QTextEdit *rules;
    QVBoxLayout *tools, *bigGridLayout;
    QWidget *home, *gridWidget;
};

int _interface(int argc, char* argv[]);

#endif
