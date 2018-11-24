//
// Created by 张炎 on 11/23/18.
//

//#ifndef TESTVEC3D_VEC3D_H
//#define TESTVEC3D_VEC3D_H
#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Vec3d{
private:
    T x,y,z;
public:
    Vec3d(T x,T y,T z):x(x),y(y),z(z){}
    friend Vec3d operator +(Vec3d left, Vec3d right){
        return Vec3d(left.x+right.x,left.y+right.y,left.z+right.z);
    }
    friend ostream& operator<<(ostream& s,Vec3d f){
        s<<'('<<f.x<<','<<f.y<<','<<f.z<<')'<<' ';
        return s;
    }
};
//#endif //TESTVEC3D_VEC3D_H
