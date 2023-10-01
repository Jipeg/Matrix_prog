#include <iostream>
#include <fstream>
#include <iomanip>   // std::setprecision, std::setw

using std::cout;
//using std::cin;
std::ifstream cin("input2.txt");

int n, m;

void show(float** a) {
    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << std::setw(5) << a[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

float** input(float** a) {
    a = new float* [m];
    for (int i = 0; i < m; i++) {
        a[i] = new float[n];
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    return a;
}
float** copy(float** a) {
    float** c = new float* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new float[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j];
        }
    }
    return c;
}

float** IdMatrix(int N) {
    float** c = new float* [N];
    for (int i = 0; i < N; i++) {
        c[i] = new float[N];
        for (int j = 0; j < N; j++) {
            c[i][j] = i == j ? 1. : 0.;
        }
    }
    return c;
}


float** add(float** a, float** b) {
    float** c = new float* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new float[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

float** mult(float** a, int b) {
    float** c = new float* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new float[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] * b;
        }
    }
    return c;
}

float** minus(float** a, float** b) {
    float** c = add(a, mult(b, -1));
    return c;
}

float** mult(float** a, float** b) {
    float** c = new float* [m];
    for (int i = 0; i < m; i++) {
        c[i] = new float[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

// Деревянное возведение в степень
float** pow(float** a, unsigned int P) {
    float** c = nullptr;
    c = mult(a, a);
    P--;
    while (--P) {
        c = mult(c, a);
    }
    return c;
}

// Функция, которая вернет минор(M,N) матрицы а
float** minor(float** a, int M, int N, int m, int n) {
    float** c = new float* [m-1];
    for (int i = 0; i < m-1; i++) {
        c[i] = new float[n-1];
        for (int j = 0; j < n-1; j++) {
            int I = i < M ? i : i + 1;
            int J = j < N ? j : j + 1;
            c[i][j] = a[I][J];
        }
    }
    return c;
}

// Определитель по 1й строке
float det(float** a, int N) {
    if (N == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    else {
        float s = 0;
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

// Три элементарных шага метода Гаусса
void subtract_rows(float** a, int i, int k, float coeff) {
    for (size_t j = 0; j < n; j++)
    {
        a[i][j] -= coeff * a[k][j];
    }
}
void change_rows(float** a, int i, int k) {
    for (size_t j = 0; j < n; j++)
    {
        float c = a[i][j];
        a[i][j] = a[k][j];
        a[k][j] = c;
    }
}
void mult_row(float** a, int i, float coeff) {
    for (size_t j = 0; j < n; j++)
    {
        a[i][j] = coeff * a[i][j];
    }
}

float** inverse(float** a) {
    float** c = copy(a);
    float** cc = IdMatrix(n);
    // Прямой ход метода Гаусса
    for (int j = 0; j < n; j++)
    {
        //show(c);
        if (c[j][j] == 0) {
            bool singular = true;
            for (int k = j; k < m; k++) {
                if (c[k][j] != 0) {
                    change_rows(c, k, j);
                    change_rows(cc, k, j);
                    cout << "changing rows\n";
                    singular = false;
                    break;
                }
            }
            if (singular) {
                cout << "matrix has no inverse!\n";
                return {};
            }
            
        }
        for (int i = j+1; i < m; i++)
        {
            float coeff = c[i][j] / c[j][j];
            subtract_rows(c, i, j, coeff);
            subtract_rows(cc, i, j, coeff);
        }
    }
    
    // Проверка определителя
    float d = 1;
    for (int i = 0; i < m; i++) {
        d *= c[i][i];
    }
    cout << "determinant = " << d << '\n';
    if (d == 0) {
        cout << "matrix has no inverse!\n";
        return {};
    }

    // Обратный ход метода Гаусса
    for (int j = n-1; j >= 0; j--)
    {
        //show(c);
        for (int i = j - 1; i >= 0; i--)
        {
            float coeff = c[i][j] / c[j][j];
            subtract_rows(c, i, j, coeff);
            subtract_rows(cc, i, j, coeff);
        }
    }

    // От диагональной к единичной
    for (int i = 0; i < n; i++)
    {
        mult_row(cc, i, 1 / c[i][i]);
    }
    return cc;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cin >> m >> n;
    float** a = nullptr;
    a = input(a);
    show(a);

    float** b = nullptr;
    b = input(b);
    show(b);

    cout << "Сумма а+b:\n";
    float** c = add(a, b);
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

    show(b);
    cout << "Det b = " << det(b, 5) << '\n';

    float ** bb = inverse(b);
    cout << "b ^ -1 = \n";
    show(bb);
    float** cc = mult(b, bb);
    cout << "b * b ^ -1\n";
    show(cc);

    return 0;
}
