#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

int LCS_RECURSIVE(const string& a, const string& b, int m, int n, int** memo) {
    if (m == 0 || n == 0) {
        return 0;
    }
    if (memo[m][n] != -1) {
        return memo[m][n];
    }
    if (a[m - 1] == b[n - 1]) {
        return memo[m][n] = 1 + LCS_RECURSIVE(a, b, m - 1, n - 1, memo);
    }
    return memo[m][n] = max(LCS_RECURSIVE(a, b, m - 1, n, memo), LCS_RECURSIVE(a, b, m, n - 1, memo));
}

void PrintLCS_RECURSIVE(const string& a, const string& b, int m, int n, int** memo) {
    if (m == 0 || n == 0) {
        return;
    }
    if (a[m - 1] == b[n - 1]) {
        PrintLCS_RECURSIVE(a, b, m - 1, n - 1, memo);
        cout << a[m - 1];
    } else if (memo[m - 1][n] >= memo[m][n - 1]) {
        PrintLCS_RECURSIVE(a, b, m - 1, n, memo);
    } else {
        PrintLCS_RECURSIVE(a, b, m, n - 1, memo);
    }
}

void PrintLCS(char** d, const string& str, int i, int j) {
    if (i > 0 && j > 0) {
        if (d[i][j] == '\\') {
            PrintLCS(d, str, i - 1, j - 1);
            cout << str[i - 1];
        } else if (d[i][j] == '|') {
            PrintLCS(d, str, i - 1, j);
        } else {
            PrintLCS(d, str, i, j - 1);
        }
    }
}

char** LCS_ITERATIVE(const string& a, const string& b, int& lcsLength) {
    int lenA = a.length();
    int lenB = b.length();

    int** dp = new int*[lenA + 1];
    char** d = new char*[lenA + 1];
    for (int i = 0; i <= lenA; i++) {
        dp[i] = new int[lenB + 1];
        d[i] = new char[lenB + 1];
    }

    for (int i = 0; i <= lenA; i++) dp[i][0] = 0;
    for (int j = 0; j <= lenB; j++) dp[0][j] = 0;

    for (int i = 1; i <= lenA; i++) {
        for (int j = 1; j <= lenB; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                d[i][j] = '\\';
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                d[i][j] = '|';
            } else {
                dp[i][j] = dp[i][j - 1];
                d[i][j] = '-';
            }
        }
    }

    lcsLength = dp[lenA][lenB];

    int i = lenA, j = lenB;
    string lcs = "";
    while (i > 0 && j > 0) {
        if (d[i][j] == '\\') {
            lcs = a[i - 1] + lcs;
            i--;
            j--;
        } else if (d[i][j] == '|') {
            i--;
        } else {
            j--;
        }
    }

    cout << "LCS: " << lcs << endl;

    for (int i = 0; i <= lenA; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return d;
}

string GenerateRandomString(int length) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string randomStr;
    for (int i = 0; i < length; i++) {
        randomStr += alphabet[rand() % alphabet.length()];
    }
    return randomStr;
}

int main() {

    string a = "ABCBDAB";
    string b = "BDCABB";
    int length;

    cout << "Recursive version of LCS:" << endl;
    int** memo = new int*[a.length() + 1];
    for (int i = 0; i <= a.length(); i++) {
        memo[i] = new int[b.length() + 1];
        for (int j = 0; j <= b.length(); j++) {
            memo[i][j] = -1;
        }
    }
    int lcsLengthRecursive = LCS_RECURSIVE(a, b, a.length(), b.length(), memo);
    cout << "LCS Length: " << lcsLengthRecursive << endl;

    cout << "LCS: ";
    PrintLCS_RECURSIVE(a, b, a.length(), b.length(), memo);
    cout << endl;

    for (int i = 0; i <= a.length(); i++) {
        delete[] memo[i];
    }
    delete[] memo;

    cout << "\nIterative version of LCS:" << endl;
    char** d = LCS_ITERATIVE(a, b, length);
    cout << "LCS Length: " << length << endl;

    PrintLCS(d, a, a.length(), b.length());
    cout << endl;

    for (int i = 0; i <= a.length(); i++) {
        delete[] d[i];
    }
    delete[] d;

    srand(time(0));

    int lengths[] = {500, 1000, 2000, 4000, 8000, 10000};
    for (int len : lengths) {
        string a = GenerateRandomString(len);
        string b = GenerateRandomString(len);

        auto startRecursive = high_resolution_clock::now();
        memo = new int*[a.length() + 1];
        for (int i = 0; i <= a.length(); i++) {
            memo[i] = new int[b.length() + 1];
            for (int j = 0; j <= b.length(); j++) {
                memo[i][j] = -1;
            }
        }
        LCS_RECURSIVE(a, b, a.length(), b.length(), memo);
        auto stopRecursive = high_resolution_clock::now();
        auto durationRecursive = duration_cast<microseconds>(stopRecursive - startRecursive);

        auto startIterative = high_resolution_clock::now();
        d = LCS_ITERATIVE(a, b, length);
        auto stopIterative = high_resolution_clock::now();
        auto durationIterative = duration_cast<microseconds>(stopIterative - startIterative);

        cout << "Length: " << len << endl;
        cout << "Recursive time: " << durationRecursive.count() / 1000000.0 << " sekundy" << endl;
        cout << "Iterative time: " << durationIterative.count() / 1000000.0 << " sekundy" << endl;

        for (int i = 0; i <= a.length(); i++) {
            delete[] memo[i];
        }
        delete[] memo;

        for (int i = 0; i <= a.length(); i++) {
            delete[] d[i];
        }
        delete[] d;
    }

    return 0;
}
