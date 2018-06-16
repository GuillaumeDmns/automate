/*!
    * \file interface.cpp
    * \brief Définition des méthodes et fonctions de l'interface
    * \author Guillaume Damiens, Solène Houlliez, Oscar Roisin
    * \version 0.1
    * \date 16 juin 2018
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
#include <fstream>

//Definition des attributs static
int MainWindow::Gridsize = 400;
const int dimensionMin=10;
const int dimensionMax=150;

/*!
 * \fn void MainWindow::changeCell(int row, int colomn)
 * \brief Permet de changer la valeur (c'est-à-dire l'état) d'une cellule dont la position est fournie en paramètre
 *
 * \param int row : Numéro de la ligne
 * \param int colomn : Numéro de la colonne
 * \return void
 */
void MainWindow::changeCell(int row, int colomn) {
    if(!simu->getNumEtat()){
        simu->setValueDepart(colomn, row, (simu->getValueCurrent(colomn, row)+1)%simu->getAutomate()->getNbEtats());
        afficheGrid();
    }
}

/*!
 * \fn void MainWindow::stopGrid()
 * \brief Permet d'arrêter la simulation en cours
 *
 * \return void
 */
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

/*!
 * \fn void MainWindow::playGrid()
 * \brief Permet de lancer la simulation de l'automate simulé
 *
 * \return void
 */
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

/*!
 * \fn void MainWindow::resetGrid()
 * \brief Permet de revenir dans la situation initiale de la simulation
 *
 * \return void
 */
void MainWindow::resetGrid() {
    simu->reset();
    afficheGrid();
    counter->setText(QString::number(static_cast<int>(simu->getNumEtat())));
}

/*!
 * \fn void MainWindow::createGrid()
 * \brief Permet la création de la grille
 *
 * \return void
 */
void MainWindow::createGrid() {
    grid->setRowCount(dimensionH->value());
    grid->setColumnCount(dimensionL->value());
    if(simu->getAutomate()->getNbDim() == 1) grid->setFixedSize(dimensionL->value()*(Gridsize/dimensionL->value()), 25);
    else grid->setFixedSize(dimensionL->value()*(Gridsize/dimensionL->value()), dimensionH->value()*(Gridsize/dimensionH->value()));
    for(int row=0; row<dimensionH->value(); row++){
        if (simu->getAutomate()->getNbDim() == 1) grid->setRowHeight(row, 25);
        else grid->setRowHeight(row, Gridsize/dimensionH->value());
        for(int col=0; col<dimensionL->value(); col++){
            grid->setColumnWidth(col, Gridsize/dimensionL->value());
            grid->setItem(row, col, new QTableWidgetItem(""));
        }
    }
    afficheGrid();
    disp->setCurrentWidget(gridWidget);
    toolsStacked->setCurrentWidget(toolsWidgetRun);
}

/*!
 * \fn void MainWindow::backToHome()
 * \brief Permet le retour à la page d'Accueil
 *
 * \return void
 */
void MainWindow::backToHome() {
    delete simu;
    disp->setCurrentWidget(home);
    toolsStacked->setCurrentWidget(toolsWidgetHome);
    for(int row=0; row<dimensionH->value(); row++){
        for(int col=0; col<dimensionL->value(); col++){
            delete grid->item(row, col);
        }
    simu=nullptr;
    }
}

/*!
 * \fn void MainWindow::setLoadedAutomate()
 * \brief Permet de charger un automate pré-existant
 *
 * \return void
 */
