#include <iostream>
using namespace std;

class NumberList {
    int* numbers; // Array-ul dinamic
    int capacity; // Capacitatea actual? a array-ului
    int count;    // Num?rul de elemente din array

public:
    NumberList();
    ~NumberList(); // Destructor pentru eliberarea memoriei alocate dinamic
    void Init();
    bool Add(int x);
    void Sort();
    void Print();
};

NumberList::NumberList() {
    capacity = 10; // Capacitatea ini?ial?
    numbers = new int[capacity]; // Alocare memorie pentru array
    count = 0;
}

NumberList::~NumberList() {
    delete[] numbers; // Eliberare memorie alocat? dinamic
}

void NumberList::Init() {
    count = 0;
}

bool NumberList::Add(int x) {
    if (count >= capacity) {
        // Redimensionarea array-ului (cre?tere)
        int newCapacity = capacity * 2; // Dublarea capacit??ii
        int* newArray = new int[newCapacity]; // Alocare memorie pentru noul array

        // Copierea elementelor existente în noul array
        for (int i = 0; i < capacity; i++) {
            newArray[i] = numbers[i];
        }

        // Eliberarea memoriei alocate pentru array-ul vechi
        delete[] numbers;

        // Actualizarea array-ului ?i a capacit??ii
        numbers = newArray;
        capacity = newCapacity;
    }

    // Ad?ugarea noului element
    numbers[count] = x;
    count++;

    return true;
}

void NumberList::Sort() {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < count - 1; i++) {
            if (numbers[i] > numbers[i + 1]) {
                int temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                sorted = false;
            }
        }
    }
}

void NumberList::Print() {
    for (int i = 0; i < count; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
}

int main() {
    NumberList list;
    list.Init();

    // Ad?ugare elemente în list?
    for (int i = 10; i > 0; i--) {
        list.Add(i);
    }

    cout << "Lista original?: ";
    list.Print();

    // Sortarea listei
    list.Sort();

    cout << "Lista sortat?: ";
    list.Print();

    return 0;
}
