//
// Created by 李源 on 2020-01-01.
//

#ifndef LIDANDELAUNAY_VEC_H
#define LIDANDELAUNAY_VEC_H


#include <math.h>
#include <iostream>
#include <assert.h>
#include <vector>



template<size_t DimCols ,size_t DimRows,typename T> class mat ;

template<size_t DIM,typename T> struct vec
{
private:
    union{
        T data_[DIM] ;
    };
public:
    vec(){
        for(size_t i = DIM ;i--;data_[i]=T() ) ;
    }
    T& operator[](const size_t i ){ assert(i<DIM); return data_[i] ;}
    const T& operator[](const size_t i) const{assert (i<DIM); return data_[i] ;}
};

template<size_t DIM,typename T> T& operator*(const vec<DIM,T>& lhs,const vec<DIM,T>& rhs)
{
    T ret = T() ;
    for(size_t i = DIM;i-- ;ret+=lhs[i]*rhs[i]) ;
    return ret ;
}

template<size_t DIM,typename T> vec<DIM,T> operator+(vec<DIM,T> lhs ,const vec<DIM,T> rhs)
{
    vec<DIM,T> ret;
    for(size_t i=DIM;i--; ret[i] = lhs[i]+rhs[i]) ;
    return ret ;

//    for(size_t i=DIM;i--; lhs[i]+=rhs[i]) ;
//    return lhs ;
}
template<size_t DIM,typename T,typename U> vec<DIM,T> operator+(vec<DIM,T> lhs ,const vec<DIM,U> rhs)
{
    vec<DIM,T> ret;
    for(size_t i=DIM;i--; ret[i] = lhs[i]+rhs[i]) ;
    return ret ;

}

template<size_t DIM,typename T> vec<DIM,T> operator-(vec<DIM,T> lhs ,const vec<DIM,T> rhs)
{

    vec<DIM,T> ret;
    for(size_t i=DIM;i--; ret[i] = lhs[i]-rhs[i]) ;
    return ret ;
}


template<size_t LEN,size_t DIM ,typename T> vec<LEN,T> embed(const vec<DIM,T> &v, T fill=1)
{
    vec<LEN,T> ret;
    for (size_t i=LEN; i--; ret[i]=(i<DIM?v[i]:fill));
    return ret;
}

template<size_t LEN,size_t DIM,typename T> vec<LEN,T> proj(const vec<DIM,T>& v)
{
    vec<LEN,T> ret;
    for(size_t i=LEN;i--;ret[i] = v[i] ) ;
    return ret ;
}



template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, vec<DIM,T>& v) {
    for(unsigned int i=0; i<DIM; i++) {
        out << v[i] << " " ;
    }
    return out ;
}





/////////////////////////////
template<typename T> struct vec<2,T>{

    union{
        struct{ T x,y ;} ;
        T data_[2] ;
    };

    vec():x(T()),y(T()){}
    vec(T X,T Y):x(X),y(Y) {}
    template <class U> vec<2,T>(const vec<2,U>& v) ;
    vec<2,T>(const vec<2,T>& v):
            x(T()) ,
            y(T())
    {
        *this = v ;
    }

    vec<2,T>& operator =(const vec<2,T> &v)
    {
        if(this!=&v)
        {
            x = v.x ;
            y = v.y ;
        }
        return *this ;
    }
    T& operator[](const size_t i){ assert(i<2) ;return i<=0? x:y ;}
    const T& operator[](const size_t i) const{ assert(i<2); return i<=0?x:y ;}

};


////////////////////////////
template<typename T> struct vec<3,T>
{
    union{
        struct{T x,y,z;} ;
        T data_[3] ;
    };



    vec():x(T()),y(T()),z(T()){}
    vec(T X,T Y,T Z):x(X),y(Y),z(Z) {}


    template <class U> vec<3,T>(const vec<3,U> &v);


    vec<3,T>(const vec<3,T>& v):
            x(T()) ,
            y(T()),
            z(T())
    {
        *this = v ;
    }

    vec<3,T>& operator =(const vec<3,T> &v)
    {
        if(this!=&v)
        {
            x = v.x ;
            y = v.y ;
            z = v.z ;
        }
        return *this ;
    }


    T& operator[](const size_t i)       { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    const T& operator[](const size_t i) const { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    T norm() { return sqrt(x*x+y*y+z*z); }
    vec<3,T> & normalize(T l=1) { *this = (*this)*(l/norm()); return *this; }
};


template <typename T> vec<3,T> cross(vec<3,T> v1, vec<3,T> v2) {
    return vec<3,T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}



/////////////////////////
template<typename T> struct vec<4,T>
{
    union{
        struct{T x,y,z,k;} ;
        T data_[4] ;
    };



    vec():x(T()),y(T()),z(T()),k(T()){}
    vec(T X,T Y,T Z,T K):x(X),y(Y),z(Z),k(K) {}


    template <class U> vec<4,T>(const vec<4,U> &v);


    vec<4,T>(const vec<4,T>& v):
            x(T()) ,
            y(T()),
            z(T()),
            k(T())
    {
        *this = v ;
    }

    vec<4,T>& operator =(const vec<4,T> &v)
    {
        if(this!=&v)
        {
            x = v.x ;
            y = v.y ;
            z = v.z ;
            k = v.k ;
        }
        return *this ;
    }

    bool operator ==(const vec<4,T> &v) const
    {
        if(this!=&v)
        {
            if((*this-v).norm()<1)
            {
                return true ;
            }else{
                return false ;
            }
        }
        return true ;
    }


    T& operator[](const size_t i)       { assert(i<4); return i<=0 ? x : (1==i ? y :(i==2?z:k)) ; }
    const T& operator[](const size_t i) const { assert(i<4); return i<=0 ? x : (1==i ? y :(i==2?z:k)) ; }
    T norm() { return sqrt(x*x+y*y+z*z+k*k); }
    vec<4,T> & normalize(T l=1) { *this = (*this)*(l/norm()); return *this; }
};




////////////////////////
template<size_t DIM,typename T,typename  U> vec<DIM,T> operator*(vec<DIM,T> lhs ,const U& rhs )
{
    for(size_t i=DIM;i--;lhs[i]*=rhs) ;
    return lhs ;
}

template<size_t DIM,typename T,typename U> vec<DIM,T> operator/(vec<DIM,T> lhs,const U& rhs)
{
    for(size_t i=DIM;i--;lhs[i]/=rhs) ;
    return lhs ;
}


/////////////////

//对模版类中的模版函数进行定义 给定一个不同的构造函数的定义
template<> template<> vec<3,int>::vec(const vec<3,float>& v) ;
template<> template<> vec<3,float>::vec(const vec<3,int>& v) ;


////////////////////////////
//我太喜欢这个操作了 只需要定义XX<1,Y>里面放一个XX的baseLine 就可以支撑所有的递归操作 也就是要在你的代码中的递归中投放DIM
// 但是这种操作会让行列式的计算变得低效
template<size_t DIM,typename T> struct dt{
    static T det(const mat<DIM,DIM,T>& src)
    {
        T ret = 0 ;
        for(size_t i =DIM;i--;ret += src[0][i]*src.cofactor(0,i)) ;
        return ret ;
    }
};


template<typename T> struct dt<1,T>
{
    static T det(const mat<1,1,T>& src) {
        return src[0][0];
    }
};
///////////////

typedef vec<2,  float> Vec2f;
typedef vec<2,  int>   Vec2i;
typedef vec<3,  float> Vec3f;
typedef vec<3,  int>   Vec3i;
typedef vec<4,  float> Vec4f;

#endif //LIDANDELAUNAY_VEC_H
