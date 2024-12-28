#ifndef INCHIDEREZI_H
#define INCHIDEREZI_H

#include <string>
#include "CSVHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

class inchidereZi
{
private:
    float venituri = 0.0f;
    float cheltuieli = 0.0f;
    float profit = 0.0f;

public:
    float getVenituri(const std::string &locatie);
    float getCosturi(const std::string &locatie);
    float getProfit();
    void inchidereZiCalcul(const std::string &locatie);
};

#endif
