#include <iostream>
#include "client.h"

using namespace std;

Client::Client(string identifiant, string nomFamille, string prenomClient, string telephone) {
    CIN = identifiant;
    nom = nomFamille;
    prenom = prenomClient;
    numero = telephone;
}

Client::~Client() {}

string Client::getCIN() const {
    return CIN;
}

string Client::getNom() const {
    return nom;
}

string Client::getPrenom() const {
    return prenom;
}

string Client::getTelephone() const {
    return numero;
}
