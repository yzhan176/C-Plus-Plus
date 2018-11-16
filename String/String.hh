//
// Created by 张炎 on 2018/10/29.
//
#include <iostream>
#include <stdint.h>
using namespace std;
#ifndef STRING_STRING_H
#define STRING_STRING_H


class String {
private:
    uint32_t capacity;
    uint32_t len;
    char* s;
    uint32_t stringlen(const char* str) {
        uint32_t count = 0;
        while (*str++ != '\0')
            count++;
        return count;
    }
    void checkGrow(uint32_t newLen){
        if(newLen>capacity){
            capacity=2*newLen;
            char* old=s;
            s=new char[capacity];
            for(int i=0;i<len;i++){
                s[i]=old[i];
            }
        }
    }
public:
    String();
    String(const char str[]);

    String(const char str[], uint32_t mult);
    ~String();

    //copy constructor
    String(const String& orig);
    String& operator =(const String& orig);
    char  operator [](const uint32_t pos)const;

char& operator [](uint32_t pos);
friend ostream& operator<<(ostream& s, const String& str);
    String& operator +=(const char str[]);
    String substring(uint32_t pos,uint32_t length);
    void replace(char orig,char current);
    uint32_t length()const;
    void insert(uint32_t pos,const String& orig);
friend String operator +(const String& left,const String& right);
};



#endif //STRING_STRING_H
