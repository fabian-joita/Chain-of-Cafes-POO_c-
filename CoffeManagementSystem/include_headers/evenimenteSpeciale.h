#ifndef EVENIMENTESPECIALE_H
#define EVENIMENTESPECIALE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Globals.h"

using namespace std;

/*Encapsularea : Toate atributele(cum ar fi numeEveniment, costOrganizare, etc.)
 sunt private si sunt accesibile doar prin metodele getter si setter.Acest lucru
 protejeaza datele interne ale obiectului, prevenind accesul direct din exterior si
 asigurand controlul asupra modului in care sunt modificate valorile acestora.

Abstractie : Clasa Eveniment ascunde detaliile
 implementarii evenimentelor si ofera doar metode pentru manipularea si accesul la atributele acestora.*/
class Eveniment
{
private:
    string numeEveniment;
    string dataEveniment;
    string intervalOrar;
    float costOrganizare;
    float costParticipare;
    int locuriDisponibile;
    int locuriOcupate;
    string descriereEveniment;

public:
    Eveniment(string nume, string data, string interval, float costOrg, float costPart, int locDisp, int locOcp, string descriere);
    ~Eveniment();

    string getNumeEveniment() const;
    void setNumeEveniment(const string &nume);

    string getDataEveniment() const;
    void setDataEveniment(const string &data);

    string getIntervalOrar() const;
    void setIntervalOrar(const string &interval);

    float getCostOrganizare() const;
    void setCostOrganizare(float costOrg);

    float getCostParticipare() const;
    void setCostParticipare(float costPart);

    int getLocuriDisponibile() const;
    void setLocuriDisponibile(int locDisp);

    int getLocuriOcupate() const;
    void setLocuriOcupate(int locOcp);

    string getDescriereEveniment() const;
    void setDescriereEveniment(const string &descriere);

    float calculVenitEveniment() const;
    void afiseazaDetalii() const;
};

// Template pentru GestionareEvenimente
// Template-uri: GestionareEvenimente este o clasa templatata, ceea ce inseamna ca permite
// gestionarea unui tip generic de obiecte (in acest caz, Eveniment). Astfel, putem folosi
// aceeasi clasa pentru a lucra cu tipuri diferite de evenimente sau obiecte, fara a fi nevoie
// sa refacem clasa pentru fiecare tip in parte.

template <typename T>
class GestionareEvenimente
{
private:
    vector<T> listaEvenimente;

public:
    void adaugaEveniment(const T &eveniment);
    void afiseazaToateEvenimentele() const;
    const vector<T> &getToateEvenimentele() const;
    float calculVenitTotal() const;
    float calculCostTotal() const;

    void salveazaEvenimenteInFisier(const string &caleFisier, Eveniment eveniment) const;
    void citesteEvenimenteDinFisier(const string &caleFisier);
};

template <typename T>
void GestionareEvenimente<T>::adaugaEveniment(const T &eveniment)
{
    listaEvenimente.push_back(eveniment);
}

template <typename T>
void GestionareEvenimente<T>::afiseazaToateEvenimentele() const
{
    for (const auto &eveniment : listaEvenimente)
    {
        eveniment.afiseazaDetalii();
        cout << "----------------------" << endl;
    }
}

template <typename T>
const vector<T> &GestionareEvenimente<T>::getToateEvenimentele() const
{
    return listaEvenimente;
}

template <typename T>
float GestionareEvenimente<T>::calculVenitTotal() const
{
    float venitTotal = 0;
    for (const auto &eveniment : listaEvenimente)
    {
        venitTotal += eveniment.calculVenitEveniment();
    }
    return venitTotal;
}

template <typename T>
float GestionareEvenimente<T>::calculCostTotal() const
{
    float costTotal = 0;
    for (const auto &eveniment : listaEvenimente)
    {
        costTotal += eveniment.getCostOrganizare();
    }
    return costTotal;
}

template <typename T>
void GestionareEvenimente<T>::salveazaEvenimenteInFisier(const string &caleFisier, Eveniment eveniment) const
{
    ofstream fisierOut(caleFisier);

    if (!fisierOut.is_open())
    {
        cout << "Eroare la deschiderea fisierului pentru scriere!" << endl;
        return;
    }

    fisierOut << eveniment.getNumeEveniment() << ","
              << eveniment.getDataEveniment() << ","
              << eveniment.getIntervalOrar() << ","
              << eveniment.getCostOrganizare() << ","
              << eveniment.getCostParticipare() << ","
              << eveniment.getLocuriDisponibile() << ","
              << eveniment.getLocuriOcupate() << ","
              << eveniment.getDescriereEveniment() << "\n";

    fisierOut.close();
}

template <typename T>
void GestionareEvenimente<T>::citesteEvenimenteDinFisier(const string &caleFisier)
{
    ifstream fisierIn(caleFisier);

    if (!fisierIn.is_open())
    {
        cout << "Eroare la deschiderea fisierului pentru citire!" << endl;
        return;
    }

    listaEvenimente.clear();

    string primaLinie;
    getline(fisierIn, primaLinie);

    string linie;
    while (getline(fisierIn, linie))
    {
        stringstream ss(linie);
        string numeEveniment, dataEveniment, intervalOrar;
        float costOrganizare, costParticipare;
        int locuriDisponibile, locuriOcupate;
        string descriere;

        getline(ss, numeEveniment, ',');
        getline(ss, dataEveniment, ',');
        getline(ss, intervalOrar, ',');
        ss >> costOrganizare;
        ss.ignore();
        ss >> costParticipare;
        ss.ignore();
        ss >> locuriDisponibile;
        ss.ignore();
        ss >> locuriOcupate;
        ss.ignore();
        getline(ss, descriere);

        Eveniment eveniment(numeEveniment, dataEveniment, intervalOrar, costOrganizare, costParticipare, locuriDisponibile, locuriOcupate, descriere);
        listaEvenimente.push_back(eveniment);
    }

    fisierIn.close();
}

// Singleton pentru ManagerEvenimente
/*Singleton : Clasa ManagerEvenimente implementeaza un pattern Singleton, ceea ce inseamna
ca aceasta clasa va avea doar o singura instanta in intreaga aplicatie, accesibila prin metoda
 getInstance().Acest pattern este folosit pentru a controla accesul la o resursa comuna, in
 acest caz, un manager de evenimente global.
*/
class ManagerEvenimente
{
private:
    static ManagerEvenimente *instance;
    GestionareEvenimente<Eveniment> gestionare;

    ManagerEvenimente() {}

public:
    static ManagerEvenimente *getInstance();
    GestionareEvenimente<Eveniment> &getGestionare();
};

#endif
