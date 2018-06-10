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
#include <QStackedLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <sstream>
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

void MainWindow::createGrid() {
    disp->setCurrentWidget(submit2);

}

void MainWindow::backToHome() {
    disp->setCurrentWidget(home);
}

void MainWindow::setLoadedAutomate() {
    const QString& PathLoadAutomate = QFileDialog::getOpenFileName(this, "test", QDir::homePath(), "Texte (*.txt)");
    //rules->setText(PathLoadAutomate);
    QFile loadedFile(PathLoadAutomate);
    QString text, tempText;
    if (loadedFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream flux(&loadedFile);
        unsigned int getParamAutomate = 0;

        while (!flux.atEnd()) {
            tempText = flux.readLine();
            switch (getParamAutomate) {
            case 0: // type d'automate
                typeAutomate->setCurrentIndex(tempText.toInt());
                break;
            case 1: // hauteur
                dimensionH->setValue(tempText.toInt());
                break;
            case 2: // largeur
                dimensionL->setValue(tempText.toInt());
                break;
            default:
                text += tempText + '\n';
                break;
            }
            ++getParamAutomate;
        }
        loadedFile.close();
        rules->setText(text);
    }
    else {
        text = "Le fichier n'a pas pu être ouvert !";
    }
}

MainWindow::MainWindow():QWidget() {
    //int widthMax(1200), heightMax(800);
    int dimensionMin(10), dimensionMax(100);
    QFont bigTitle("Arial", 30, QFont::Bold);
    QFont subTitle("Arial", 20, QFont::Bold);

            displayTitle = new QLabel("Créer un automate");
            displayTitle->setFont(subTitle);
            typeAutomate = new QComboBox;
            typeAutomate->addItem("Vie 1D");
            typeAutomate->addItem("Vie 2D");
            typeAutomate->addItem("Feu de forêt");
                    dimensionH = new QSpinBox;
                    dimensionH->setMinimum(dimensionMin);
                    dimensionH->setMaximum(dimensionMax);
                    timesDimensions = new QLabel("x");
                    dimensionL = new QSpinBox;
                    dimensionL->setMinimum(dimensionMin);
                    dimensionL->setMaximum(dimensionMax);
                dimensions = new QHBoxLayout;
                dimensions->addWidget(dimensionH);
                dimensions->addWidget(timesDimensions, 0, Qt::AlignCenter);
                dimensions->addWidget(dimensionL);
                rules = new QTextEdit;
                generation = new QComboBox;
                generation->addItem("Grille vide");
                generation->addItem("Remplissage aléatoire");
                generation->addItem("Remplissage symétrique");
            newAutomate = new QFormLayout;
            newAutomate->addRow("Type d'automate", typeAutomate);
            newAutomate->addRow("Dimensions", dimensions);
            newAutomate->addRow("Règles", rules);
            newAutomate->addRow("Génération", generation);
            submit = new QPushButton("Valider");
                loadLastAutomate = new QPushButton("Charger le dernier automate");
                loadOtherAutomate = new QPushButton("Charger un autre automate");
                //
            loadAutomate = new QVBoxLayout;
            loadAutomate->addWidget(loadLastAutomate, 1, Qt::AlignCenter);
            loadAutomate->addWidget(loadOtherAutomate, 1, Qt::AlignCenter);
        display = new QGridLayout;
        display->addWidget(displayTitle, 0, 0, 1, 5, Qt::AlignCenter);
        display->addLayout(loadAutomate, 1, 4, 6, 1, Qt::AlignCenter);
        display->addLayout(newAutomate, 1, 0, 5, 4, Qt::AlignCenter);
        display->addWidget(submit, 6, 0, 1, 4, Qt::AlignCenter);
        home = new QWidget;
        home->setLayout(display);
            generalTitle = new QLabel("AUTOCELL");
            generalTitle->setFont(bigTitle);
        header = new QHBoxLayout;
        header->addWidget(generalTitle, 1, Qt::AlignCenter);
            quit = new QPushButton("Quitter");
            toolsInfo = new QLabel("Qu'est-ce qu'un automate cellulaire ?");
        tools = new QVBoxLayout;
        tools->addWidget(toolsInfo, 0, Qt::AlignCenter);
        tools->addWidget(quit, 0, Qt::AlignBottom|Qt::AlignRight);

    mainLayout = new QGridLayout;

    disp = new QStackedLayout;
    disp->insertWidget(0, home);
    mainLayout->addLayout(disp, 1, 0, 4, 4);
    mainLayout->addLayout(header, 0, 0, 1, 5);
    mainLayout->addLayout(tools, 1, 4, 4, 1);
    setLayout(mainLayout);
    setWindowTitle("AUTOCELL");
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    submit2 = new QPushButton("PRANK ! CLIQUER POUR REVENIR EN ARRIERE");
    disp->insertWidget(1, submit2);
    connect(submit, SIGNAL(clicked()), this, SLOT(createGrid()));
    connect(submit2, SIGNAL(clicked()), this, SLOT(backToHome()));
    connect(loadOtherAutomate, SIGNAL(clicked()), this, SLOT(setLoadedAutomate()));
}


int _interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    /* CREATION ET PARAMETRAGE DE LA FENETRE */


    MainWindow fenetre;
    //fenetre.setFixedSize(widthMax, heightMax);






    fenetre.show();
    return app.exec();
}



