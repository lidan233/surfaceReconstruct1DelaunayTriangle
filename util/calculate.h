//
// Created by 李源 on 2019-11-15.
//

#ifndef LIDANDELAUNAY_CALCULATE_H
#define LIDANDELAUNAY_CALCULATE_H

#include "edge.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <sstream>
#include <iomanip>

typedef double ll;
inline bool ge(const ll& a, const ll& b) { return a >= b; }
inline bool le(const ll& a, const ll& b) { return a <= b; }
inline bool eq(const ll& a, const ll& b) { return a == b; }
inline bool gt(const ll& a, const ll& b) { return a > b; }
inline bool lt(const ll& a, const ll& b) { return a < b; }
inline int sgn(const ll& a) { return a >= 0 ? a ? 1 : 0 : -1; }

//
//inline double Det3x3(double * col_0, double * col_1,double * col_2)
//{
//    Eigen::Matrix3d a ;
//    a<< col_0[0],col_1[0],col_2[0] ,
//        col_0[1],col_1[1],col_2[1] ,
//        col_0[2],col_1[2],col_2[2] ;
//
//   return a.determinant()>0;
//
//}

//inline double Det4x4(double* col_0, double* col_1, double* col_2, double* col_3)
//{
//    Eigen::Matrix4d a;
//    a<<     col_0[0],col_1[0],col_2[0],col_3[0] ,
//            col_0[1],col_1[1],col_2[1],col_3[1],
//            col_0[2],col_1[2],col_2[2],col_3[2],
//            col_0[3],col_1[3],col_2[3],col_3[3];
//    return a.determinant() ;
//}
//inline double Det4x4(double* col_0, double* col_1, double* col_2, double* col_3)
//{
//    // Gets the determinant of a 4x4 matrix, where the arguments are 4-long column vectors
//
//    // Name all the objects in the matrix for my convenience
//    double a = col_0[0];
//    double b = col_1[0];
//    double c = col_2[0];
//    double d = col_3[0];
//    double e = col_0[1];
//    double f = col_1[1];
//    double g = col_2[1];
//    double h = col_3[1];
//    double i = col_0[2];
//    double j = col_1[2];
//    double k = col_2[2];
//    double l = col_3[2];
//    double m = col_0[3];
//    double n = col_1[3];
//    double o = col_2[3];
//    double p = col_3[3];
//
//    // Compute 3x3 determinants
//    double adet = a * ((f * k * p) - (f * l * o) - (g * j * p) + (g * l * n) + (h * j * o) - (h * k * n));
//    double bdet = b * ((e * k * p) - (e * l * o) - (g * i * p) + (g * l * m) + (h * i * o) - (h * k * m));
//    double cdet = c * ((e * j * p) - (e * l * n) - (f * i * p) + (f * l * m) + (h * i * n) - (h * j * m));
//    double ddet = d * ((e * j * o) - (e * k * n) - (f * i * o) + (f * k * m) + (g * i * n) - (g * j * m));
//
//    // Return their alternating sum
//    double det = adet - bdet + cdet - ddet;
//    return det;
//}

inline template <class T>
        T det3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3) {
return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) +
a3 * (b1 * c2 - c1 * b2);
}

//the last vertex is in the circle of the first 3 node
inline bool inCircle(Vertex *a, Vertex*b,Vertex* c,Vertex*d)
{
//    double m[4][4] = {	{ a->x(), b->x(), c->x(), d->x() },
//                          { a->y(), b->y(), c->y(), d->y() },
//                          { a->lengthsquared(), b->lengthsquared(), c->lengthsquared(), d->lengthsquared() },
//                          { 1, 1, 1, 1 } };

//    double m1[3][3] = {	{ a->x()-d->x(), b->x()-d->x(), c->x()-d->x()  },
//                           { a->y()-d->y() , b->y()-d->y() , c->y()-d->y() },
//                           { a->lengthsquared()-d->lengthsquared(), b->lengthsquared()-d->lengthsquared(), c->lengthsquared()-d->lengthsquared() }};

//    return Det3x3(m1[0],m1[1],m1[2])!=0;

    __int128 det = -det3<__int128>(b->x(), b->y(), b->lengthsquared(), c->x(), c->y(),
                                   c->lengthsquared(), d->x(), d->y(), d->lengthsquared());
    det += det3<__int128>(a->x(), a->y(), a->lengthsquared(), c->x(), c->y(), c->lengthsquared(), d->x(),
                          d->y(), d->lengthsquared());
    det -= det3<__int128>(a->x(), a->y(), a->lengthsquared(), b->x() ,b->y(), b->lengthsquared(), d->x(),
                          d->y(), d->lengthsquared());
    det += det3<__int128>(a->x(), a->y(), a->lengthsquared(), b->x(), b->y(), b->lengthsquared(), c->x(),
                          c->y(), c->lengthsquared());
    return det > 0;

//    return Det4x4(m[0],m[1],m[2],m[3])>0;

}
inline double Det3x3(double* col_0, double* col_1, double* col_2)
{
    // Gets the determinant of a 3x3 matrix, where the arguments ae 3-long column vectors

    // Names all the objects in the matrix for my convenience
    double a = col_0[0];
    double b = col_1[0];
    double c = col_2[0];
    double d = col_0[1];
    double e = col_1[1];
    double f = col_2[1];
    double g = col_0[2];
    double h = col_1[2];
    double i = col_2[2];

    // Return the alternating sum of the 2x2 determinants of the coproducts
    double det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    return det;
}



