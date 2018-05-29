/*!
    * \file interface.cpp
    * \brief Définition des méthodes et fonctions de l'interface
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Programme pour définir les fonctions et les méthodes relatives à l'interface graphique
    *
    */


#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QMessageBox>
#include "interface.h"


/*!
    * \fn int interface(int argc, char * argv[])
    * \brief Programme d'affichage de l'interface
    * 
    * \param int argc :
    * \param char* argv[] :
    *
    * \return app.exec() : execution de l'application de l'interface graphique
    *
    */
int interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    /* CREATION ET PARAMETRAGE DE LA FENETRE */
    int widthMax(1200), heightMax(800);
    int dimensionMin(10), dimensionMax(100);

    QWidget fenetre;
    //fenetre.setFixedSize(widthMax, heightMax);

    QFont bigTitle("Arial", 30, QFont::Bold);
    QFont subTitle("Arial", 20, QFont::Bold);

            QLabel *displayTitle = new QLabel("Créer un automate");
            displayTitle->setFont(subTitle);
            QComboBox *typeAutomate = new QComboBox;
            typeAutomate->addItem("Vie 1D");
            typeAutomate->addItem("Vie 2D");
            typeAutomate->addItem("Feu de forêt");
                    QSpinBox *dimensionH = new QSpinBox;
                    dimensionH->setMinimum(dimensionMin);
                    dimensionH->setMaximum(dimensionMax);
                    QLabel *timesDimensions = new QLabel("x");
                    QSpinBox *dimensionL = new QSpinBox;
                    dimensionL->setMinimum(dimensionMin);
                    dimensionL->setMaximum(dimensionMax);
                QHBoxLayout *dimensions = new QHBoxLayout;
                dimensions->addWidget(dimensionH);
                dimensions->addWidget(timesDimensions, 0, Qt::AlignCenter);
                dimensions->addWidget(dimensionL);
                QTextEdit *rules = new QTextEdit;
                QComboBox *generation = new QComboBox;
                generation->addItem("Grille vide");
                generation->addItem("Remplissage aléatoire");
                generation->addItem("Remplissage symétrique");
            QFormLayout *newAutomate = new QFormLayout;
            newAutomate->addRow("Type d'automate", typeAutomate);
            newAutomate->addRow("Dimensions", dimensions);
            newAutomate->addRow("Règles", rules);
            newAutomate->addRow("Génération", generation);
            QPushButton *submit = new QPushButton("Valider");
                QPushButton *loadLastAutomate = new QPushButton("Charger le dernier automate");
                QPushButton *loadOtherAutomate = new QPushButton("Charger un autre automate");
            QVBoxLayout *loadAutomate = new QVBoxLayout;
            loadAutomate->addWidget(loadLastAutomate, 1, Qt::AlignCenter);
            loadAutomate->addWidget(loadOtherAutomate, 1, Qt::AlignCenter);
        QGridLayout *display = new QGridLayout;
        display->addWidget(displayTitle, 0, 0, 1, 5, Qt::AlignCenter);
        display->addLayout(loadAutomate, 1, 4, 6, 1, Qt::AlignCenter);
        display->addLayout(newAutomate, 1, 0, 5, 4, Qt::AlignCenter);
        display->addWidget(submit, 6, 0, 1, 4, Qt::AlignCenter);
            QLabel *generalTitle = new QLabel("AUTOCELL");
            generalTitle->setFont(bigTitle);
        QHBoxLayout *header = new QHBoxLayout;
        header->addWidget(generalTitle, 1, Qt::AlignCenter);
            QPushButton *quit = new QPushButton("Quitter");
            QLabel *toolsInfo = new QLabel("Qu'est-ce qu'un automate cellulaire ?");
        QVBoxLayout *tools = new QVBoxLayout;
        tools->addWidget(toolsInfo, 0, Qt::AlignCenter);
        tools->addWidget(quit, 0, Qt::AlignBottom|Qt::AlignRight);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(display, 1, 0, 4, 4);
    mainLayout->addLayout(header, 0, 0, 1, 5);
    mainLayout->addLayout(tools, 1, 4, 4, 1);

    QObject::connect(quit, SIGNAL(clicked()), &app, SLOT(quit()));

    fenetre.setLayout(mainLayout);
    fenetre.setWindowTitle("AUTOCELL");
    fenetre.show();
    return app.exec();
}



