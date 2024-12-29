#include "evenimenteSpeciale.h"
#include <iostream>
#include <string>

using namespace std;

Eveniment::Eveniment(string nume, string data, string interval, float costOrg, float costPart, int locDisp, int locOcp, string descriere)
    : numeEveniment(nume), dataEveniment(data), intervalOrar(interval),
      costOrganizare(costOrg), costParticipare(costPart),
      locuriDisponibile(locDisp), locuriOcupate(locOcp), descriereEveniment(descriere) {}

Eveniment::~Eveniment() {}

string Eveniment::getNumeEveniment() const { return numeEveniment; }
void Eveniment::setNumeEveniment(const string &nume) { numeEveniment = nume; }

string Eveniment::getDataEveniment() const { return dataEveniment; }
void Eveniment::setDataEveniment(const string &data) { dataEveniment = data; }

string Eveniment::getIntervalOrar() const { return intervalOrar; }
void Eveniment::setIntervalOrar(const string &interval) { intervalOrar = interval; }

float Eveniment::getCostOrganizare() const { return costOrganizare; }
void Eveniment::setCostOrganizare(float costOrg) { costOrganizare = costOrg; }

float Eveniment::getCostParticipare() const { return costParticipare; }
void Eveniment::setCostParticipare(float costPart) { costParticipare = costPart; }

int Eveniment::getLocuriDisponibile() const { return locuriDisponibile; }
void Eveniment::setLocuriDisponibile(int locDisp) { locuriDisponibile = locDisp; }

int Eveniment::getLocuriOcupate() const { return locuriOcupate; }
void Eveniment::setLocuriOcupate(int locOcp) { locuriOcupate = locOcp; }

string Eveniment::getDescriereEveniment() const { return descriereEveniment; }
void Eveniment::setDescriereEveniment(const string &descriere) { descriereEveniment = descriere; }

float Eveniment::calculVenitEveniment() const
{
    return locuriOcupate * costParticipare;
}

void Eveniment::afiseazaDetalii() const
{
    if (languageOption == "EN")
    {
        cout << "Event: " << numeEveniment << endl;
        cout << "Date: " << dataEveniment << endl;
        cout << "Time interval: " << intervalOrar << endl;
        cout << "Organizing cost: " << costOrganizare << " RON" << endl;
        cout << "Participation cost: " << costParticipare << " RON" << endl;
        cout << "Available seats: " << locuriDisponibile << endl;
        cout << "Occupied seats: " << locuriOcupate << endl;
        cout << "Description: " << descriereEveniment << endl;
        cout << "Estimated total income: " << calculVenitEveniment() << " RON" << endl;
    }
    else
    {
        cout << "Eveniment: " << numeEveniment << endl;
        cout << "Data: " << dataEveniment << endl;
        cout << "Interval orar: " << intervalOrar << endl;
        cout << "Cost organizare: " << costOrganizare << " RON" << endl;
        cout << "Cost participare: " << costParticipare << " RON" << endl;
        cout << "Locuri disponibile: " << locuriDisponibile << endl;
        cout << "Locuri ocupate: " << locuriOcupate << endl;
        cout << "Descriere: " << descriereEveniment << endl;
        cout << "Venit total estimat: " << calculVenitEveniment() << " RON" << endl;
    }
}

ManagerEvenimente *ManagerEvenimente::instance = nullptr;

ManagerEvenimente *ManagerEvenimente::getInstance()
{
    if (!instance)
    {
        instance = new ManagerEvenimente();
    }
    return instance;
}

GestionareEvenimente<Eveniment> &ManagerEvenimente::getGestionare()
{
    return gestionare;
}
