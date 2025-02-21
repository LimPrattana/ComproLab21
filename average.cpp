#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
int main(int argc,char * argv[]){

    if(argc<2){
        cout<<"Please input numbers to find average.\n";
        return 1;
    }
    cout<<"---------------------------------\n";
    double sum = 0;
    double avg;
    int count = argc-1;
    for(int i=1;i<argc;i++){
        sum+= atof(argv[i]);
    }
    avg = sum/count;
    cout<<"Average of "<<count<<" numbers = "<<avg;
    cout<<"\n---------------------------------";
return 0;
}
