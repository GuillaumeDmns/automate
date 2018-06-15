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
#include <iostream>
#include <unistd.h>
#include <QTimer>
#include "interface.h"
#include <QTimer>


int MainWindow::Gridsize = 400;
const int dimensionMin=10;
const int dimensionMax=150;


void MainWindow::changeCell(int row, int colomn) {
    if(!simu->getNumEtat()){
        simu->setValueDepart(colomn, row, (simu->getValueCurrent(colomn, row)+1)%simu->getAutomate()->getNbEtats());
        afficheGrid();
    }
}

void MainWindow::stopGrid() {
    timer->stop();
    stop->setHidden(true);
    play->setHidden(false);
    next->setDisabled(false);
    save->setDisabled(false);
    reset->setDisabled(false);
    speedtime->setDisabled(false);
    backHomeButton->setDisabled(false);
}

void MainWindow::playGrid() {
    timer->start(speedtime->maximum()+speedtime->minimum()-speedtime->value());
    play->setHidden(true);
    stop->setHidden(false);
    next->setDisabled(true);
    save->setDisabled(true);
    reset->setDisabled(true);
    speedtime->setDisabled(true);
    backHomeButton->setDisabled(true);
}

void MainWindow::resetGrid() {
    simu->reset();
    afficheGrid();
    counter->setText(QString::number(static_cast<int>(simu->getNumEtat())));
}

void MainWindow::createGrid() {
    unsigned int rule[6];
    rule[0]=0;
    rule[1]=minRenait->value();
    rule[2]=maxRenait->value();
    rule[3]=1;
    rule[4]=minVit->value();
    rule[5]=maxVit->value();
    simu = new Simulateur(typeAutomate->currentText().toStdString(),rule,generation->currentText().toStdString(),dimensionL->value(),dimensionH->value());
    grid->setRowCount(dimensionH->value());
    grid->setColumnCount(dimensionL->value());
    grid->setFixedSize(dimensionL->value()*(Gridsize/dimensionL->value()), dimensionH->value()*(Gridsize/dimensionH->value()));
    for(int row=0; row<dimensionH->value(); row++){
        grid->setRowHeight(row, Gridsize/dimensionH->value());
        for(int col=0; col<dimensionL->value(); col++){
            grid->setColumnWidth(col, Gridsize/dimensionL->value());
            grid->setItem(row, col, new QTableWidgetItem(""));
        }
    }
    afficheGrid();
    disp->setCurrentWidget(gridWidget);

    counterLabel->setHidden(false);
    counter->setHidden(false);
    toolsInfo->setHidden(true);
    toolsInfo2->setHidden(true);
    toolsInfo3->setHidden(true);
    loadOtherAutomate->setHidden(true);
    next->setHidden(false);
    play->setHidden(false);
    reset->setHidden(false);
    save->setHidden(false);
    speedtime->setHidden(false);

}

void MainWindow::backToHome() {
    delete simu;
    disp->setCurrentWidget(home);
    for(int row=0; row<dimensionH->value(); row++){
        for(int col=0; col<dimensionL->value(); col++){
            delete grid->item(row, col);
        }
    }

    counterLabel->setHidden(true);
    counter->setHidden(true);
    next->setHidden(true);
    reset->setHidden(true);
    play->setHidden(true);
    save->setHidden(true);
    speedtime->setHidden(true);
    toolsInfo->setHidden(false); // gérer selon les différents cas !
    loadOtherAutomate->setHidden(false);
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
        //rules->setText(text);
    }
    else {
        text = "Le fichier n'a pas pu être ouvert !";
    }
}

void MainWindow::changeForm(int index) {
    switch (index) {
    case 0:
       toolsInfo->setHidden(false);
       toolsInfo2->setHidden(true);
       toolsInfo3->setHidden(true);
       timesDimensions->setHidden(true);
       dimensionH->setHidden(true);
       dimensionH->setMinimum(1);
       dimensionH->setValue(1);
       dimensionH->setMaximum(1);
       minRenait->setMinimum(0);
       minRenait->setMaximum(2);
       maxRenait->setMinimum(0);
       maxRenait->setMaximum(2);
       minVit->setMinimum(0);
       minVit->setMaximum(2);
       maxVit->setMinimum(0);
       maxVit->setMaximum(2);
       minRenait->setEnabled(true);
       maxRenait->setEnabled(true);
       minVit->setEnabled(true);
       maxVit->setEnabled(true);
       minRenait->setValue(1);
       maxRenait->setValue(1);
       minVit->setValue(1);
       maxVit->setValue(1);
        break;
    case 1:
        toolsInfo->setHidden(true);
        toolsInfo2->setHidden(false);
        toolsInfo3->setHidden(true);
        timesDimensions->setHidden(false);
        dimensionH->setHidden(false);
        dimensionH->setMinimum(dimensionMin);
        dimensionH->setMaximum(dimensionMax);
        dimensionH->setValue(25);
        minRenait->setMinimum(0);
        minRenait->setMaximum(8);
        maxRenait->setMinimum(0);
        maxRenait->setMaximum(8);
        minVit->setMinimum(0);
        minVit->setMaximum(8);
        maxVit->setMinimum(0);
        maxVit->setMaximum(8);
        minRenait->setEnabled(true);
        maxRenait->setEnabled(true);
        minVit->setEnabled(true);
        maxVit->setEnabled(true);
        maxRenait->setValue(3);
        maxVit->setValue(3);
        minRenait->setValue(3);
        minVit->setValue(2);
        break;
    case 2:
        toolsInfo->setHidden(true);
        toolsInfo2->setHidden(true);
        toolsInfo3->setHidden(false);
        timesDimensions->setHidden(false);
        dimensionH->setHidden(false);
        dimensionH->setMinimum(dimensionMin);
        dimensionH->setMaximum(dimensionMax);
        dimensionH->setValue(25);
        minRenait->setEnabled(false);
        maxRenait->setEnabled(false);
        minVit->setEnabled(false);
        maxVit->setEnabled(false);
        break;
    default:
        break;
    }
}

