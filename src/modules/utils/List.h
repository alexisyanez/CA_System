/*
 * List.h
 *
 *  Created on: Jan 17, 2018
 *      Author: root
 */

#ifndef MODULES_UTILS_LIST_H_
#define MODULES_UTILS_LIST_H_

#include "Nodelist.h"

using namespace std;

template <class T>

class List
{
    public:
        List();
        ~List();

        void add_head(T);
        void add_end(T);
        void add_sort(T);
        void concat(List);
        void del_all();
        void del_by_data(T);
        void del_by_position(int);
        void fill_by_user(int);
        void fill_random(int);
        void intersection(List);
        void invert();
        void print();
        void search(T);
        void sort();

    private:
        Nodelist<T> *m_head;
        int m_num_nodes;
};



#endif /* MODULES_UTILS_LIST_H_ */
