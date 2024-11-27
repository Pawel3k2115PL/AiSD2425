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

struct Node {
    double key;
    Node* next;

    Node(double value) : key(value), next(nullptr) {}
};

struct List {
    Node* head;

    List() : head(nullptr) {}
};

void LIST_INSERT(List& L, Node* x) {
    x->next = L.head;
    L.head = x;
}

void INSERTIONSORT(List& L) {
    if (L.head == nullptr || L.head->next == nullptr) {
        return;
    }

    Node* sortedEnd = L.head;
    while (sortedEnd->next != nullptr) {
        Node* current = sortedEnd->next;
        compare_counter++;
        if (current->key >= sortedEnd->key) {
            sortedEnd = current;
        } else {
            sortedEnd->next = current->next;
            assign_counter++;
            compare_counter++;
            if (current->key < L.head->key) {
                assign_counter++;
                current->next = L.head;
                L.head = current;
            } else {
                Node* search = L.head;
                while (search->next != nullptr && search->next->key < current->key) {
                    compare_counter++;
                    assign_counter++;
                    search = search->next;
                }
                current->next = search->next;
                search->next = current;
            }
        }
    }
}

void BUCKET_SORT1(double arr[], int n) {
    List* buckets = new List[n];

    for (int i = 0; i < n; ++i) {
        int bucketIndex = static_cast<int>(n * arr[i]);
        LIST_INSERT(buckets[bucketIndex], new Node(arr[i]));
        compare_counter++;
    }

    for (int i = 0; i < n; ++i) {
        INSERTIONSORT(buckets[i]);
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        Node* current = buckets[i].head;
        while (current != nullptr) {
            arr[index++] = current->key;
            Node* temp = current;
            current = current->next;
            assign_counter++;
            compare_counter++;
            delete temp;
        }
    }
    delete[] buckets;
}

void BUCKET_SORT2(double arr[], int n) {
    double min = arr[0], max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            assign_counter++;
        }
        if (arr[i] > max) {
            max = arr[i];
            assign_counter++;
        }
        compare_counter += 2;
    }

    double range = max - min;
    List* buckets = new List[n];

    for (int i = 0; i < n; ++i) {
        int bucketIndex = static_cast<int>(n * (arr[i] - min) / range);
        if (bucketIndex == n) bucketIndex--;
        assign_counter++;
        LIST_INSERT(buckets[bucketIndex], new Node(arr[i]));
    }

    for (int i = 0; i < n; ++i) {
        INSERTIONSORT(buckets[i]);
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        Node* current = buckets[i].head;
        while (current != nullptr) {
            arr[index++] = current->key;
            assign_counter++;
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] buckets;
}

void utwórz_dla_Bucket1(double arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<double>(rand()) / RAND_MAX;
    }
}

void utwórz_dla_Bucket2(double arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() % 20000 - 10000) / 100.0;
    }
}

void WYPISZ(double arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));

    int sizes[] = {100, 250, 500, 750, 1000};

    for (int s = 0; s < 5; ++s) {
        int size = sizes[s];
        double* A = new double[size];
        double* B = new double[size];

        cout << "Rozmiar tablicy: " << size << endl;

        utwórz_dla_Bucket1(A, size);
        cout << "BUCKET_SORT1 przed sortowaniem: ";
        WYPISZ(A, size);
        BUCKET_SORT1(A, size);
        cout << "BUCKET_SORT1 po sortowaniu: ";
        WYPISZ(A, size);
        print_counters();

        utwórz_dla_Bucket2(B, size);
        cout << "BUCKET_SORT2 przed sortowaniem: ";
        WYPISZ(B, size);
        BUCKET_SORT2(B, size);
        cout << "BUCKET_SORT2 po sortowaniu: ";
        WYPISZ(B, size);
        print_counters();

        delete[] A;
        delete[] B;

        cout << endl;
    }

    return 0;
}
