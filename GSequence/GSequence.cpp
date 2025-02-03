#include <iostream>


using namespace std;

int Gsequence(int n);

int main()
{
    for(int i=0;i<11;i++)
    {
        cout << "G(" << i << ")="<< Gsequence(i) << endl;
    }
    int value=0;
    cout << "Which term in the G Sequence?: ";
    cin >> value;

    cout << "G(" << value << ")="<< Gsequence(value) << endl;

    return 0;
}

int Gsequence(int n){
    if(n==0){
        return 0;
    }else{
        return n-Gsequence(Gsequence(n-1));
    }
}
