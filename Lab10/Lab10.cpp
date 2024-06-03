#include <iostream>
#include <exception>

using namespace std;

class IndexOutOfBoundsException : public exception 
{
    virtual const char* what() const throw() 
    {
        return "Index is out of bounds!";
    }
};

class Compare ///pentru comparare
{
public:
    virtual int CompareElements(void* e1, void* e2) = 0;
};

template<class T> 
class ArrayIterator 
{
private:
    T** List;
    int Current; //nr elemente din lista
public:
    ArrayIterator() : List(nullptr), Current(0) {} //Constructor - initializare lista vida
    ArrayIterator(T** list, int current) : List(list), Current(current) {} //constructor care are o lista ca parametru
    ArrayIterator<T>& operator ++ () ///operator ++ prefixat
    {
        ++Current; //creste cu 1 nr de elemente din lista
        return *this;
    }
    ArrayIterator<T>& operator -- () ///operator -- prefixat
    {
        --Current; ///scade cu 1 nr de elemente din lista
        return *this;
    }
    ArrayIterator<T> operator ++ (int val) //operator ++ postfixat -> cu parametru pt a face distinctia
    {
        ArrayIterator<T> temp = *this; //il preluam inainte de a creste nr de elem 
        ++Current; //creste nr de elem
        return temp; //il returnam, varianta dinainte de a creste nr de element
    }
    ArrayIterator<T> operator -- (int val) //operator -- postfixat -> cu parametru pt a face distinctia
    {
        ArrayIterator<T> temp = *this; //il preluam inainte de a scadea nr de elem 
        --Current; //scadem nr de elem
        return temp; //il returnam, varianta dinainte de a scadea nr de element
    }

    bool operator=(ArrayIterator<T>& other) ///operator =
    {
        this->List = other.List; //copiem lista
        this->Current = other.Current; //copiem nr de elemente
        return true;
    }
    bool operator!=(ArrayIterator<T> other) ///operator !=
    {
        return this->Current != other.Current; ///verifica daca nr de elemente este egal
    }
    T* GetElement() //returneaza ultimul element
    {
        if (this->Current >= 0) //daca are macar un element(cel de pe poz 0)
            return List[Current]; //il returnam
        return nullptr;
    }
};
template<class T>
class Array
{
private:
    T** List; // lista cu pointeri la obiecte de tipul T*
    int Capacity; // dimensiunea listei de pointeri
    int Size; // cate elemente sunt in lista
public:
    Array() // Lista nu e alocata, Capacity si Size = 0
    { 
        this->List = nullptr;
        this->Capacity = 0;
        this->Size = 0;
    }
    ~Array() // destructor
    { 
        delete[] this->List;
    }
    Array(int capacity) // Lista e alocata cu 'capacity' elemente
    { 
        this->Capacity = capacity; ///completam capacitatea care e data
        this->Size = 0;
        this->List = new T * [capacity]; ///alocam memorie
    }
    Array(const Array<T>& otherArray) // constructor de copiere
    { 
        this->Capacity = otherArray.Capacity; ///copiem capacity
        this->Size = otherArray.Size; ///copiem size
        for (int i = 0; i < this->Size; i++)
            this->List[i] = new T(*otherArray.List[i]);
    }

    T& operator[] (int index) // arunca exceptie daca index este out of range
    { 
        if (index < 0 || index >= this->Size) //daca nu are dimensiune potrivita(iese din vector)
            throw IndexOutOfBoundsException();
        return *List[index];//daca e bun returnam elementul
    }

    const Array<T>& operator+=(const T& newElem) // adauga un element de tipul T la sfarsitul listei si returneaza this
    { 
        if (this->Size >= this->Capacity) Resize(2 * Capacity);//redimensionam daca este nevoie
        List[Size++] = new T(newElem); //adaugam elemntul
        return *this;
    }
    const Array<T>& Insert(int index, const T& newElem) // adauga un element pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
    { 
        if (index < 0 || index > this->Size) ///daca indexul este invalid
            throw IndexOutOfBoundsException();
        if (Size >= Capacity) Resize(2 * Capacity); //daca e nevoie redimensionam
        for (int i = Size; i > index; i--) //facem loc mutand tot ce este dupa index cu o poz mai la dreapta
            List[i] = List[i - 1];
        List[index] = new T(newElem); //il adaugam
        Size++; //creste nr de elem cu 1
        return *this;
    }
    const Array<T>& Insert(int index, const Array<T> otherArray) // adauga o lista pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
    { 
        if (index < 0 || index > this->Size) ///daca pozitia nu e valida
            throw IndexOutOfBoundsException();
        if (Size + otherArray.Size >= Capacity) Resize(2 * Capacity); //daca e nevoie redimensionam
        for (int i = 0; i < otherArray.Size; ++i) 
        {
            Insert(index + i, *otherArray.List[i]); //adauga o lista folosind fct Insert
        }
        return *this;
    }
    const Array<T>& Delete(int index) // sterge un element de pe pozitia index, returneaza this. Daca index e invalid arunca o exceptie
    { 
        if (index < 0 || index >= this->Size) //daca pozitia index nu este valida
            throw IndexOutOfBoundsException();
        delete List[index]; //stergem elementul de pe poz index
        for (int i = index; i < Size - 1; ++i) //mutam tot de dupa index cu o poz la stg
        {
            List[i] = List[i + 1];
        }
        Size--; //scade nr de elemente
        return *this;
    }

    bool operator=(const Array<T>& otherArray) //operator de =
    {
        this->Capacity = otherArray.Capacity; //copiem capacity
        this->Size = otherArray.Size; //copiem size
        for (int i = 0; i < this->Size; i++) //copiem elementele
            this->List[i] = new T(*otherArray.List[i]);
        return true;
    }

