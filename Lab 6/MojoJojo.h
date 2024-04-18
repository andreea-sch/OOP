#pragma once

class MojoJojo
{
    float damage;
    float health;
public:
    MojoJojo(int nr);///constructorul
    int GetHealth();
    int GetDamage();
    void Atac(int x);
    void Mod_damage(int x);
};