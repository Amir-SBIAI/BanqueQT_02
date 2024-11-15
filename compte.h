#ifndef COMPTE_H
#define COMPTE_H

#include <iostream>
#include <string>
#include "client.h"

using namespace std;

class Compte {
private:
    string ID;
    double solde;
    string iban;
    Client proprietaire;

public:
    Compte(string, double, Client);
    ~Compte();

    string getIban() const;
    double getSolde() const;
    string getProprietaireNom() const;
    string getProprietairePrenom() const;
    string getProprietaireTelephone() const;

    void Crediter(double montant);
    void Debiter(double montant);
    void Transfert(double montant);
    void AfficherInfos() const;
    void menu();
};

#endif
