#include <iostream>
#include <vector>

using namespace std;

enum ContactType
{
    FRIEND,
    ACQUAINTANCE,
    COLLEAGUE
};

class Contact
{
public:
    const char* name;
    virtual const char* Getname() = 0;
    virtual ContactType getType() = 0;
};

class Friend : public Contact
{
    const char* phone;
    const char* data_nasterii;
    const char* adresa;
public:
    Friend(const char* nume,const char* data,const char* adresa,const char* phone)
    {
        this->name = nume;
        this->data_nasterii = data;
        this->adresa = adresa;
        this->phone = phone;
    }
    ~Friend()
    {
        delete[] phone;
        delete[] data_nasterii;
        delete[] adresa;
        delete[] name;
    }
    const char* Getname()
    {
        return this->name;
    }
    ContactType getType()
    {
        return ContactType::FRIEND;
    }
    const char* GetphoneNumber()
    {
        return this->phone;
    }
    const char* getaddress()
    {
        return this->adresa;
    }
    const char* getdatanasterii()
    {
        return this->data_nasterii;
    }
};

class Acquaintance : public Contact
{
    const char* phone;
public:
    Acquaintance(const char* nume, const char* phone)
    {
        this->name = nume;
        this->phone = phone;
    }
    ~Acquaintance()
    {
        delete[] name;
        delete[] phone;
    }
    ContactType getType()
    {
        return ContactType::ACQUAINTANCE;
    }
    const char* Getname()
    {
        return this->name;
    }
    const char* Getphone()
    {
        return this->phone;
    }
};

class Colleague : public Contact
{
    const char* phone;
    const char* companie;
    const char* adresa;
public:
    Colleague(const char* nume, const char* phone, const char* companie, const char* adresa)
    {
        this->name = nume;
        this->phone = phone;
        this->companie = companie;
        this->adresa = adresa;
    }
    ~Colleague()
    {
        delete[] name;
        delete[] phone;
        delete[] companie;
        delete[] adresa;
    }
    ContactType getType()
    {
        return ContactType::COLLEAGUE;
    }
    const char* Getname()
    {
        return this->name;
    }
    const char* getphone()
    {
        return this->phone;
    }
    const char* getcompanie()
    {
        return this->companie;
    }
    const char* getadresa()
    {
        return this->adresa;
    }
};

class AddressBook
{
    vector<Contact*> contacts;
public:
    Contact* cautaContact(const char* nume)
    {
        for (auto contact : contacts)
            if (contact->Getname() == nume) return contact;
        return nullptr;
    }
    vector<Friend*> listFriends()
    {
        vector<Friend*>friends;
        for (auto contact : contacts)
            if (contact->getType() == ContactType::FRIEND)
                friends.push_back(static_cast<Friend*>(contact)); //il convertim de la Conact la Friend
        return friends;
    }
    void stergeContact(const char* nume)
    {
        for (auto it = contacts.begin(); it != contacts.end(); it++)
            if (nume == (*it)->Getname())
            {
                contacts.erase(it); //il eliminam
                break;
            }
    }
    void adaugacontact(Contact* contact)
    {
        contacts.push_back(contact);
    }
};

int main()
{
    AddressBook addressBook;
    Friend* f = new Friend("Alina", "1990-01-01", "1234567890", "123 Street A");
    Acquaintance* a = new Acquaintance("Andrei", "2345678901");
    Colleague* c = new Colleague("Stefan", "3456789012", "ABC Corp", "456 Street B");
    addressBook.adaugacontact(f);
    addressBook.adaugacontact(a);
    addressBook.adaugacontact(c);
    Contact* contact = addressBook.cautaContact("Alina");
    if (contact)
    {
        cout << "Gasit: " << contact->Getname() << "\n";
    }
    else
    {
        cout << "Nu a fost gasit." << "\n";
    }
    vector<Friend*> friends = addressBook.listFriends();
    for (auto it : friends)
    {
        cout << "Friend: " << it->Getname() << "\n";
    }
    addressBook.stergeContact("Andrei");
    contact = addressBook.cautaContact("Andrei");
    if (contact)
    {
        cout << "Gasit: " << contact->Getname() << "\n";
    }
    else
    {
        cout << "Nu a fost gasit." << "\n";
    }
    return 0;
}