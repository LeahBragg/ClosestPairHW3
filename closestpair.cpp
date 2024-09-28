#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

//given brute force approach
Outcome brute(const vector<Point>& data) {
    Outcome best(data[0], data[1], distSquared(data[0],data[1]));
    for (unsigned int j = 1; j < data.size(); j++) {
        for (unsigned int k = 0; k < j; k++) {
            long long temp = distSquared(data[j], data[k]);
            if (temp < best.dsq) {
                best = Outcome(data[j], data[k], temp);
            }
        }
    }
    return best;
}

//recursive divide and conquer 
Outcome divideAndConquer(const vector<Point>& data, vector<int> dataX, vector<int> dataY, int start, int end){
   
    int n = end - start; //base case
    Outcome best;
    if (n <= 1000){ 
        //brute force
        Outcome best(data[dataX[start]], data[dataX[start + 1]], distSquared(data[dataX[start]], data[dataX[start + 1]])); //use first two points 
        for(int j = start + 1; j <= end - 1; j++){ 
            for(int k = j + 1; k <= end; k++){ 
                long long temp = distSquared(data[dataX[j]], data[dataX[k]]); 
                if(temp < best.dsq){ 
                    best.dsq = temp;
                    best.p = data[dataX[j]];
                    best.q = data[dataX[k]]; 
                } 
            } 
        } 
        return best; 
    } 

    //spliting the Y vector
    int midAll = (end - start)/2 + start; //find median between end and start
    int midY = dataY.size()/2;

    vector<int> dataYLeft(midAll - start + 1);
    vector<int> dataYRight(end - midAll + 1);

    copy(dataY.begin(), dataY.begin() + midY, dataYLeft.begin());
    copy(dataY.begin() + midY, dataY.end(), dataYRight.begin());

    Outcome cpLeft = divideAndConquer(data, dataX, dataYLeft, start, midAll);
    Outcome cpRight = divideAndConquer(data, dataX, dataYRight, midAll + 1, end);
        
    //find minimum from Left and Right and set it to "best"
    if(cpLeft.dsq > cpRight.dsq){
        best.dsq = cpRight.dsq;
        best.p = cpRight.p;
        best.q = cpRight.q;
    } else {
        best.dsq = cpLeft.dsq;
        best.p = cpLeft.p;
        best.q = cpLeft.q;
    }

    //loop vertically through points close to median
    for(unsigned int i = 0; i < dataY.size() - 1; i++){
        if(abs(data[dataY[i]].x - dataX[midAll]) <= sqrt(best.dsq)){ //if point is in rang of the median
            for(unsigned int j = i + 1; j < dataY.size(); j++){ //loop upwards
                if((abs(data[dataY[j]].x - dataX[midAll]) <= sqrt(best.dsq))){ //if this point is also in range        
                    long long int newDisSq = distSquared(data[dataY[i]], data[dataY[j]]);
                    if(newDisSq < best.dsq){//new minimum found
                        best.dsq = newDisSq;
                        best.p = data[dataY[i]];
                        best.q = data[dataY[j]];

                    } else { //stop looping, out of bounds
                        break;
                    }
                } 
            }
        }
    }

    return best;
    
}

vector<int> sortX(const vector<Point>& data){
    vector<int> dataX;
    for(unsigned int i = 0; i < data.size(); i++){ 
        dataX.push_back(i);
    }

    stable_sort(dataX.begin(), dataX.end(), [&data](int i1, int i2) {return compareByX(data[i1], data[i2]);});
    return dataX;
}

vector<int> sortY(const vector<Point>& data){
    vector<int> dataY;
    for(unsigned int i = 0; i < data.size(); i++){ 
        dataY.push_back(i);
    }
    
    stable_sort(dataY.begin(), dataY.end(), [&data](int i1, int i2) {return compareByY(data[i1], data[i2]);});
    return dataY;
}

Outcome efficient(const vector<Point>& data) {

    vector<int> dataX = sortX(data);
    vector<int> dataY = sortY(data);
    
    //Divide and conquer
    Outcome best = divideAndConquer(data, dataX, dataY, 0, data.size() - 1);

    return best;
}


Outcome extra(const vector<Point>& data) {
    return Outcome();
}
