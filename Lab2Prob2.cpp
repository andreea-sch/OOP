#include <iostream>
#include <string>
using namespace std;

class Masina {
private:
    string marca;
    double litriCombustibil;
    double consum;
    double kilometraj;

public:
    Masina(string marca, double litriCombustibil, double consum, double kilometraj);

    string getMarca();
    void setMarca(string marca);
    double getLitriCombustibil();
    void setLitriCombustibil(double litriCombustibil);
    double getConsum();
    void setConsum(double consum);
    double getKilometraj();
    void setKilometraj(double kilometraj);

    void bisnitar();
    void cursa(double distanta);
};

Masina::Masina(string marca, double litriCombustibil, double consum, double kilometraj) {
    this->marca = marca;
    this->litriCombustibil = litriCombustibil;
    this->consum = consum;
    this->kilometraj = kilometraj;
}

string Masina::getMarca() {
    return marca;
}

void Masina::setMarca(string marca) {
    this->marca = marca;
}

double Masina::getLitriCombustibil() {
    return litriCombustibil;
}

void Masina::setLitriCombustibil(double litriCombustibil) {
    this->litriCombustibil = litriCombustibil;
}

double Masina::getConsum() {
    return consum;
}

void Masina::setConsum(double consum) {
    this->consum = consum;
}

double Masina::getKilometraj() {
    return kilometraj;
}

void Masina::setKilometraj(double kilometraj) {
    this->kilometraj = kilometraj;
}

void Masina::bisnitar() {
    if (kilometraj >= 1000)
        kilometraj -= 1000;
}

void Masina::cursa(double distanta) {
    double combustibilNecesar = distanta * consum;
    if (combustibilNecesar <= litriCombustibil) {
        kilometraj += distanta;
        litriCombustibil -= combustibilNecesar;
    }
    else {
        cout << "Nu exista suficient combustibil pentru a efectua cursa." << endl;
    }
}

int main() {
    Masina masinaMea("Toyota", 50.0, 0.08, 10000.0);

    cout << "Marca masinii: " << masinaMea.getMarca() << endl;
    cout << "Kilometraj: " << masinaMea.getKilometraj() << endl;
    cout << "Combustibil ramas: " << masinaMea.getLitriCombustibil() << " litri" << endl;

    masinaMea.cursa(200);
    cout << "Kilometraj dupa cursa: " << masinaMea.getKilometraj() << endl;
    cout << "Combustibil ramas dupa cursa: " << masinaMea.getLitriCombustibil() << " litri" << endl;

    masinaMea.bisnitar();
    cout << "Kilometraj dupa bisnita: " << masinaMea.getKilometraj() << endl;

    return 0;
}
