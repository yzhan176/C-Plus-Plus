/*
	Cube
	Cylinder
	Sphere (optional)

https://en.wikipedia.org/wiki/STL_(file_format)
	
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
const double PI=3.141592654;
class Point{
private:
    double x,y,z;
public:
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }
    Point(double x,double y,double z):x(x),y(y),z(z){}
    friend ostream& operator<<(ostream& s,const Point& f){
        s<<f.x<<' '<<f.y<<' '<<f.z;
        return s;
    }
};

class Facet{
private:
    Point p1;
    Point p2;
    Point p3;
public:
    Point getP1(){
        return p1;
    }
    Point getP2(){
        return p2;
    }
    Point getP3(){
        return p3;
    }
    Facet(const Point& p1,const Point& p2,const Point& p3):p1(p1),p2(p2),p3(p3){}
    Point normal(){
        double a=(p2.getY()-p1.getY())*(p3.getZ()-p1.getZ())-(p3.getY()-p1.getY())*(p2.getZ()-p1.getZ());
        double b=(p2.getZ()-p1.getZ())*(p3.getX()-p1.getX())-(p3.getZ()-p1.getZ())*(p2.getX()-p1.getX());
        double c=(p2.getX()-p1.getX())*(p3.getY()-p1.getY())-(p3.getX()-p1.getX())*(p2.getY()-p1.getY());
        double mag=sqrt(a*a+b*b+c*c);
        return Point(a/mag,b/mag,c/mag);
    }
    friend ostream& operator<<(ostream& s,Facet& m){
        s << "facet normal " << m.normal() << '\n'
          << "\touter loop\n"
          << "\t\tvertex " << m.p1 << '\n'
          << "\t\tvertex " << m.p2 << '\n'
          << "\t\tvertex " << m.p3 << '\n'
          << "\tendloop\n"
          << "endfacet\n";
        return s;
    }
};

class shape{

};

class Cube:public shape{
private:
    double size;
    Facet arr[12]={
            Facet(Point(0,0,0),Point(size,0,0),Point(size,0,size)),
            Facet(Point(0,0,0),Point(0,0,size),Point(size,0,size)),

            Facet(Point(size,0,0),Point(size,size,0),Point(size,0,size)),
            Facet(Point(size,size,0),Point(size,size,size),Point(size,0,size)),

            Facet(Point(size,size,0),Point(0,size,0),Point(size,size,size)),
            Facet(Point(0,size,0),Point(0,size,size),Point(size,size,size)),

            Facet(Point(0,0,0),Point(0,size,0),Point(0,0,size)),
            Facet(Point(0,0,size),Point(0,size,size),Point(0,size,0)),

            Facet(Point(0,0,0),Point(size,0,0),Point(0,size,0)),
            Facet(Point(0,size,0),Point(size,size,0),Point(size,0,0)),

            Facet(Point(0,0,size),Point(size,0,size),Point(0,size,size)),
            Facet(Point(0,size,size),Point(size,size,size),Point(size,0,size))
    };
    int len=12;
public:
    int getLen(){
        return len;
    }
    Cube(double size):size(size){
//        Facet arr[]={
//                Facet(Point(0,0,0),Point(size,0,0),Point(size,0,size)),
//                Facet(Point(0,0,0),Point(0,0,size),Point(size,0,size)),
//
//                Facet(Point(size,0,0),Point(size,size,0),Point(size,0,size)),
//                Facet(Point(size,size,0),Point(size,size,size),Point(size,0,size)),
//
//                Facet(Point(size,size,0),Point(0,size,0),Point(size,size,size)),
//                Facet(Point(0,size,0),Point(0,size,size),Point(size,size,size)),
//
//                Facet(Point(0,0,0),Point(0,size,0),Point(0,0,size)),
//                Facet(Point(0,0,size),Point(0,size,size),Point(0,size,0)),
//
//                Facet(Point(0,0,0),Point(size,0,0),Point(0,size,0)),
//                Facet(Point(0,size,0),Point(size,0,size),Point(size,0,0)),
//
//                Facet(Point(0,0,size),Point(size,0,size),Point(0,size,size)),
//                Facet(Point(0,size,size),Point(size,size,size),Point(size,0,size)),
//        };

    }
    double volume(){
        return size*size*size;
    }
    void translate(double x,double y,double z){
        Facet arr1[]={
                Facet(Point(0+x,0+y,0+z),Point(size+x,0+y,0+z),Point(size+x,0+y,size+z)),
                Facet(Point(0+x,0+y,0+z),Point(0+x,0+y,size+z),Point(size+x,0+y,size+z)),

                Facet(Point(size+x,0+y,0+z),Point(size+x,size+y,0+z),Point(size+x,0+y,size+z)),
                Facet(Point(size+x,size+y,0+z),Point(size+x,size+y,size+z),Point(size+x,0+y,size+z)),

                Facet(Point(size+x,size+y,0+z),Point(0+x,size+y,0+z),Point(size+x,size+y,size+z)),
                Facet(Point(0+x,size+y,0+z),Point(0+x,size+y,size+z),Point(size+x,size+y,size+z)),

                Facet(Point(0+x,0+y,0+z),Point(0+x,size+y,0+z),Point(0+x,0+y,size+z)),
                Facet(Point(0+x,0+y,size+z),Point(0+x,size+y,size+z),Point(0+x,size+y,0+z)),

                Facet(Point(0+x,0+y,0+z),Point(size+x,0+y,0+z),Point(0+x,size+y,0+z)),
                Facet(Point(0+x,size+y,0+z),Point(size+x,size+y,0+z),Point(size+x,0+y,0+z)),

                Facet(Point(0+x,0+y,size+z),Point(size+x,0+y,size+z),Point(0+x,size+y,size+z)),
                Facet(Point(0+x,size+y,size+z),Point(size+x,size+y,size+z),Point(size+x,0+y,size+z))
        };
        for(int i=0;i<12;i++){
            arr[i]=arr1[i];
        }
    }
    void write(const string& name){
        ofstream fout(name);
        fout<<"solid OpenSCAD_Model"<<endl;
        for(int i=0;i<12;i++){
            fout<<arr[i];
        }
        fout<<"ensolid OpenSCAD_Model"<<endl;
        fout.close();
    }
    friend ostream& operator<<(ostream& s,Cube& f){
        for(int i=0;i<f.len;i++){
            s << "facet normal " << f.arr[i].normal() << '\n'
              << "\touter loop\n"
              << "\t\tvertex " << f.arr[i].getP1() << '\n'
              << "\t\tvertex " << f.arr[i].getP2() << '\n'
              << "\t\tvertex " << f.arr[i].getP3() << '\n'
              << "\tendloop\n"
              << "endfacet\n";
        }
        return s;
    }
};

class Cylinder: public shape{
private:
    double r,h;
    Facet arr[20]={
            Facet(Point(r,0,0),Point(r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0)),
            Facet(Point(-r,0,0),Point(-r*sin(30*PI/180),r*cos(30*PI/180),0),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),0)),
            Facet(Point(-r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0)),
            Facet(Point(-r*sin(30*PI/180),r*cos(30*PI/180),0),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0)),

            Facet(Point(r,0,h),Point(r*sin(30*PI/180),r*cos(30*PI/180),h),Point(r*sin(30*PI/180),-r*cos(30*PI/180),h)),
            Facet(Point(-r,0,h),Point(-r*sin(30*PI/180),r*cos(30*PI/180),h),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),h)),
            Facet(Point(-r*sin(30*PI/180),r*cos(30*PI/180),h),Point(r*sin(30*PI/180),r*cos(30*PI/180),h),Point(r*sin(30*PI/180),-r*cos(30*PI/180),h)),
            Facet(Point(-r*sin(30*PI/180),r*cos(30*PI/180),h),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),h),Point(r*sin(30*PI/180),-r*cos(30*PI/180),h)),

            Facet(Point(r,0,0),Point(r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r,0,h)),
            Facet(Point(r,0,h),Point(r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r*sin(30*PI/180),r*cos(30*PI/180),h)),

            Facet(Point(r,0,0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(r,0,h)),
            Facet(Point(r,0,h),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),h)),

            Facet(Point(-r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r*sin(30*PI/180),r*cos(30*PI/180),0),Point(-r*sin(30*PI/180),r*cos(30*PI/180),h)),
            Facet(Point(-r*sin(30*PI/180),r*cos(30*PI/180),h),Point(r*sin(30*PI/180),r*cos(30*PI/180),0),Point(r*sin(30*PI/180),r*cos(30*PI/180),h)),

            Facet(Point(-r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),h)),
            Facet(Point(-r*sin(30*PI/180),-r*cos(30*PI/180),h),Point(r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(r*sin(30*PI/180),-r*cos(30*PI/180),h)),

            Facet(Point(-r,0,0),Point(-r*sin(30*PI/180),r*cos(30*PI/180),0),Point(-r,0,h)),
            Facet(Point(-r,0,h),Point(-r*sin(30*PI/180),r*cos(30*PI/180),0),Point(-r*sin(30*PI/180),r*cos(30*PI/180),h)),

            Facet(Point(-r,0,0),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(-r,0,h)),
            Facet(Point(-r,0,h),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),0),Point(-r*sin(30*PI/180),-r*cos(30*PI/180),h))
    };
    int len=20;
public:
    int getLen(){
        return len;
    }
    Cylinder(double r,double h):r(r),h(h){}
    double volume(){
        return PI*r*r*h;
    }
    friend ostream& operator<<(ostream& s,Cylinder& f){
        for(int i=0;i<f.len;i++){
            s << "facet normal " << f.arr[i].normal() << '\n'
              << "\touter loop\n"
              << "\t\tvertex " << f.arr[i].getP1() << '\n'
              << "\t\tvertex " << f.arr[i].getP2() << '\n'
              << "\t\tvertex " << f.arr[i].getP3() << '\n'
              << "\tendloop\n"
              << "endfacet\n";
        }
        return s;
    }
};

class Design{
private:
    vector<Cube*> cubes;
    vector<Cylinder*> cylinders;
public:
    Design(){}
    void add(Cube& c){
        cubes.push_back(&c);
    }
    void add(Cylinder& cyl){
        cylinders.push_back(&cyl);
    }
    void write(const string& name){
        ofstream fout(name);
        fout<<"solid OpenSCAD_Model"<<endl;
        for(int i=cubes.size()-1;i>=0;i--){
                fout<<*cubes[i];
        }
        for(int j=cylinders.size()-1;j>=0;j--){
            fout<<*cylinders[j];
        }
        fout<<"ensolid OpenSCAD_Model"<<endl;
        fout.close();
    }
};

int main() {
    Design d;
    double s = 10;
    Cube c(s);

    double x=1;
    double y=2;
    double z=3;

    c.translate(x,y,z);
    // rotate??
    cout << c.volume() << '\n';
    c.write("out.stl"); // how to get all my shapes into the same file
    d.add(c);
    double r = 10, height  = 20;
    Cylinder cyl(r, height);
    d.add(cyl);
    d.write("test.stl");
}
