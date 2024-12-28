#include "adaugareClientFidel.h"
#include "CSVHandler.h"

void adaugareComanda(const string &locatie, float *cheltuieli)
{
    CSV newCSV;
    vector<string> headers;
    vector<vector<string>> data;

    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string finalpath = basePath + locatie + "/" + "Comenzi.csv";
    string clientiFideliFile = basePath + "clientiFideliOnChain.csv";
    string produsePreturiFile = basePath + locatie + "/Produse_Preturi.csv";
    string stocFile = basePath + locatie + "/stoc.csv";
    string compozitieProduseFile = basePath + "compozitieProduse&&produseBrute.csv";

    string numeClient, produseStr;
    float pretTotal = 0.0f;

    vector<vector<string>> produsePreturi = newCSV.readCSV(produsePreturiFile);
    vector<vector<string>> clientiFideliData = newCSV.readCSV(clientiFideliFile);
    vector<vector<string>> stoc = newCSV.readCSV(stocFile);
    vector<vector<string>> compozitieProduse = newCSV.readCSV(compozitieProduseFile);

    if (produsePreturi.empty() || stoc.empty() || compozitieProduse.empty())
    {
        cerr << "Eroare la citirea fisierelor necesare!" << endl;
        return;
    }

    vector<Client> clientiFideli;
    for (const auto &row : clientiFideliData)
    {
        string line = row[0] + "," + row[1] + "," + row[2];
        clientiFideli.push_back(Client::creeazaDinSir(line));
    }

    if (newCSV.readCSV(finalpath).empty())
    {
        headers = {"Nume Client", "Produse Comandate", "Pret Total"};
    }

    cout << "1. Nume Client: ";
    cin.ignore();
    getline(cin, numeClient);
    cout << "2. Produse Comandate (unite prin '+'): ";
    getline(cin, produseStr);

    stringstream ss(produseStr);
    string produs;
    bool comandaValida = true;

    while (getline(ss, produs, '+'))
    {
        bool produsGasit = false;
        float costProdus = 0.0f;

        // verif daca produsul exista in meniu
        for (const auto &row : produsePreturi)
        {
            if (row[0] == produs)
            {
                produsGasit = true;
                float pretProdus = stof(row[1]);
                pretTotal += pretProdus;

                // verificarea stocului si actualizarea acestuia
                // fiecare produs are mai multe ingrediente
                // daca un ingredient este indisponibil, atunci nu se poate plasa comanda
                for (const auto &compozitieRow : compozitieProduse)
                {
                    if (compozitieRow[0] == produs)
                    {
                        stringstream compozitieSS(compozitieRow[1]);
                        string ingredient;
                        while (getline(compozitieSS, ingredient, '+'))
                        {
                            bool ingredientGasit = false;

                            for (auto &stocRow : stoc)
                            {
                                if (stocRow[0] == ingredient)
                                {
                                    ingredientGasit = true;
                                    int unitatiDisponibile = stoi(stocRow[1]);

                                    if (unitatiDisponibile < 1)
                                    {
                                        cout << "Stoc insuficient pentru ingredientul: " << ingredient << endl;
                                        comandaValida = false;
                                        break;
                                    }
                                    else
                                    {
                                        unitatiDisponibile--;
                                        stocRow[1] = to_string(unitatiDisponibile);
                                    }
                                }
                            }

                            if (!ingredientGasit)
                            {
                                cout << "Ingredientul '" << ingredient << "' nu exista in stoc!" << endl;
                                comandaValida = false;
                                break;
                            }

                            if (!comandaValida)
                                break;
                        }

                        break;
                    }
                }

                break;
            }
        }

        if (!produsGasit)
        {
            cout << "Produsul '" << produs << "' nu a fost gasit in meniu. Te rugam sa reintroduci comanda." << endl;
            comandaValida = false;
            break;
        }

        if (!comandaValida)
            break;
    }

    if (comandaValida)
    {
        Client *client = nullptr;
        for (auto &c : clientiFideli)
        {
            if (c.getName() == numeClient)
            {
                client = &c;
                break;
            }
        }

        if (client)
        {
            float reducere = client->getProcentReducere();
            cout << "Client fidel! Reducere: " << reducere << "%" << endl;
            pretTotal -= (pretTotal * reducere / 100);

            // crestem reducerea daca totalul este peste 10 lei
            if (pretTotal > 10)
            {
                client->incrementReducere();
            }
        }
        else
        {
            // adaugarea clientului nou ca si client fidel
            Client nouClient(numeClient, true, 1);
            clientiFideli.push_back(nouClient);
        }

        data.push_back({numeClient, produseStr, to_string(pretTotal)});
        newCSV.writeCSV(finalpath, data, headers);

        vector<string> headerStoc = {"Ingredient", "Unitati"};
        newCSV.rewriteCSV(stocFile, stoc, headerStoc);

        // vector cu vectori de continut string reprezentand obiectul tranformat in sirul de caractere
        vector<vector<string>> clientiFideliSerialized;

        // c => clientul fidel din vectorul de clienti fideli
        for (const auto &c : clientiFideli)
        {
            clientiFideliSerialized.push_back({c.getName(), c.isFidel() ? "1" : "0", to_string(c.getProcentReducere())});
        }
        newCSV.rewriteCSV(clientiFideliFile, clientiFideliSerialized, {"Nume Client", "Fidel", "Reducere"});

        cout << "Comanda a fost adaugata si stocul a fost actualizat!" << endl;
    }
    else
    {
        cout << "Comanda nu a fost valida si nu a fost adaugata!" << endl;
    }
}
