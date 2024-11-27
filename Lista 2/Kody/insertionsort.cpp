#include <iostream>
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
    int key;
    Node* next;

    Node(int value) : key(value), next(nullptr) {}
};

struct List {
    Node* head;

    List() : head(nullptr) {}
};

void LIST_INSERT(List& L, Node* x) {
    x->next = L.head;
    L.head = x;
}

void PRINT_LIST(const List& L) {
    Node* current = L.head;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->next;
    }
    cout << endl;
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

void TEST_INSERTIONSORT() {
    cout << "Przykład 1: Sortowanie liczb całkowitych" << endl;
    List L1;
    LIST_INSERT(L1, new Node(3));
    LIST_INSERT(L1, new Node(1));
    LIST_INSERT(L1, new Node(4));
    LIST_INSERT(L1, new Node(5));
    LIST_INSERT(L1, new Node(2));

    cout << "Lista przed sortowaniem: ";
    PRINT_LIST(L1);

    INSERTIONSORT(L1);

    cout << "Lista po sortowaniu: ";
    PRINT_LIST(L1);
    print_counters();

    cout << "\nPrzykład 2: Sortowanie z liczbami ujemnymi" << endl;
    List L2;
    LIST_INSERT(L2, new Node(-3));
    LIST_INSERT(L2, new Node(7));
    LIST_INSERT(L2, new Node(0));
    LIST_INSERT(L2, new Node(-1));
    LIST_INSERT(L2, new Node(4));

    cout << "Lista przed sortowaniem: ";
    PRINT_LIST(L2);

    INSERTIONSORT(L2);

    cout << "Lista po sortowaniu: ";
    PRINT_LIST(L2);
    print_counters();

    cout << "\nPrzykład 3: Lista z powtarzającymi się elementami" << endl;
    List L3;
    LIST_INSERT(L3, new Node(5));
    LIST_INSERT(L3, new Node(3));
    LIST_INSERT(L3, new Node(3));
    LIST_INSERT(L3, new Node(1));
    LIST_INSERT(L3, new Node(5));

    cout << "Lista przed sortowaniem: ";
    PRINT_LIST(L3);

    INSERTIONSORT(L3);

    cout << "Lista po sortowaniu: ";
    PRINT_LIST(L3);
    print_counters();
}

int main() {
    TEST_INSERTIONSORT();
    return 0;
}
