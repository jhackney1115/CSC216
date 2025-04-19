#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int flips=0;
    int trials=0;
    double headsChance=0.1;
    int heads=0;
    ofstream output;
    bool worked=false;
    output.open("CoinData.csv",ios::out); 
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
        srand(static_cast<unsigned>(time(nullptr)));
        output << "Number of Flips (N), Prob. of heads (P), "
        "Trial Number (M), Heads\n";
        trials=10;
        flips=10;
        for(int k=0; k<5; k++){
            for(int l=0; l<5; l++){
                if(l==0){
                    headsChance=0.1;
                }else if(l==1){
                    headsChance=0.25;
                }else if(l==2){
                    headsChance=1.0/3.0;
                }else if(l==3){
                    headsChance=0.5;
                }else{
                    headsChance=0.75;
                }
                for(int i=0; i<trials; i++){
                    for(int j=0; j<flips; j++){
                        if(((rand()%100)+1)<=headsChance*100){
                            heads++;
                        }
                    }
                    output << flips << "," << headsChance << "," 
                        << i+1 << "," << heads <<'\n';
                    heads=0;
                }
            }
            flips=flips*10;
        }
        output.close();
    }
    return 0;
}
