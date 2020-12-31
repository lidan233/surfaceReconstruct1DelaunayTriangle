//
// Created by 李源 on 2019-11-16.
//


#include "Delaunay.h"


//Generate a random number between 0 and `choices' - 1.
 unsigned long Delaunay::randomnation(unsigned int choices)
{
    unsigned long randomseed = (randomseed * 1366l + 150889l) % 714025l;
    return randomseed / (714025l / choices + 1);
}

//void Delaunay::shuttleVertex(VertexList vl,int begin ,int end)
//{
//
//
//    Vertex* temp ;
//    if(end==begin)
//    {
//        return ;
//    }
//
//    if(end-begin==1)
//    {
//        if((vl[begin]->x()>vl[end]->x())||
//                (vl[begin]->x()==vl[end]->x() && vl[begin]->y()>vl[end]->y()))
//        {
//            temp = vl[begin] ;
//            vl[begin] = vl[end] ;
//            vl[end] = temp ;
//        }
//        return ;
//    }
//
//    int left = begin ;
//    int right = end ;
//    int midindex = (int) randomnation((unsigned int)(end-begin))+begin ;
//    double mid_x = vl[midindex]->x() ;
//    double mid_y = vl[midindex]->y() ;
//
//
//    left = begin-1 ;
//    right = end +1 ;
//    while(left<right)
//    {
//        do{
//            left++ ;
//        }while((left <= right)&&(vl[left]->x()<mid_x||(vl[left]->x()==mid_x && vl[left]->y()<mid_y))) ;
//
//        do{
//            right-- ;
//        }while((left<=right)&&(vl[right]->x()>mid_x||(vl[right]->x()==mid_x && vl[right]->y()>mid_y))) ;
//
//        if(left<right)
//        {
//            temp = vl[left] ;
//            vl[left] = vl[right] ;
//            vl[right] = temp ;
//        }
//
//
//    }
//
//    if(left>begin+1)
//    {
//        shuttleVertex(vl,begin,left-1) ;
//    }
//
//    if(right<end-1)
//    {
//        shuttleVertex(vl,midindex+1,end) ;
//    }
//
//}

void Delaunay::generateRandomVertexs(int n)
{
    srand(time(NULL)) ;//C++11 提供更好的随机数生成机制
    std::vector<Vertex*> buffer ;
    for(int i = 0; i < n;i++)
    {
        Vertex* temp = new Vertex(rand()%1024,rand()%1024)  ;
        buffer.push_back(temp ) ;
    }

//    shuttleVertex(buffer,0,n-1) ;
    std::sort(buffer.begin(),buffer.end(),Vertex::compare) ;
    buffer.erase(std::unique(buffer.begin(), buffer.end()), buffer.end());
    for (int i = 0; i < buffer.size(); i++)
    {
        vertexs_.push_back(new Vertex(buffer[i]->x(), buffer[i]->y()));
    }
}

Vertex* Delaunay::getVertex(int n)
{
    if(n<vertexs_.size())
    {
        return vertexs_[n] ;
    }

    return NULL ;
}

Delaunay::Delaunay(int n)
{

    this->edges = QuadList() ;
    generateRandomVertexs(n);
    srand(time(NULL)) ;
    this->randomseed = rand() ;
}
Delaunay::Delaunay(string path)
{
    string temp ;
    ifstream file(path) ;

    std::vector<Vec4f> buffer ;

    double temp1 = 0.0 ;
    double temp2 = 0.0 ;
    double temp3 = 0.0 ;
    int i = 1 ;


    while(getline(file,temp))
    {

        vector<string> temp_s = getstring(temp,false) ;
        temp1 = round((float)std::atof(temp_s[0].c_str()),2);
        temp2 = round((float)std::atof(temp_s[1].c_str()),2);
        temp3 = round((float)std::atof(temp_s[2].c_str()),2);


        Vec4f xyzk ;
        xyzk[0] = temp1 ;
        xyzk[1] = temp2 ;
        xyzk[2] = temp3 ;
        xyzk[3] = i++ ;


        buffer.push_back(xyzk) ;
    }

//    shuttleVertex(buffer,0,buffer.size()-1) ;
    std::sort(buffer.begin(),buffer.end(),[](const Vec4f& a, const Vec4f& b) {
        return lt(a[0], b[0]) || (eq(a[0], b[0]) && lt(a[1], b[1]));
    }) ;
    for(int i = 0; i< buffer.size();i++)
    {
        cout<<buffer[i][3]<<endl ;
        cout<<buffer[i][0]<<" "<<buffer[i][1]<<endl ;
    }

    buffer.erase(std::unique(buffer.begin(),buffer.end()),buffer.end()) ;


    for(int i = 0; i< buffer.size();i++)
    {
        Vertex* temp = new Vertex(buffer[i][0],buffer[i][1]) ;
        temp->setz(buffer[i][2]) ;
        temp->setallIndex(buffer[i][3]) ;
        vertexs_.push_back(new Vertex(temp)) ;
    }
    srand(time(NULL)) ;
    this->randomseed = rand() ;

}

VertexPartition Delaunay::partitionVertex(const VertexList & vl)
{
    int median = ceil(vl.size()/2.0 ) ;

    VertexList left(vl.begin(),vl.begin()+median) ;
    VertexList right(vl.begin()+median ,vl.end()) ;

    return VertexPartition(left,right) ;
}

Edge* Delaunay::MakeEdgeBetween(int a, int b, const VertexList& points)
{
    Edge* e = Edge::MakeEdge(edges,points[a],points[b]) ;
    cout<<" we connect "<<points[a]->getallIndex()<<" "<<points[b]->getallIndex() <<endl ;
    return e ;
}

