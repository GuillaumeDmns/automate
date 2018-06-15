/*!
    * \file interface.cpp
    * \brief Définition des méthodes et fonctions de l'interface
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 28 mai 2018
    *
    * \details Programme pour définir les fonctions et les méthodes non inline relatives à l'interface graphique
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
#include <QTableWidget>
#include "interface.h"
#include <iostream>

int MainWindow::Gridsize = 400;
const int dimensionMin=10;
const int dimensionMax=100;

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
    unsigned int rule[6] = {0,1,2,1,1,1};
    simu = new Simulateur(typeAutomate->currentText().toStdString(),rule,generation->currentText().toStdString(),dimensionL->value(),dimensionH->value());
    grid->setRowCount(dimensionH->value());
    grid->setColumnCount(dimensionL->value());
    grid->setFixedSize(dimensionH->value()*(Gridsize/dimensionH->value()), dimensionL->value()*(Gridsize/dimensionL->value()));
    for(int row=0; row<dimensionH->value(); row++){
        grid->setRowHeight(row, Gridsize/dimensionH->value());
        for(int col=0; col<dimensionL->value(); col++){
            grid->setColumnWidth(col, Gridsize/dimensionL->value());
            grid->setItem(row, col, new QTableWidgetItem(""));
            switch(simu->getValueCurrent(col, row)){
            case 0 :
                grid->item(row, col)->setBackgroundColor("white");
                grid->item(row, col)->setTextColor("white");
                break;
            case 1 :
                grid->item(row, col)->setBackgroundColor("green");
                grid->item(row, col)->setTextColor("green");
                break;
            case 2 :
                grid->item(row, col)->setBackgroundColor("red");
                grid->item(row, col)->setTextColor("red");
                break;
            case 3 :
                grid->item(row, col)->setBackgroundColor("black");
                grid->item(row, col)->setTextColor("black");
                break;
            default :
                grid->item(row, col)->setBackgroundColor("black");
                grid->item(row, col)->setTextColor("black");
                break;
            }
            /* if ((row+col)%2 == 0) {
                grid->item(row, col)->setBackgroundColor("white");
                grid->item(row, col)->setTextColor("white");
            }
            else {
                grid->item(row, col)->setBackgroundColor("black");
                grid->item(row, col)->setTextColor("black");
            }*/
        }
    }
    disp->setCurrentWidget(gridWidget);
}

void MainWindow::backToHome() {
    delete simu;
    disp->setCurrentWidget(home);
    for(int row=0; row<dimensionH->value(); row++){
        for(int col=0; col<dimensionL->value(); col++){
            delete grid->item(row, col);
        }
    }
}

void MainWindow::setLoadedAutomate() {
    const QString& PathLoadAutomate = QFileDialog::getOpenFileName(this, "test", QDir::currentPath(), "Texte (*.txt)");
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

void MainWindow::changeForm(int index) {
    switch (index) {
    case 0:
       timesDimensions->setHidden(true);
       dimensionH->setHidden(true);
       dimensionH->setMinimum(1);
       dimensionH->setMaximum(1);
        break;
    default:
        timesDimensions->setHidden(false);
        dimensionH->setHidden(false);
        dimensionH->setMinimum(dimensionMin);
        dimensionH->setMaximum(dimensionMax);
        break;
    }
}

MainWindow::MainWindow():QWidget() {
    QFont bigTitle("Arial", 30, QFont::Bold);
    QFont subTitle("Arial", 20, QFont::Bold);

            displayTitle = new QLabel("Créer un automate");
            displayTitle->setFont(subTitle);
            typeAutomate = new QComboBox;
            typeAutomate->addItem("Vie 1D");
            typeAutomate->addItem("Vie 2D");
            typeAutomate->addItem("Feu de forêt");
                    dimensionL = new QSpinBox;
                    dimensionL->setMinimum(dimensionMin);
                    dimensionL->setMaximum(dimensionMax);
                    timesDimensions = new QLabel("x");
                    timesDimensions->setHidden(true);
                    dimensionH = new QSpinBox;
                    dimensionH->setMinimum(1);
                    dimensionH->setMaximum(1);
                    dimensionH->setHidden(true);
                dimensions = new QHBoxLayout;
                dimensions->addWidget(dimensionL);
                dimensions->addWidget(timesDimensions, 0, Qt::AlignCenter);
                dimensions->addWidget(dimensionH);
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
            backHomeButton = new QPushButton("Retour");
        display = new QGridLayout;
        display->addWidget(displayTitle, 0, 0, 1, 5, Qt::AlignCenter);
        display->addLayout(newAutomate, 1, 0, 5, 5, Qt::AlignCenter);
        display->addWidget(submit, 6, 0, 1, 5, Qt::AlignCenter);
        home = new QWidget;
        home->setLayout(display);
            generalTitle = new QLabel("AUTOCELL");
            generalTitle->setFont(bigTitle);
        header = new QHBoxLayout;
        header->addWidget(generalTitle, 1, Qt::AlignCenter);
            quit = new QPushButton("Quitter");
            loadOtherAutomate = new QPushButton("Charger un autre automate");
            toolsInfo = new QLabel("Qu'est-ce qu'un automate cellulaire ?");
        tools = new QVBoxLayout;
        tools->addWidget(toolsInfo, 0, Qt::AlignCenter);
        tools->addWidget(loadOtherAutomate, 0, Qt::AlignCenter);
        tools->addWidget(quit, 0, Qt::AlignBottom|Qt::AlignRight);
                grid = new QTableWidget(dimensionH->value(), dimensionL->value());
                grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                grid->horizontalHeader()->setVisible(false);
                grid->verticalHeader()->setVisible(false);
                //grid->setFixedSize(Gridsize, Gridsize);
                grid->setEditTriggers(QAbstractItemView::NoEditTriggers);
            bigGridLayout = new QVBoxLayout;
            bigGridLayout->addWidget(grid, 1, Qt::AlignCenter);
            bigGridLayout->addWidget(backHomeButton, 1, Qt::AlignCenter);
        gridWidget = new QWidget;
        gridWidget->setLayout(bigGridLayout);

    mainLayout = new QGridLayout;

    disp = new QStackedLayout;
    disp->insertWidget(0, home);
    disp->insertWidget(1, gridWidget);
    mainLayout->addLayout(disp, 1, 0, 4, 4);
    mainLayout->addLayout(header, 0, 0, 1, 5);
    mainLayout->addLayout(tools, 1, 4, 4, 1);
    setLayout(mainLayout);
    setWindowTitle("AUTOCELL");
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    connect(submit, SIGNAL(clicked()), this, SLOT(createGrid()));
    connect(backHomeButton, SIGNAL(clicked()), this, SLOT(backToHome()));
    connect(loadOtherAutomate, SIGNAL(clicked()), this, SLOT(setLoadedAutomate()));
    connect(typeAutomate, SIGNAL(currentIndexChanged(int)), this, SLOT(changeForm(int)));
}

MainWindow::~MainWindow() {

}

int _interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    /* CREATION ET PARAMETRAGE DE LA FENETRE */


    MainWindow fenetre;
    int widthMax(800), heightMax(600);
    fenetre.setFixedSize(widthMax, heightMax);






    fenetre.show();
    return app.exec();
}



