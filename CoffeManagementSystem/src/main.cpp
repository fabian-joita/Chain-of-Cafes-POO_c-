#include <iostream>
#include <filesystem>
#include "cafe_chain.h"
#include "optiunea6.h"

using namespace std;

int main()
{
    bool continua = true;

    CAFE cafeChain; // Crearea obiectului CAFE

    // Adaugă cafenele în lista sedii
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
            cout << "Introduceți locația noii cafenele: ";
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

            if (cafenea)
            {
                cafenea->display();
                feedback = true;

                int aceeasi_cafenea;

                do
                {
                    int alegere;
                    cout << "Ce operatie doresti sa faci in aceasta cafenea? " << endl;
                    cout << "1. Intra in lista de angajati / organizarea personalului." << endl;
                    cout << "2. Intra in lista de clienti fideli." << endl;
                    cout << "3. Intra in meniu." << endl;
                    cout << "4. Intra in stocuri / gestionare produse." << endl;
                    cout << "5. Evenimente / Campanii de marketing" << endl;
                    cout << "6. Scrierea intr-un fisier csv cu date despre cafenea." << endl;
                    cout << "7. Citirea dintr-un fisier csv cu date despre cafenea." << endl;

                    cin >> alegere;
                    if (alegere == 6)
                    {
                        string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
                        Optiunea6::writeCSVFile(path, cafenea->getLocatie());
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
            cout << "-----------------------------------------------------------------------------------" << endl;
        } while (feedback == false);

        cout << "Vrei sa continui procesul de cautare a informatiilor? (1 - da, 0 - nu): " << endl;

        int rasp;
        cin >> rasp;

        if (rasp == 0)
            continua = false;
    } while (continua == true);
}
