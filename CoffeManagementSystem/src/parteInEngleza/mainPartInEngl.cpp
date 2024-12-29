#include "parteInEngleza/mainPartInEngl.h"
using namespace std;

void progInEnglish()
{
    bool continues = true;
    float revenue = 0, expenses = 0;
    CAFE cafeChain;

    Display *cafe1 = new Display();
    cafe1->setLocation("Bucharest");
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
        cout << "Welcome to CafeaBuna!" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;

        cout << "Available Cafes: " << endl;
        cafeChain.displayCafeLocations();
        cout << "-----------------------------------------------------------------------------------" << endl;

        bool feedback = true;
        do
        {
            cout << "-----------------------------------------------------------------------------------" << endl;
            int option;
            cout << "Which cafe would you like to continue with? (Insert number)" << endl;
            cin >> option;
            Sediu *cafe = cafeChain.getPtrUnit(option);
            cafe->loadEmployeesFromFile("Employees_Roles.csv", cafe->getLocatie());

            cout << "Would you like to access the app as an employee or owner? 1-employee / 2-owner" << endl;
            int access;
            cin >> access;
            if (access == 1)
            {
                if (cafe)
                {
                    cafe->display();
                    feedback = true;

                    int stayInCafe;
                    do
                    {
                        int choice;
                        cout << "-----------------------------------------------------------------------------------" << endl;
                        cout << "What operation would you like to perform in this cafe?" << endl;
                        cout << "1. Change employee details/products prices/ingredient stock." << endl;
                        cout << "2. Add an order." << endl;
                        cout << "3. Close the day (calculate revenue = income - expenses) => delete orders." << endl;
                        cout << "4. Manage Special Events (add, show, calculate income/cost)." << endl;
                        cout << "5. Write data to a CSV file about the cafe." << endl;
                        cout << "6. Read data from a CSV file about the cafe." << endl;
                        cout << "-----------------------------------------------------------------------------------" << endl;

                        string eventPath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH/";

                        // de schimbat aici fisierul
                        string fullEventPath = eventPath + cafe->getLocatie() + "/SpecialEvents.csv";
                        ManagerEvenimente::getInstance()->getGestionare().citesteEvenimenteDinFisier(fullEventPath);

                        cin >> choice;
                        cout << "-----------------------------------------------------------------------------------" << endl;
                        if (choice == 1)
                        {
                            cout << "Which details would you like to change? (employees/products/stocks)" << endl;
                            string change;
                            cin >> change;
                            schimbare_detalii(change, cafe->getLocatie());
                        }
                        else if (choice == 2)
                        {
                            adaugareComanda(cafe->getLocatie(), &expenses);
                        }
                        else if (choice == 3)
                        {
                            inchidereZi zi;
                            zi.inchidereZiCalcul(cafe->getLocatie());
                        }
                        else if (choice == 4)
                        {
                            int eventChoice;
                            do
                            {
                                cout << "-----------------------------------------------------------------------------------" << endl;
                                cout << "---------------- Manage Special Events ----------------" << endl;
                                cout << "1. Add Special Event." << endl;
                                cout << "2. Show all Special Events." << endl;
                                cout << "3. Calculate Total Income from Events." << endl;
                                cout << "4. Calculate Total Costs from Events." << endl;
                                cout << "0. Back to the main menu." << endl;
                                cout << "-----------------------------------------------------------------------------------" << endl;
                                cin >> eventChoice;
                                cout << "-----------------------------------------------------------------------------------" << endl;

                                if (eventChoice == 1)
                                {
                                    string name, date, timeInterval;
                                    float organizationCost, participationCost;
                                    int availableSeats, occupiedSeats;
                                    string description;

                                    cout << "Enter the event name: ";
                                    cin.ignore();
                                    getline(cin, name);

                                    cout << "Enter the event date (YYYY-MM-DD): ";
                                    cin >> date;

                                    cout << "Enter the time interval (HH:MM-HH:MM): ";
                                    cin >> timeInterval;

                                    cout << "Enter the organization cost: ";
                                    cin >> organizationCost;

                                    cout << "Enter the participation cost per person: ";
                                    cin >> participationCost;

                                    cout << "Enter the number of available seats: ";
                                    cin >> availableSeats;

                                    cout << "Enter the number of occupied seats: ";
                                    cin >> occupiedSeats;

                                    cout << "Enter the event description: ";
                                    cin.ignore();
                                    getline(cin, description);
                                    cout << "-----------------------------------------------------------------------------------" << endl;

                                    Eveniment event(name, date, timeInterval, organizationCost, participationCost, availableSeats, occupiedSeats, description);
                                    ManagerEvenimente::getInstance()->getGestionare().salveazaEvenimenteInFisier(fullEventPath, event);
                                    ManagerEvenimente::getInstance()->getGestionare().citesteEvenimenteDinFisier(fullEventPath);

                                    cout << "Event successfully added!" << endl;
                                }
                                else if (eventChoice == 2)
                                {
                                    cout << "-----------------------------------------------------------------------------------" << endl;
                                    cout << "---------------- List of Special Events ----------------" << endl;
                                    ManagerEvenimente::getInstance()->getGestionare().afiseazaToateEvenimentele();
                                    cout << "-----------------------------------------------------------------------------------" << endl;
                                }
                                else if (eventChoice == 3)
                                {
                                    float totalEventRevenue = ManagerEvenimente::getInstance()->getGestionare().calculVenitTotal();
                                    cout << "Total revenue from special events: " << totalEventRevenue << " RON" << endl;
                                }
                                else if (eventChoice == 4)
                                {
                                    float totalEventCosts = ManagerEvenimente::getInstance()->getGestionare().calculCostTotal();
                                    cout << "Total costs of special events: " << totalEventCosts << " RON" << endl;
                                }
                                else if (eventChoice != 0)
                                {
                                    cout << "Invalid option!" << endl;
                                }
                            } while (eventChoice != 0);
                        }
                        else if (choice == 5)
                        {
                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH";
                            Optiunea6::writeCSVFile(path, cafe->getLocatie());
                        }
                        else if (choice == 6)
                        {
                            string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH" + cafe->getLocatie() + "/";
                            listFilesInDirectory(path);

                            string fileName;
                            cout << "Enter the exact name of the file you want to read as shown above: " << endl;
                            cin >> fileName;
                            path = path + fileName;
                            Optiunea7::readCSVFile(path);
                        }

                        cout << "Do you want to stay in this cafe for more operations? (yes: 1 / no: 0)" << endl;
                        cin >> stayInCafe;
                    } while (stayInCafe == 1);
                }
                else
                {
                    cout << "Invalid option!" << endl;
                    feedback = false;
                }
            }
            else if (access == 2)
            {
                // Owner logic (optional)
            }
            else
            {
                cout << "Invalid option!" << endl;
            }

            cout << "-----------------------------------------------------------------------------------" << endl;

        } while (feedback == false);

        cout << "Do you want to continue searching for information? (1 - yes, 0 - no): " << endl;
        int answer;
        cin >> answer;

        if (answer == 0)
            continues = false;
    } while (continues == true);
}
