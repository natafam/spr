#include <iostream>
#include <cmath>

using namespace std;

// Funkcje pomocnicze dla rekurencji
double zad1_rekurencyjnie_helper(double A, double B, double C, double x0, double y0);
bool zad2_rekurencyjnie_helper(double A, double B, double C, double xA, double yA, double xB, double yB);
bool zad3_rekurencyjnie_helper(double xA, double yA, double xB, double yB, double x0, double y0);
void zad4_rekurencyjnie_helper(double xA, double yA, double xB, double yB, double x0, double y0);
void zad5_rekurencyjnie_helper(double xA, double yA, double xB, double yB);


// Zadanie 1.
// Dane są prosta o równaniu ogólnym  𝐴𝑥+𝐵𝑦+𝐶=0  i punkt  𝑃=(𝑥0,𝑦0)  Napisz program, który obliczy odległość punktu  𝑃  od tej prostej. Współrzędne punktu  𝑃  oraz współczynniki prostej:  𝐴,𝐵,𝐶  należy wprowadzić z klawiatury.

void zad1_iteracyjnie() {
    double A, B, C, x, y;
    cout << "Podaj wspolczynniki prostej Ax + By + C = 0:" << endl;
    cout << "A = ";
    cin >> A;
    cout << "B = ";
    cin >> B;
    cout << "C = ";
    cin >> C;

    cout << "Podaj wspolrzedne punktu P(x0, y0):" << endl;
    cout << "x = ";
    cin >> x;
    cout << "y =: ";
    cin >> y;

    double distance = abs(A * x + B * y + C) / sqrt(A * A + B * B);
    cout << "Iteracyjnie: Odleglosc punktu P od prostej Ax + By + C = 0: " << distance << endl;
}

void zad1_rekurencyjnie() {
    double A, B, C, x, y;
    cout << "Podaj wspolczynniki prostej Ax + By + C = 0:" << endl;
    cout << "A = ";
    cin >> A;
    cout << "B = ";
    cin >> B;
    cout << "C = ";
    cin >> C;

    cout << "Podaj wspolrzedne punktu P(x0, y0):" << endl;
    cout << "x = ";
    cin >> x;
    cout << "y =: ";
    cin >> y;

    double distance = zad1_rekurencyjnie_helper(A, B, C, x, y);
    cout << "Rekurencyjnie: Odleglosc punktu P od prostej Ax + By + C = 0: " << distance << endl;
}

double zad1_rekurencyjnie_helper(double A, double B, double C, double x0, double y0) {
    if (A == 0 && B == 0) return 0;
    return abs(A * x0 + B * y0 + C) / sqrt(A * A + B * B);
}


// Zadanie 2.
// Dane są prosta o równaniu  𝐴𝑥+𝐵𝑦+𝐶=0  i odcinek  |𝐴𝐵| , gdzie  𝐴=(𝑥𝐴,𝑦𝐴)  i  𝐵=(𝑥𝐵,𝑦𝐵) . Napisz program, który sprawdzi, czy odcinek  |𝐴𝐵|  leży na tej prostej. Wszystkie potrzebne dane wprowadź z klawiatury.

void zad2_iteracyjnie() {
    double A, B, C;
    double A_x, A_y, B_x, B_y;

    cout << "Podaj wspolczynniki prostej Ax + By + C = 0:" << endl;
    cout << "A = ";
    cin >> A;
    cout << "B = ";
    cin >> B;
    cout << "C = ";
    cin >> C;

    cout << "Podaj wspolrzedne punktu A(xA, yA):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(xB, yB):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    if (A * A_x + B * A_y + C == 0 && A * B_x + B * B_y + C == 0) {
        cout << "Iteracyjnie: Odcinek AB lezy na prostej Ax + By + C = 0." << endl;
    } else {
        cout << "Iteracyjnie: Odcinek AB nie lezy na prostej Ax + By + C = 0." << endl;
    }
}

void zad2_rekurencyjnie() {
    double A, B, C;
    double A_x, A_y, B_x, B_y;

    cout << "Podaj wspolczynniki prostej Ax + By + C = 0:" << endl;
    cout << "A = ";
    cin >> A;
    cout << "B = ";
    cin >> B;
    cout << "C = ";
    cin >> C;

    cout << "Podaj wspolrzedne punktu A(xA, yA):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(xB, yB):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    if (zad2_rekurencyjnie_helper(A, B, C, A_x, A_y, B_x, B_y)) {
        cout << "Rekurencyjnie: Odcinek AB lezy na prostej Ax + By + C = 0." << endl;
    } else {
        cout << "Rekurencyjnie: Odcinek AB nie lezy na prostej Ax + By + C = 0." << endl;
    }
}

