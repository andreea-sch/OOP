#include <iostream>
#include "PowerPuffGirl.h"
#include "Profesor.h"

using namespace std; 

Profesor::Profesor(int nr_ingrediente, char ingrediente[50][50])
{
    int sugar = 0;
    int spice = 0;
    int everything_nice = 0;
    ///a doua litera e dif - o folosim pt a dif ingredientele
    for (int i = 0; i < nr_ingrediente; ++i)
        if (ingrediente[i][1] == 'u') sugar++;
        else if (ingrediente[i][1] == 'p') spice++;
        else everything_nice++;
    if (sugar < spice) nr_fetite = sugar;
    else nr_fetite = spice;
    if (everything_nice < nr_fetite) nr_fetite = everything_nice;
    girls = new PowerPuffGirl * [nr_fetite];///alocam memorie
    for (int i = 0; i < nr_fetite; ++i)
        girls[i] = nullptr;
}
const int Profesor:: GetNr()
{
    return this->nr_fetite;
}
void Profesor:: AddGirl(PowerPuffGirl* girl, int poz)
{
    girls[poz] = girl;
}
void Profesor:: AddGirls()
{
    for (int i = 0; i < nr_fetite; ++i)
        if (i % 3 == 0) AddGirl(new ButterCup(), i);
        else if (i % 3 == 1) AddGirl(new Bubbles(), i);
        else AddGirl(new Blossom(), i);
}
int Profesor:: GetGirlDamage(int poz)
{
    return girls[poz]->GetDamage();
}
int Profesor:: GetGirlHealth(int poz)
{
    return girls[poz]->GetHealth();
}
void Profesor:: Mod_damage(int poz, int x)
{
    girls[poz]->damage = x;
}
void Profesor:: Mod_health(int poz, int x)
{
    girls[poz]->health = x;
}
int Profesor:: Damage_total()
{
    int sum = 0;
    int x = this->GetNr();
    for (int i = 0; i < x; ++i)
    {
        sum += this->GetGirlDamage(i);
    }
    return sum;
}
void Profesor:: Mod_vector(int poz)
{
    swap(girls[poz], girls[this->nr_fetite - 1]);
    this->nr_fetite--;
}