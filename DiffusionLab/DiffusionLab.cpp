#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int steps=0;
    int trials=0;
    int currentPosition=0;
    ofstream output;
    bool worked=false;
    output.open("DiffusionData.csv",ios::out); 
        if(output.is_open())
        {
            if(output.good())
                {
                    worked=true;
                }
                else
                {
                    if(!output.eof())
                    {
                        cerr << "Error Cannot read data\n";
                    }
                }
        }
        else
        {
            cerr << "Error! Cannot open file \n";
        }
    if(worked){
        //For allowing custom input
        /*cout << "How many steps?: ";
        cin >> steps;
        cout << "How many trials?: ";
        cin >> trials;*/
        srand(static_cast<unsigned>(time(nullptr)));
        output << "Number of Steps (N), Trial Number (M), Final" 
            "Position (D)\n";
            trials=10;
            steps=5;
        for(int k=0; k<4;k++){
            for(int i=0; i<trials; i++){
                for(int j=0; j<steps; j++){
                    if(rand()%2==0){
                        currentPosition++;
                    }else{
                        currentPosition--;
                    }
                }
                output << steps << "," << i+1 << "," << 
                    currentPosition 
                    << '\n';
                cout << "\nTrial " << i+1 << ": Final Position: " 
                << currentPosition;
                currentPosition=0;
            }
            steps=steps*10;
        }
        output.close();
    }
    return 0;
}
