#include <iostream>
#include <cstring>

using namespace std;

template <typename K, typename V> ///ii dam 2 tipuri de date pt key si val
class Map
{
private:
    struct MapIt
    {
        K key;
        V value;
        int index;
    };
    MapIt* items;
    int n = 0;///nr de elem din vectorul pt map
public:
    Map() ///constructorul
    {
        this->items = nullptr;///vectorul e vid initial
        this->n = 0;///are 0 elemente
    }
    ~Map() ///destructorul
    {
        delete[] items; ///eliberam memoria folosita pt vectorul dinamic
    }
    int Count() ///fct care returneaza nr de elem din map
    {
        return this->n;
    }
    void Clear() ///care sterge intregul map
    {
        delete[] items; ///eliberam memoria folosita pt vectorul dinamic
        items = nullptr; ///il reinitializam cu vectorul vid
        this->n = 0;///resetam nr de elem la 0
    }
    void Set(const K& key, const V& val) ///pt a seta o valoare unei chei
    {
        for (int i = 0; i < this->n; ++i) ///cautam daca exista cheia in map
            if (items[i].key == key) ///daca am gasit cheia
            {
                items[i].value = val; ///modificam valoarea
                return; ///ne oprim
            }
        ///daca nu am gasit trebuia adaugat - folosim un vector temporar pt alocarea memoriei
        MapIt* temp = new MapIt[n + 1]; ///alocam memorie
        for (int i = 0; i < this->n; ++i) ///copiem elementele curente
            temp[i] = items[i];
        temp[n].key = key; ///adaugam noul element
        temp[n].value = val;
        temp[n].index = n;
        n++; ///creste nr de elem
        delete[] items; ///golim items
        items = temp;///copiem vectorul temporar in items
    }
    bool Get(const K& key, V& value)
    {
        for (int i = 0; i < n; i++) ///cauta cheia key
            if (items[i].key == key) ///daca o gaseste
            {
                value = items[i].value; ///copiaza valoarea din campul val in parametrul value
                return true; ///returneaza true
            }
        return false; ///altfel returneaza false
    }
    bool Delete(const K& key) ///pt a sterge o anumita cheie
    {
        for (int i = 0; i < n; i++) ///cautam cheia
            if (items[i].key == key) ///daca am gasit cheia
            {   ///folosim din nou un vector temporar pt a sterge
                MapIt* temp = new MapIt[n - 1]; ///alocam memorie
                for (int j = 0; j < i; j++) ///copiem elementele dinaintea lui
                    temp[j] = items[j];
                for (int j = i; j < n - 1; j++) ///copiem elementele de dupa el
                {
                    items[j + 1].index--; ///scadem cu 1 indexul fiecarui element
                    temp[j] = items[j + 1]; ///copiem elementul
                }
                n--; ///actualizam nr de elemente
                delete[] items; ///golim ce era in vecroul items
                items = temp; ///copiem noul vector
                return true; ///returnam true
            }
        return false; ///daca nu am gasit cheia
    }
    bool Includes(const Map<K, V>& map) ///verificam daca map ul dat este inclus in map ul nostru
    {
        if (map.n > n)  return false; ///daca are mai multe elem decat map ul nostru nu are cum sa fie inclus
        for (int i = 0; i < map.n; i++) ///parcurgem toate elementele map ului dat
        {
            bool ok = 0;
            for (int j = 0; j < n; j++) ///cautam elem i in map ul nostru
                if (map.items[i].key == items[j].key) ///daca l-am gasit
                {
                    ok = 1;
                    break; ///iesim
                }
            if (!ok)  return false; ///daca nu am gasit un element returnam false
        }
        return true;
    }
    V& operator[] (const K& key)
    {
        for (int i = 0; i < n; i++) ///cautam cheia 
            if (items[i].key == key)
                return items[i].value; ///ii returnam valoarea
        Set(key, "");
        return items[n - 1].value;
    }
    const MapIt* begin() const ///incepultul map ului
    {
        return &items[0];
    }
    const MapIt* end() const ///finalul map ului
    {
        return &items[n];
    }
};

int main()
{
    Map<int, const char*> m; ///trebuie sa declar template ul Map
    m[10] = "C++";
    m[20] = "test";
    m[30] = "Poo";
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
    m[20] = "result";
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
    return 0;
}