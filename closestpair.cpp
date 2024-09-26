#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <iostream>
using namespace std;

Outcome brute(const vector<Point>& data) {
    Outcome best(data[0], data[1], distSquared(data[0],data[1]));
    for (unsigned int j=1; j < data.size(); j++) {
        for (unsigned int k=0; k < j; k++) {
            long long temp = distSquared(data[j], data[k]);
            if (temp < best.dsq) {
                best = Outcome(data[j], data[k], temp);
            }
        }
    }
    return best;
}


Outcome divideAndConquer(vector<Point>& data, vector<Point> dataX,vector<Point> dataY,int start, int end){
    /*int n = dataX.size();
    if (n <= 3){
        return myBrute(dataX);
    } else {
        Point mid = data[dataX[n/2]]; //midpoint //not always the midpoint
        divideAndConquer(data, dataX, dataY, 0, mid);
        divideAndConquer(data, dataX, dataY, mid + 1, n-1);
    }*/
   return Outcome();
}

vector<int> sortX(const vector<Point>& data){
    vector<int> idx(data.size());
    for(int i = 0; i < data.size(); i++){ //check to see if it sorted them right !!!!!!!!!!!!!!!!!!!!!!!!!
        idx[i] = i;
    }

    stable_sort(idx.begin(), idx.end(), [&data](int i1, int i2) {return compareByX(data[i1], data[i2]);});
    return idx;
}

Outcome efficient(const vector<Point>& data) {
    // Sort the data

    for(int i = 0; i < data.size(); i ++){ //check to see if it sorted them right !!!!!!!!!!!!!!!!!!!!!!!!!
        cout << data[i].x;
    }
    cout << "\n";
    vector<int> dataX = sortX(data);
    vector<Point> dataY = data;
    //std::sort(dataX.begin(), dataX.end(), compareByX); //sort by X values
    //std::sort(dataY.begin(), dataY.end(), compareByY); //sort by Y values
    //^not the sorted indeces, this is sorted data
    
    for(int i = 0; i < data.size(); i ++){ //check to see if it sorted them right !!!!!!!!!!!!!!!!!!!!!!!!!
        cout << dataX[i];
    }
    cout << "\n";

    // Divide and conquer
    //Outcome best = divideAndConquer(data, dataX, dataY, 0, data.size() - 1);

    return Outcome();
}


Outcome extra(const vector<Point>& data) {
    return Outcome();
}
