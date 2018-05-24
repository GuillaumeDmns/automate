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
#include "interface.h"

int interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    /* CREATION ET PARAMETRAGE DE LA FENETRE */
    int widthMax(1200), heightMax(800);
    int dimensionMin(10), dimensionMax(100);

    QWidget fenetre;
    //fenetre.setFixedSize(widthMax, heightMax);

    QFont bigTitle("Arial", 30, QFont::Bold);
    QFont subTitle("Arial", 20, QFont::Bold);

            QLabel *displayTitle = new QLabel("Créer automate");
            displayTitle->setFont(subTitle);
            QComboBox *typeAutomate = new QComboBox;
            typeAutomate->addItem("Vie 1D");
            typeAutomate->addItem("Vie 2D");
            typeAutomate->addItem("Feu de forêt");
                QSpinBox *dimensionH = new QSpinBox;
                dimensionH->setMinimum(dimensionMin);
                dimensionH->setMaximum(dimensionMax);
                QSpinBox *dimensionL = new QSpinBox;
                dimensionL->setMinimum(dimensionMin);
                dimensionL->setMaximum(dimensionMax);
                QTextEdit *rules = new QTextEdit;
                QComboBox *generation = new QComboBox;
                generation->addItem("Grille vide");
                generation->addItem("Remplissage aléatoire");
                generation->addItem("Remplissage symétrique");
                QPushButton *submit = new QPushButton("Valider");
                submit->setMaximumWidth(100);
            QFormLayout *newAutomate = new QFormLayout;
            newAutomate->addRow("Type d'automate", typeAutomate);
            newAutomate->addRow("Hauteur", dimensionH);
            newAutomate->addRow("Largeur", dimensionL);
            newAutomate->addRow("Règles", rules);
            newAutomate->addRow("Génération", generation);
            newAutomate->addRow(submit);
                QPushButton *loadLastAutomate = new QPushButton("Charger le dernier automate");
                QPushButton *loadOtherAutomate = new QPushButton("Charger un autre automate");
            QVBoxLayout *loadAutomate = new QVBoxLayout;
            loadAutomate->addWidget(loadLastAutomate, 1, Qt::AlignCenter);
            loadAutomate->addWidget(loadOtherAutomate, 1, Qt::AlignCenter);
        QGridLayout *display = new QGridLayout;
        display->addWidget(displayTitle, 0, 0, 1, 5, Qt::AlignCenter);
        display->addLayout(loadAutomate, 1, 4, 5, 1, Qt::AlignCenter);
        display->addLayout(newAutomate, 1, 0, 5, 4, Qt::AlignCenter);
            QLabel *generalTitle = new QLabel("AUTOCELL");
            generalTitle->setFont(bigTitle);
        QHBoxLayout *header = new QHBoxLayout;
        header->addWidget(generalTitle, 1, Qt::AlignCenter);
            QPushButton *quit = new QPushButton("Quitter");
            QLabel *toolsInfo = new QLabel("Qu'est-ce qu'un automate cellulaire ?");
        QVBoxLayout *tools = new QVBoxLayout;
        tools->addWidget(toolsInfo, 2, Qt::AlignCenter);
        tools->addWidget(quit, 1, Qt::AlignCenter);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(display, 1, 0, 4, 4);
    mainLayout->addLayout(header, 0, 0, 1, 5);
    mainLayout->addLayout(tools, 0, 4, 4, 1);

    /*
            // MISE EN PLACE DU TITRE/HEADER + TAILLE ET POLICE
            QLabel *header = new QLabel("AUTOCELL");
            int HeightMaxHeader = 100;
            header->setFixedWidth(widthMax);
            header->setMaximumHeight(HeightMaxHeader);
            header->setAlignment(Qt::AlignCenter);
            QFont bigTitle( "Arial", 30, QFont::Bold);
            header->setFont(bigTitle);


                QLabel *displayTitle = new QLabel("Créer Automate");
                displayTitle->setAlignment(Qt::AlignCenter);
                    QPushButton *loadLastAutomate = new QPushButton("Charger le dernier automate");
                    QPushButton *loadOtherAutomate = new QPushButton("Charger un autre automate");
                QHBoxLayout *loadAutomate = new QHBoxLayout;
                loadAutomate->addWidget(loadLastAutomate);
                loadAutomate->addWidget(loadOtherAutomate);
                    QComboBox *typeAutomate = new QComboBox;
                    typeAutomate->addItem("Vie 1D");
                    typeAutomate->addItem("Vie 2D");
                    typeAutomate->addItem("Feu de forêt");
                QFormLayout *formAutomate = new QFormLayout;
                formAutomate->addWidget(typeAutomate);
            QVBoxLayout *display = new QVBoxLayout;
            display->addWidget(displayTitle);
            display->addLayout(loadAutomate);
            display->addLayout(formAutomate);
                QLabel *toolsInfo = new QLabel("Qu'est-ce qu'un automate cellulaire ?");
                QPushButton *quitter = new QPushButton("Quitter");
            QVBoxLayout *tools = new QVBoxLayout;
            tools->addWidget(toolsInfo);
            tools->addWidget(quitter);

        QHBoxLayout *body = new QHBoxLayout;
        body->addLayout(display);
        body->addLayout(tools);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(header);
    mainLayout->addLayout(body);

      */

    fenetre.setLayout(mainLayout);
    fenetre.setWindowTitle("AUTOCELL");
    fenetre.show();
    return app.exec();
}