void MainWindow::setLoadedAutomate() {
    QString PathLoadAutomate = QFileDialog::getOpenFileName(this, tr("Load Simulation"),"simulation.csv",tr("Data (*.csv)"));
    char delim;
    ifstream file;
    file.open(PathLoadAutomate.toStdString());
    if(file.is_open()){
        unsigned int numEtat;
        file >> numEtat;
        string idA;
        file >> idA;
        unsigned int nbEtats;
        file >> nbEtats;
        file >> delim;
        unsigned int tailleRegle;
        file >> tailleRegle;
        unsigned int** a = new unsigned int*[nbEtats];
        for(unsigned int i=0; i<nbEtats; ++i){
            a[i]=new unsigned int[tailleRegle+1];
            for(unsigned int j=0; j<=tailleRegle; ++j){
                file >> a[i][j];
                file >> delim;
            }
        }
        string idE;
        file >> idE;
        unsigned int dimN, dimM;
        file >> dimN;
        file >> delim;
        file >> dimM;
        if(dimM){
            unsigned int** dep = new unsigned int*[dimN];
            for(unsigned int i=0; i<dimN; ++i){
                dep[i]=new unsigned int[dimM];
                for(unsigned int j=0; j<dimM; ++j){
                    file >> dep[i][j];
                    file >> delim;
                }
            }
            file >> delim;
            unsigned int** cur = new unsigned int*[dimN];
            for(unsigned int i=0; i<dimN; ++i){
                cur[i]=new unsigned int[dimM];
                for(unsigned int j=0; j<dimM; ++j){
                    file >> cur[i][j];
                    file >> delim;
                }
            }
            simu = new Simulateur(idA,const_cast<const unsigned int**>(a),dimN,dimM,numEtat,const_cast<const unsigned int**>(dep),const_cast<const unsigned int**>(cur));
            for(unsigned int i=0; i<dimN;++i){
                delete dep[i];
                delete cur[i];
            }
            delete dep;
            delete cur;
        }else{
            dimM++;
            unsigned int* dep = new unsigned int[dimN];
            for(unsigned int i=0; i<dimN; ++i){
                file >> dep[i];
                file >> delim;
            }
            file >> delim;
            unsigned int* cur = new unsigned int[dimN];
            for(unsigned int i=0; i<dimN; ++i){
                file >> cur[i];
                file >> delim;
            }
            simu = new Simulateur(idA,const_cast<const unsigned int**>(a),dimN,numEtat,const_cast<const unsigned int*>(dep),const_cast<const unsigned int*>(cur));
            delete dep;
            delete cur;
        }
        delete a;

        dimensionH->setMinimum(dimensionMin);
        dimensionH->setMaximum(dimensionMax);
        dimensionH->setValue(dimM);
        dimensionL->setMinimum(dimensionMin);
        dimensionL->setMaximum(dimensionMax);
        dimensionL->setValue(dimN);
        createGrid();
    }
    file.close();
}

/*!
 * \fn void MainWindow::validAuto()
 * \brief Crée l'automate pour la simulation
 *
 * \return void
 */
void MainWindow::validAuto(){
    unsigned int rule[6];
    rule[0]=0;
    rule[1]=minRenait->value();
    rule[2]=maxRenait->value();
    rule[3]=1;
    rule[4]=minVit->value();
    rule[5]=maxVit->value();
    simu = new Simulateur(typeAutomate->currentText().toStdString(),rule,generation->currentText().toStdString(),dimensionL->value(),dimensionH->value());
    createGrid();
}

/*!
 * \fn void MainWindow::changeForm(int index)
 * \brief Permet de changer l'affichage en fonction des caractéristiques de l'automate simulé
 *
 * \param int index : Choix de l'automate à simuler
 * \return void
 */
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

/*!
 * \fn void MainWindow::nextEtat()
 * \brief Permet le passage à l'état suivant de l'automate simulé
 *
 * \return void
 */
void MainWindow::nextEtat() {
    simu->next();
    afficheGrid();
    counter->setText(QString::number(static_cast<int>(simu->getNumEtat())));
}

/*!
 * \fn void MainWindow::checkRules()
 * \brief Récupère les règles pour la simulation
 *
 * \return void
 */
void MainWindow::checkRules(){
    minRenait->setMaximum(maxRenait->value());
    maxRenait->setMinimum(minRenait->value());
    minVit->setMaximum(maxVit->value());
    maxVit->setMinimum(minVit->value());
}

/*!
 * \fn void MainWindow::afficheGrid()
 * \brief Permet l'affichage de la grille
 *
 * \return void
 */
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

/*!
 * \fn void MainWindow::saveSimu()
 * \brief Permet de sauvegarder la simulation courante
 *
 * \return void
 */
void MainWindow::saveSimu(){
    QString PathSaveSimu = QFileDialog::getSaveFileName(this, tr("Save Simulation"),"simulation.csv",tr("Data (*.csv)"));
    simu->save(PathSaveSimu.toStdString());
}

/*!
 * \fn MainWindow::MainWindow()
 * \brief Constructeur de la classe MainWindow
 *
 */
