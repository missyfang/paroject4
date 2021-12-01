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
    bool discovered = false;
    // index of pred node
    int pred;
};

class B {
    // node or node* ??
    int total;
    vector<node*> grid;
    vector<node*> cycle;
    void readB(); 
    double randomInsert();
    double distance(int x, int y); 
};

double B::randomInsert(){
    double sum = 0;
    // connect first 3 nodes
    // assumes size >= 3
    double dist = distance(1, 2);
    grid[2]->pred = 1;
    sum += dist;
    dist = distance(2, 3);
    grid[3]->pred = 2;
    sum += dist;
    dist = distance(3, 1);
    grid[1]->pred = 3;
    sum += dist;
    // while node all nodes in cycle, maybe total + 1;
    while (cycle.size() != total){
        // find random node idk how to do this efficently.
        // idk this errors
      //  int rand = rand() % total;
        // just 
        if (grid[rand]->discovered == false){
            grid[rand]->discovered = true;
            // find nearest node;
            double min = numeric_limits<double>::infinity();
            int min_index;
            for (int i = 0; i < cycle.size() ; i++){
                double dist = distance(i, rand);
                if (dist < min){
                    min = dist;
                    min_index = i;
                } // if
            } // for
            // insert between and fix sum 
            sum =- distance(min_index,grid[min_index]->pred);
            int temp = grid[min_index]->pred;
            grid[min_index]->pred = rand;
            grid[rand]->pred = temp;
            sum += distance(temp,rand);
            sum += distance(rand,min_index);
        } // if
    } // while
    
    return sum;
    
}
double B::distance(int j, int k){
    double dist = 0;
    double x = static_cast<double>(grid[j]->x) - static_cast<double>(grid[k]->x);
    double y =  static_cast<double>(grid[j]->y) - static_cast<double>(grid[k]->y);
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
        node* c = new node;
        c->x = x;
        c->y = y;
        grid.push_back(c);
    }
}
