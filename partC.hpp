// 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
//  partC.hpp
//  project4
//
//  Created by Missy Fang  on 12/5/21.
//

#ifndef partC_hpp
#define partC_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits>
#include <utility>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
// is this okay to include?
#include <math.h>
using namespace std;
#endif /* partC_hpp */

struct node_c {
    int x;
    int y;
    double distance = numeric_limits<double>::infinity();
    int pred;
    
};
class C{
    
public:
    int total;
    vector<int> best_path;
    vector<node_c> grid;
    double curr_cost = 0;
    double best_cost = 0;
    void genPerms(vector<int> &path, size_t permLength);
    void readC();
    bool promising(vector<int> &path, int permLength);
    double distance(int j, int k);
    double partB();
    double partA(vector<int> &path, int permLength);
};

void C::readC(){
    int num = 0;
    total = num;
    cin >> num;
    int x;
    int y;
    while (cin >> x){
        cin >> y;
        struct node_c c;
        c.x = x;
        c.y = y;
        grid.push_back(c);
    }
}

// intial call to part b to set best cost
void C::genPerms(vector<int> &path, size_t permLength) {
    //have reached leaf node
  if (permLength == path.size()) {
      curr_cost += distance(path[0],path[permLength - 1]);
      if (curr_cost < best_cost){
          best_cost = curr_cost;
          best_path = path;
      }
      curr_cost -= distance(path[0],path[permLength - 1]);
    return;
  } // if
    if (!promising(path, permLength)){
        return;
    }
  for (size_t i = permLength; i < path.size(); ++i) {
      swap(path[permLength], path[i]);
      double new_dist = distance(path[permLength],path[permLength - 1]);
      curr_cost += new_dist;
      genPerms(path, permLength + 1);
      curr_cost -= new_dist;
      swap(path[permLength], path[i]);
  } // for
} // genPerms()

double C::distance(int j, int k){
    double dist = 0;
    double x = static_cast<double>(grid[j].x) - static_cast<double>(grid[k].x);
    double y =  static_cast<double>(grid[j].y) - static_cast<double>(grid[k].y);
    dist = (x * x) + (y * y);
    return sqrt(dist);
}

double C::partB(){
    double sum = 0;
    sum = distance(0,1) + distance(1,2) + distance(2,0);
    best_path.push_back(0);
    best_path.push_back(1);
    best_path.push_back(2);
    
    int rand = 3;
    while (rand < grid.size()){
        double min = numeric_limits<double>::infinity();
        int min_pred = 0;
        double dist;
        for (int i = 0; i < best_path.size(); i++){
            //wrap around;
            if (i == (best_path.size() - 1)){
                dist = distance(rand,best_path[i]) + distance(rand, best_path[0]) - distance(best_path[i],best_path[0]);
            }
            else{
                dist = distance(rand,best_path[i]) + distance(rand, best_path[i+1]) - distance(best_path[i],best_path[i + 1]);
            }
            if (dist < min){
                    min_pred = i;
                    min = dist;
            }
        }
        int new_index = min_pred + 1;
        if (min_pred == (best_path.size() - 1)){
            sum -= distance(best_path[0],best_path[min_pred]);
            best_path.insert(best_path.begin() + new_index, rand);
            sum += distance(best_path[new_index - 1],best_path[new_index]);
            sum += distance(best_path[0],best_path[new_index]);
        }
        else {
            sum -= distance(best_path[min_pred],best_path[min_pred+1]);
            best_path.insert(best_path.begin() + new_index, rand);
            sum += distance(best_path[new_index],best_path[new_index + 1]) + distance(best_path[new_index -1],best_path[new_index]);
        }
        rand++;
    }
    best_cost = sum;
    curr_cost = 0; 
    return sum;
    
}

double C::partA(vector<int> &path, int permLength){
    double sum = 0;
    for (int i = permLength; i < grid.size(); i ++){
        grid[path[i]].distance = numeric_limits<double>::infinity();
    }
    
    vector<int> unvisited (path.begin() + permLength, path.end());
    vector<int> MST;
    grid[path[permLength]].distance = 0;
    while (MST.size() < (path.size() - permLength)){
    double min = numeric_limits<double>::infinity();
    int min_index = numeric_limits<double>::infinity();
    int k = 0;
    for (int i = 0; i < unvisited.size() ; i++){
        if (grid[unvisited[i]].distance < min){
            min = grid[unvisited[i]].distance;
            min_index = unvisited[i];
            k = i;
        }
    }
    MST.push_back(min_index);
    sum += grid[min_index].distance;
    // erase that node from unvisted vector
    unvisited.erase(unvisited.begin() + k);
    for (int i = 0; i < unvisited.size(); i++){
        double dist = distance(min_index,unvisited[i]);
        if (dist < grid[unvisited[i]].distance){
            grid[unvisited[i]].distance = dist;
        }
    }
    }
    return sum;
}

bool C::promising(vector<int> &path, int permLength){
    if (permLength > (path.size() - 4)){
        return true;
    }
    double estimate = partA(path, permLength);
    double min_arm1 = numeric_limits<double>::infinity();
    double min_arm2 = numeric_limits<double>::infinity();
    int arm1;
    int arm2;
    
    for (int i = permLength ; i < path.size() ; i++){
        if (min_arm1 > distance(path[0],path[i])){
            min_arm1 = distance(path[0],path[i]);
            arm1 = i;
        }
        if (min_arm2 > distance(path[permLength - 1],path[i])){
            min_arm2 = distance(path[permLength - 1],path[i]);
            arm2 = i;
        }
    }
    
    // check if proming or not
    bool promise;
    double total_cost = curr_cost + min_arm1 + min_arm2 + estimate;
    if ((curr_cost + min_arm1 + min_arm2 + estimate) < best_cost){
    
       promise = true;
    }
    else {
        promise = false;
    }
    /*
    cerr << path[0] << " ";
    for ( int i = 1; i < path.size() ; i++){
        cerr << setw(2) << path[i] << " ";
    }
        cerr << setw(4) << permLength << setw(10) << curr_cost;
       // cerr << setw(10) << min_arm1 << setw(10) << curr_cost;
        cerr << setw(10) << min_arm1 << setw(10) << min_arm2 << "\n";
        cerr << estimate << setw(10) << total_cost  << " "  << boolalpha << promise << "\n";
    */
    return promise;
}

// prominisng
/*
 dont call wen the number not fixed < ?
 call part A
 figure out connecting arms, shortest possible so to the closest node
 try every possibility?
 check if curr cost + connecting arms + mst < best
 */

/*
 set best length and path to part b
 part A only need the cost not the path? 
 */
