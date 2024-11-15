#include <iostream>
#include "compte.h"

using namespace std;

Compte::Compte(string idClient, double montantInitial, Client clientProprio)
    : ID(idClient), solde(montantInitial), proprietaire(clientProprio) {}

Compte::~Compte() {}

double Compte::getSolde() const {
    return solde;
}

string Compte::getIban() const {
    return iban;
}

string Compte::getProprietaireNom() const {
    return proprietaire.getNom();
}

string Compte::getProprietairePrenom() const {
    return proprietaire.getPrenom();
}

string Compte::getProprietaireTelephone() const {
    return proprietaire.getTelephone();
}

void Compte::Crediter(double montant) {
    if (montant > 0) {
        solde += montant;
        cout << "\nARGENT AJOUTE ! Solde actuel : " << solde << " euros\n";
    } else {
        cout << "\nERREUR : Montant invalide\n";
    }
}

void Compte::Debiter(double montant) {
    if (montant > 0 && montant <= solde) {
        solde -= montant;
        cout << "\nARGENT RETIRE ! Solde actuel : " << solde << " euros\n";
    } else {
        cout << "\nERREUR : Montant invalide ou insuffisant\n";
    }
}

void Compte::Transfert(double montant) {
    if (montant > 0 && montant <= solde) {
        solde -= montant;
        cout << "\nTRANSFERT REUSSI ! Solde actuel : " << solde << " euros\n";
    } else {
        cout << "\nERREUR : Montant incorrect\n";
    }
}

void Compte::AfficherInfos() const {
    cout << "\n\tDETAILS DU COMPTE\n";
    cout << "Nom du titulaire : " << getProprietaireNom() << endl;
    cout << "Prenom du titulaire : " << getProprietairePrenom() << endl;
    cout << "Telephone : " << getProprietaireTelephone() << endl;
    cout << "Solde disponible : " << solde << " euros" << endl;
}