void MainWindow::nextEtat() {
    simu->next();
    afficheGrid();
    counter->setText(QString::number(static_cast<int>(simu->getNumEtat())));
}

void MainWindow::checkRules(){
    minRenait->setMaximum(maxRenait->value());
    maxRenait->setMinimum(minRenait->value());
    minVit->setMaximum(maxVit->value());
    maxVit->setMinimum(minVit->value());
}

void MainWindow::afficheGrid() {
    for(int row=0; row<dimensionH->value(); row++){
        for(int col=0; col<dimensionL->value(); col++){
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
        }
    }
    counter->setText(QString::number(static_cast<int>(simu->getNumEtat())));
}

MainWindow::MainWindow():QWidget() {
    QFont bigTitle("Arial", 30, QFont::Bold);
    QFont subTitle("Arial", 20, QFont::Bold);
    timer = new QTimer(this);
            displayTitle = new QLabel("Créer un automate");
            displayTitle->setFont(subTitle);
            typeAutomate = new QComboBox;
            typeAutomate->addItem("Vie 1D");
            typeAutomate->addItem("Vie 2D");
            typeAutomate->addItem("Feu de forêt");
                    dimensionL = new QSpinBox;
                    dimensionL->setMinimum(dimensionMin);
                    dimensionL->setMaximum(dimensionMax);
                    dimensionL->setValue(25);
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
                    minR = new QLabel("min");
                    minRenait = new QSpinBox;
                    minRenait->setMinimum(0);
                    minRenait->setMaximum(2);
                    minRenait->setValue(1);
                    maxR = new QLabel("max");
                    maxRenait = new QSpinBox;
                    maxRenait->setMinimum(0);
                    maxRenait->setMaximum(2);
                    maxRenait->setValue(1);
                    minV = new QLabel("min");
                    minVit = new QSpinBox;
                    minVit->setMinimum(0);
                    minVit->setMaximum(2);
                    minVit->setValue(1);
                    maxV = new QLabel("max");
                    maxVit = new QSpinBox;
                    maxVit->setMinimum(0);
                    maxVit->setMaximum(2);
                    maxVit->setValue(1);
                rulesRenait = new QHBoxLayout;
                rulesRenait->addWidget(minR);
                rulesRenait->addWidget(minRenait);
                rulesRenait->addWidget(maxR);
                rulesRenait->addWidget(maxRenait);
                rulesVit = new QHBoxLayout;
                rulesVit->addWidget(minV);
                rulesVit->addWidget(minVit);
                rulesVit->addWidget(maxV);
                rulesVit->addWidget(maxVit);
                generation = new QComboBox;
                generation->addItem("Grille vide");
                generation->addItem("Remplissage aléatoire");
                generation->addItem("Remplissage symétrique");
            newAutomate = new QFormLayout;
            newAutomate->addRow("Type d'automate", typeAutomate);
            newAutomate->addRow("Dimensions", dimensions);
            newAutomate->addRow("Nombre de voisins \n pour renaître", rulesRenait);
            newAutomate->addRow("Nombre de voisins \n pour rester vivant", rulesVit);
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
            loadOtherAutomate = new QPushButton("Charger un automate");
            counterLabel = new QLabel("Génération ");
            counterLabel->setHidden(true);
            counter = new QLabel("0");
            counter->setHidden(true);
            toolsInfo = new QLabel("<b>Qu'est-ce que l'automate Cell1D ?</b> <br /> Cet automate permet de simuler un <br /> automate cellulaire en une dimension !");
            toolsInfo2 = new QLabel("<b>Qu'est-ce que l'automate JeuDeLaVie ?</b> <br /> Cet automate permet de simuler un <br />automate cellulaire en 2 dimensions !");
            toolsInfo2->setHidden(true);
            toolsInfo3 = new QLabel("<b>Qu'est-ce que l'automate FeuDeForet ?</b> <br /> Cet Automate rend hommage à la pyromanie de Solène !");
            toolsInfo3->setHidden(true);
            next = new QPushButton("Next");
            next->setHidden(true);
            reset = new QPushButton("Reset");
            reset->setHidden(true);
            play = new QPushButton("Play");
            play->setHidden(true);
            stop = new QPushButton("Stop");
            stop->setHidden(true);
            save = new QPushButton("Save");
            save->setHidden(true);
            speedtime = new QSlider(Qt::Horizontal);
            speedtime->setMinimum(20);
            speedtime->setMaximum(2000);
            speedtime->setValue(500);
            speedtime->setHidden(true);
        tools = new QVBoxLayout;
        tools->addWidget(counterLabel, 0, Qt::AlignCenter);
        tools->addWidget(counter, 0, Qt::AlignCenter);
        tools->addWidget(toolsInfo, 0, Qt::AlignCenter);
        tools->addWidget(toolsInfo2, 0, Qt::AlignCenter);
        tools->addWidget(toolsInfo3, 0, Qt::AlignCenter);
        tools->addWidget(loadOtherAutomate, 0, Qt::AlignCenter);
        tools->addWidget(next, 0, Qt::AlignCenter);
        tools->addWidget(play, 0, Qt::AlignCenter);
        tools->addWidget(stop, 0, Qt::AlignCenter);
        tools->addWidget(speedtime, 0, Qt::AlignCenter);
        tools->addWidget(reset, 0, Qt::AlignCenter);
        tools->addWidget(save, 0, Qt::AlignCenter);
        tools->addWidget(quit, 0, Qt::AlignBottom|Qt::AlignRight);
                grid = new QTableWidget(dimensionH->value(), dimensionL->value());
                grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                grid->setSelectionMode(QAbstractItemView::NoSelection);
                grid->horizontalHeader()->setVisible(false);
                grid->verticalHeader()->setVisible(false);
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

    /* Tous les connects */
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(next, SIGNAL(clicked()), this, SLOT(nextEtat()));
    connect(submit, SIGNAL(clicked()), this, SLOT(createGrid()));
    connect(reset, SIGNAL(clicked()), this, SLOT(resetGrid()));
    connect(backHomeButton, SIGNAL(clicked()), this, SLOT(backToHome()));
    connect(loadOtherAutomate, SIGNAL(clicked()), this, SLOT(setLoadedAutomate()));
    connect(typeAutomate, SIGNAL(currentIndexChanged(int)), this, SLOT(changeForm(int)));
    connect(play, SIGNAL(clicked()), this, SLOT(playGrid()));
    connect(stop, SIGNAL(clicked()), this, SLOT(stopGrid()));
    connect(grid, SIGNAL(cellClicked(int,int)), this, SLOT(changeCell(int, int)));
    connect(minRenait, SIGNAL(valueChanged(int)), this, SLOT(checkRules()));
    connect(maxRenait, SIGNAL(valueChanged(int)), this, SLOT(checkRules()));
    connect(minVit, SIGNAL(valueChanged(int)), this, SLOT(checkRules()));
    connect(maxVit, SIGNAL(valueChanged(int)), this, SLOT(checkRules()));  
    connect(timer, SIGNAL(timeout()), this, SLOT(nextEtat()));
}

