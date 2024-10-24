#include <iostream>
#include <limits.h> // dla INT_MAX
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


int LEFT(int i) {
    return 2* i + 1;
}

int RIGHT(int i) {
    return 2 * i + 2;
}

int LEFT2(int i) {
    return 3 * i + 1;
}

int MIDDLE2(int i) {
    return 3 * i + 2;
}

int RIGHT2(int i) {
    return 3 * i + 3;
}

void HEAPIFY(int A[], int i, int n) {
    int largest = i;
    int l = LEFT(i);
    int r = RIGHT(i);

    compare_counter++;
    if (l < n && A[l] > A[largest]) {
        assign_counter++;
        largest = l;
    }

    compare_counter++;
    if (r < n && A[r] > A[largest]) {
        assign_counter++;
        largest = r;
    }

    compare_counter++;
    if (largest != i) {
        assign_counter++;
        swap(A[i], A[largest]);
        HEAPIFY(A, largest, n);
    }
}

void BUILD_HEAP(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        HEAPIFY(A, i, n);
    }
}

void HEAP_SORT(int A[], int n) {
    BUILD_HEAP(A, n);

    for (int i = n - 1; i > 0; i--) {
        assign_counter++;
        swap(A[0], A[i]);
        HEAPIFY(A, 0, i);
    }
}

void HEAPIFY_TERNARY(int A[], int i, int n) {
    int largest = i;
    int l = LEFT2(i);
    int m = MIDDLE2(i);
    int r = RIGHT2(i);

    compare_counter++;
    if (l < n && A[l] > A[largest]) {
        assign_counter++;
        largest = l;
    }

    compare_counter++;
    if (m < n && A[m] > A[largest]) {
        assign_counter++;
        largest = m;
    }

    compare_counter++;
    if (r < n && A[r] > A[largest]) {
        assign_counter++;
        largest = r;
    }

    compare_counter++;
    if (largest != i) {
        assign_counter++;
        swap(A[i], A[largest]);
        HEAPIFY_TERNARY(A, largest, n);
    }
}

void BUILD_HEAP_TERNARY(int A[], int n) {

    for (int i = n / 3 - 1; i >= 0; i--) {
        HEAPIFY_TERNARY(A, i, n);
    }
}

void HEAP_SORT_TERNARY(int A[], int n) {
    BUILD_HEAP_TERNARY(A, n);

    for (int i = n - 1; i > 0; i--) {
        assign_counter++;
        swap(A[0], A[i]);
        HEAPIFY_TERNARY(A, 0, i);
    }
}

