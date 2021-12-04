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

/*class compare {
public:
    bool operator()(struct cage* left, struct cage* right){
        return true;
    }
};
*/

class A {
    public:
    // do all the stuff 
    void readA();
    // why are these ptrs? 
    vector<cage> prim_table;
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
    int num = 0;
    cin >> num;
    int x;
    int y;
    while (cin >> x){
        cin >> y;
        // need to worry about leaking here?
        struct cage c;
        // any point in making a pair?
        c.x = x;
        c.y = y;
        if (x <= 0 && y <= 0){
            if (x == 0 || y == 0){
                c.cat = 'b';
            }
            else {
                c.cat = 'w';
            }
        }
        prim_table.push_back(c);
    }
}

double A::primsAlg(){
    double sum = 0;
    uint64_t min_index = 0;
    prim_table[0].dist = 0;
    prim_table[min_index].visited = true;
    size_t i = 0;
    while (i < prim_table.size()){
        // find min is there a way where i dont have too loop thru the whole thing?
        if (i > 0){
            double min = numeric_limits<double>::infinity();
            // can start at 1?
            size_t  j = 0;
            while (j < prim_table.size()){
            // <= is a edge case thing
                if (prim_table[j].dist <= min && !prim_table[j].visited){
                // what up with what min is
                    min = prim_table[j].dist;
                    min_index = j;
                }//if
                j++;
            }//while
            // chain broken there is not MST
            if (prim_table[min_index].dist == numeric_limits<double>::infinity()){
                return 0;
            }
        }//if
       // cout << "min_index" << min_index << "\n";
        // why not set min_index to true here
        size_t k = 0;
        while (k < prim_table.size()){
            if (!prim_table[k].visited && k != min_index){
            double dist = distance(static_cast<int>(min_index),static_cast<int>(k));
                if (dist < prim_table[k].dist){
                   // cout << "min_index " << min_index << " now goes to node" << k <<"\n";
                    prim_table[k].dist = dist;
                  //  cout << "distance " << dist << "\n";
                    prim_table[k].pred = static_cast<int>(min_index);
                  //  cout << "node " << k << "pred is now " << prim_table[k].pred << "\n";
                }//if
            } // if
            k++;
        } // while
       // prim_table[min_index]->visited = true;
        // create pair
        // want to not do this check some how?
        if (min_index != 0){
           // cout << min_index << "set to true\n";
            prim_table[min_index].visited = true;
            pair<int,int> p;
            p.first = min(prim_table[min_index].pred,static_cast<int>(min_index));
            p.second = max(prim_table[min_index].pred,static_cast<int>(min_index));
           // auto p = minmax(prim_table[min_index]->pred,static_cast<int>(min_index));
            tree.push_back(p);
            sum += distance(prim_table[min_index].pred, static_cast<int>(min_index));
          //  cout << "entered into tree" << tree.back().first << " " << tree.back().second << "\n";
           // cout << static_cast<int>(min_index) << " " << prim_table[min_index].pred << "\n";
        }
        i++;
    }//while
    return sum;
}

// distance is weird decimal
double A::distance(int j, int k){
    // dont think need to worry about overflow or negs
    // issue here when there is no MST bc
    if ((prim_table[j].cat == 'w' && prim_table[k].cat == 's') || (prim_table[k].cat == 'w' && prim_table[j].cat =='s')){
        return numeric_limits<double>::infinity();
    }
    double dist = 0;
    double x = static_cast<double>(prim_table[j].x) - static_cast<double>(prim_table[k].x);
    double y =  static_cast<double>(prim_table[j].y) - static_cast<double>(prim_table[k].y);
    dist = (x * x) + (y * y);
    return sqrt(dist);
}


// print
