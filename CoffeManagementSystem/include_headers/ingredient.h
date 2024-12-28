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

    string getName() const;
    int getGramaj() const;
};

#endif