void print_array(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    reset_counters();

    int n;

    int B1[] = {8, 65, 62, 60, 83, 30, 52, 59, 94, 82, 37, 95, 61, 17, 83, 7, 77, 30, 69, 58, 76, 92, 40, 58, 68, 72, 80, 0, 97, 39, 31, 38, 26, 1, 50, 56, 70, 88, 93, 94, 54, 54, 60, 51, 56, 61, 73, 56, 93, 51, 44, 11, 27, 33, 24, 81, 47, 65, 29, 53}; // 60 elements
    int B2[] = {31, 29, 8, 72, 8, 73, 45, 1, 45, 84, 84, 77, 46, 59, 25, 93, 16, 39, 88, 81, 48, 69, 54, 80, 55, 2, 31, 58, 63, 48, 25, 79, 62, 85, 43, 43, 47, 30, 69, 29, 80, 62, 96, 56, 3, 66, 48, 6, 99, 59, 85, 45, 74, 48, 27, 93, 80, 78, 76, 62, 89, 95, 49, 27, 23, 92, 54, 31, 22, 91, 97, 93, 38, 31, 27, 56, 9, 61, 78, 19}; // 80 elements
    int B3[] = {67, 34, 58, 41, 80, 12, 94, 78, 47, 53, 90, 81, 35, 19, 61, 97, 94, 44, 18, 64, 99, 59, 5, 88, 41, 0, 44, 87, 5, 37, 74, 7, 71, 43, 12, 0, 45, 91, 24, 69, 30, 59, 1, 0, 35, 31, 73, 91, 57, 68, 55, 30, 35, 27, 92, 15, 68, 75, 81, 18, 85, 50, 30, 74, 56, 15, 91, 80, 70, 55, 9, 67, 24, 96, 85, 50, 38, 92, 74, 11, 19, 4, 5, 98, 67, 41, 88, 56, 22, 80, 88, 69, 66, 29, 96, 75}; // 100 elements
    int B4[] = {8, 37, 55, 61, 63, 76, 93, 83, 19, 66, 69, 48, 30, 91, 54, 98, 55, 98, 36, 60, 18, 27, 76, 35, 98, 5, 84, 56, 16, 44, 41, 54, 61, 49, 85, 9, 82, 23, 24, 8, 96, 53, 25, 41, 19, 5, 9, 98, 56, 80, 74, 99, 89, 27, 48, 14, 85, 64, 89, 56, 49, 24, 21, 40, 60, 91, 96, 37, 23, 4, 38, 35, 57, 72, 61, 19, 19, 41, 21, 67, 57, 5, 16, 98, 66, 71, 90, 91, 18, 79, 51, 77, 93, 38, 96, 60, 29, 33, 23, 15, 57, 38, 19, 48, 4, 37, 60, 64, 93, 39, 8, 80, 51, 40}; // 120 elements
    int B5[] = {76, 94, 44, 77, 92, 81, 63, 56, 34, 95, 7, 2, 41, 38, 83, 35, 77, 92, 77, 22, 4, 92, 47, 66, 8, 58, 43, 74, 98, 60, 27, 48, 71, 55, 43, 31, 77, 76, 16, 70, 52, 45, 25, 76, 93, 0, 49, 4, 87, 15, 48, 53, 31, 45, 49, 88, 82, 79, 81, 58, 74, 12, 41, 89, 30, 84, 35, 71, 77, 7, 20, 41, 19, 15, 71, 16, 93, 71, 1, 51, 77, 34, 81, 70, 95, 14, 30, 57, 75, 31, 93, 81, 41, 91, 14, 46, 73, 98, 19, 16, 90, 96, 12, 35, 20, 92, 68, 44, 23, 50, 12, 57, 9, 56, 17, 56, 2, 30, 91, 88, 81, 66, 60, 12, 92, 56, 30, 79, 56, 90}; // 140 elements
    int B6[] = {44, 51, 63, 99, 36, 92, 22, 46, 78, 62, 83, 18, 58, 2, 82, 39, 56, 6, 73, 46, 90, 21, 48, 63, 83, 93, 76, 71, 75, 91, 30, 54, 59, 70, 31, 78, 99, 37, 95, 79, 67, 15, 74, 80, 1, 16, 34, 70, 66, 12, 46, 85, 59, 78, 29, 87, 95, 36, 40, 87, 41, 71, 20, 62, 73, 60, 49, 60, 60, 27, 17, 0, 62, 16, 94, 63, 15, 40, 90, 53, 6, 29, 8, 88, 79, 95, 61, 45, 78, 71, 77, 60, 68, 34, 0, 98, 14, 37, 18, 14, 69, 38, 68, 87, 22, 55, 72, 61, 83, 81, 49, 8, 75, 64, 35, 41, 54, 53, 27, 27, 95, 53, 48, 8, 77, 39, 96, 85, 17, 54, 77, 24, 14, 50, 89, 62, 46, 96, 9, 13, 90, 54, 12, 89, 18, 95, 34, 41}; // 160 elements

    cout << "\nHEAP_SORT_TERNARY:\n\n";

    //Tablica 1
    cout << "Tablica 1:\n";
    n = sizeof(B1) / sizeof(B1[0]);
    HEAP_SORT_TERNARY(B1, n);
    print_counters();

    //Tablica 2
    cout << "Tablica 2:\n";
    n = sizeof(B2) / sizeof(B2[0]);
    HEAP_SORT_TERNARY(B2, n);
    print_counters();

    //Tablica 3
    cout << "Tablica 3:\n";
    n = sizeof(B3) / sizeof(B3[0]);
    HEAP_SORT_TERNARY(B3, n);
    print_counters();

    //Tablica 4
    cout << "Tablica 4:\n";
    n = sizeof(B4) / sizeof(B4[0]);
    HEAP_SORT_TERNARY(B4, n);
    print_counters();

    //Tablica 5
    cout << "Tablica 5:\n";
    n = sizeof(B5) / sizeof(B5[0]);
    HEAP_SORT_TERNARY(B5, n);
    print_counters();

    //Tablica 6
    cout << "Tablica 6:\n";
    n = sizeof(B6) / sizeof(B6[0]);
    HEAP_SORT_TERNARY(B6, n);
    print_counters();

    int A1[] = {8, 65, 62, 60, 83, 30, 52, 59, 94, 82, 37, 95, 61, 17, 83, 7, 77, 30, 69, 58, 76, 92, 40, 58, 68, 72, 80, 0, 97, 39, 31, 38, 26, 1, 50, 56, 70, 88, 93, 94, 54, 54, 60, 51, 56, 61, 73, 56, 93, 51, 44, 11, 27, 33, 24, 81, 47, 65, 29, 53}; // 60 elements
    int A2[] = {31, 29, 8, 72, 8, 73, 45, 1, 45, 84, 84, 77, 46, 59, 25, 93, 16, 39, 88, 81, 48, 69, 54, 80, 55, 2, 31, 58, 63, 48, 25, 79, 62, 85, 43, 43, 47, 30, 69, 29, 80, 62, 96, 56, 3, 66, 48, 6, 99, 59, 85, 45, 74, 48, 27, 93, 80, 78, 76, 62, 89, 95, 49, 27, 23, 92, 54, 31, 22, 91, 97, 93, 38, 31, 27, 56, 9, 61, 78, 19}; // 80 elements
    int A3[] = {67, 34, 58, 41, 80, 12, 94, 78, 47, 53, 90, 81, 35, 19, 61, 97, 94, 44, 18, 64, 99, 59, 5, 88, 41, 0, 44, 87, 5, 37, 74, 7, 71, 43, 12, 0, 45, 91, 24, 69, 30, 59, 1, 0, 35, 31, 73, 91, 57, 68, 55, 30, 35, 27, 92, 15, 68, 75, 81, 18, 85, 50, 30, 74, 56, 15, 91, 80, 70, 55, 9, 67, 24, 96, 85, 50, 38, 92, 74, 11, 19, 4, 5, 98, 67, 41, 88, 56, 22, 80, 88, 69, 66, 29, 96, 75}; // 100 elements
    int A4[] = {8, 37, 55, 61, 63, 76, 93, 83, 19, 66, 69, 48, 30, 91, 54, 98, 55, 98, 36, 60, 18, 27, 76, 35, 98, 5, 84, 56, 16, 44, 41, 54, 61, 49, 85, 9, 82, 23, 24, 8, 96, 53, 25, 41, 19, 5, 9, 98, 56, 80, 74, 99, 89, 27, 48, 14, 85, 64, 89, 56, 49, 24, 21, 40, 60, 91, 96, 37, 23, 4, 38, 35, 57, 72, 61, 19, 19, 41, 21, 67, 57, 5, 16, 98, 66, 71, 90, 91, 18, 79, 51, 77, 93, 38, 96, 60, 29, 33, 23, 15, 57, 38, 19, 48, 4, 37, 60, 64, 93, 39, 8, 80, 51, 40}; // 120 elements
    int A5[] = {76, 94, 44, 77, 92, 81, 63, 56, 34, 95, 7, 2, 41, 38, 83, 35, 77, 92, 77, 22, 4, 92, 47, 66, 8, 58, 43, 74, 98, 60, 27, 48, 71, 55, 43, 31, 77, 76, 16, 70, 52, 45, 25, 76, 93, 0, 49, 4, 87, 15, 48, 53, 31, 45, 49, 88, 82, 79, 81, 58, 74, 12, 41, 89, 30, 84, 35, 71, 77, 7, 20, 41, 19, 15, 71, 16, 93, 71, 1, 51, 77, 34, 81, 70, 95, 14, 30, 57, 75, 31, 93, 81, 41, 91, 14, 46, 73, 98, 19, 16, 90, 96, 12, 35, 20, 92, 68, 44, 23, 50, 12, 57, 9, 56, 17, 56, 2, 30, 91, 88, 81, 66, 60, 12, 92, 56, 30, 79, 56, 90}; // 140 elements
    int A6[] = {44, 51, 63, 99, 36, 92, 22, 46, 78, 62, 83, 18, 58, 2, 82, 39, 56, 6, 73, 46, 90, 21, 48, 63, 83, 93, 76, 71, 75, 91, 30, 54, 59, 70, 31, 78, 99, 37, 95, 79, 67, 15, 74, 80, 1, 16, 34, 70, 66, 12, 46, 85, 59, 78, 29, 87, 95, 36, 40, 87, 41, 71, 20, 62, 73, 60, 49, 60, 60, 27, 17, 0, 62, 16, 94, 63, 15, 40, 90, 53, 6, 29, 8, 88, 79, 95, 61, 45, 78, 71, 77, 60, 68, 34, 0, 98, 14, 37, 18, 14, 69, 38, 68, 87, 22, 55, 72, 61, 83, 81, 49, 8, 75, 64, 35, 41, 54, 53, 27, 27, 95, 53, 48, 8, 77, 39, 96, 85, 17, 54, 77, 24, 14, 50, 89, 62, 46, 96, 9, 13, 90, 54, 12, 89, 18, 95, 34, 41}; // 160 elements

    cout << "\nHEAP_SORT:\n\n";

    //Tablica 1
    cout << "Tablica 1:\n";
    n = sizeof(A1) / sizeof(A1[0]);
    HEAP_SORT(A1, n);
    print_counters();

    //Tablica 2
    cout << "Tablica 2:\n";
    n = sizeof(A2) / sizeof(A2[0]);
    HEAP_SORT(A2, n);
    print_counters();

    //Tablica 3
    cout << "Tablica 3:\n";
    n = sizeof(A3) / sizeof(A3[0]);
    HEAP_SORT(A3, n);
    print_counters();

    //Tablica 4
    cout << "Tablica 4:\n";
    n = sizeof(A4) / sizeof(A4[0]);
    HEAP_SORT(A4, n);
    print_counters();

    //Tablica 5
    cout << "Tablica 5:\n";
    n = sizeof(A5) / sizeof(A5[0]);
    HEAP_SORT(A5, n);
    print_counters();

    //Tablica 6
    cout << "Tablica 6:\n";
    n = sizeof(A6) / sizeof(A6[0]);
    HEAP_SORT(A6, n);
    print_counters();

    return 0;
}
