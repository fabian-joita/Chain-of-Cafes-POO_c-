#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// procentul de reducere vreau sa creasca cu unu ajungand sa fie maxim 30
// acesta va creste la fiecare comanda mai mare de 10 lei plasata de client
// o sa am fisierul permanent clientiFidelionChain, unde o sa trec lista de clienti
// si procentul de reducere pentru fiecare client
//  de fiecare data cand un client plaseaza o comanda mai mare de 10 lei
// il caut in fisier de fideli.
// daca il gasesc il cresc procentul de reducere cu 1
// daca nu il gasesc il adaug in fisier cu procentul de reducere 1

class Client
{
private:
    string name;
    bool fidel;
    int procentReducere;

public:
    Client(const string &name, bool fidel = false, int procentReducere = 0)
        : name(name), fidel(fidel), procentReducere(procentReducere) {}

    string getName() const { return name; }
    bool isFidel() const { return fidel; }
    int getProcentReducere() const { return procentReducere; }

    void incrementReducere()
    {
        if (procentReducere < 30)
        {
            procentReducere++;
        }
    }

    void setFidel(bool status) { fidel = status; }

    string convertesteInSir() const
    {
        return name + "," + (fidel ? "1" : "0") + "," + to_string(procentReducere);
    }

    static Client creeazaDinSir(const string &line)
    {
        stringstream ss(line);
        string name, fidelStr, reducereStr;
        getline(ss, name, ',');
        getline(ss, fidelStr, ',');
        getline(ss, reducereStr, ',');
        return Client(name, fidelStr == "1", stoi(reducereStr));
    }
};

#endif