    void Sort() // sorteaza folosind comparatia intre elementele din T
    { 
        for (int i = 0; i < Size - 1; i++)
            for (int j = i + 1; j < Size; j++)
                if (*List[i] > *List[j]) 
                {
                    T* temp = List[i];
                    List[i] = List[j];
                    List[j] = temp;
                }
    }
    void Sort(int(*compare)(const T&, const T&))  // sorteaza folosind o functie de comparatie
    {
        for (int i = 0; i < Size - 1; ++i)
        {
            for (int j = i + 1; j < Size; ++j) 
            {
                if (compare(*List[j], *List[i]) < 0)
                {
                    T* temp = List[i];
                    List[i] = List[j];
                    List[j] = temp;
                }
            }
        }
    }

    void Sort(Compare* comparator) // sorteaza folosind un obiect de comparatie
    { 
        for (int i = 0; i < Size - 1; ++i) 
        {
            for (int j = i + 1; j < Size; ++j)
            {
                if (comparator->CompareElements(*List[j], *List[i]) < 0) 
                {
                    T* temp = List[i];
                    List[i] = List[j];
                    List[j] = temp;
                }
            }
        }
    }

    // functii de cautare - returneaza pozitia elementului sau -1 daca nu exista
    int BinarySearch(const T& elem)  // cauta un element folosind cautarea binara
    {
        int left = 0, right = Size - 1, mid;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (*List[mid] == elem) return mid;
            else if (*List[mid] < elem) left = mid + 1;
            else right = mid - 1;
        }
        return -1;

    }
    int BinarySearch(const T& elem, int(*compare)(const T&, const T&)) //  cauta un element folosind cautare binara si o functie de comparatie
    {
        int left = 0, right = Size - 1, mid;
        while (left <= right) 
        {
            mid = (left + right) / 2;
            if (compare(elem, *List[mid]) == 0) return mid;
            else if (compare(elem, *List[mid]) < 0) left = mid + 1;
            else right = mid - 1;
        }
        return -1;

    }
    int BinarySearch(const T& elem, Compare* comparator) //  cauta un element folosind binary search si un comparator
    {
        int left = 0, right = Size - 1, mid;
        while (left <= right) 
        {
            mid = (left + right) / 2;
            if (comparator->CompareElements(elem, *List[mid]) == 0) return mid;
            else if (comparator->CompareElements(elem, *List[mid]) < 0) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    int Find(const T& elem)  // cauta un element in Array
    {
        for (int i = 0; i < Size; i++)
            if (*List[i] == elem) return i;
        return -1;
    }
    int Find(const T& elem, int(*compare)(const T&, const T&)) //  cauta un element folosind o functie de comparatie
    {
        for (int i = 0; i < Size; i++)
            if (compare(*List[i], elem) == 0) return i;
        return -1;
    }
    int Find(const T& elem, Compare* comparator) //  cauta un element folosind un comparator
    {
        for (int i = 0; i < Size; i++)
            if (comparator->CompareElements(*List[i], elem) == 0) return i;
        return -1;
    }

    int GetSize() ///returnam size
    {
        return this->Size;
    }
    int GetCapacity() ///returnam capacity
    {
        return this->Capacity;
    }
    ArrayIterator<T> GetBeginIterator() 
    {
        return ArrayIterator<T>(List, 0);
    }
    ArrayIterator<T> GetEndIterator() 
    {
        return ArrayIterator<T>(List, Size);
    }

    void Resize(int newCapacity) ///functia pt redimensionare
    {
        T** newList = new T * [newCapacity]; ///alocam mem pt lista noua
        for (int i = 0; i < this->Size; i++) ///copiem elementele
        {
            newList[i] = this->List[i];
        }
        delete[] List; ///stergem lista initiala
        this->List = newList; ///copiem lista noua in cea initiala
        this->Capacity = newCapacity; ///copiem capacity
    }
};


int main() 
{

    Array<int> arr(2);
    try 
    {   ///adaugam elemente in vector
        arr += 1;
        arr += 4;
        arr += 3;
        arr += 2;
        for (int i = 0; i < arr.GetSize(); i++) ///le afisam
            cout << arr[i] << ' ';
        cout << "\n";
        arr.Sort(); ///le sortam
        for (int i = 0; i < arr.GetSize(); i++) ///le afisam dupa sortare
            cout << arr[i] << ' ';
        cout << "\n";
        arr.Insert(2, 10); ///inseram val 10 pe poz 2
        for (int i = 0; i < arr.GetSize(); i++) ///afisam noul vector
            cout << arr[i] << ' ';
        cout << "\n";
        arr.Delete(2); ///stergem val de pe poz 2
        for (int i = 0; i < arr.GetSize(); i++) ///afisam vectorul
            cout << arr[i] << ' ';
        cout << "\n";
        cout << "Array's capacity is " << arr.GetCapacity() << "\n"; //afisam capacity
        for (ArrayIterator<int> it = arr.GetBeginIterator(); it != arr.GetEndIterator(); it++) ///afisam elementele 
            cout << *(it.GetElement()) << ' ';
        cout << "\n";
        cout << "Element 4 is found on position " << arr.Find(4) << "\n"; ///il cautam pe 4
        cout << "Using binary search, element 2 is found on position " << arr.BinarySearch(2) << "\n"; //il cautam pe 2 binar
    }
    catch (exception& e) 
    {
        cout << "Exception: " << e.what() << "\n";
    }
    try 
    {
        arr[10] = 5;
    }
    catch (exception& e)
    {
        cout << "Exception: " << e.what() << "\n";
    }
    try
    {
        arr.Insert(10, 2);
    }
    catch (exception& e)
    {
        cout << "Exception: " << e.what() << "\n";
    }
    return 0;
}