Edge* Delaunay::MakeEdge(Vertex* a,Vertex* b)
{
    Edge* e= Edge::MakeEdge(edges,a,b) ;
//    cout<<e->org()->x()<<e->Des()->x() <<endl;
    cout<<" we connect "<<a->getallIndex()<<" "<<b->getallIndex() <<endl ;
    return e ;
}

Edge* Delaunay::Connect(Edge* a,Edge* b)
{
    Edge* e = MakeEdge(a->Des(),b->org()) ;

    splice(e,a->Lnext()) ;
    splice(e->Sym(),b) ;


    return e ;
}

//std::remove and std::erase
void Delaunay::Kill(Edge* e)
{
    splice(e,e->Oprev());
    splice(e->Sym(),e->Sym()->Oprev()) ;

    cout<<" we delete "<<e->org()->getallIndex()<<" "<<e->Des()->getallIndex()<<endl ;
    QuadEdge* raw = (QuadEdge* )(e-(e->index())) ;
    edges.erase(std::remove(edges.begin(), edges.end(),raw)) ;
    delete raw ;
}

EdgePartition  Delaunay::beginTriangulate(const VertexList& vertexs )
{

    if(vertexs.size()==2)
    {
        return ProcessVertexs2(vertexs) ;
    }
    if(vertexs.size()==3)
    {
        return ProcessVertexs3(vertexs) ;
    }

    VertexPartition LR =partitionVertex(vertexs) ;
    EdgePartition left = beginTriangulate(std::get<0>(LR)) ;
    EdgePartition right = beginTriangulate(std::get<1>(LR)) ;

    //you know the inner  in left the left is cw but the right is ccw
    // we define ccw is outer and cw is inner
    //so the inner has the same top pointer
    Edge* left_outer = std::get<0>(left) ;
    Edge* left_inner = std::get<1>(left);

    Edge* right_inner = std::get<0>(right) ;
    Edge* right_outer = std::get<1>(right) ;

    //we want remove outer and make the gap be inner

    Edge* basel = findCommandTangent(left_inner,right_inner) ;

    // if the left is 2 vertexs
    if(*(left_inner->org())==*(left_outer->org())) {
        left_outer= basel->Sym() ;
    }
    if(*(right_inner->org())==*(right_outer->org()))
    {
        right_outer = basel ;
    }

    Mergehull(basel) ;
    return  EdgePartition(left_outer,right_outer) ;
}


Edge* Delaunay::findCommandTangent(Edge*& left,Edge*& right)
{
    // this left and right is inner ;
    while(true)
    {
        if(leftOf(right->org(),left))
        {
            left = left->Lnext() ;

        }else if(rightOf(left->org(),right))
        {
            right = right->Rprev() ;
        } else{
            break ;
        }
    }

    cout<<"connect base edge" ;
    Edge* newEdge = Connect(right->Sym(),left);
    cout<<endl ;
    return newEdge ;

}



EdgePartition  Delaunay::ProcessVertexs2(const VertexList& vertexs)
{
    cout<<"add line  "<<endl ;
    Vertex* a= vertexs[0] ;
    Vertex* b = vertexs[1] ;
    Edge * result = MakeEdge(a,b) ;
    cout<<"end"<<endl ;
    return EdgePartition(result,result->Sym());
}

EdgePartition  Delaunay::ProcessVertexs3(const VertexList& vertexs)
{
    cout<<"add triangle  "<<endl ;
    Vertex* a1= vertexs[0] ;
    Vertex* b1 = vertexs[1] ;
    Vertex* c1 = vertexs[2] ;

    Edge* a = MakeEdge(a1,b1) ;
    Edge* b = MakeEdge(b1,c1) ;

    splice(a->Sym(),b) ;

    if(CCW(a1,b1,c1) )
    {

        Edge* c = Connect(b,a) ;
        return EdgePartition(a,b->Sym()) ;
    }else if(CCW(a1,c1,b1))
    {
        Edge* c = Connect(b,a) ;
        return EdgePartition(c->Sym(),c) ;
    }

    cout<<" triangle end "<<endl ;
    return EdgePartition(a,b->Sym()) ;
}

Edge* Delaunay::left_Candidate(Edge* basel)
{
    Edge* lcand = basel->Sym()->Onext() ;
    if( isValid(lcand,basel))
    {
        while(inCircle(basel->Des(),basel->org(),lcand->Des(),lcand->Onext()->Des()))
        {
            Edge* t = lcand->Onext() ;
            cout<<"left " ;
            Kill(lcand) ;
            lcand = t ;
        }
    }
    return lcand;

}

Edge* Delaunay::right_Candidate(Edge *basel)
{
    Edge* rcand = basel->Oprev() ;
    if(isValid(rcand,basel))
    {
        while(inCircle(basel->Des(),basel->org(),rcand->Des(),rcand->Oprev()->Des()))
        {
            Edge* t = rcand->Oprev();
            cout<<"right " ;
            Kill(rcand) ;
            rcand = t;
        }
    }
    return rcand;
}


void Delaunay::Mergehull(Edge*& baseEdge)
{
    while(true)
    {
        Edge* lcand = left_Candidate(baseEdge) ;
        Edge* rcand = right_Candidate(baseEdge) ;

        if(!isValid(lcand,baseEdge) && !isValid(rcand,baseEdge))
        {
            return ;
        }else if(!isValid(lcand,baseEdge) ||
                (isValid(rcand,baseEdge)&&
                inCircle(lcand->Des(),lcand->org(),rcand->org(),rcand->Des())))
        {
            cout<<" add a rcand to base " ;
            baseEdge = Connect(rcand,baseEdge->Sym()) ;
            cout<<endl ;
        }else{
            cout<<" add base to lcand" ;
            baseEdge = Connect(baseEdge->Sym(),lcand->Sym()) ;
            cout<<endl ;
        }

    }
}

