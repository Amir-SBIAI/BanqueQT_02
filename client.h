#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

using namespace std;

class Client {
private:
    string CIN;
    string nom;
    string prenom;
    string numero;

public:
    Client(string, string, string, string);
    ~Client();

    string getCIN() const;
    string getNom() const;
    string getPrenom() const;
    string getTelephone() const;
};

#endif
