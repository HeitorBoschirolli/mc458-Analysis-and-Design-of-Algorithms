#include <iostream>
#include <algorithm>

using namespace std;

unsigned long long int merge_and_count(int v[], int aux[], int beginning_a, int beginning_b, int end_b) {
    int index_a = beginning_a, index_b = beginning_b, end_a = beginning_b - 1, aux_count = 0;
    unsigned long long int num_inversions = 0;

    while ((index_a <= end_a) && (index_b <= end_b)) {
        if (v[index_a] <= v[index_b]) {
            aux[aux_count] = v[index_a];
            index_a++;
        }
        else {
            aux[aux_count] = v[index_b];
            index_b++;
            num_inversions += beginning_b - index_a;
        }
        aux_count++;
    }

    while (index_a <= end_a) {
        aux[aux_count++] = v[index_a++];
    }

    while (index_b <= end_b) {
        aux[aux_count++] = v[index_b++];
    }

    for (int i = 0; i < aux_count; i++) {
        v[i + beginning_a] = aux[i];
    }

    return num_inversions;
}

unsigned long long int count_inversions(int v[], int aux[], int beginning, int end) {
    int middle = (beginning + end) / 2;
    unsigned long long int num_inversions = 0;

    if (beginning < end) {
        num_inversions = count_inversions(v, aux, beginning, middle);
        num_inversions += count_inversions(v, aux, middle + 1, end);
        num_inversions += merge_and_count(v, aux, beginning, middle + 1, end);
    }
    return num_inversions;
}

int main() {

    int n; // array size
    cin >> n;

    int *elements;
    elements = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> elements[i];
    }

    int *result = new int[n];
    unsigned long long num_inversions;

    num_inversions = count_inversions(elements, result, 0, n - 1);

    cout << num_inversions << endl;
}