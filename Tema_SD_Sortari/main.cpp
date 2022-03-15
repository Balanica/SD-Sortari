#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

int maximum( int* v, int n){
    int maxim = v[0];
    for( int i = 1; i<n; i++)
        if (maxim < v[i])
            maxim = v[i];
    return maxim;
}

void countsort_10( int* v, int n, int exp){
    int* cpy_v = (int*) malloc(n * sizeof(int));
    int i, frec[10] = {0};
    for ( i = 0; i < n; i++)
        frec[(v[i] / exp) % 10] ++;
    for ( i = 1; i < 10; i++)
        frec[i] += frec[i-1];
    for ( i = n - 1; i >= 0; i--) {
        cpy_v[frec[(v[i] / exp) % 10] - 1] = v[i];
        frec[(v[i] / exp) % 10]--;
    }
    for ( i = 0; i < n; i++)
        v[i] = cpy_v[i];

}
void countsort_16( int* v, int n, int exp){
    int* cpy_v = (int*) malloc(n * sizeof(int));
    int i, frec[16] = {0};
    for ( i = 0; i < n; i++)
        frec[(v[i] / exp) % 16] ++;
    for ( i = 1; i < 16; i++)
        frec[i] += frec[i-1];
    for ( i = n - 1; i >= 0; i--) {
        cpy_v[frec[(v[i] / exp) % 16] - 1] = v[i];
        frec[(v[i] / exp) % 16]--;
    }
    for ( i = 0; i < n; i++)
        v[i] = cpy_v[i];

}
void countsort_2_16( int* v, int n, int exp){
    int* cpy_v = (int*) malloc(n * sizeof(int));
    int i;
    int* frec = (int*) malloc(65535 * sizeof(int));
    for(int j  = 0; j < 65535; j++)
        frec[j] = 0;
    for ( i = 0; i < n; i++)
        frec[(v[i] / exp) % (65535)] ++;
    for ( i = 1; i < 65535; i++)
        frec[i] += frec[i-1];
    for ( i = n - 1; i >= 0; i--) {
        cpy_v[frec[(v[i] / exp) % (65535)] - 1] = v[i];
        frec[(v[i] / exp) % (65535)]--;
    }
    for ( i = 0; i < n; i++)
        v[i] = cpy_v[i];

}
void radixsort_10( int *v, int n){
    int maxim = maximum(v, n);
    for(int exp = 1; maxim / exp > 0; exp *= 10 )
        countsort_10(v, n, exp);

}

void radixsort_16( int *v, int n){
    int maxim = maximum(v, n);
    for(int exp = 1; maxim / exp > 0; exp *= 16 )
        countsort_16(v, n, exp);

}
void radixsort_2_16( int *v, int n){
    int maxim = maximum(v, n);
    for(int exp = 1; maxim / exp > 0; exp *= (65535) )
        countsort_2_16(v, n, exp);

}

void merge(int *v, int first, int last, int mij)
{
    int i = first, j = mij + 1, k = 0;
    int* aux = (int*) malloc((last-first+1) * sizeof(int));
    
    while (i <= mij && j <= last)
    {
        if (v[i] < v[j])
        {
            aux[k] = v[i];
            k++;
            i++;
        }
        else
        {
            aux[k] = v[j];
            k++;
            j++;
        }
    }

    while (i <= mij)
    {
        aux[k] = v[i];
        k++;
        i++;
    }

    while (j <= last)
    {
        aux[k] = v[j];
        k++;
        j++;
    }

    for (i = first; i <= last; i++)
    {
        v[i] = aux[i-first];
    }
}

void mergeSort(int *v, int first, int last)
{
    int mij;
    if (first < last)
    {
        mij=(first + last)/2;
        mergeSort(v, first, mij);
        mergeSort(v, mij+1, last);

        merge(v, first, last, mij);
    }
}

int shellSort(int* v, int n)
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int aux = v[i];

            int j;
            for (j = i; j >= gap && v[j - gap] > aux; j -= gap)
                v[j] = v[j - gap];
            v[j] = aux;
        }
    }
    return 0;
}

void countSort(int* v, int n) {
    int copie[10];
    int count[10];
    int max = v[0];
    max = maximum(v, n);

    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[v[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        copie[count[v[i]] - 1] = v[i];
        count[v[i]]--;
    }

    for (int i = 0; i < n; i++) {
        v[i] = copie[i];
    }
}

void bucketSort(int* v, int n)
{
    vector<int>* b;

    for (int i = 0; i < n; i++) {
        int bi = n * v[i];
        b[bi].push_back(v[i]);
    }
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());

    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            v[index++] = b[i][j];
}

void bubbleSort(int *v, int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (v[j] > v[j+1])
                swap(v[j], v[j+1]);
}

