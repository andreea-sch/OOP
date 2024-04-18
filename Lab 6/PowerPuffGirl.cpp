#include <iostream>
#include "PowerPuffGirl.h"

using namespace std;

ButterCup::ButterCup()///constructorul
{
    name = "ButterCup";
    damage = 15;
    health = 20;
}

const char* ButterCup:: GetGirl() ///ce fetita avem
{
    return this->name;
}

void ButterCup:: SetGirl(const char* name)
{
    this->name = name;
}

int ButterCup:: GetHealth()
{
    return this->health;
}

int ButterCup:: GetDamage()
{
    return this->damage;
}

Blossom::Blossom()///constructorul
{
    name = "Blossom";
    damage = 10;
    health = 15;
}

void Blossom:: SetGirl(const char* name)
{
    this->name = name;
}

int Blossom::GetHealth()
{
    return this->health;
}

const char* Blossom:: GetGirl() ///ce fetita avem
{
    return this->name;
}

int Blossom:: GetDamage()
{
    return this->damage;
}
    
Bubbles::Bubbles()///constructorul
{
    name = "Bubbles";
    damage = 12;
    health = 8;
}

void Bubbles::SetGirl(const char* name)
{
    this->name = name;
}

const char* Bubbles:: GetGirl() ///ce fetita avem
{
    return this->name;
}

int Bubbles:: GetHealth()
{
    return this->health;
}

int Bubbles:: GetDamage()
{
    return this->damage;
}