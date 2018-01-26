/*
 * Nodelist.h
 *
 *  Created on: Jan 17, 2018
 *      Author: root
 */

#ifndef MODULES_UTILS_NODELIST_H_
#define MODULES_UTILS_NODELIST_H_

#include <iostream>
using namespace std;

template <class T>

class Nodelist {
public:
    Nodelist();
    Nodelist(T);
    virtual ~Nodelist();

    Nodelist *next;
    T data;

    void delete_all();
    void print();

};



#endif /* MODULES_UTILS_NODELIST_H_ */