MainWindow::MainWindow():QWidget() {
    simu = nullptr;
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
            counter = new QLabel("0");
            toolsInfo = new QLabel("<b>Qu'est-ce que l'automate Cell1D ?</b> <br /> Cet automate permet de simuler un <br /> automate cellulaire en une dimension. <br /> Il s'agit du jeu de la vie sur une ligne.");
            toolsInfo2 = new QLabel("<b>Qu'est-ce que l'automate JeuDeLaVie ?</b> <br /> Cet automate permet de simuler un <br />automate cellulaire en 2 dimensions ! <br /> Il est également appelé jeu de la vie.");
            toolsInfo2->setHidden(true);
            toolsInfo3 = new QLabel("<b>Qu'est-ce que l'automate FeuDeForet ?</b> <br /> Cet automate a été créé afin d'effectuer une <br /> simulation d'un feu de forêt quelconque !");
            toolsInfo3->setHidden(true);
            next = new QPushButton("Next");
            reset = new QPushButton("Reset");
            play = new QPushButton("Play");
            stop = new QPushButton("Stop");
            stop->setHidden(true);
            save = new QPushButton("Save");
            speedtime = new QSlider(Qt::Horizontal);
            speedtime->setMinimum(20);
            speedtime->setMaximum(2000);
            speedtime->setValue(500);
        toolsHome = new QVBoxLayout;
        toolsRun = new QVBoxLayout;
        toolsRun->addWidget(counterLabel, 0, Qt::AlignCenter);
        toolsRun->addWidget(counter, 0, Qt::AlignCenter);
        toolsHome->addWidget(toolsInfo, 0, Qt::AlignCenter);
        toolsHome->addWidget(toolsInfo2, 0, Qt::AlignCenter);
        toolsHome->addWidget(toolsInfo3, 0, Qt::AlignCenter);
        toolsHome->addWidget(loadOtherAutomate, 0, Qt::AlignCenter);
        toolsRun->addWidget(next, 0, Qt::AlignCenter);
        toolsRun->addWidget(play, 0, Qt::AlignCenter);
        toolsRun->addWidget(stop, 0, Qt::AlignCenter);
        toolsRun->addWidget(speedtime, 0, Qt::AlignCenter);
        toolsRun->addWidget(reset, 0, Qt::AlignCenter);
        toolsRun->addWidget(save, 0, Qt::AlignCenter);
        toolsHome->addWidget(quit, 0, Qt::AlignBottom|Qt::AlignRight);
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
        toolsWidgetHome = new QWidget;
        toolsWidgetHome->setLayout(toolsHome);
        toolsWidgetRun = new QWidget;
        toolsWidgetRun->setLayout(toolsRun);
        gridWidget = new QWidget;
        gridWidget->setLayout(bigGridLayout);
        disp = new QStackedLayout;
        disp->insertWidget(0, home);
        disp->insertWidget(1, gridWidget);
        toolsStacked = new QStackedLayout;
        toolsStacked->insertWidget(0, toolsWidgetHome);
        toolsStacked->insertWidget(1, toolsWidgetRun);

    mainLayout = new QGridLayout;
    mainLayout->addLayout(disp, 1, 0, 4, 4);
    mainLayout->addLayout(header, 0, 0, 1, 5);
    mainLayout->addLayout(toolsStacked, 1, 4, 4, 1);
    setLayout(mainLayout);
    setWindowTitle("AUTOCELL");

    /* Tous les connects */
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(next, SIGNAL(clicked()), this, SLOT(nextEtat()));
    connect(submit, SIGNAL(clicked()), this, SLOT(validAuto()));
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
    connect(save, SIGNAL(clicked()), this, SLOT(saveSimu()));
}

/*!
 * \fn MainWindow::~MainWindow()
 * \brief Destructeur de la classe MainWindow
 *
 */
MainWindow::~MainWindow() {

    if(simu!=nullptr) delete simu;
    delete timer;
    delete displayTitle;
    delete typeAutomate;
    delete dimensionL;
    delete timesDimensions;
    delete dimensionH;
    delete dimensions;
    delete minR;
    delete minRenait;
    delete maxR;
    delete maxRenait;
    delete minV;
    delete minVit;
    delete maxV;
    delete maxVit;
    delete rulesRenait;
    delete rulesVit;
    delete generation;
    delete newAutomate;
    delete submit;
    delete backHomeButton;
    delete display;
    delete home;
    delete generalTitle;
    delete header;
    delete quit;
    delete loadOtherAutomate;
    delete counterLabel;
    delete counter;
    delete toolsInfo;
    delete toolsInfo2;
    delete toolsInfo3;
    delete next;
    delete reset;
    delete play;
    delete stop;
    delete save;
    delete speedtime;
    delete toolsHome;
    delete toolsRun;
    delete grid;
    delete bigGridLayout;
    delete gridWidget;
    delete disp;
    delete toolsWidgetHome;
    delete toolsWidgetRun;
    delete toolsStacked;
    delete mainLayout;

}

/*!
    * \fn int _interface(int argc, char * argv[])
    * \brief Programme d'affichage de l'interface
    *
    * \param int argc : nombre d'arguments, récupéré de la fonction main()
    * \param char* argv[] : arguments, récupérés de la fonction main()
    *
    * \return int
    *
    */

int _interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    MainWindow fenetre;
    int widthMax(800), heightMax(600);
    fenetre.setFixedSize(widthMax, heightMax);

    fenetre.show();
    return app.exec();
}



