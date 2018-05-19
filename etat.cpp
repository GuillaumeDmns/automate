#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>

int interface(int argc, char * argv[]) {
    QApplication app(argc, argv);

    /* CREATION ET PARAMETRAGE DE LA FENETRE */
    QWidget fenetre;
    //fenetre.setFixedSize(300, 200);

        QLabel *header = new QLabel("AUTOCELL");
                QLabel *displayTitle = new QLabel("Créer Automate");
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

    fenetre.setLayout(mainLayout);
    fenetre.setWindowTitle("AUTOCELL");
    fenetre.show();
    return app.exec();
}
