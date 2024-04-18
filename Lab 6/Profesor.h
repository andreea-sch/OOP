#pragma once
#include "PowerPuffGirl.h"

class Profesor
{
    int nr_fetite;
    PowerPuffGirl** girls; ///vectorul de fetite
public:
    Profesor(int nr_ingrediente, char ingrediente[50][50]);
    const int GetNr();
    void AddGirl(PowerPuffGirl* girl, int poz);
    void AddGirls();
    int GetGirlDamage(int poz);
    int GetGirlHealth(int poz);
    void Mod_damage(int poz, int x);
    void Mod_health(int poz, int x);
    int Damage_total();
    void Mod_vector(int poz);
};