//判定abc是否是逆时针 也就是三阶行列式是否大于0
inline bool CCW(Vertex* a, Vertex* b , Vertex*c )
{
//   Eigen::Matrix3d matrix ;
//   matrix<< a->x(),b->x(),c->x() ,
//            a->y(),b->y(),c->y(),
//            1,1,1;
//   return matrix.determinant()>0 ;
    float a_x = a->x();
    float a_y = a->y();
    float b_x = b->x();
    float b_y = b->y();
    float c_x = c->x();
    float c_y = c->y();
    double m[3][3] = { { a_x, b_x, c_x }, { a_y, b_y, c_y }, { 1, 1, 1 } };
    return Det3x3(m[0], m[1], m[2]) > 0;
}



//判定是否是逆时针 向上就不是
inline bool leftOf(Vertex* v, Edge* e)
{
    return gt(v->cross(e->org(), e->Des()), 0);
}

//判定是否是逆时针  向上就不是
inline bool rightOf(Vertex* v , Edge* e )
{
    return lt(v->cross(e->org(), e->Des()), 0) ;
}

inline string ltrim(string data) {
    string::iterator p = find_if(data.begin(), data.end(), not1(ptr_fun<int, int>(isspace)));
    data.erase(data.begin(), p);
    return data;
}

inline string rtrim(string data)
{
    string::reverse_iterator p = find_if(data.rbegin(),data.rend(),not1(ptr_fun<int,int>(isspace))) ;
    data.erase(p.base(),data.end()) ;
    return data ;
}

inline string trim(string data)
{
    return ltrim(rtrim(data)) ;
}

inline vector<string> getstring(string data,bool haveone )
{
    vector<string> result ;
    data = trim(data) ;
    stringstream ss ;
    ss<<data.c_str()[0] ;

    for(int i = 1; i<data.size();i++)
    {
        while(data.c_str()[i]==' '||data.c_str()[i]=='\t'){i++ ;}
        if(data.c_str()[i-1]==' '||data.c_str()[i-1]=='\t')
        {
            string temp = ss.str() ;
            result.push_back(temp) ;
            ss.str("");
        }
        ss<<data.c_str()[i] ;
    }
    result.push_back(ss.str()) ;
    if(haveone) result.erase(result.begin()) ;
    return result ;
}


//base is always from the right to the left
inline bool isValid(Edge* e, Edge*  base)
{
    return rightOf(e->Des(),base) ;
}
inline Eigen::Vector2f Circumcenter(Vertex *a ,Vertex*b,Vertex* c)
{
    float d = 2 * (a->x() * (b->y() - c->y()) + b->x() * (c->y() - a->y()) + c->x() * (a->y() - b->y()));

    float x = (float)(a->lengthsquared() * (b->y() - c->y()) + b->lengthsquared() * (c->y() - a->y()) + c->lengthsquared() * (a->y() - b->y())) / d;
    float y = (float)(a->lengthsquared() * (c->x() - b->x()) + b->lengthsquared() * (a->x() - c->x()) + c->lengthsquared() * (b->x() - a->x())) / d;

    return Eigen::Vector2f(x, y);
}

// insert a into in
inline void splice(Edge *a ,Edge *b)
{
    Edge * alpha = a->Onext()->Rot() ;
    Edge* beta = b->Onext()->Rot();

    Edge* t1 = b->Onext() ;
    Edge* t2 = a->Onext() ;
    Edge* t3 = alpha->Onext() ;
    Edge* t4 = beta->Onext() ;

    a->setNext(t1) ;
    b->setNext(t2) ;
    alpha->setNext(t4) ;
    beta->setNext(t3) ;
}

inline double round(double src,int precise)
{
    stringstream ss ;
    ss<<std::fixed<< setprecision(precise) << src;
    ss>>src ;
    return src ;
}


inline void add(vector<Vertex*> &v,Edge*& e,vector<Edge*> & edges)
{
    Edge* curr = e;
    do{
        curr->used = true ;
        v.push_back(curr->org()) ;
        edges.push_back(curr->Sym()) ;
        curr = curr->Lnext() ;
    }while(curr!=e) ;
}
#endif //LIDANDELAUNAY_CALCULATE_H
