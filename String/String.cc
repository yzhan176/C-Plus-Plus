//
// Created by 张炎 on 2018/10/29.
//

#include "String.hh"
//#include "String.hh"

String::String() {
    this->capacity=0;
    this->len=0;
    this->s= nullptr;
}

String::String(const char str[]) {
    this->capacity=this->stringlen(str);
    this->len=this->stringlen(str);
    this->s=new char[len];
    for(int i=0;i<len;i++){
        s[i]=str[i];
    }
}

String::String(const char str[], uint32_t mult) {
    this->capacity=(this->stringlen(str))*mult;
    //this->checkGrow((this->stringlen(str))*mult);
    this->len=(this->stringlen(str))*mult;
    this->s=new char[this->stringlen(str)*mult];
    for(int i=0;i<=mult;i++){
        for(int j=0;j<this->stringlen(str);j++){
            s[j+i*this->stringlen(str)]=str[j];
        }
    }
}

String::~String() {
    delete [] s;
}

//copy constructor
String::String(const String& orig) {
    this->len=orig.len;
    this->capacity=orig.capacity;
    this->s=new char[this->len];
    for(int i=0;i<len;i++){
        s[i]=orig.s[i];
    }
}
String& String::operator =(const String& orig) {
    String copy(orig);
    this->len=orig.len;
    this->capacity=orig.capacity;
    swap(this->s,copy.s);
    return *this;
}

char String::operator [](const uint32_t pos)const {
//    char* k=this->s;
//    for(int i=0;i<pos;i++){
//        k++;
//    }
//    return *k;
    return this->s[pos];
}
char& String::operator [](uint32_t pos) {
    return this->s[pos];
}

ostream& operator<<(ostream& s, const String& str) {
    for(int i=0;i<str.len;i++){
        s<<str.s[i]<<'\t';
    }
    return s;
}

String& String::operator +=(const char str[]){
    this->len=this->len+this->stringlen(str);
    //this->capacity=this->capacity+this->stringlen(str);
    this->checkGrow(this->capacity+this->stringlen(str));
    char* p=new char[this->capacity];
    for(int i=0;i<len-stringlen(str);i++){
        p[i]=s[i];
    }
    for(int j=len-stringlen(str);j<len;j++){
        p[j]=str[j-len+stringlen(str)];
    }
    swap(p,this->s);
    return *this;
}

String String::substring(uint32_t pos, uint32_t length) {

//    this->len=length;
//    this->capacity=length;
//    char* p=new char[length];
//    for(int i=0;i<length;i++){
//        p[i]=this->s[pos+i];
//    }
//    swap(p,this->s);
    String ans;
    ans.len=length;
    ans.capacity=length;
    ans.s=new char[length];
    for(int i=0;i<length;i++){
        ans.s[i]=this->s[pos+i];
        //cout<<1<<ans.s[i]<<endl;
    }
    return ans;
}

void String::replace(char orig,char current){
    for(int i=0;i<this->len;i++){
        if(this->s[i]==orig){
            this->s[i]=current;
        }
    }
}

uint32_t String::length()const{
    return this->len;
}

void String::insert(uint32_t pos, const String &orig) {
    this->len=this->len+orig.len;
    //this->capacity=this->capacity+orig.capacity;
    this->checkGrow(this->capacity+orig.capacity);
    char* p=new char[this->capacity];
    for(int i=0;i<pos;i++){
        p[i]=this->s[i];
    }
    for(int j=pos;j<pos+orig.len;j++){
        p[j]=orig.s[j-pos];
    }
    for(int k=pos+orig.len;k<len;k++){
        p[k]=this->s[k-orig.len];
    }
    swap(p,this->s);
}

String operator +(const String& left,const String& right){
    String ans;
    ans.len=left.len+right.len;
    ans.capacity=left.capacity+right.capacity;
    ans.s=new char[ans.len];
    for(int i=0;i<left.len;i++){
        ans.s[i]=left.s[i];
    }
    for(int j=left.len;j<ans.len;j++){
        ans.s[j]=right.s[j-left.len];
    }
    return ans;
}