#include "adaugareComanda.h"
#include "Globals.h"

void adaugareComanda(const string &locatie, float *cheltuieli)
{
    CSV newCSV;
    vector<string> headers;
    vector<vector<string>> data;

    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/";
    string csvPath = (languageOption == "EN") ? basePath + "CSV_FILES_ENGLISH/" : basePath + "CSV_FILES/";
    string finalpath = (languageOption == "EN") ? csvPath + locatie + "/" + "Orders.csv" : csvPath + locatie + "/" + "Comenzi.csv";
    string clientiFideliFile = (languageOption == "EN") ? csvPath + "loyalCustomersOnChain.csv" : csvPath + "clientiFideliOnChain.csv";
    string produsePreturiFile = (languageOption == "EN") ? csvPath + locatie + "/Products_Prices.csv" : csvPath + locatie + "/Produse_Preturi.csv";
    string stocFile = (languageOption == "EN") ? csvPath + locatie + "/stock.csv" : csvPath + locatie + "/stoc.csv";
    string compozitieProduseFile = (languageOption == "EN") ? csvPath + "productComposition&&rawProducts.csv" : csvPath + "compozitieProduse&&produseBrute.csv";

    string numeClient, produseStr;
    float pretTotal = 0.0f;

    vector<vector<string>> produsePreturi = newCSV.readCSV(produsePreturiFile);
    vector<vector<string>> clientiFideliData = newCSV.readCSV(clientiFideliFile);
    vector<vector<string>> stoc = newCSV.readCSV(stocFile);
    vector<vector<string>> compozitieProduse = newCSV.readCSV(compozitieProduseFile);

    if (produsePreturi.empty() || stoc.empty() || compozitieProduse.empty())
    {
        cerr << ((languageOption == "EN") ? "Error reading required files!" : "Eroare la citirea fisierelor necesare!") << endl;
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
        headers = (languageOption == "EN") ? vector<string>{"Client Name", "Ordered Products", "Total Price"}
                                           : vector<string>{"Nume Client", "Produse Comandate", "Pret Total"};
    }

    cout << ((languageOption == "EN") ? "1. Client Name: " : "1. Nume Client: ");
    cin.ignore();
    getline(cin, numeClient);
    cout << ((languageOption == "EN") ? "2. Ordered Products (separated by '+'): " : "2. Produse Comandate (unite prin '+'): ");
    getline(cin, produseStr);

    stringstream ss(produseStr);
    string produs;
    bool comandaValida = true;

    while (getline(ss, produs, '+'))
    {
        bool produsGasit = false;

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
                                        cout << ((languageOption == "EN") ? "Insufficient stock for ingredient: " : "Stoc insuficient pentru ingredientul: ")
                                             << ingredient << endl;
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
                                cout << ((languageOption == "EN") ? "Ingredient '" : "Ingredientul '") << ingredient
                                     << ((languageOption == "EN") ? "' is not in stock!" : "' nu exista in stoc!") << endl;
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
            cout << ((languageOption == "EN") ? "Product '" : "Produsul '") << produs
                 << ((languageOption == "EN") ? "' was not found on the menu. Please re-enter your order."
                                              : "' nu a fost gasit in meniu. Te rugam sa reintroduci comanda.")
                 << endl;
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
            cout << ((languageOption == "EN") ? "Loyal customer! Discount: " : "Client fidel! Reducere: ") << reducere << "%" << endl;
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

        vector<string> headerStoc = (languageOption == "EN") ? vector<string>{"Ingredient", "Units"} : vector<string>{"Ingredient", "Unitati"};
        newCSV.rewriteCSV(stocFile, stoc, headerStoc);

        // vector cu vectori de continut string reprezentand obiectul tranformat in sirul de caractere
        vector<vector<string>> clientiFideliSerialized;

        // c => clientul fidel din vectorul de clienti fideli
        for (const auto &c : clientiFideli)
        {
            clientiFideliSerialized.push_back({c.getName(), c.isFidel() ? "1" : "0", to_string(c.getProcentReducere())});
        }
        newCSV.rewriteCSV(clientiFideliFile, clientiFideliSerialized,
                          (languageOption == "EN") ? vector<string>{"Client Name", "Loyal", "Discount"}
                                                   : vector<string>{"Nume Client", "Fidel", "Reducere"});

        cout << ((languageOption == "EN") ? "Order added successfully and stock updated!"
                                          : "Comanda a fost adaugata si stocul a fost actualizat!")
             << endl;
    }
    else
    {
        cout << ((languageOption == "EN") ? "Order was not valid and was not added!"
                                          : "Comanda nu a fost valida si nu a fost adaugata!")
             << endl;
    }
}
