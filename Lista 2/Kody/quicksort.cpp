#include <iostream>
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

int PARTITION(int A[], int poczatek, int koniec) {
    int x = A[koniec];
    int i = poczatek - 1;

    for (int j = poczatek; j < koniec; j++) {
        compare_counter++;
        if (A[j] <= x) {
            i++;
            assign_counter += 2;
            swap(A[i], A[j]);
        }
    }
    assign_counter += 2;
    swap(A[i + 1], A[koniec]);
    return i + 1;
}

void QUICK_SORT(int A[], int p, int k) {
    if (p < k) {
        int s = PARTITION(A, p, k);
        QUICK_SORT(A, p, s - 1);
        QUICK_SORT(A, s + 1, k);
    }
}

void PARTITION_WITH_TWO_PIVOTS(int A[], int poczatek, int koniec, int& lt, int& gt) {
    compare_counter++;
    if (A[poczatek] > A[koniec]) {
        swap(A[poczatek], A[koniec]);
    }

    int p = A[poczatek];
    int q = A[koniec];
    int i = poczatek + 1;
    lt = poczatek + 1;
    gt = koniec - 1;

    while (i <= gt) {
        compare_counter += 2;
        if (A[i] < p) {
            compare_counter -= 1;
            assign_counter += 2;
            swap(A[i], A[lt]);
            lt++;
        } else if (A[i] > q) {
            assign_counter += 2;
            swap(A[i], A[gt]);
            gt--;
            i--;
        }
        i++;
    }

    lt--;
    gt++;

    assign_counter += 2;
    swap(A[poczatek], A[lt]);
    swap(A[koniec], A[gt]);
}

void QUICK_SORT2(int A[], int p, int k) {
    if (p < k) {
        int lt, gt;
        PARTITION_WITH_TWO_PIVOTS(A, p, k, lt, gt);
        QUICK_SORT2(A, p, lt - 1);
        QUICK_SORT2(A, lt + 1, gt - 1);
        QUICK_SORT2(A, gt + 1, k);
    }
}

void Tworzenie_tablicy(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

void Wypisz_tablice(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));

    int sizes[] = {100, 250, 500, 750, 1000};

    for (int s = 0; s < 5; s++) {
        int size = sizes[s];
        int* A = new int[size];
        int* B = new int[size];

        Tworzenie_tablicy(A, size);
        for (int i = 0; i < size; i++) B[i] = A[i];

        cout << "Rozmiar tablicy: " << size << endl;

        cout << "QUICK_SORT przed sortowaniem: ";
        Wypisz_tablice(A, size);
        QUICK_SORT(A, 0, size - 1);
        cout << "QUICK_SORT po sortowaniu: ";
        Wypisz_tablice(A, size);
        print_counters();

        cout << "QUICK_SORT z dwoma pivotami przed sortowaniem: ";
        Wypisz_tablice(B, size);
        QUICK_SORT2(B, 0, size - 1);
        cout << "QUICK_SORT z dwoma pivotami po sortowaniu: ";
        Wypisz_tablice(B, size);
        print_counters();

        delete[] A;
        delete[] B;

        cout << endl;
    }

    return 0;
}
