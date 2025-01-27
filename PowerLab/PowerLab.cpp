#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

int naivePower(int base, int power);
int unoptimizedDCPower(int base, int power);
int optimizedDCPower(int base, int power);

int main(){
    int baseNum=0;
    int powerNum=0;
    cout<<"input a base and a power with a space between the values:";
    cin >> baseNum >> powerNum;

    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    long long int average = 0;

    // output values
    cout << naivePower(baseNum,powerNum) << endl;
    cout << unoptimizedDCPower(baseNum,powerNum) << endl;
    cout << optimizedDCPower(baseNum,powerNum) << endl;

    //average times
    for(int i=1;i<100;i++){
        start = high_resolution_clock::now();
        naivePower(baseNum,powerNum);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=100;
    cout << "Naive took "<<  average << " nanoseconds" << endl;

    average=0;
    for(int i=1;i<100;i++){
        start = high_resolution_clock::now();
        unoptimizedDCPower(baseNum,powerNum);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=100;
    cout << "Unoptimized took "<<  average << " nanoseconds" << endl;
    
    average=0;
    for(int i=1;i<100;i++){
        start = high_resolution_clock::now();
        optimizedDCPower(baseNum,powerNum);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        average+=duration.count();
    }
    average/=100;
    cout << "Optimized took "<<  average << " nanoseconds" << endl;

    return 0;
}

int naivePower(int base, int power){
    if(base==0){
        return 0;
    }
    if(power==0){
        return 1;
    }
    return base * naivePower(base, power-1);
}

int unoptimizedDCPower(int base, int power){
    if(base==0){
        return 0;
    }
    if(power==0){
        return 1;
    }
    if(power%2==0){
        return unoptimizedDCPower(base, power/2) *
            unoptimizedDCPower(base, power/2);
    }else{
        return unoptimizedDCPower(base, power/2) *
            unoptimizedDCPower(base, power/2) * base;
    }
}

int optimizedDCPower(int base, int power){
    if(base==0){
        return 0;
    }
    if(power==0){
        return 1;
    }
    int temp = optimizedDCPower(base, power/2);
    if(power%2==0){
        return temp * temp;
    }else{
        return temp * temp * base;
    }
}
