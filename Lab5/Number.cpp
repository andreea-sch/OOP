#include "Number.h"
#include <iostream>

Number::Number(const char* value, int base) ///din baza base in baza 10
{
    ///this->as_char = (char*)value;
    this->base = base;
    this->base10 = 0;
    int lg = 0;
    while (value[lg] != '\0') lg++;
    this->as_char = new char[lg + 1];
    memcpy(this->as_char, value, lg + 1);
    for (int i = 0; i<lg; i++)
        if ('0' <= as_char[i] && as_char[i] <= '9') this->base10 = this->base10 * base + value[i] - '0';
        else this->base10 = this->base10 * base + value[i] - 'A' + 10;
}

Number::Number(int nr) ///cand ni se da un nr, baza va fi implicit baza 10
{
    this->base = 10;
    this->base10 = nr;///nr in baza 10 e chiar el
    int aux = nr;
    int lg = 0;///vrem sa alfam nr de cifre ale nr pt a putea aloca memorie
    while (aux != 0) { lg++; aux /= 10; } 
    this->as_char = new char[lg + 1];///alocam memorie
    for (int i = lg - 1; i >= 0; i--)///completam sirul incepand de la final cu cifrele nr
    {
        this->as_char[i] = (nr % 10) + '0';///completam vactorul cu cifrele in char
        nr /= 10;
    }
    this->as_char[lg] = '\0';
}

Number::Number(const Number& other) ///constructor de copiere -> din other in this
{
    this->base = other.base;
    this->base10 = other.base10;
    int lg = 0;///calculam lg lui as_char din other pt a putea aloca memorie pt as_char din this
    while (other.as_char[lg] != '\0') lg++;///nr se termina cu enter
    this->as_char = new char[lg + 1];///declaram memorie pt vectorul din this
    memcpy(this->as_char, other.as_char, lg + 1);///copiem in this vectorul as_char din other 
}

Number::Number(Number&& other) ///constructorul de mutare -> muta si sterge other
{
    this->base = other.base;///copiem baza;
    this->base10 = other.base10;///copiem nr in b10
    other.base = 0;
    other.base10 = 0;
    int lg = 0;///calculam lg lui as_char din other pt a putea aloca memorie pt as_char din this
    while (other.as_char[lg] != '\0') lg++;///nr se termina cu enter
    this->as_char = new char[lg + 1];///declaram memorie pt vectorul din this
    memcpy(this->as_char, other.as_char, lg + 1);///copiem in this vectorul as_char din other 
    other.as_char = nullptr;
}

Number::~Number() ///destructor
{
	delete[] this->as_char;
}

Number& Number::operator=(const Number& other) ///de copiere
{
    if (this != &other) ///daca trebuie sa ii dam lui this ceva de la alta adresa -> facem atribuirea
    {
        delete[] this->as_char;///stergem ce era inainte in this
        this->base = other.base;///schimbam baza
        this->base10 = other.base10;///nr in baza 10
        int lg = 0;
        while (other.as_char[lg] != '\0') lg++;
        this->as_char = new char[lg + 1];///alocam memorie
        memcpy(this->as_char, other.as_char, lg + 1);///copiem din other in this vectorul de char
    }
    return *this;
}

Number& Number::operator=(Number&& other) ///de mutare
{
    if (this != &other) ///daca trebuie sa ii dam lui this ceva de la alta adresa -> facem atribuirea
    {
        delete[] this->as_char;///stergem ce era inainte in this
        this->base = other.base;///schimbam baza
        this->base10 = other.base10;///nr in baza 10
        int lg = 0;
        while (other.as_char[lg] != '\0') lg++;///o calculam
        this->as_char = new char[lg + 1];///alocam memorie
        memcpy(this->as_char, other.as_char, lg + 1);///copiem din other in this vectorul de char
        ///stergem din other
        other.base = 0;
        other.base10 = 0;
        other.as_char = nullptr;
    }
    return *this;
}

