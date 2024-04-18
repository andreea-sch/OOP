#include <iostream>
#include <cstdlib> 
#include <cstring>
#include "PowerPuffGirl.h"
#include "Profesor.h"
#include "MojoJojo.h"

using namespace std;

MojoJojo::MojoJojo(int nr)///constructor
{
    damage = 40;
    health = 20;
}
int MojoJojo:: GetHealth()
{
    return this->health;
}
int MojoJojo:: GetDamage()
{
    return this->damage;
}
void MojoJojo:: Atac(int x)
{
    if (this->health >= x) this->health -= x;
    else this->health = 0;
}
void MojoJojo:: Mod_damage(int x)
{
    this->damage = x;
}