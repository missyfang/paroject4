//3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
//  main.cpp
//  paroject4
//
//  Created by Missy Fang  on 11/22/21.
//

#include <iostream>
#include <getopt.h>
#include <string>
#include "xcode_redirect.hpp"
#include "partA.hpp"
#include <iomanip>
using namespace std;

string getMode(int argC, char * arg[]);

int main(int argc,  char * argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    cout << std::setprecision(2);
    cout << std::fixed; 
    
    string mode = getMode(argc, argv);
    // will always have to read in, always have to create cages. 
    if (mode == "MST"){
        A a;
        a.readA();
        cout << a.primsAlg() << "\n";
        sort(a.tree.begin(), a.tree.end());
        for (int i = 0; i < a.tree.size(); i++){
        cout << a.tree[i].first << " " << a.tree[i].second << "\n";
        } //for
    } // if
    return 0;
}

string getMode(int argc, char * argv[]){
    string mode;
    // These are used with getopt_long()
   // opterr = false; // Let us handle all error output for command line options
    int choice_index = 0;
    int choice;
    struct option long_options[] = {
        { "help", no_argument, nullptr, 'h'},
        { "mode", required_argument, nullptr, 'm'},
        // always have to denote end
        { nullptr, 0, nullptr, '\0' }};
    while ((choice = getopt_long(argc, argv,"hm:", long_options, &choice_index)) != -1) {
        switch (choice) {
        case 'h':
                std::cout << "you need help";
                exit(0);

        case 'm':
                // will this get only the first char
                mode = optarg;
                if (mode == "MST" || mode == "OPTTSP" || mode == "FASTTSP" ){
                    break;
                }
                std::cerr << "invalid mode";
                exit(1);
                break;
        }
    }
    return mode;
}


/*
 
// mem vars
 vector
 // will i want this struct in all parts?
 struct coors k v d
 decault false inf
 // how to make part A templeted
 // print nodes that are made perm
// adjlist 
 
 
// distance function
 safe <-> wild is inf
 else find dis
 int coors to doubles
 do i want them all to remain a double or just for dis calc
 
 //euclidians
 // does this take care over overflow
 double x
 double y
return sqrt( y2 + x2 )
 
 
 
 //prims
 loop
 put all into prim will never pick inf
 
 // comparator
 cares about wild <-> safe and one that doesnt.
 always calcualte the distance since will use in part c alot or depend on?
 will this cause me to go over time in part A? 
 
 // struct node
  wild or safe or boarder (char)
  coors
  visited?
 
 // will I need the adjlsit in call parts? use swap or copy or something.
 // put struct in main??
 // how will A work with C?
    copy C remianing nodes to A vector and call prims?
    do i want to a return it inorder?
 */