Number& Number::operator=(const char* value) ///ne trebuie pt n4="13579"
{
    ///baza lui nu se va schimba -> transformam sirul din b10 in baza lui
    char* rez = Number::Convertire(value, 10, this->base);///convertim sirul ala care e un nr in b10 intr-un sir care e un nr in base
    int lg = 0;///calculam lungimea
    while (rez[lg] != '\0') lg++;
    delete[] this->as_char;///stergem ce era in el anterior
    this->as_char = new char[lg + 1];///alocam memorie
    memcpy(this->as_char, rez, lg + 1);///punem nr obtinut
    this->base10 = 0;
    for (int i = 0; value[i] != 0; i++)///il trecem in baza 10
        this->base10 = this->base10 * base + value[i] - '0';
    return *this;
}

void Number::Print()
{
    std::cout << "Valoare:" << this->as_char << " " << "Baza:" << this->base << " " << "Reprezentare in baza 10:" << this->base10 << "\n";
}

int Number::GetDigitsCount()
{
    int ct = 0;
    while (this->as_char[ct] != '\0') ct++;
    return ct;
}

int Number::GetBase()
{
    return this->base;
}

Number operator+(const Number& n1, const Number& n2) ///functie friend pt adunare
{
    ///determinam baza mai mare
    int baza = n1.base;
    if (n2.base > baza) baza = n2.base;
    int suma = n1.base10 + n2.base10;///adunam reprezentarile in baza 10
    char* result = Number::IntToChar(suma);///trecem suma intr-un sir de caractere pe care sa il convertim in baza base
    result = Number::Convertire(result, 10, baza);///il convertim din b10 in base
    Number n(result, baza);///creem un obiect nou care este rezultatul adunarii -> apelam constructorul nr 1
    ///n.base10 = suma;
    delete[] result;///l-am creat dinamic -> trebuie sters
    return n;///returnam obiectul care e rez sumei
}

Number operator+=(Number& n1,Number& n2)
{
    n1.base10 = n1.base10 + n2.base10;
    char* result = Number::IntToChar(n1.base10);///trecem suma intr-un sir de caractere pe care sa il convertim in baza lui n1
    result = Number::Convertire(result, 10, n1.base);///il convertim din b10 in baza lui n1
    int lg = 0;///calculam lungimea
    while (result[lg] != '\0') lg++;
    delete[] n1.as_char;///stergem ce era in el anterior
    n1.as_char = new char[lg + 1];///alocam memorie
    memcpy(n1.as_char, result, lg + 1);///punem nr obtinut
    return n1;///obiectul care e rez sumei
}

Number operator-(const Number& n1, const Number& n2) ///functie friend pt scadere
{
    ///determinam baza mai mare
    int baza = n1.base;
    if (n2.base > baza) baza = n2.base;
    int suma = n1.base10 - n2.base10;///scadem reprezentarile in baza 10
    char* result = Number::IntToChar(suma);///trecem diferenta intr-un sir de caractere pe care sa il convertim in baza base
    result = Number::Convertire(result, 10, baza);///il convertim din b10 in base
    Number n(result, baza);///creem un obiect nou care este rezultatul scaderii -> apelam constructorul nr 1
    ///n.base10 = suma;
    delete[] result;///l-am creat dinamic -> trebuie sters
    return n;///returnam obiectul care e rez scaderii
}

char& Number::operator[](int index) ///cifra din nr de la poz index
{
    return this->as_char[index];
}

bool Number::operator<(const Number& other)
{
    if (this->base10 < other.base10)  
    {
        return 1;
    }
    return 0; 
}

bool Number::operator>(const Number& other)
{
    if (this->base10 > other.base10)  
    {
        return 1;
    }
    return 0; 
}

bool Number::operator<=(const Number& other)
{
    if (this->base10 <= other.base10)  
    {
        return 1;
    }
    return 0;
}

bool Number::operator>=(const Number& other)
{
    if (this->base10 >= other.base10)  
    {
        return 1;
    }
    return 0; 
}

bool Number::operator==(const Number& other)
{
    if (this->base10 == other.base10)  
    {
        return 1;
    }
    return 0; 
}

bool Number::operator!=(const Number& other)
{
    if (this->base10 != other.base10)  
    {
        return 1;
    }
    return 0; 
}

