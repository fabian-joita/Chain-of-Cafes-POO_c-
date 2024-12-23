// Ingredient.h
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>

using namespace std;

struct Ingredient
{
    string name;
    int gramaj;

    Ingredient(const string &ingredientName, int ingredientGramaj)
        : name(ingredientName), gramaj(ingredientGramaj) {}

    string getName() const; // metoda getName() ar trebui să fie const
    int getGramaj() const;  // metoda getGramaj() ar trebui să fie const
};

#endif // INGREDIENT_H
