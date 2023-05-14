#ifndef FILM
#define FILM
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>

#include "../inc/quick_sort..hh"
#include "../inc/merge_sort.hh"
#include "../inc/intro.hh"
#include "../inc/binary_search.hh"

 struct Film{
    float rating;
    int id;
    int votes;
    std::string title;
    bool operator <(Film compare){return (rating < compare.rating);};
    bool operator >(Film compare){return (rating > compare.rating);};
    bool operator <=(Film compare){return (rating <= compare.rating);}; 
   //bool operator <(int compare){return (id < compare);};
    //bool operator >(int compare){return (id > compare);};
    //bool operator ==(int compare){return (id == compare);};

};

int binar_search(Film arr[],int element,int l, int r);

#endif