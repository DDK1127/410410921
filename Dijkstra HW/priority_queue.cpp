#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    vector<int>values(7);
    for(int i = 0 ; i < 3; i++){
        values[i] = i*10;
    }
    values[3] = 9999;
    values[4] = 9999;
    values[5] = 9999;
    priority_queue <int, vector<int>, greater<int> > minqueue(values.begin(), values.end());

    while (!minqueue.empty()){
            values[4] = 9999-1;
        for(int i =0; i < values.size(); i++){
            if(values[i] == minqueue.top())
                cout <<"answer is = "<< i  << " , =" << values[i]<< endl;
        }
        minqueue.pop();
    }
    for(int i = 0; i < 6; i++)
        cout << "value["<< i << "] is = " << values[i] << endl;


    
    return 0;
}