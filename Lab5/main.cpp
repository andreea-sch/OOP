#include <iostream>
#include "Number.h"
using namespace std;

int main()
{
    Numar n1("10110010", 2); // Numarul n1 initializat cu valoarea "10110010" in baza 2
    Numar n2("734", 8); // Numarul n2 initializat cu valoarea "734" in baza 8
    Numar n3("FF", 16); // Numarul n3 initializat cu valoarea "FF" in baza 16

    printf("n1 are %d cifre si este scris in baza %d\n", n1.GetDigitsCount(), n1.GetBase()); // Afiseaza numarul de cifre si baza numarului n1
    for (int tr = 0; tr < n1.GetDigitsCount(); tr++)
    {
        printf("n1[%d]=%c\n", tr, n1[tr]); // Afiseaza fiecare cifra a numarului n1
    }
    n1.Print(); // Afiseaza numarul n1
    n2.Print(); // Afiseaza numarul n2
    ///n3.Print();///MEU
    n1 = (n2 + n3 - n1) + n1; // dupa aceasta, n1 va fi in baza 16

    ///n1.Print();///MEU

    n1.SwitchBase(2); // Schimba baza numarului n1 la 2
    n1.Print(); // Afiseaza numarul n1

    if (n1 > n2) printf("n1 este mai mare decat n2\n");
    else printf("n2 este mai mare decat n1\n");

    Numar n4 = 12345; // n4 va fi in baza 10
    n1 = 255; // n1 va fi 11111111 (valoarea 255 din baza 10 in baza 2)
    n4 += n1; // Adauga n1 la n4
    n4.Print(); // Afiseaza numarul n4

    n4 = "13579"; // n4 isi mentine baza (10) si va fi 13579
    n4.Print(); // Afiseaza numarul n4
    --n4; // prima cifra din n4 va fi eliminata ==> n4 devine 3579
    n4.Print(); // Afiseaza numarul n4
    n4--; // ultima cifra din n4 va fi eliminata ==> n4 devine 357
    n4.Print(); // Afiseaza numarul n4
    return 0;
}
