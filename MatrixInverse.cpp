#include <bits/stdc++.h>
#include "frac.h"
#define eps 1e-10
using namespace std;
using namespace Frac;

int n;

inline frac Gauss(vector<vector<frac>>& A, int n) {
    for (int i = 0; i < n; ++i) {
        int r = i;
        for (int j = i + 1; j < n; ++j)
            if (A[r][i] < A[j][i])
                r = j;
        if (r != i)
            for (int j = 0; j <= n; ++j)
                swap(A[r][j], A[i][j]);
        for (int k = i + 1; k < n; ++k) {
            if (A[i][i].num == 0)
                return 0;
	    // cout << A[i][i] << endl;
            frac f = A[k][i] / A[i][i];
	    // cout << f << endl;
            for (int j = i; j <= n; ++j) A[k][j] = A[k][j] - f * A[i][j];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j)
            A[i][n] = A[i][n] - A[j][n] * A[i][j];
	// cout << "(" << i << ", " << i << ")" << " " << A[i][i] << endl;
	if (A[i][i].num == 0) return 0;
        A[i][n] = A[i][n] / A[i][i];
    }
    frac ret(1, 1);
    /*
     for (int i = 0; i < n; ++i)
     ret *= A[i][n];
     */
    // for (int i = 0; i < n; ++i) printf("%.6f\n", A[i][i]);
    for (int i = 0; i < n; ++i) {
	// cout << A[i][i] << endl;
        ret = ret * A[i][i];
    }
    return ret;
}

inline vector<vector<frac>> adjoint(const vector<vector<frac>>& A, int n) {
    vector<vector<frac>> Astar(n, vector<frac>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            frac sgn;
            if ((i + j) & 1)
                sgn.setValue(-1, 1);
            else
                sgn.setValue(1, 1);
            vector<vector<frac>> rest(n, vector<frac>(n));
            for (int k = 0, r = 0; k < n; ++k) {
                if (k == i) continue;
                for (int t = 0, c = 0; t < n; ++t) {
                    if (t == j) continue;
                    if (A[i][j].num == 0) {
                        rest[r][c++].setValue(0, 1);
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
            frac det = Gauss(rest, n - 1);
            Astar[i][j] = sgn * det;
            // printf("adjoint(%d, %d):%.6f\n", i, j, Astar[i][j]);
        }
    }
    return Astar;
}

inline vector<vector<frac>> transpose(const vector<vector<frac>>& A, int n) {
    vector<vector<frac>> AT(n, vector<frac>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            AT[j][i] = A[i][j];
    return AT;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // freopen("out.txt", "w", stdout);
    cin >> n;
    vector<vector<frac>> M(n, vector<frac>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M[i][j].input();
    /*
     for (int i = 0; i < n; ++i) {
     for (int j = 0; j < n; ++j)
     cout << M[i][j] << " ";
     cout << endl;
     }
     */
    vector<vector<frac>> A(n + 1, vector<frac>(n + 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = M[i][j];
    frac det = Gauss(A, n);
    cout << det << endl;
    if (det.num == 0) {
        printf("Failed! The Matrix is strange!\n");
        return 1;
    }
    vector<vector<frac>> Astar = adjoint(M, n);
    vector<vector<frac>> inv = transpose(Astar, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            inv[i][j] = inv[i][j] / det;
            if (inv[i][j].num == 0) inv[i][j].setValue(0, 1);
        }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << inv[i][j] << " ";
        cout << endl;
    }
    return 0;
}
