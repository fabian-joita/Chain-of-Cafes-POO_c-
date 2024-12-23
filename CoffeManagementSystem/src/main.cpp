#include <iostream>
#include <filesystem>
#include "listareFisiere.cpp"
#include "cafe_chain.h"
#include "optiunea6.h"
#include "optiunea7.h"

using namespace std;

int main()
{
    bool continua = true;

    CAFE cafeChain; // crearea obiectului CAFE

    // adaugare a celor 5 cafenele din cerinta problemei
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
        cout << "Se afiseaza cafenelele diponibile: " << endl;
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
            // aici o sa vreau sa implementez doua ramuri n functie de cel care vrea sa aiba acces la program
            // owner ul lantului e cafenele va putea sa adauge sau sa stearga angajati
            // acceul la contul de owner se va face prin introducerea unui cod de acces
            // angajatul va beneficia de abilitatea de a adauga produse, sterge stocuri, adauga clienti fideli
            //++sa faca inchiderea de casa

            cout << "Vrei sa accesezi aplicatia ca si anajat sau owner? 1-angajat/2-owner" << endl;
            int acces;
            cin >> acces;
            if (acces == 1)
            {
                if (cafenea)
                {
                    cafenea->display(); // afisez detaliile despre cafeneaua aleasa
                    feedback = true;

                    int aceeasi_cafenea;

                    do
                    {
                        int alegere;
                        cout << "Ce operatie doresti sa faci in aceasta cafenea? " << endl;
                        // cout << "1. Intra in lista de clienti fideli." << endl;
                        // cout << "2. Intra in meniu." << endl;
                        // cout << "3. Intra in stocuri / gestionare produse." << endl;
                        // cout << "4. Evenimente / Campanii de marketing" << endl;
                        cout << "5. Scrierea intr-un fisier csv cu date despre cafenea." << endl;
                        cout << "6. Citirea dintr-un fisier csv cu date despre cafenea." << endl;

                        cin >> alegere;
                        if (alegere == 5)
                        {
                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
                            Optiunea6::writeCSVFile(path, cafenea->getLocatie());
                        }
                        else if (alegere == 6)
                        {
                            cout << "Se afiseaza fisierele disponibile pentru citire: " << endl;

                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/" + cafenea->getLocatie() + "/";
                            listFilesInDirectory(path);

                            // aici o sa scriu la tastatura exact numele fisierului din care vreau sa citesc
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
            else if (acces == 2) // aici o sa aibe accesul la aplicatie ownerul
            {
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
}
