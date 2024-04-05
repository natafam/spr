#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

// 1. Wyznaczanie miejsc zerowych funkcji metodą połowienia.
double funkcja(double x) {
    return x*x - 6;
}

double miejsceZeroweMetodaPolowienia(double a, double b, double epsilon) {
    double F_a = funkcja(a);
    double F_b = funkcja(b);

    if (F_a * F_b > 0) {
        cout << "Nie można zagwarantować istnienia miejsca zerowego w przedziale [" << a << ", " << b << "]." << endl;
        return -1;
    }

    double c = 0;

    while (fabs(b - a) > epsilon) {
        c = (a + b) / 2;
        double fc = funkcja(c);

        if (fc == 0)
            return c;
        else if (F_a * fc < 0)
            b = c;
        else
            a = c;
    }

    return c;
}

// 2. Obliczanie pierwiastka kwadratowego metodą Herona.
double pierwiastekKwadratowyMetodaHerona(double x) {
    if (x == 0) return 0;
    double przyblizenie = x / 2.0;


    while (true) {
        double następnePrzyblizenie = 0.5 * (przyblizenie + x / przyblizenie);

        if (abs(następnePrzyblizenie - przyblizenie) < 0.0001) {
            return następnePrzyblizenie;
        }
        przyblizenie = następnePrzyblizenie;
    }
}

// 3. Stos (from scratch): dodawanie elementów, wypisanie elementów, usuwanie elementów ze stosu.
class Stos {
private:
    vector<int> stos;
public:
    void dodaj(int element) {
        stos.push_back(element);
        cout << "Dodano element " << element << " do stosu." << endl;
    }

    void wypisz() {
        cout << "Zawartość stosu: ";
        for (int i = stos.size() - 1; i >= 0; --i) {
            cout << stos[i] << " ";
        }
        cout << endl;
    }

    void usun() {
        if (!stos.empty())
            stos.pop_back();
            cout << "Usunięto ostatni element ze stosu." << endl;
    }
};

// 4. Lista dwukierunkowa (biblioteka standardowa C++): dodanie elementów wczytanych z pliku tekstowego (dowolna liczba elementów w pliku tekstowym, odzielonych przecinkiem), posortowanie elementów w liście, usunięcie wybranego elementu z listy, dodanie dowolnego elementu do posortowanej listy.
void wczytajElementyZPlikuDoListy(const string& nazwaPliku, list<int>& lista) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cout << "Nie można otworzyć pliku." << endl;
        return;
    }

    string linia;
    while (getline(plik, linia, ',')) {
        int element;
        stringstream(linia) >> element;
        lista.push_back(element);
    }

    plik.close();
}

void sortujListe(list<int>& lista) {
    lista.sort();
    cout << "Posortowano elementy listy." << endl;
}

void usunElementZListy(list<int>& lista, int element) {
    lista.remove(element);
    cout << "Usunięto element " << element << " z listy." << endl;
}

void dodajElementDoListy(list<int>& lista, int element) {
    lista.push_back(element);
    cout << "Dodano element " << element << " do listy." << endl;
}

void wypiszElementyListy(const list<int>& lista) {
    cout << "Zawartość listy: ";
    for (const auto& element : lista) {
        cout << element << " ";
    }
    cout << endl;
}

int main() {
    // 1. Wyznaczanie miejsc zerowych funkcji metodą połowienia.
    double poczatkowyPunktPrzedzialu = -2;
    double koncowyPunktPrzedziału = 5;
    double dokladnosc = 0.0001;
    
    double miejsceZero = miejsceZeroweMetodaPolowienia(poczatkowyPunktPrzedzialu, koncowyPunktPrzedziału, dokladnosc);
    if (miejsceZero != -1)
        cout << "Miejsce zerowe: " << miejsceZero << "\n\n-----\n" << endl;

    // 2. Obliczanie pierwiastka kwadratowego metodą Herona.
    int pierwiastek = 16;
    double wartośćPierwiastka = pierwiastekKwadratowyMetodaHerona(pierwiastek);
    cout << "Wartość pierwiastka kwadratowego z " << pierwiastek << " wynosi: " << wartośćPierwiastka << "\n\n-----\n" << endl;

    // 3. Stos (from scratch)
    Stos stos;

    stos.dodaj(3);
    stos.dodaj(9);
    stos.dodaj(18);
    stos.dodaj(12);
    stos.wypisz();
    cout << "\n";

    stos.usun();
    stos.wypisz();
    cout << "\n-----\n" << endl;
    

    // 4. Lista dwukierunkowa (biblioteka standardowa C++).
    list<int> lista;
    wczytajElementyZPlikuDoListy("plik.txt", lista);
    sortujListe(lista);
    wypiszElementyListy(lista);
    cout << "\n";

    usunElementZListy(lista, 14);
    wypiszElementyListy(lista);
    cout << "\n";

    dodajElementDoListy(lista, 8);
    dodajElementDoListy(lista, 29);
    wypiszElementyListy(lista);
    cout << "\n";

    sortujListe(lista);
    wypiszElementyListy(lista);
    cout << "\n-----\n";

    return 0;
}
