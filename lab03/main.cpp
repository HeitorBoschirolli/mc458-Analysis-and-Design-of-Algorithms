#include <iostream>
#include <cmath>

using namespace std;

long int select(long int *A, long int p, long int r, long int i);
long int particione_bfprt(long int *A, long int p, long int r);


void insertion_sort (long int *v, long int p, long int r) {

    for (long int j = p + 1; j <= r; j++) {
        long int chave = v[j];
        long int i = j - 1;
        while (i >= p && v[i] > chave) {
            v[i + 1] = v[i];
            i = i - 1;
        }
        v[i + 1] = chave;
    }
}

void troca (long int *A, long int i, long int j) {
    long int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

long int particione (long int *A, long int p, long int r) {
    long int x = A[r]; // x eh o pivo
    long int i = p - 1;
    for (long int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;
            troca(A, i, j);
        }
    }

    troca (A, i + 1, r);
    return i + 1;
}

long int select(long int *A, long int p, long int r, long int i) {
    if (p == r) {
        return p;
    }

    long int q = particione_bfprt(A, p, r);
    long int k = q - p + 1;

    if (i == k) {
        return q;
    }
    else if (i < k) {
        return select(A, p, q - 1, i);
    }
    else {
        return select(A, q + 1, r, i - k);
    }
}

long int particione_bfprt(long int *A, long int p, long int r) {
    long int n = r - p + 1;
    for (long int j = p; j <= (p + 5 * (ceil(n/5) - 1)); j = j + 5) {
        insertion_sort(A, j, j+4);
    }
    insertion_sort(A, p + 5 * (n/5), n);

    for (long int j = 1; j <= ceil(n/5) - 1; j++) {
        troca (A, j, p + 5 * j - 3);
    }
    troca (A, (ceil(n/5)), (p + 5 * (n/5) + n)/2);

    long int k = select(A, p, p + ceil(n/5) - 1, (ceil(n/5) + 1)/2);

    troca (A, k, r);

    return particione(A, p, r);
}

int main() {

    long int n, k;
    cin >> n;
    cin >> k;

    long int *v = new long int [n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    v[0] = -123456789;

    for (int i = 1; i <= n; i++)
        cout << v[i] << " ";
    cout << endl;

    cout << particione_bfprt(v, 1, n);
    cout << endl;
}