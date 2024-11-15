#include "window.h"
#include "compte.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QWidget(parent),
      compteActif(nullptr) // Initialisation du compte actif
{
    QLabel *idLabel = new QLabel(tr("Identifiant:"));
    idLineEdit = new QLineEdit;
    idLineEdit->setPlaceholderText("Entrer votre identifiant");

    QLabel *passwordLabel = new QLabel(tr("Mot de passe:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setPlaceholderText("Entrer votre mot de passe");

    showIDCheckBox = new QCheckBox(tr("Afficher l'identifiant"));
    connect(showIDCheckBox, &QCheckBox::toggled, this, &Window::toggleIDField);

    showPasswordCheckBox = new QCheckBox(tr("Afficher le mot de passe"));
    connect(showPasswordCheckBox, &QCheckBox::toggled, this, &Window::togglePasswordField);

    connectButton = new QPushButton(tr("Se connecter"));
    connect(connectButton, &QPushButton::clicked, this, &Window::onConnectButtonClicked);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(idLabel, 0, 0);
    layout->addWidget(idLineEdit, 0, 1);
    layout->addWidget(showIDCheckBox, 0, 2);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordLineEdit, 1, 1);
    layout->addWidget(showPasswordCheckBox, 1, 2);
    layout->addWidget(connectButton, 2, 1);

    setLayout(layout);
    setWindowTitle(tr("LA BANQUE DU BOSS AMIR"));
}

void Window::toggleIDField(bool checked) {
    idLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::PasswordEchoOnEdit);
}

void Window::togglePasswordField(bool checked) {
    passwordLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void Window::onConnectButtonClicked() {
    QString id = idLineEdit->text();
    QString password = passwordLineEdit->text();

    // Création de clients pour la démonstration
    Client client1("FR1234", "SBIAI", "Amir", "0645687654");
    Compte *compte1 = new Compte("FR1234", 5000, client1);

    // Vérification des identifiants
    if (id == "Amir" && password == "1234") {
        compteActif = compte1; // Compte actif après connexion

        QWidget *newWindow = new QWidget;
        newWindow->setWindowTitle("MENU DU COMPTE");
        newWindow->resize(400, 300);

        QVBoxLayout *layout = new QVBoxLayout;

        QPushButton *CrediterButton = new QPushButton(tr("Crediter"));
        QPushButton *DebiterButton = new QPushButton(tr("Debiter"));
        QPushButton *TransfertButton = new QPushButton(tr("Transfert"));
        QPushButton *InfosButton = new QPushButton(tr("Afficher Infos"));
        QPushButton *quitButton = new QPushButton(tr("Quitter"));

        layout->addWidget(CrediterButton);
        layout->addWidget(DebiterButton);
        layout->addWidget(TransfertButton);
        layout->addWidget(InfosButton);
        layout->addWidget(quitButton);

        connect(quitButton, &QPushButton::clicked, newWindow, &QWidget::close);
        connect(CrediterButton, &QPushButton::clicked, this, &Window::openCrediterPage);
        connect(DebiterButton, &QPushButton::clicked, this, &Window::openDebiterPage);
        connect(TransfertButton, &QPushButton::clicked, this, &Window::openTransfertPage);
        connect(InfosButton, &QPushButton::clicked, this, &Window::openInfosPage);

        newWindow->setLayout(layout);
        newWindow->show();
    } else {
        QMessageBox::warning(this, tr("Erreur de connexion"), tr("Identifiants ou mot de passe incorrects."));
    }
}

void Window::openCrediterPage() {
    // Créer la fenêtre de créditer
    QWidget *creditWindow = new QWidget;
    creditWindow->setWindowTitle("CREDITER");
    creditWindow->resize(400, 300);

    // Champ de saisie pour le montant à créditer
    QLabel *amountLabel = new QLabel(tr("Entrez le montant à créditer :"));
    QLineEdit *amountLineEdit = new QLineEdit;
    amountLineEdit->setPlaceholderText("Montant");

    // Bouton de validation pour créditer
    QPushButton *creditButton = new QPushButton(tr("Créditer"));
    connect(creditButton, &QPushButton::clicked, [this, amountLineEdit]() {
        bool ok;
        double montant = amountLineEdit->text().toDouble(&ok);  // Conversion du texte en double
        if (ok && montant > 0) {
            if (compteActif) {
                compteActif->Crediter(montant);  // Appeler la méthode de crédit du compte actif



            }
        }
    });

    // Layout pour la fenêtre de créditer
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(amountLabel);
    layout->addWidget(amountLineEdit);
    layout->addWidget(creditButton);

    creditWindow->setLayout(layout);
    creditWindow->show();
}

void Window::openDebiterPage() {
    // Ouvrir la page pour débiter
    QWidget *debitWindow = new QWidget;
    debitWindow->setWindowTitle("DEBITER");
    debitWindow->resize(400, 300);
    debitWindow->show();
}

void Window::openTransfertPage() {
    // Ouvrir la page pour un transfert
    QWidget *transfertWindow = new QWidget;
    transfertWindow->setWindowTitle("TRANSFERT");
    transfertWindow->resize(400, 300);
    transfertWindow->show();
}

void Window::openInfosPage() {
    // Ouvrir la page d'informations
    QWidget *infosWindow = new QWidget;
    infosWindow->setWindowTitle("INFORMATIONS");
    infosWindow->resize(400, 300);

    if (compteActif) {
        QLabel *infosLabel = new QLabel(tr("Nom: %1\nPrénom: %2\nTéléphone: %3\nSolde: %4")
                                            .arg(QString::fromStdString(compteActif->getProprietaireNom()))
                                            .arg(QString::fromStdString(compteActif->getProprietairePrenom()))
                                            .arg(QString::fromStdString(compteActif->getProprietaireTelephone()))
                                            .arg(QString::number(compteActif->getSolde())));
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(infosLabel);
        infosWindow->setLayout(layout);
    }
    infosWindow->show();
}
