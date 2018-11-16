//
// Created by 张炎 on 11/6/18.
//

//#ifndef BITMAP_COLOR_H
//#define BITMAP_COLOR_H
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cmath>
using namespace std;
#pragma once

class Color {
private:
    uint32_t rgba;
public:
    uint32_t getcolor() {
        return rgba;
    }
    Color(uint8_t r, uint8_t g, uint8_t b) {//opaque:255
        this->rgba=(r<<24)+(g<<16)+(b<<8)+255;
    }
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
        this->rgba=(r<<24)+(g<<16)+(b<<8)+alpha;
    }
};

class Bitmap{
private:
    uint32_t rows,cols;
    //uint32_t ** m;
    uint32_t *m;
public:
    Bitmap(uint32_t r,uint32_t c):rows(r),cols(c),m(new uint32_t[r]) {
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                m[i*c+j]=0;
            }
        }
    }
    ~Bitmap(){
        delete [] m;
    }

    void line(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,Color c){
        if((x1==y1)&&(x2==y2)){
            for(int i=x1;i<=x2;i++){
                this->m[i*this->cols+i]=c.getcolor();
            }
        }
        else{
            double deltax=x2-x1;
            double deltay=y2-y1;
            double deltaerr=abs((double)deltay/(double)deltax);
            double error=0.0;
            uint32_t y=y1;
            for(uint32_t x=x1;x<=x2;x++){
                error=error+deltaerr;
                if(error>=0.5){
                    y=y+1;
                    error=error-1;
                }
                this->m[x*this->cols+y]=c.getcolor();
            }
        }
    }

    double ipart(double x){
        return floor(x);
    }
    double round(double x){
        return ipart(x+0.5);
    }
    double fpart(double x){
        return x-floor(x);
    }
    double rfpart(double x){
        return 1-fpart(x);
    }
    void line1(uint32_t x0,uint32_t y0,uint32_t x1,uint32_t y1,Color c){
        bool steep=((abs((int)y1-(int)y0))>(abs((int)x1-(int)x0)));
        if(steep){
            swap(x0,y0);
            swap(x1,y1);
        }
        if(x0>x1){
            swap(x0,x1);
            swap(y0,y1);
        }
        double dx=(double)x1-(double)x0;
        double dy=(double)y1-(double)y0;
        double gradient=dy/dx;
        if(dx==0){
            gradient=1.0;
        }
        double xend=round((double)x0);
        double yend=(double)y0+gradient*(xend-(double)x0);
        double xgap=rfpart(double(x0)+0.5);
        double xpxll=xend;
        double ypxll=ipart(yend);
        if(steep){
            this->m[uint32_t (ypxll*this->cols+xpxll)]=c.getcolor();
            this->m[uint32_t ((ypxll+1)*this->cols+xpxll)]=c.getcolor();
        }
        else{
            this->m[uint32_t (xpxll*this->cols+ypxll)]=c.getcolor();
            this->m[uint32_t (xpxll*this->cols+(ypxll+1))]=c.getcolor();
        }
        double intery=yend+gradient;
        xend=round(double(x1));
        yend=double(y1)+gradient*(xend-double(x1));
        xgap=fpart(double(x1)+0.5);
        double xpx12=xend;
        double ypx12=ipart(yend);
        if(steep){
            this->m[uint32_t (ypx12*this->cols+xpx12)]=c.getcolor();
            this->m[uint32_t ((ypx12+1)*this->cols+xpx12)]=c.getcolor();
        }
        else{
            this->m[uint32_t (xpx12*this->cols+ypx12)]=c.getcolor();
            this->m[uint32_t (xpx12*this->cols+(ypx12+1))]=c.getcolor();
        }
        if(steep){
            for(int x=(int)(xpxll+1);x<(int)(xpx12);x++){
                this->m[uint32_t (ipart(intery)*this->cols+x)]=c.getcolor();
                this->m[uint32_t ((ipart(intery)+1)*this->cols+x)]=c.getcolor();
                intery=intery+gradient;
            }
        }
        else{
            for(int x=(int)(xpxll+1);x<(int)(xpx12);x++){
                this->m[uint32_t (x*this->cols+ipart(intery))]=c.getcolor();
                this->m[uint32_t (x*this->cols+ipart(intery)+1)]=c.getcolor();
                intery=intery+gradient;
            }
        }
    }

    void horizLine(uint32_t x1,uint32_t x2,uint32_t y,Color c){
        for(uint32_t i=x1;i<=x2;i++){
            this->m[i*this->cols+y]=c.getcolor();
        }
    }

    void vertLine(uint32_t x,uint32_t y1,uint32_t y2,Color c){
        for(uint32_t i=y1;i<=y2;i++){
            this->m[x*this->cols+i]=c.getcolor();
        }
    }

    void fillRect(uint32_t x,uint32_t y,uint32_t w,uint32_t h,Color c){
        for(uint32_t i=x+1;i<=x+h-1-1;i++){
            for(uint32_t j=y+1;j<=y+w-1-1;j++){
                this->m[i*this->cols+j]=c.getcolor();
            }
        }
    }

    void drawRect(uint32_t x,uint32_t y, uint32_t w,uint32_t h,Color c){
        for(uint32_t j=y;j<=y+w-1;j++){
            this->m[x*this->cols+j]=c.getcolor();
            this->m[(x+h-1)*this->cols+j]=c.getcolor();
        }
        for(uint32_t i=x;i<=x+h-1-1;i++){
            this->m[i*this->cols+y]=c.getcolor();
            this->m[i*this->cols+y+w-1]=c.getcolor();
        }
    }

    void ellipse(uint32_t x,uint32_t y,uint32_t w,uint32_t h,Color c){
        if(w>h){
            int i=-(int)h/2;
            for(i;i<=(int)h/2;i++) {
                for (int j = (int)y - (int)w / 2 + abs(i); j <= (int)y + (int)w / 2 - abs(i)-1; j++) {
                    if(abs(i)==(int)h/2){
                        this->m[(x+h/2)*this->cols+y]=c.getcolor();
                        this->m[(x-h/2)*this->cols+y]=c.getcolor();
                        break;
                    }
                    if(j>=0) {
                        this->m[((int) x + i) * (int) this->cols + j] = c.getcolor();
                    }
                }
            }
        }
//        else{
//
//        }
    }
    friend ostream& operator <<(ostream& s,const Bitmap& f);
};

ostream& operator <<(ostream& s,const Bitmap& f){
    for(uint32_t i=0;i<f.rows;i++){
        for(uint32_t j=0;j<f.cols;j++){
            //s<<f.m[i*f.cols+j]<<'\t';
            switch(f.m[i*f.cols+j]){
                case 0xFF0000FF: {
                    s << 'R' << '\t';
                    break;
                }
                case 0x00FF00FF:{
                    s<<'B'<<'\t';
                    break;
                }
                case 0x0000FFFF:{
                    s<<'G'<<'\t';
                    break;
                }
                case 0xFFFFFFFF:{
                    s<<'W'<<'\t';
                    break;
                }
                case 0x000000FF:{
                    s<<'K'<<'\t';
                    break;
                }
                case 0:{
                    s<<0<<'\t';
                    break;
                }
            }
        }
        s<<endl;
    }
    return s;
}



//#endif //BITMAP_COLOR_H
