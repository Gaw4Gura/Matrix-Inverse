#include <bits/stdc++.h>
#define eps 1e-10
using namespace std;

int n;

inline double Gauss(vector<vector<double>>& A, int n) {
    for (int i = 0; i < n; ++i) {
        int r = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(A[j][i]) > fabs(A[r][i]))
                r = j;
        if (r != i)
            for (int j = 0; j <= n; ++j)
                swap(A[r][j], A[i][j]);
        for (int k = i + 1; k < n; ++k) {
            if (A[i][i] == 0)
                return 0;
            double f = A[k][i] / A[i][i];
            for (int j = i; j <= n; ++j) A[k][j] -= f * A[i][j];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j)
            A[i][n] -= A[j][n] * A[i][j];
        A[i][n] /= A[i][i];
    }
    double ret = 1.0;
    /*
     for (int i = 0; i < n; ++i)
     ret *= A[i][n];
     */
    // for (int i = 0; i < n; ++i) printf("%.6f\n", A[i][i]);
    for (int i = 0; i < n; ++i)
        ret *= A[i][i];
    return ret;
}

inline vector<vector<double>> adjoint(const vector<vector<double>>& A, int n) {
    vector<vector<double>> Astar(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sgn = ((i + j) & 1) ? -1.0 : 1.0;
            vector<vector<double>> rest(n, vector<double>(n));
            for (int k = 0, r = 0; k < n; ++k) {
                if (k == i) continue;
                for (int t = 0, c = 0; t < n; ++t) {
                    if (t == j) continue;
                    if (A[i][j] == 0.0) {
                        rest[r][c++] = 0.0;
                        continue;
                    }
                    rest[r][c++] = A[k][t];
                }
                ++r;
            }
            /*
             for (int k = 0; k < n - 1; ++k)
             for (int t = 0; t < n - 1; ++t)
             printf("%.6f%c", rest[k][t], t == n - 2 ? '\n' : ' ');
             */
            double det = Gauss(rest, n - 1);
            Astar[i][j] = sgn * det;
            // printf("adjoint(%d, %d):%.6f\n", i, j, Astar[i][j]);
        }
    }
    return Astar;
}

inline vector<vector<double>> transpose(const vector<vector<double>>& A, int n) {
    vector<vector<double>> AT(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            AT[j][i] = A[i][j];
    return AT;
}

int main() {
    scanf("%d", &n);
    vector<vector<double>> M(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%lf", &M[i][j]);
    vector<vector<double>> A(n + 1, vector<double>(n + 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = M[i][j];
    double det = Gauss(A, n);
    printf("det:%.6f\n", fabs(det));
    if (fabs(det) <= eps) {
        printf("Failed! The Matrix is strange!\n");
        return 1;
    }
    vector<vector<double>> Astar = adjoint(M, n);
    vector<vector<double>> inv = transpose(Astar, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            inv[i][j] /= det;
            if (fabs(inv[i][j]) < eps) inv[i][j] = 0.0;
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            printf("%.6f%c", inv[i][j], j == n - 1 ? '\n' : ' ');
    return 0;
}
