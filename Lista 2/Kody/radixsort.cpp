#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int compare_counter = 0;
int assign_counter = 0;

void reset_counters() {
    compare_counter = 0;
    assign_counter = 0;
}

void print_counters() {
    cout << "Porownania: " << compare_counter << "\nPrzypisania: " << assign_counter << "\n";
    reset_counters();
}

void COUNTING_SORT(int A[], int n, int exp, int d) {
    int B[n];
    int C[d] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (A[i] / exp) % d;
        C[digit]++;
        compare_counter++;
    }

    for (int i = 1; i < d; i++) {
        C[i] += C[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (A[i] / exp) % d;
        B[C[digit] - 1] = A[i];
        C[digit]--;
    }

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
        assign_counter++;
    }
}

void RADIX_SORT(int A[], int n, int d) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) max = A[i];
        compare_counter++;
    }

    for (int exp = 1; max / exp > 0; exp *= d) {
        COUNTING_SORT(A, n, exp, d);
    }
}

void RADIX_SORT_NEGATIVE(int A[], int n, int d) {
    int negatives[n], positives[n];
    int negCount = 0, posCount = 0;

    for (int i = 0; i < n; i++) {
        compare_counter++;
        if (A[i] < 0) {
            negatives[negCount++] = -A[i];
            assign_counter++;
        } else {
            positives[posCount++] = A[i];
            assign_counter++;
        }
    }

    if (posCount > 0) {
        RADIX_SORT(positives, posCount, d);
    }
    if (negCount > 0) {
        RADIX_SORT(negatives, negCount, d);
    }

    int index = 0;
    for (int i = negCount - 1; i >= 0; i--) {
        A[index++] = -negatives[i];
        assign_counter++;
    }
    for (int i = 0; i < posCount; i++) {
        A[index++] = positives[i];
        assign_counter++;
    }
}

void Tworzenie_dodatniej(int T[], int size) {
    for (int i = 0; i < size; i++) {
        T[i] = rand() % 10000 + 1;
    }
}

void Tworzenie_dowolnej(int T[], int size) {
    for (int i = 0; i < size; i++) {
        T[i] = rand() % 20001 - 10000;
    }
}

void wypisz_tablice(int T[], int size) {
    for (int i = 0; i < size; i++) {
        cout << T[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));

    int sizes[] = {100, 250, 500, 750, 1000};

    for (int s = 0; s < 5; s++) {
        int size = sizes[s];

        int* Dodatnia_tablica = new int[size];
        Tworzenie_dodatniej(Dodatnia_tablica, size);
        cout << "RADIX_SORT przed sortowaniem (rozmiar " << size << "): ";
        wypisz_tablice(Dodatnia_tablica, size);

        RADIX_SORT(Dodatnia_tablica, size, 32);
        cout << "RADIX_SORT po sortowaniu: ";
        wypisz_tablice(Dodatnia_tablica, size);
        print_counters();

        int* Dowolna_tablica = new int[size];
        Tworzenie_dowolnej(Dowolna_tablica, size);
        cout << "RADIX_SORT_NEGATIVE przed sortowaniem (rozmiar " << size << "): ";
        wypisz_tablice(Dowolna_tablica, size);

        RADIX_SORT_NEGATIVE(Dowolna_tablica, size, 32);
        cout << "RADIX_SORT_NEGATIVE po sortowaniu: ";
        wypisz_tablice(Dowolna_tablica, size);
        print_counters();

        delete[] Dodatnia_tablica;
        delete[] Dowolna_tablica;

        cout << endl;
    }

    return 0;
}
