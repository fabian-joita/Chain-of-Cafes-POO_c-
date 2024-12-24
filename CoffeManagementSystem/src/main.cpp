#include <iostream>
#include <filesystem>
#include <vector>
#include <memory>
#include "listareFisiere.cpp"
#include "cafe_chain.h"
#include "optiunea6.h"
#include "optiunea7.h"
#include "schimbare_caracteristici.h"
#include "adaugareComanda.h"

using namespace std;

// Assuming the necessary classes for Employee, Product, Order, Ingredient, Display, Sediu, and CAFE are defined elsewhere.

int main()
{
    bool continua = true;

    float vanzari = 0, cheltuieli = 0;

    CAFE cafeChain; // Creating the CAFE object

    // Adding the five cafes as described in the problem
    Display *cafe1 = new Display();
    cafe1->setLocation("Bucuresti");
    cafeChain.addCafeUnit(cafe1);

    Display *cafe2 = new Display();
    cafe2->setLocation("Cluj");
    cafeChain.addCafeUnit(cafe2);

    Display *cafe3 = new Display();
    cafe3->setLocation("Timisoara");
    cafeChain.addCafeUnit(cafe3);

    Display *cafe4 = new Display();
    cafe4->setLocation("Iasi");
    cafeChain.addCafeUnit(cafe4);

    Display *cafe5 = new Display();
    cafe5->setLocation("Brasov");
    cafeChain.addCafeUnit(cafe5);

    do
    {
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << "Bine ai venit in aplicatia CafeaBuna!" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;

        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << "Vrei sa adaugi o alta cafenea?" << endl;
        cout << "1. DA" << endl;
        cout << "2. NU" << endl;
        int newCafe;
        cin >> newCafe;

        if (newCafe == 1)
        {
            cout << "Introduceti locatia noii cafenele: ";
            string locatie;
            cin >> locatie;

            Display *cafe = new Display();
            cafe->setLocation(locatie);
            cafeChain.addCafeUnit(cafe);

            cout << "Noua cafenea din " << locatie << " a fost adăugată cu succes!" << endl;
        }
        cout << "-----------------------------------------------------------------------------------" << endl;

        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << "Se afiseaza cafenelele disponibile: " << endl;
        cafeChain.displayCafeLocations();
        cout << "-----------------------------------------------------------------------------------" << endl;

        bool feedback = true;
        do
        {
            cout << "-----------------------------------------------------------------------------------" << endl;
            int optiune;
            cout << "Cu ce cafenea vrei sa continui? (insert number)" << endl;
            cin >> optiune;
            Sediu *cafenea = cafeChain.getPtrUnit(optiune);

            cout << "Ptr cafenea este: " << cafenea << endl;

            cout << "Vrei sa accesezi aplicatia ca si angajat sau owner? 1-angajat/2-owner" << endl;
            int acces;
            cin >> acces;
            if (acces == 1)
            {
                if (cafenea)
                {
                    cafenea->display(); // Display details about the selected cafe
                    feedback = true;

                    int aceeasi_cafenea;

                    do
                    {
                        int alegere;
                        // vreau sa imi fac un fisier care sa contina meniul
                        // cand adaug o comanda o sa ma folosesc de preturile din meniu pentru a se adauga singure
                        // meniul o sa fie unul pe tot lantul
                        // o sa difere doar stocul

                        // o sa am un fisier cu produse si costul lor de preparare
                        // vanzaribani - (nrcafele * $ + nrape * $ + ...)
                        // asa calculez venitul zilnic
                        // vanzari bani va aduna sumele din fisierul comenzi
                        cout << "Ce operatie doresti sa faci in aceasta cafenea? " << endl;
                        cout << "1. Schimbare detalii angajati produse_preturi / stocuri_ingrediente." << endl;
                        cout << "2. Adaugare comanda." << endl;
                        cout << "5. Scrierea intr-un fisier csv cu date despre cafenea." << endl;
                        cout << "6. Citirea dintr-un fisier csv cu date despre cafenea." << endl;

                        cin >> alegere;
                        if (alegere == 1)
                        {
                            cout << "Despre ce vrei sa schimbi detalii? (angajati/produse/stocuri)" << endl;
                            string schimbare;
                            cin >> schimbare;
                            schimbare_detalii(schimbare, cafenea->getLocatie());
                        }
                        else if (alegere == 2)
                        {
                            adaugareComanda(cafenea->getLocatie(), &vanzari, &cheltuieli);
                        }
                        else if (alegere == 5)
                        {
                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";

                            // Pass the populated containers to writeCSVFile
                            Optiunea6::writeCSVFile(path, cafenea->getLocatie());
                        }
                        else if (alegere == 6)
                        {
                            cout << "Se afiseaza fisierele disponibile pentru citire: " << endl;

                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/" + cafenea->getLocatie() + "/";
                            listFilesInDirectory(path);

                            string numeFisier;
                            cout << "Introduceti numele fisierului pe care doriti sa il cititi, exact ca si cel afisat: " << endl;
                            cin >> numeFisier;
                            path = path + numeFisier;

                            Optiunea7::readCSVFile(path);
                        }

                        cout << "Doresti sa ramai in aceasta cafenea pentru a executa alte operatii? (da: 1/ nu: 0)" << endl;
                        cin >> aceeasi_cafenea;
                    } while (aceeasi_cafenea == 1);
                }
                else
                {
                    cout << "Opțiune invalidă!" << endl;
                    feedback = false;
                }
            }
            else if (acces == 2)
            {
                // Owner-related logic can be implemented here
            }
            else
            {
                cout << "Opțiune invalidă!" << endl;
            }

            cout << "-----------------------------------------------------------------------------------" << endl;

        } while (feedback == false);

        cout << "Vrei sa continui procesul de cautare a informatiilor? (1 - da, 0 - nu): " << endl;

        int rasp;
        cin >> rasp;

        if (rasp == 0)
            continua = false;
    } while (continua == true);

    return 0;
}
