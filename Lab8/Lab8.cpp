#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cctype> ///pt fct de convertire litere

using namespace std;

ifstream fin("input.txt");

vector<string> spargere(const string& sir, const string& del)
{
    vector<string> rez;///vectorul cu cuvintele
    size_t i = sir.find_first_not_of(del);///cauta prima poz din sir care nu este delimitator
    while (i != string::npos)
    {
        size_t end = sir.find_first_of(del, i);///cauta de la poz i prima poz din del 
        rez.push_back(sir.substr(i, end - i));///adauga la rez cuv format din cele end-i litere pornind de la i
        i = sir.find_first_not_of(del, end);///mergem mai departe cu i la primul car din del pornind de la end
    }
    return rez;
}

string transforma_mici(const string& word) ///transformam cuvntul trecand toate literele mari in litere mici
{
    string rez;
    for (int i = 0; i < word.length(); ++i)
    {
        rez += tolower(word[i]);///transformam litera si o adaugam
    }
    return rez;
}

class Comparator ///comparatorul pt coada cu prioritati
{
public:
    bool operator()(pair<string, int>& a, pair<string, int>& b)
    {
        if (a.second != b.second) return a.second < b.second;
        return a.first > b.first;
    }
};

int main()
{
    string sir;
    getline(fin, sir); ///citim sirul din fisier
    string del = " .?!,"; ///delimitatorii
    vector<string>cuv = spargere(sir, del);///luam un vector de cuvinte in care putem cuv dupa spargere
    map<string, int> mapcuv;///mapul in care key este cuv si val este nr de ap a cuv
    for (const auto& word : cuv)///parcurgem cuv din vectorul de cuvinte cu variabila word care are tipul nespecificat
    {
        string cuv_mic = transforma_mici(word);///transformam literele mari in litere mici din fiecare cuv
        mapcuv[cuv_mic]++;///creste val din map de la poz cuv_mic cu 1 (inca o aparitie)
    }
    priority_queue<pair<string, int>, vector<pair<string, int>>, Comparator>q;///declaram coada cu prioritati in care 
    ///vom pune elementele din map care sunt de forma unor perechi <string,int> care vor fi stocare intr-un vector 
    ///de acest tip si vor fi sortate conform comparatorului
    for (auto& p : mapcuv)///cu p parcurgem map ul
    {
        q.push(p);///ad fiecare elem din map la coada
    }
    while (!q.empty())///cat timp coada nu e vida
    {
        cout << q.top().first << "=>" << q.top().second << "\n";///afisam cuv din vf cozii si nr lui de aparitii
        q.pop();///il eliminam
    }
    fin.close();///inchidem fis din care am citit
    return 0;
}