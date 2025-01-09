#include <iostream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

int CUT_ROD(int p[], int n) {
    if (n == 0) return 0;
    int q = -1;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + CUT_ROD(p, n - i));
    }
    return q;
}

int MEMORIZED_CUT_ROD_AUX(int p[], int n, int r[], int s[]) {
    if (r[n] >= 0) return r[n];
    int q = (n == 0) ? 0 : -1;
    for (int i = 1; i <= n; i++) {
        int current_value = p[i] + MEMORIZED_CUT_ROD_AUX(p, n - i, r, s);
        if (q < current_value) {
            q = current_value;
            s[n] = i;
        }
    }
    r[n] = q;
    return q;
}

int MEMORIZED_CUT_ROD(int p[], int n, int s[]) {
    int r[n + 1];
    memset(r, -1, sizeof(r));
    return MEMORIZED_CUT_ROD_AUX(p, n, r, s);
}

void ITER_CUT_ROD(int p[], int n, int r[], int s[]) {
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = -1;
        for (int i = 1; i <= j; i++) {
            if (q < p[i] + r[j - i]) {
                q = p[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
}

void PRINT_SOLUTION(int s[], int n) {
    while (n > 0) {
        cout << s[n] << " ";
        n -= s[n];
    }
    cout << endl;
}

void generateRandomPrices(int p[], int n, int minPrice = 1, int maxPrice = 100) {
    for (int i = 1; i <= n; i++) {
        p[i] = rand() % (maxPrice - minPrice + 1) + minPrice;
    }
}


int main() {
    srand(time(0));

    int naive_lengths[] = {5, 10, 15, 20, 25};
    int other_lengths[] = {50, 100, 200, 400, 800, 1000};

    for (int i = 0; i < 5; i++) {
        int n = naive_lengths[i];

        int p[n + 1];
        generateRandomPrices(p, n);

        auto startRecursive = high_resolution_clock::now();
        cout << "Maksymalna cena (naiwna rekurencyjna) dla dlugosci " << n << ": " << CUT_ROD(p, n) << endl;
        auto stopRecursive = high_resolution_clock::now();
        auto durationRecursive = duration_cast<microseconds>(stopRecursive - startRecursive);
        cout << "Czas wykonania (rekurencyjna) dla dlugosci " << n << ": " << durationRecursive.count() / 1000000.0 << " sekundy" << endl;
    }

    for (int i = 0; i < 6; i++) {
        int n = other_lengths[i];

        int p[n + 1];
        generateRandomPrices(p, n);

        auto startMemoized = high_resolution_clock::now();
        int s1[n + 1];
        int max_price_memorized = MEMORIZED_CUT_ROD(p, n, s1);
        cout << "Maksymalna cena (z pamietaniem) dla dlugosci " << n << ": " << max_price_memorized << endl;
        cout << "Optymalny podzial (z pamietaniem): ";
        PRINT_SOLUTION(s1, n);
        auto stopMemoized = high_resolution_clock::now();
        auto durationMemoized = duration_cast<microseconds>(stopMemoized - startMemoized);
        cout << "Czas wykonania (z pamietaniem) dla dlugosci " << n << ": " << durationMemoized.count() / 1000000.0 << " sekundy" << endl;

        auto startIterative = high_resolution_clock::now();
        int r[n + 1], s2[n + 1];
        ITER_CUT_ROD(p, n, r, s2);
        cout << "Maksymalna cena (iteracyjna) dla dlugosci " << n << ": " << r[n] << endl;
        cout << "Optymalny podzial (iteracyjna): ";
        PRINT_SOLUTION(s2, n);
        auto stopIterative = high_resolution_clock::now();
        auto durationIterative = duration_cast<microseconds>(stopIterative - startIterative);
        cout << "Czas wykonania (iteracyjna) dla dlugosci " << n << ": " << durationIterative.count() / 1000000.0 << " sekundy" << endl;
    }

    return 0;
}
