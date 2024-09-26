#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <iostream>
#include <cmath>
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


Outcome divideAndConquer(const vector<Point>& data, vector<int> dataX, vector<int> dataY,int start, int end){
    int n = end - start;

    if (n <= 3){
        if (n <= 0.1*data.size()){ //once it gets down to 10% of og points 
            Outcome best(data[dataX[start]],data[dataX[end]],distSquared(data[dataX[start]],data[dataX[end]])); //use first two points 
            for(int j = start; j < end-1; j++){ 
                for(int k = j+1; k < end; k++){ 
                    long long temp = distSquared(data[j],data[k]); 
                    if(temp < best.dsq){ 
                        best = Outcome(data[j], data[k],temp); 
                    } 
                } 
            } 
            return best; 
        }

    } else {
        int mid = (end - start)/2 + start;
        Outcome cp1 = divideAndConquer(data, dataX, dataY, 0, mid);
        Outcome cp2 = divideAndConquer(data, dataX, dataY, mid + 1, n-1);
        Outcome minCp;
        
        //find minimum from Left and Right
        if(cp1.dsq > cp2.dsq){
            minCp.dsq = cp2.dsq;
            minCp.p = cp2.p;
            minCp.q = cp2.q;
        } else {
            minCp.dsq = cp1.dsq;
            minCp.p = cp1.p;
            minCp.q = cp1.q;
        }

        for(int i = 0; i < dataY.size() - 1; i++){
            if(data[dataY[i]].x - dataX[mid] <= sqrt(minCp.dsq) &&
                data[dataY[i + 1]].x - dataX[mid] <= sqrt(minCp.dsq)){ //within range of the median
                if(distSquared(data[dataY[i]], data[dataY[i + 1]]) < minCp.dsq){
                    minCp.dsq = distSquared(data[dataY[i]], data[dataY[i + 1]]);
                    minCp.p = data[dataY[i]];
                    minCp.q = data[dataY[i + 1]];
                }
            }
        }

        return minCp;
    }
}

vector<int> sortX(const vector<Point>& data){
    vector<int> dataX;
    for(int i = data.size() - 1; i >= 0; i--){ 
        dataX.push_back(i);
    }
    
    stable_sort(dataX.begin(), dataX.end(), [&data](int i1, int i2) {return compareByX(data[i1], data[i2]);});
    return dataX;
}

vector<int> sortY(const vector<Point>& data){
    vector<int> dataY;
    for(int i = data.size() - 1; i >= 0; i--){ 
        dataY.push_back(i);
    }
    
    stable_sort(dataY.begin(), dataY.end(), [&data](int i1, int i2) {return compareByY(data[i1], data[i2]);});
    return dataY;
}

Outcome efficient(const vector<Point>& data) {
    // Sort the data
    for(int i = 0; i < data.size(); i++){ 
        cout << data[i].x << endl;
    }

    cout << "\n";
    vector<int> dataX = sortX(data);
    vector<int> dataY = sortY(data);
        
    for(int i = 0; i < data.size(); i ++){ 
        cout << dataX[i];
    }
    cout << "\n";

    //Divide and conquer
    Outcome best = divideAndConquer(data, dataX, dataY, 0, data.size() - 1);

    return Outcome();
}


Outcome extra(const vector<Point>& data) {
    return Outcome();
}
