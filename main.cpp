#include <iostream>
#include "Delaunay.h"
#include <igl/opengl/glfw/Viewer.h>
#include <igl/jet.h>

using namespace std ;

void writeObj(string st,vector<Vertex*>& vertexs,vector<tuple<Vertex*,Vertex*,Vertex*>> tris)
{
    ofstream ou(st) ;
    int k = 1 ;
    for(int i = 0; i< vertexs.size();i++)
    {
        ou<<"v "<<setprecision(2)<<"  "<<vertexs[i]->x()<<" "<<vertexs[i]->y()<<" "<<vertexs[i]->z()<<endl;
        vertexs[i]->setallIndex(k++) ;
    }
    for(int i = 0 ;i< tris.size();i++)
    {
        ou<<"f "<<setprecision(2)
                <<std::get<0>(tris[i])->getallIndex()<<" "
                <<std::get<1>(tris[i])->getallIndex()<<" "
                <<std::get<2>(tris[i])->getallIndex()<<endl ;

    }

    ou.close();

}


int main() {

    Delaunay* a= new Delaunay("/Users/lidan/Desktop/数字高程模型/样例/resource2.node") ;
    EdgePartition all = a->beginTriangulate(a->getVertexs() ) ;

    VertexList vl_list = a->getVertexs() ;
    VertexList vl ;
    QuadList el = a->getEdges() ;


    Edge* e= std::get<0>(all)  ;
    vector<Edge*> edges = {e};




    while(!rightOf(e->Onext()->Des(),e))
    {
        e = e->Onext() ;
    }

    add(vl,e,edges) ;
    vl.clear() ;
    int k = 0 ;
    while(k<edges.size())
    {
        if(!((e=edges[k++])->used))
        {
            add(vl,e,edges) ;
        }
    }

    vector<tuple<Vertex*,Vertex*,Vertex*>> tris ;
    for(int i = 0; i < (int)vl.size();i+=3)
    {
        tris.push_back(make_tuple(vl[i],vl[i+1],vl[i+2])) ;
    }




    for(int i = 0; i< el.size();i++)
    {
        cout<<el[i]->edges[0].org()->getallIndex()<<"    "
        <<el[i]->edges[0].Lnext()->org()->getallIndex()<<"    "
        <<el[i]->edges[0].Lnext()->Lnext()->org()->getallIndex()<<endl ;
    }

    string obj= "/Users/lidan/Desktop/数字高程模型/样例/resource.obj";
    writeObj(obj,vl_list, tris);

//    string obj = "/Users/lidan/Desktop/数字高程模型/数字高程模型代码/样例数据/another.obj";
//    string obj = "/Users/lidan/CLionProjects/marchingcube/data.obj" ;
//    Eigen::MatrixXd V;
//    Eigen::MatrixXi F;
//    Eigen::MatrixXd C;
//
//    igl::readOBJ(obj, V, F);
//
//    igl::opengl::glfw::Viewer viewer;
//    viewer.data().set_mesh(V, F);
//
//    // Use the z coordinate as a scalar field over the surface
//
//    Eigen::VectorXd Z = V.col(2);
//
//    // Compute per-vertex colors
//    igl::jet(Z,true,C);
//
//    // Add per-vertex colors
//    viewer.data().set_colors(C);
//
//    // Launch the viewer
//    viewer.launch();
}