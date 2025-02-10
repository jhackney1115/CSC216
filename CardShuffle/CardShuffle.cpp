#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
using namespace std::chrono;

void BadShuffle(int* array, int size);
void MidShuffle(int* array, int size);
void GoodShuffle(int* array, int size);


int main(){

    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    long long int average = 0;

    int arr1[10];
    int size1 = 10;
    int arr2[50];
    int size2 = 50;
    int arr3[100];
    int size3 = 100;
    int arr4[500];
    int size4 = 500;
    
    for(int i=0; i<size1; i++){
        arr1[i]=i;
    }
    for(int i=0; i<size2; i++){
        arr2[i]=i;
    }
    for(int i=0; i<size3; i++){
        arr3[i]=i;
    }
    for(int i=0; i<size4; i++){
        arr4[i]=i;
    }

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        BadShuffle(arr1, size1);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Bad with 10 took "<<  average << " nanoseconds" << endl;
    average=0; 

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        BadShuffle(arr2, size2);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Bad with 50 took "<<  average << " nanoseconds" << endl;
    average=0;

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        BadShuffle(arr3, size3);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Bad with 100 took "<<  average << " nanoseconds" << endl;
    average=0;

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        BadShuffle(arr4, size4);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Bad with 500 took "<<  average << " nanoseconds" << endl;
    average=0;


    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        MidShuffle(arr1, size1);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Mid with 10 took "<<  average << " nanoseconds" << endl;
    average=0; 

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        MidShuffle(arr2, size2);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Mid with 50 took "<<  average << " nanoseconds" << endl;
    average=0; 

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        MidShuffle(arr3, size3);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Mid with 100 took "<<  average << " nanoseconds" << endl;
    average=0;

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        MidShuffle(arr4, size4);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Mid with 500 took "<<  average << " nanoseconds" << endl;
    average=0;  


    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        GoodShuffle(arr1, size1);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Good with 10 took "<<  average << " nanoseconds" << endl;
    average=0; 

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        GoodShuffle(arr2, size2);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Good with 50 took "<<  average << " nanoseconds" << endl;
    average=0; 

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        GoodShuffle(arr3, size3);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Good with 100 took "<<  average << " nanoseconds" << 
        endl;
    average=0; 

    for(int j=0; j<4;j++){
        start = high_resolution_clock::now();
        GoodShuffle(arr4, size4);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=4;
    cout << "Good with 500 took "<<  average << " nanoseconds" << 
        endl;
    average=0; 

    return 0;
}

void BadShuffle(int* array, int size) {
    int* copy = new int[size];
    int n = size, i;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int j = 0; j < size; j++) {
        copy[j] = -1;
    }

    while (n) {
        i = rand() % size; 
        // This is done like this because rand() is different in C++

        if (array[i] != -1) { 
            // Simulating 'delete' by checking a placeholder
            copy[size - n] = array[i];
            array[i] = -1; // Mark as deleted
            n--;
        }
    }

    // Copy shuffled elements back
    for (int j = 0; j < size; j++) {
        array[j] = copy[j];
    }
    
    delete[] copy;
}

void MidShuffle(int* array, int size) {
    int* copy = new int[size];
    int n = size;
    int i=0;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int j = 0; j < size; j++) {
        i = rand() % n;
        copy[j] = array[i];
        
        
        for (int k = i; k < n - 1; k++) {
            array[k] = array[k + 1];
        }
        n--;
    }

    for (int j = 0; j < size; j++) {
        array[j] = copy[j];
    }
    
    delete[] copy;
}

void GoodShuffle(int* array, int size) {
    int m = size, t, i;

    srand(static_cast<unsigned>(time(nullptr)));

    while (m) {
        i = rand() % m--;

        t = array[m];
        array[m] = array[i];
        array[i] = t;
    }
}

