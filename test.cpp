#include<iostream>
#include<cstdio>
#include<ctime>
#include<fstream>

using namespace std;

int main(){
    int A = 5;
    clock_t start = clock();
    ofstream myfile;
    myfile.open("eyetrack.csv");
    while(true){
        myfile << A << "," << A << "," << A << ",\n";
        if(clock() - start > 2 * CLOCKS_PER_SEC){
            myfile.close();
            break;
        }
    }
}