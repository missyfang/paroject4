//3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
//  partB.hpp
//  project4
//
//  Created by Missy Fang  on 11/29/21.
//
#ifndef partB_hpp
#define partB_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits>
#include <utility>
#include <iostream>
#include <string>
#include <stdlib.h>
// is this okay to include?
#include <math.h>
using namespace std;
#endif /* partB_hpp */

struct node{
    int x;
    int y;
};

class B {
public:
    int total;
    vector<node> grid;
    vector<int> path;
    void readB(); 
    double randomInsert();
    double distance(int x, int y); 
};

double B::randomInsert(){
    double sum = 0;
    sum = distance(0,1) + distance(1,2) + distance(2,0);
    path.push_back(0);
    path.push_back(1);
    path.push_back(2);
    
    int rand = 3;
    while (rand < grid.size()){
        double min = numeric_limits<double>::infinity();
        int min_pred = 0;
        double dist;
        for (int i = 0; i < path.size(); i++){
            //wrap around;
            if (i == (path.size() - 1)){
                dist = distance(rand,path[i]) + distance(rand, path[0]) - distance(path[i],path[0]);
            }
            else{
                dist = distance(rand,path[i]) + distance(rand, path[i+1]) - distance(path[i],path[i + 1]);
            }
            if (dist < min){
                    min_pred = i;
                    min = dist;
            }
        }
        int new_index = min_pred + 1;
        if (min_pred == (path.size() - 1)){
            sum -= distance(path[0],path[min_pred]);
            path.insert(path.begin() + new_index, rand);
            sum += distance(path[new_index - 1],path[new_index]);
            sum += distance(path[0],path[new_index]);
        }
        else {
            sum -= distance(path[min_pred],path[min_pred+1]);
            path.insert(path.begin() + new_index, rand);
            sum += distance(path[new_index],path[new_index + 1]) + distance(path[new_index -1],path[new_index]);
        }
        rand++;
    }
    return sum;
    
}
double B::distance(int j, int k){
    double dist = 0;
    double x = static_cast<double>(grid[j].x) - static_cast<double>(grid[k].x);
    double y =  static_cast<double>(grid[j].y) - static_cast<double>(grid[k].y);
    dist = (x * x) + (y * y);
    return sqrt(dist);
}

void B::readB(){
    int num = 0;
    total = num;
    cin >> num;
    int x;
    int y;
    while (cin >> x){
        cin >> y;
        struct node c;
        c.x = x;
        c.y = y;
        grid.push_back(c);
    }
}