MainWindow::~MainWindow() {
    delete typeAutomate;
    delete generation;
    delete newAutomate;
    delete display;
    delete mainLayout;
    delete dimensions;
    delete header;
    delete rulesRenait;
    delete rulesVit;
    delete VHeader;
    delete HHeader;
    delete displayTitle;
    delete timesDimensions;
    delete generalTitle;
    delete toolsInfo;
    delete toolsInfo2;
    delete toolsInfo3;
    delete counter;
    delete counterLabel;
    delete minR;
    delete maxR;
    delete minV;
    delete maxV;
    delete submit;
    delete backHomeButton;
    delete loadOtherAutomate;
    delete quit;
    delete next;
    delete reset;
    delete save;
    delete stop;
    delete play;
    delete simu;
    delete dimensionH;
    delete dimensionL;
    delete minRenait;
    delete maxRenait;
    delete minVit;
    delete maxVit;
    delete disp;
    delete grid;
    delete timer;
    delete tools;
    delete bigGridLayout;
    delete home;
    delete gridWidget;
    delete speedtime;
}

/*!
    * \fn int _interface(int argc, char * argv[])
    * \brief Programme d'affichage de l'interface
    *
    * \param int argc :
    * \param char* argv[] :
    *
    * \return int
    *
    */
int _interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    /* CREATION ET PARAMETRAGE DE LA FENETRE */


    MainWindow fenetre;
    int widthMax(800), heightMax(600);
    fenetre.setFixedSize(widthMax, heightMax);


    fenetre.show();
    return app.exec();
}



