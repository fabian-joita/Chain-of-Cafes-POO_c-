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
#include "inchidereZi.h"
#include "evenimenteSpeciale.h"

using namespace std;

int main()
{
    bool continua = true;

    float venituri = 0, cheltuieli = 0;

    CAFE cafeChain;

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
            cafenea->loadEmployeesFromFile("Angajati_Functii.csv", cafenea->getLocatie());
            cout << "Vrei sa accesezi aplicatia ca si angajat sau owner? 1-angajat/2-owner" << endl;
            int acces;
            cin >> acces;
            if (acces == 1)
            {
                if (cafenea)
                {
                    cafenea->display();
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
                        cout << "-----------------------------------------------------------------------------------" << endl;
                        cout << "Ce operatie doresti sa faci in aceasta cafenea? " << endl;
                        cout << "1. Schimbare detalii angajati produse_preturi / stocuri_ingrediente." << endl;
                        cout << "2. Adaugare comanda." << endl;
                        cout << "3. Inchidere zi (calcul venit = incasari - cheltuieli) => stergere comenzi." << endl;
                        cout << "4. Gestionare Evenimente Speciale (adaugare, afisare, calcul venituri/costuri)." << endl;
                        cout << "5. Scrierea intr-un fisier csv cu date despre cafenea." << endl;
                        cout << "6. Citirea dintr-un fisier csv cu date despre cafenea." << endl;
                        cout << "-----------------------------------------------------------------------------------" << endl;

                        string pathEvenim = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
                        string FullPathEvenim = pathEvenim + cafenea->getLocatie() + "/evenimenteSpeciale.csv";

                        ManagerEvenimente::getInstance()->getGestionare().citesteEvenimenteDinFisier(FullPathEvenim);

                        cin >> alegere;
                        cout << "-----------------------------------------------------------------------------------" << endl;
                        if (alegere == 1)
                        {
                            cout << "Despre ce vrei sa schimbi detalii? (angajati/produse/stocuri)" << endl;
                            string schimbare;
                            cin >> schimbare;
                            schimbare_detalii(schimbare, cafenea->getLocatie());
                        }
                        else if (alegere == 2)
                        {
                            adaugareComanda(cafenea->getLocatie(), &cheltuieli);
                        }
                        else if (alegere == 3)
                        {
                            inchidereZi zi;
                            zi.inchidereZiCalcul(cafenea->getLocatie());
                        }
                        else if (alegere == 4)
                        {

                            int optiuneEveniment;
                            do
                            {
                                cout << "-----------------------------------------------------------------------------------" << endl;
                                cout << "---------------- Gestionare Evenimente Speciale ----------------" << endl;
                                cout << "1. Adauga Eveniment Special." << endl;
                                cout << "2. Afiseaza toate Evenimentele Speciale." << endl;
                                cout << "3. Calculeaza Venituri Totale din Evenimente." << endl;
                                cout << "4. Calculeaza Costuri Totale din Evenimente." << endl;
                                cout << "0. Inapoi la meniul principal." << endl;
                                cout << "-----------------------------------------------------------------------------------" << endl;
                                cin >> optiuneEveniment;
                                cout << "-----------------------------------------------------------------------------------" << endl;

                                if (optiuneEveniment == 1)
                                {
                                    string nume, data, interval;
                                    float costOrganizare, costParticipare;
                                    int locuriDisponibile, locuriOcupate;
                                    string descriere;

                                    cout << "-----------------------------------------------------------------------------------" << endl;
                                    cout << "Introduceti numele evenimentului: ";
                                    cin.ignore();
                                    getline(cin, nume);

                                    cout << "Introduceti data evenimentului (YYYY-MM-DD): ";
                                    cin >> data;

                                    cout << "Introduceti intervalul orar (HH:MM-HH:MM): ";
                                    cin >> interval;

                                    cout << "Introduceti costul de organizare: ";
                                    cin >> costOrganizare;

                                    cout << "Introduceti costul de participare per persoana: ";
                                    cin >> costParticipare;

                                    cout << "Introduceti numarul de locuri disponibile: ";
                                    cin >> locuriDisponibile;

                                    cout << "Introduceti numarul de locuri ocupate: ";
                                    cin >> locuriOcupate;

                                    cout << "introduceti descriere eveniment: ";
                                    cin.ignore();
                                    getline(cin, descriere);
                                    cout << "-----------------------------------------------------------------------------------" << endl;

                                    Eveniment eveniment(nume, data, interval, costOrganizare, costParticipare, locuriDisponibile, locuriOcupate, descriere);
                                    ManagerEvenimente::getInstance()->getGestionare().salveazaEvenimenteInFisier(FullPathEvenim, eveniment);
                                    ManagerEvenimente::getInstance()->getGestionare().citesteEvenimenteDinFisier(FullPathEvenim);

                                    cout << "Evenimentul a fost adaugat cu succes!" << endl;
                                }
                                else if (optiuneEveniment == 2)
                                {
                                    cout << "-----------------------------------------------------------------------------------" << endl;
                                    cout << "---------------- Lista Evenimentelor Speciale ----------------" << endl;

                                    ManagerEvenimente::getInstance()->getGestionare().afiseazaToateEvenimentele();
                                    cout << "-----------------------------------------------------------------------------------" << endl;
                                }
                                else if (optiuneEveniment == 3)
                                {
                                    float venituriEvenimente = ManagerEvenimente::getInstance()->getGestionare().calculVenitTotal();
                                    cout << "Veniturile totale din evenimente speciale: " << venituriEvenimente << " RON" << endl;
                                }
                                else if (optiuneEveniment == 4)
                                {
                                    float costuriEvenimente = ManagerEvenimente::getInstance()->getGestionare().calculCostTotal();
                                    cout << "Costurile totale ale evenimentelor speciale: " << costuriEvenimente << " RON" << endl;
                                }
                                else if (optiuneEveniment != 0)
                                {
                                    cout << "Optiune invalida!" << endl;
                                }
                            } while (optiuneEveniment != 0);
                        }
                        else if (alegere == 5)
                        {
                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";

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
                    cout << "Optiune invalida!" << endl;
                    feedback = false;
                }
            }
            else if (acces == 2)
            {
                // owner logic
            }
            else
            {
                cout << "Optiune invalida!" << endl;
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