bool zad2_rekurencyjnie_helper(double A, double B, double C, double xA, double yA, double xB, double yB) {
    if (A * xA + B * yA + C == 0 && A * xB + B * yB + C == 0) return true;
    return false;
}


// Zadanie 3.
// Dane są punkt  𝑃=(𝑥0,𝑦0)  i odcinek  |𝐴𝐵| , gdzie  𝐴=(𝑥𝐴,𝑦𝐴)  i  𝐵=(𝑥𝐵,𝑦𝐵) .Napisz program,który sprawdzi, czy punkt  𝑃  jest środkiem odcinka  |𝐴𝐵| .Współrzędne punktów należy wprawadzić z klawiatury.

void zad3_iteracyjnie() {
    double A_x, A_y, B_x, B_y, P_x, P_y, S_x, S_y;
    cout << "Podaj wspolrzedne punktu A(x, y):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(x, y):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    cout << "Podaj wspolrzedne punktu P(x, y):" << endl;
    cout << "Px = ";
    cin >> P_x;
    cout << "Py = ";
    cin >> P_y;

    S_x = (A_x + B_x) / 2;
    S_y = (A_y + B_y) / 2;

    if (S_x == P_x && S_y == P_y) {
        cout << "Iteracyjnie: Punkt P jest środkiem odcinka |AB|" << endl;
    } else {
        cout << "Iteracyjnie: Punkt P nie jest środkiem odcinka |AB|" << endl;
    }
}

void zad3_rekurencyjnie() {
    double A_x, A_y, B_x, B_y, P_x, P_y;
    cout << "Podaj wspolrzedne punktu A(x, y):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(x, y):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    cout << "Podaj wspolrzedne punktu P(x, y):" << endl;
    cout << "Px = ";
    cin >> P_x;
    cout << "Py = ";
    cin >> P_y;

    if (zad3_rekurencyjnie_helper(A_x, A_y, B_x, B_y, P_x, P_y)) {
        cout << "Rekurencyjnie: Punkt P jest środkiem odcinka |AB|" << endl;
    } else {
        cout << "Rekurencyjnie: Punkt P nie jest środkiem odcinka |AB|" << endl;
    }
}

bool zad3_rekurencyjnie_helper(double xA, double yA, double xB, double yB, double x0, double y0) {
    if ((xA + xB) / 2 == x0 && (yA + yB) / 2 == y0) return true;
    return false;
}


// Zadanie 4.
// Dane są punkt  𝑃=(𝑥0,𝑦0)  i odcinek  |𝐴𝐵| , gdzie  𝐴=(𝑥𝐴,𝑦𝐴)  i  𝐵=(𝑥𝐵,𝑦𝐵) .Napisz program,który sprawdzi, czy punkt  𝑃  leży powyżej, czy poniżej odcinka  |𝐴𝐵| . Współrzędne punktów należy wprawadzić z klawiatury. Jeśli okaże się, że punkty  𝐴 ,  𝐵  i  𝑃  są współliniowe, program ma wyświetlić użytkownikowi prośbę o podanie kolejnego zestawu danych.

void zad4_iteracyjnie() {
    double A_x, A_y, B_x, B_y, P_x, P_y;
    cout << "Podaj wspolrzedne punktu A(x, y):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(x, y):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    cout << "Podaj wspolrzedne punktu P(x, y):" << endl;
    cout << "Px = ";
    cin >> P_x;
    cout << "Py = ";
    cin >> P_y;

    double wyznacznik = (B_y - A_y) * (P_x - A_x) - (B_x - A_x) * (P_y - A_y);

    if (wyznacznik == 0) {
        cout << "Punkty A, B i P sa wspolliniowe. Podaj nowe dane." << endl;
        return;
    }

    if (wyznacznik > 0) {
        cout << "Iteracyjnie: Punkt P lezy powyzej odcinka |AB|." << endl;
    } else {
        cout << "Iteracyjnie: Punkt P lezy ponizej odcinka |AB|." << endl;
    }
}

void zad4_rekurencyjnie() {
    double A_x, A_y, B_x, B_y, P_x, P_y;
    cout << "Podaj wspolrzedne punktu A(x, y):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(x, y):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    cout << "Podaj wspolrzedne punktu P(x, y):" << endl;
    cout << "Px = ";
    cin >> P_x;
    cout << "Py = ";
    cin >> P_y;

    zad4_rekurencyjnie_helper(A_x, A_y, B_x, B_y, P_x, P_y);
}

