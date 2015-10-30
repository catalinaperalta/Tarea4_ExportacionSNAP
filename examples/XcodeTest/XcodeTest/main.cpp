//
//  main.cpp
//  Tarea4
//
//  Created by Catalina Peralta on 10/27/15.
//  Copyright © 2015 Catalina Peralta. All rights reserved.
//

#include "Snap.h"

#include <iostream>
#include <chrono>
#include <fstream>

void exportGraphML(PNGraph g);
void exportGEXF(PNGraph g);
void exportGDF(PNGraph g);
void exportJSON(PNGraph g);

int main()
{
    PNGraph g = TSnap::LoadEdgeList<PNGraph>("/Users/icaty/Downloads/facebook_combined.txt", 0, 1);

    auto begin = std::chrono::high_resolution_clock::now();
    exportGraphML(g);
    auto end = std::chrono::high_resolution_clock::now();
    auto graphML = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"GraphML: "<<graphML.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    exportGEXF(g);
    end = std::chrono::high_resolution_clock::now();
    auto gexf = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"GEXF: "<<gexf.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    exportGDF(g);
    end = std::chrono::high_resolution_clock::now();
    auto gdf = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"GDF: "<<gdf.count()<<std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    exportJSON(g);
    end = std::chrono::high_resolution_clock::now();
    auto json = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"JSON: "<<json.count()<<std::endl;
    
    return 0;
}

void exportGraphML(PNGraph g)
{
    std::ofstream file("./facebook_combined.graphml");
    
    if (file.is_open())
    {
        file<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file<<"<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        file<<"<graph id=\"G\" edgedefault=\"undirected\">\n";
        
        for (PNGraph::TObj::TNodeI node = g->BegNI(); node < g->EndNI(); node++)
        {
            file<<"<node id=\""<<node.GetId()<<"\"/>\n";
        }
        
        int i = 1;
        for (PNGraph::TObj::TEdgeI edge = g->BegEI(); edge < g->EndEI(); edge++)
        {
            file<<"<edge id=\"e"<<i<<"\" source=\""<<edge.GetSrcNId()<<"\" target=\""<<edge.GetDstNId()<<"\"/>\n";
            i++;
        }
        
        file<<"</graph>\n";
        file<<"</graphml>\n";
        
        file.close();
    }
}

void exportGEXF(PNGraph g)
{
    std::ofstream file("./facebook_combined.gexf");
    
    if (file.is_open())
    {
        file<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file<<"<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        file<<"<graph mode=\"static\" defaultedgetype=\"directed\">\n";
        file<<"<nodes>\n";
        
        for (PNGraph::TObj::TNodeI node = g->BegNI(); node < g->EndNI(); node++)
        {
            file<<"<node id=\""<<node.GetId()<<"\" />\n";
        }
        
        file<<"</nodes>\n";
        file<<"<edges>\n";
        
        int i = 1;
        for (PNGraph::TObj::TEdgeI edge = g->BegEI(); edge < g->EndEI(); edge++, i++)
        {
            file<<"<edge id=\""<<i<<"\" source=\""<<edge.GetSrcNId()<<"\" target=\""<< edge.GetDstNId()<<"\" />\n";
            i++;
            
        }
        
        file << "</edges>\n";
        file << "</graph>\n";
        file << "</gexf>\n";
        file.close();
    }
}

void exportGDF(PNGraph g)
{
    std::ofstream file("./facebook_combined.gdf");
    
    if (file.is_open())
    {
        file<<"nodedef> name VARCHAR\n";
        for (PNGraph::TObj::TNodeI node = g->BegNI(); node < g->EndNI(); node++)
        {
            file<<node.GetId()<<"\n";
        }
        
        file<<"edgedef>source VARCHAR, destination VARCHAR\n";
        
        for (PNGraph::TObj::TEdgeI edge = g->BegEI(); edge < g->EndEI(); edge++)
        {
            file<<edge.GetSrcNId()<<", "<<edge.GetDstNId()<<"\n";
        }
        
        file.close();
    }
}

void exportJSON(PNGraph g)
{
    std::ofstream file("./facebook_combined.json");
    
    if (file.is_open())
    {
        file<<"{ \"graph\": {\n";
        file<<"\"nodes\": [\n";
        for (PNGraph::TObj::TNodeI node = g->BegNI(); node < g->EndNI();)
        {
            file<<"{ \"id\": \""<<node.GetId()<<"\" }";
            node++;
            
            if (node == g->EndNI())
            {
                file<<" ],\n";
            }
            else
            {
                file<<",\n";
            }
        }
        
        file << "\"edges\": [\n";
        
        for (PNGraph::TObj::TEdgeI edge = g->BegEI(); edge < g->EndEI();)
        {
            file<<"{ \"source\": \""<<edge.GetSrcNId()<<"\", \"target\": \""<<edge.GetDstNId()<<"\" }";
            edge++;
            
            if (edge == g->EndEI())
            {
                file<<" ]\n";
            }
            else
            {
                file<<",\n";
            }
        }
        
        file << "} }";
        file.close();
    }

}
