//3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
//  partA.hpp
//  project4
//
//  Created by Missy Fang  on 11/22/21.
//

#ifndef partA_hpp
#define partA_hpp
#include <vector>
#include <algorithm> 
#include <stdio.h>
#include <limits>
#include <utility>
#include <iostream>
#include <string>
// is this okay to include?
#include <math.h>
using namespace std;

#endif /* partA_hpp */

struct cage{
    char cat = 's';
    bool visited = false;
    double dist = numeric_limits<double>::infinity();
    int x;
    int y; 
    // idk if this is right could be int would save space ....
    int pred;
};

class compare {
public:
    bool operator()(struct cage* left, struct cage* right){
        return true;
    }
};


class A {
    public:
    // do all the stuff 
    void readA();
    vector<cage*> prim_table;
    vector<pair<int,int>> tree;
    //void just modify cage??
    // want to just pass in comp
     double primsAlg();
    // calaculate distance
    // what is best to pass here
    double distance(int, int);
};



// read in coors and push to vector
void A::readA(){
    int num;
    cin >> num;
    int x;
    int y;
    while (cin >> x){
        cin >> y;
        // need to worry about leaking here?
        cage* c = new cage;
        // any point in making a pair?
        c->x = x;
        c->y = y;
        if (x <= 0 && y <= 0){
            if (x == 0 || y == 0){
                c->cat = 'b';
            }
            else {
                c->cat = 'w';
            }
        }
        prim_table.push_back(c);
    }
}

double A::primsAlg(){
    double sum = 0;
    int min_index = 0;
    prim_table[0]->dist = 0;
    prim_table[min_index]->visited = true;
    int i = 0;
    while (i < prim_table.size()){
        // find min is there a way where i dont have too loop thru the whole thing?
        if ( i > 0){
            double min = numeric_limits<double>::infinity();
            // can start at 1?
            int j = 0;
            while (j < prim_table.size()){
            // <= is a edge case thing
                if (prim_table[j]->dist <= min && !prim_table[j]->visited){
                // what up with what min is
                    min = prim_table[j]->dist;
                    min_index = j;
                }//if
                j++;
            }//while
        }//if
        int k = 0;
        while (k < prim_table.size()){
            if (!prim_table[k]->visited && k != min_index){
            double dist = distance(min_index,k);
                if (dist < prim_table[k]->dist){
                    prim_table[k]->dist = dist;
                    prim_table[k]->pred = min_index;
                }//if
            } // if
            k++;
        } // while
       // prim_table[min_index]->visited = true;
        // create pair
        // want to not do this check some how?
        if (min_index != 0){
            prim_table[min_index]->visited = true;
            auto p = minmax(prim_table[min_index]->pred, min_index);
                tree.push_back(p);
        //    tree[prim_table[min_index]->pred] = min_index;
            sum += distance(prim_table[min_index]->pred, min_index);
        }
        i++;
    }//while
    return sum;
}

// distance is weird decimal
double A::distance(int j, int k){
    // dont think need to worry about overflow or negs
    if ((prim_table[j]->cat == 'w' && prim_table[k]->cat == 's') || (prim_table[k]->cat == 'w' && prim_table[j]->cat =='s')){
        return numeric_limits<double>::infinity();
    }
    double dist;
    double x = static_cast<double>(prim_table[j]->x) - static_cast<double>(prim_table[k]->x);
    double y =  static_cast<double>(prim_table[j]->y) - static_cast<double>(prim_table[k]->y);
    dist = (x * x) + (y * y);
    return sqrt(dist);
}
