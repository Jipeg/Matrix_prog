#include <iostream>
#include <fstream>

using std::cout;
//using std::cin;
std::ifstream cin("input.txt");

void show(int** a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int** input(int** a, int m, int n) {
    a = new int* [m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    return a;
}

int** add(int** a, int** b, int m, int n) {
    int** c = new int* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new int[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

int** mult(int** a, int b, int m, int n) {
    int** c = new int* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new int[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] * b;
        }
    }
    return c;
}

int** minus(int** a, int** b, int m, int n) {
    int** c = add(a, mult(b, -1, m, n), m, n);
    return c;
}

int** mult(int** a, int** b, int m, int n) {
    int** c = new int* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new int[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

int** pow(int** a, unsigned int P, int m, int n) {
    int** c = nullptr;
    c = mult(a, a, m, n);
    P--;
    while (--P) {
        c = mult(c, a, m, n);
    }
    return c;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n, m;
    cin >> m >> n;
    int** a = nullptr;
    a = input(a, m, n);
    show(a, m, n);

    int** b = nullptr;
    b = input(b, m, n);
    show(b, m, n);

    cout << "Сумма а+b:\n";
    int** c = add(a, b, m, n);
    show(c, m, n);

    cout << "10a:\n";
    c = mult(a, 10, m, n);
    show(c, m, n);

    cout << "произведение a*b:\n";
    c = mult(a, b, m, n);
    show(c, m, n);

    cout << "Степень a^5:\n";
    c = pow(a, 5, m, n);
    show(c, m, n);

    return 0;
}