int partition (int* v, int low, int high)
{
    int aux = v[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (v[j] < aux)
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}

void quickSort(int* v, int low, int high)
{
    if (low < high)
    {
        int aux = partition(v, low, high);
        quickSort(v, low, aux - 1);
        quickSort(v, aux + 1, high);
    }
}



int* v;
int main() {
    ifstream fin("input.txt");
    int teste, n, m;
    fin>>teste;
    for(int j = 1; j<= teste; j++){
        fin >> n >> m;
        cout<<"Test "<<j<<endl<<"N = "<<n<<"  Maxim = "<<m<<endl;
        v =(int*) malloc(n * sizeof(int));
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, m);
        for (int i = 0; i < n; i++) {
            v[i] = distribution(generator);
            //cout << v[i] << endl;
        }
            int* copie = (int*) malloc(n * sizeof(int));
            for(int x = 0; x < n; x++)
                copie[x] = v[x];
            int* v_sortat = (int*) malloc(n * sizeof(int));
            for(int x = 0; x < n; x++)
                v_sortat[x] = v[x];
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);
            ios_base::sync_with_stdio(false);
            sort(v_sortat, v_sortat+n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        cout << "Time taken by stl sort is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec"<<endl;

            clock_gettime(CLOCK_MONOTONIC, &start);
            ios_base::sync_with_stdio(false);
            radixsort_10(v, n);
            clock_gettime(CLOCK_MONOTONIC, &end);
            time_taken = (end.tv_sec - start.tv_sec) * 1e9;
            time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

            cout << "Time taken by radixsort 10 is : " << fixed
                 << time_taken << setprecision(9);
            cout << " sec";
            int cnt = 1;
            for(int i = 0; i<n; i++){
                if (v[i] != v_sortat[i])
                    cnt = 0;
                v[i] = copie[i];
            }
            if (cnt == 1)
                cout<<" Sorted"<<endl;
            else{
                cout<<"NUU!"<<endl;
            }
        clock_gettime(CLOCK_MONOTONIC, &start);
        ios_base::sync_with_stdio(false);
        radixsort_16(v, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        cout << "Time taken by radixsort 16 is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec";
        cnt = 1;
        for(int i = 0; i<n; i++){
            if (v[i] != v_sortat[i])
                cnt = 0;
            v[i] = copie[i];
        }
        if (cnt == 1)
            cout<<" Sorted"<<endl;
        else{
            cout<<"NUU!"<<endl;
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        ios_base::sync_with_stdio(false);
        radixsort_2_16(v, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        cout << "Time taken by radixsort 2^16 is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec";
        cnt = 1;
        for(int i = 0; i<n; i++){
            if (v[i] != v_sortat[i])
                cnt = 0;
            v[i] = copie[i];
        }
        if (cnt == 1)
            cout<<" Sorted"<<endl;
        else{
            cout<<"NUU!"<<endl;
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        ios_base::sync_with_stdio(false);
        mergeSort(v,0 ,n-1);
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        cout << "Time taken by mergesort is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec";
        cnt = 1;
        for(int i = 0; i<n; i++){
            if (v[i] != v_sortat[i])
                cnt = 0;
            v[i] = copie[i];
        }
        if (cnt == 1)
            cout<<" Sorted"<<endl;
        else{
            cout<<"NUU!"<<endl;
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        ios_base::sync_with_stdio(false);
        shellSort(v, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        cout << "Time taken by shellsort is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec";

        cnt = 1;
        for(int i = 0; i<n; i++){
            if (v[i] != v_sortat[i])
                cnt = 0;
            v[i] = copie[i];
        }
        if (cnt == 1)
            cout<<" Sorted"<<endl;
        else{
            cout<<"NUU!"<<endl;
        }
        if(n<1000000) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            ios_base::sync_with_stdio(false);
            bubbleSort(v, n);
            clock_gettime(CLOCK_MONOTONIC, &end);
            time_taken = (end.tv_sec - start.tv_sec) * 1e9;
            time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

            cout << "Time taken by bubblesort is : " << fixed
                 << time_taken << setprecision(9);
            cout << " sec";

            cnt = 1;
            for (int i = 0; i < n; i++) {
                if (v[i] != v_sortat[i])
                    cnt = 0;
                v[i] = copie[i];
            }
            if (cnt == 1)
                cout << " Sorted" << endl;
            else {
                cout << "NUU!" << endl;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        ios_base::sync_with_stdio(false);
        quickSort(v, 0, n-1);
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        cout << "Time taken by quicksort is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec";
        cnt = 1;
        for(int i = 0; i<n; i++){
            if (v[i] != v_sortat[i])
                cnt = 0;
            v[i] = copie[i];
        }
        if (cnt == 1)
            cout<<" Sorted"<<endl;
        else{
            cout<<"NUU!"<<endl;
        }
            free(v);
        }

    return 0;
}
