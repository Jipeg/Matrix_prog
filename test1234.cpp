#include <iostream>
#include <fstream>

using std::cout;
//using std::cin;
std::ifstream cin("input2.txt");

int n, m;

void show(int** a) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int** input(int** a) {
    a = new int* [m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    return a;
}

int** add(int** a, int** b) {
    int** c = new int* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new int[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

int** mult(int** a, int b) {
    int** c = new int* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new int[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] * b;
        }
    }
    return c;
}

int** minus(int** a, int** b) {
    int** c = add(a, mult(b, -1));
    return c;
}

int** mult(int** a, int** b) {
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

int** pow(int** a, unsigned int P) {
    int** c = nullptr;
    c = mult(a, a);
    P--;
    while (--P) {
        c = mult(c, a);
    }
    return c;
}

int** minor(int** a, int M, int N, int m, int n) {
    int ** c = new int* [m-1];
    for (int i = 0; i < m-1; i++) {
        c[i] = new int[n-1];
        for (int j = 0; j < n-1; j++) {
            int I = i < M ? i : i + 1;
            int J = j < N ? j : j + 1;
            c[i][j] = a[I][J];
        }
    }
    return c;
}

int det(int** a, int N) {
    if (N == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    else {
        int s = 0;
        for (int j = 0; j < N; j++)
        {
            //cout << '+' << a[0][j] << '*' << det(minor(a, 0, j, N, N), N - 1) << '\n';
            // Важно!:
            // j = 0,1,2,....
            s += (1 - 2 * (j % 2)) * a[0][j] * det(minor(a, 0, j, N, N), N - 1);
            //show(minor(a, 0, j, N, N));
        }
        return s;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cin >> m >> n;
    int** a = nullptr;
    a = input(a);
    show(a);

    int** b = nullptr;
    b = input(b);
    show(b);

    cout << "Сумма а+b:\n";
    int** c = add(a, b);
    show(c);

    cout << "10a:\n";
    c = mult(a, 10);
    show(c);

    cout << "произведение a*b:\n";
    c = mult(a, b);
    show(c);

    cout << "Степень a^5:\n";
    c = pow(a, 5);
    show(c);

    cout << "Det b\n";
    cout << det(b, 5) << '\n';

    return 0;
}