void zad4_rekurencyjnie_helper(double xA, double yA, double xB, double yB, double x0, double y0) {
    double wyznacznik = (yB - yA) * (x0 - xA) - (xB - xA) * (y0 - yA);

    if (wyznacznik == 0) {
        cout << "Punkty A, B i P sa wspolliniowe. Podaj nowe dane." << endl;
        return;
    }

    if (wyznacznik > 0) {
        cout << "Rekurencyjnie: Punkt P lezy powyzej odcinka |AB|." << endl;
    } else {
        cout << "Rekurencyjnie: Punkt P lezy ponizej odcinka |AB|." << endl;
    }
}


// Zadanie 5.
// Dany jest odcinek  |𝐴𝐵| , gdzie  𝐴=(𝑥𝐴,𝑦𝐴)  i  𝐵=(𝑥𝐵,𝑦𝐵)  Napisz program, który będzie odnajdywał końce odcinka  |𝐶𝐷| , gdzie  𝐶=(𝑥𝐶,𝑦𝐶)  i  𝐷=(𝑥𝐷,𝑦𝐷) . Odcinek  |𝐶𝐷|  powinien mieć taką samą długość jak odcinek  |𝐴𝐵|  i przecinać odcinek  |𝐴𝐵|  w połowie jego długości pod kątem prostym. Współrzędne końców odcinka  |𝐴𝐵|  powinien podać użytkownik.

void zad5_iteracyjnie() {
    double A_x, A_y, B_x, B_y;
    cout << "Podaj wspolrzedne punktu A(x, y):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(x, y):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    double S_x = (A_x + B_x) / 2;
    double S_y = (A_y + B_y) / 2;
    double length = sqrt((B_x - A_x) * (B_x - A_x) + (B_y - A_y) * (B_y - A_y));
    double dx = (B_y - A_y) / length;
    double dy = (A_x - B_x) / length;

    double C_x = S_x + dx * (length / 2);
    double C_y = S_y + dy * (length / 2);
    double D_x = S_x - dx * (length / 2);
    double D_y = S_y - dy * (length / 2);

    cout << "Iteracyjnie: Punkt C: (" << C_x << ", " << C_y << ")" << endl;
    cout << "Iteracyjnie: Punkt D: (" << D_x << ", " << D_y << ")" << endl;
}

void zad5_rekurencyjnie() {
    double A_x, A_y, B_x, B_y;
    cout << "Podaj wspolrzedne punktu A(x, y):" << endl;
    cout << "Ax = ";
    cin >> A_x;
    cout << "Ay = ";
    cin >> A_y;

    cout << "Podaj wspolrzedne punktu B(x, y):" << endl;
    cout << "Bx = ";
    cin >> B_x;
    cout << "By = ";
    cin >> B_y;

    zad5_rekurencyjnie_helper(A_x, A_y, B_x, B_y);
}

void zad5_rekurencyjnie_helper(double xA, double yA, double xB, double yB) {
    double S_x = (xA + xB) / 2;
    double S_y = (yA + yB) / 2;
    double length = sqrt((xB - xA) * (xB - xA) + (yB - yA) * (yB - yA));
    double dx = (yB - yA) / length;
    double dy = (xA - xB) / length;

    double C_x = S_x + dx * (length / 2);
    double C_y = S_y + dy * (length / 2);
    double D_x = S_x - dx * (length / 2);
    double D_y = S_y - dy * (length / 2);

    cout << "Rekurencyjnie: Punkt C: (" << C_x << ", " << C_y << ")" << endl;
    cout << "Rekurencyjnie: Punkt D: (" << D_x << ", " << D_y << ")" << endl;
}


int main() {
    int wybor;
    do {
        cout << "Wybierz zadanie do wykonania (1, 2, 3, 4, 5) lub 0, aby zakończyć: ";
        cin >> wybor;
        switch (wybor) {
            case 1:
                zad1_iteracyjnie();
                zad1_rekurencyjnie();
                break;
            case 2:
                zad2_iteracyjnie();
                zad2_rekurencyjnie();
                break;
            case 3:
                zad3_iteracyjnie();
                zad3_rekurencyjnie();
                break;
            case 4:
                zad4_iteracyjnie();
                zad4_rekurencyjnie();
                break;
            case 5:
                zad5_iteracyjnie();
                zad5_rekurencyjnie();
                break;
            case 0:
                cout << "Koniec programu." << endl;
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 0);

    return 0;
}
