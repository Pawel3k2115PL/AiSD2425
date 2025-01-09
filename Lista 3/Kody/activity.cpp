#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <climits>
#include <iomanip>  // Dodane dla std::fixed i std::setprecision

using namespace std;
using namespace std::chrono;

void Rec_1(int p[], int k[], int n, int current, int zajecia[], int &ile) {
    int next = current + 1;
    while (next <= n && p[next] < k[current]) {
        next++;
    }
    if (next <= n) {
        zajecia[ile++] = next;
        Rec_1(p, k, n, next, zajecia, ile);
    }
}

void Iter_1(int p[], int k[], int n, int zajecia[], int &ile) {
    zajecia[ile++] = 1;
    int current = 1;

    for (int next = 2; next <= n; next++) {
        if (p[next] >= k[current]) {
            zajecia[ile++] = next;
            current = next;
        }
    }
}

void Rec_2(int p[], int k[], int current, int zajecia[], int &ile) {
    int prev = current - 1;
    while (prev > 0 && k[prev] > p[current]) {
        prev--;
    }
    if (prev > 0) {
        zajecia[ile++] = prev;
        Rec_2(p, k, prev, zajecia, ile);
    }
}

void Iter_2(int p[], int k[], int n, int zajecia[], int &ile) {
    zajecia[ile++] = n - 1;
    int current = n - 1;

    for (int prev = n - 2; prev >= 1; prev--) {
        if (k[prev] <= p[current]) {
            zajecia[ile++] = prev;
            current = prev;
        }
    }
}

void Dyn(int p[], int k[], int n) {
    int** c = new int*[n + 2];
    int** b = new int*[n + 2];

    for (int i = 0; i < n + 2; ++i) {
        c[i] = new int[n + 2]{0};
        b[i] = new int[n + 2]{0};
    }

    for (int length = 2; length <= n + 1; ++length) {
        for (int i = 0; i <= n - length + 1; ++i) {
            int j = i + length;

            for (int m = j - 1; m > i; --m) {
                if (k[i] <= p[m] && k[m] <= p[j] &&
                    c[i][m] + c[m][j] + 1 > c[i][j]) {
                    c[i][j] = c[i][m] + c[m][j] + 1;
                    b[i][j] = m;
                }
            }
        }
    }

    cout << "Maksymalna liczba zajec: " << c[0][n + 1] << endl;

    for (int i = 0; i < n + 2; ++i) {
        delete[] c[i];
        delete[] b[i];
    }
    delete[] c;
    delete[] b;
}

void UTWORZ_p(int p[], int n) {
    p[0] = 0;
    for (int i = 1; i <= n; i++) {
        p[i] = rand() % (n * 2);
    }
    p[n + 1] = INT_MAX;
    sort(p + 1, p + n + 1);
}

void UTWORZ_k(int k[], int p[], int n) {
    k[0] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        k[i] = p[i] + rand() % 100 + 1;
    }
    k[n + 1] = 0;
}

void WYSWIETL_WYNIKI(const string &nazwa, int zajecia[], int ile) {
    cout << nazwa << ": ";
    for (int i = ile - 1; i >= 0; i--) {
        cout << zajecia[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int wielkosci[] = {500, 1000, 2000, 4000, 8000, 10000};

    for (int n : wielkosci) {
        cout << "\nPorownanie dla n = " << n << endl;

        int p[n + 1];
        int k[n + 1];
        UTWORZ_p(p, n);
        UTWORZ_k(k, p, n);

        int zajecia_rec_1[n];
        int ile_rec_1 = 0;
        auto start_rec_1 = high_resolution_clock::now();
        Rec_1(p, k, n, 0, zajecia_rec_1, ile_rec_1);
        auto stop_rec_1 = high_resolution_clock::now();
        auto duration_rec_1 = duration_cast<microseconds>(stop_rec_1 - start_rec_1);
        WYSWIETL_WYNIKI("Rec_1", zajecia_rec_1, ile_rec_1);
        cout << "Czas dla Rec_1: " << fixed << setprecision(6) << duration_rec_1.count() / 1000000.0 << " sekund" << endl;

        int zajecia_iter_1[n];
        int ile_iter_1 = 0;
        auto start_iter_1 = high_resolution_clock::now();
        Iter_1(p, k, n, zajecia_iter_1, ile_iter_1);
        auto stop_iter_1 = high_resolution_clock::now();
        auto duration_iter_1 = duration_cast<microseconds>(stop_iter_1 - start_iter_1);
        WYSWIETL_WYNIKI("Iter_1", zajecia_iter_1, ile_iter_1);
        cout << "Czas dla Iter_1: " << fixed << setprecision(6) << duration_iter_1.count() / 1000000.0 << " sekund" << endl;

        int zajecia_rec_2[n];
        int ile_rec_2 = 0;
        auto start_rec_2 = high_resolution_clock::now();
        Rec_2(p, k, n + 1, zajecia_rec_2, ile_rec_2);
        auto stop_rec_2 = high_resolution_clock::now();
        auto duration_rec_2 = duration_cast<microseconds>(stop_rec_2 - start_rec_2);
        WYSWIETL_WYNIKI("Rec_2", zajecia_rec_2, ile_rec_2);
        cout << "Czas dla Rec_2: " << fixed << setprecision(6) << duration_rec_2.count() / 1000000.0 << " sekund" << endl;

        int zajecia_iter_2[n];
        int ile_iter_2 = 0;
        auto start_iter_2 = high_resolution_clock::now();
        Iter_2(p, k, n, zajecia_iter_2, ile_iter_2);
        auto stop_iter_2 = high_resolution_clock::now();
        auto duration_iter_2 = duration_cast<microseconds>(stop_iter_2 - start_iter_2);
        WYSWIETL_WYNIKI("Iter_2", zajecia_iter_2, ile_iter_2);
        cout << "Czas dla Iter_2: " << fixed << setprecision(6) << duration_iter_2.count() / 1000000.0 << " sekund" << endl;

        auto start_dyn = high_resolution_clock::now();
        Dyn(p, k, n);
        auto stop_dyn = high_resolution_clock::now();
        auto duration_dyn = duration_cast<microseconds>(stop_dyn - start_dyn);
        cout << "Czas dla Dyn: " << fixed << setprecision(6) << duration_dyn.count() / 1000000.0 << " sekund" << endl;
    }

    return 0;
}