Number& Number::operator--()///prefixat ->eliminam bitul din stg
{
    int lg = 0;///lungimea
    while (this->as_char[lg] != '\0') lg++;
    if (lg == 0) return *this;///daca are 0 cifre nu avem ce elimina
    ///mutam totul cu o poz sprea stg
    for (int i = 0; i < lg; ++i)
        this->as_char[i] = this->as_char[i + 1];
    this->base10 = 0;
    for (int i = 0; i < lg-1; i++)
        if ('0' <= as_char[i] && as_char[i] <= '9') this->base10 = this->base10 * base + as_char[i] - '0';
        else this->base10 = this->base10 * base + as_char[i] - 'A' + 10; 
    return *this;
}

Number& Number::operator--(int)///postfixat ->elimina bitul din drp
{
    int  lg = 0;///lungimea
    while (this->as_char[lg] != '\0') lg++;
    this->as_char[lg - 1] = '\0';///stergem ultimul elem
    this->base10 = 0;
    for (int i = 0; i < lg-1; i++)
        if ('0' <= this->as_char[i] && this->as_char[i] <= '9') this->base10 = this->base10 * base + this->as_char[i] - '0';
        else this->base10 = this->base10 * base + this->as_char[i] - 'A' + 10; 
    return *this;
}

void Number::SwitchBase(int newBase)
{
    if (this->base == newBase) return;///daca e ac baza nu facem nimc
    char* nr = Number::Convertire(this->as_char, this->base, newBase);///convertim in noua baza
    this->base = newBase;///schimbam baza
    delete[] this->as_char;///stergem ce era inainte aici
    int lg = 0;///calculam lungimea
    while (nr[lg] != '\0') lg++;
    this->as_char = new char[lg + 1];///alocam memorie
    memcpy(this->as_char, nr, lg + 1);///copiem nr in as_char
    delete[] nr;///nr a fost declarat dinamic deci trebuie eleberata memoria
}

char* Number::Convertire(const char* value, int baza_initiala, int baza_finala)
{
    ///din baza curenta in baza 10
    int lg = 0;///vedem lungimea
    while (value[lg] != '\0') lg++;
    int rez = 0;///formam nr din vectorul de char
    for (int i = 0; i < lg; ++i) ///parcuregm vectorul
    {
        int cif=0;
        if ('0' <= value[i] && value[i] <= '9') cif = value[i] - '0';
        if ('A' <= value[i] && value[i] <= 'F') cif = value[i] - 'A' + 10;
        rez = rez * baza_initiala + cif;
    }
    ///transformam din b10 in baza_finala
    ///trebuie sa fie un vector de tip char -> baza_finala>10
    char* nr_nou = new char[16];///nu poate avea mai mult de 16 cif
    int i = 0;///pt parcurgere -> pt completarea poz cu poz
    while (rez != 0)
    {
        int cif = rez % baza_finala;///luam resturile
        char ciff;///transformam cifra in char
        if (cif < 10) ciff = cif + '0';
        else ciff = cif + 'A' - 10;
        nr_nou[i++] = ciff;///punem cifra in vectorul nr
        rez /= baza_finala;
    }
    if (i == 0) ///daca nr era 0 -> caz particular
        nr_nou[i++] = '0'; //punem 0
    nr_nou[i] = '\0'; ///punem NULL pe ultima poz
    ///in nr_nou cifrele sunt invers decat ar trebui -> la inversam 
    for (int j = 0; j < i / 2; ++j)
    {
        char aux = nr_nou[j];
        nr_nou[j] = nr_nou[i - j - 1];
        nr_nou[i - j - 1] = aux;
    }
    return nr_nou;///adresa spre vectorul care contine nr
}

char* Number::IntToChar(int nr)
{
    int aux = nr, lg = 0;///determinam nr de cifre
    while (aux != 0) { lg++; aux /= 10; }
    char* value = new char[lg + 1];///alocam memorie pt char ul pe care incercam sa il formam
    for (int i = lg - 1; i >= 0; i--)
    {
        value[i] = (nr % 10) + '0';///fiecare cifra trecuta in char
        nr /= 10;
    }
    value[lg] = '\0';
    return value;///returnam sirul format
}