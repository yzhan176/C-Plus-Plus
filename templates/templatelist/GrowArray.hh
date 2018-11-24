//
// Created by 张炎 on 11/23/18.
//

//#ifndef TEMPLATELIST_GROWARRAY_H
//#define TEMPLATELIST_GROWARRAY_H

#pragma once

#include <iostream>
#include <cmath>
using namespace std;
template<typename T>
class GrowArray {
private:
    int used;
    int capacity;
    T* data;
    void checkGrow() {
        if(used==0){
            data=new T[capacity];
        }
        if (used<capacity){
            used++;
            return; // don't grow unless you have to
        }
        T* old = data;
        //TODO: every time the list grows, double it!!!
        data = new T[2*capacity]; // calls T::T()
        capacity=2*capacity;
        for (int i = 0; i < used; i++)
            data[i] = old[i];
        used++;
        delete [] old;
    }
public:
    GrowArray() : used(0), capacity(1), data(nullptr) {}
    GrowArray(int  initialCapacity) : used(0), capacity(initialCapacity){
        data=new T[initialCapacity];
    } //TODO: fix! {}

    //TODO: add destructor, copy constructor, operator =
    ~GrowArray(){
        delete [] data;
    }

    GrowArray(const GrowArray& orig){
        this->used=orig.used;
        this->capacity=orig.capacity;
        this->data=new T[capacity];
        for(int i=0;i<used;i++){
            this->data[i]=orig.data[i];
        }
    }

    GrowArray& operator=(const GrowArray& orig){
        GrowArray copy(orig);
        this->used=orig.used;
        this->capacity=orig.capacity;
        swap(this->data,copy.data);
        return *this;
    }

    void addEnd(const T& v) {
        checkGrow();
        data[used-1] = v;
    }

    T removeEnd() {
        used--;
        return data[used];
    }
    T operator [](int i) const {
        return data[i];
    }

    T& operator [](int i) {
        return data[i];
    }

    friend ostream& operator <<(ostream& s, const GrowArray<T>& list) {
        for (int i = 0; i < list.used; i++)
            s << list.data[i] << ' ';
        return s;
    }
};







//#endif //TEMPLATELIST_GROWARRAY_H
