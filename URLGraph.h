/* 
*	This class takes the URLS that we find in SimpleCurl 
*	and puts them into an easiy readable graph to be able 
*	to better read the URLS that were found
*	Created by Ginny McCauley
*/
#ifndef URLGRAPH_H
#define URLGRAPH_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include "SimpleCurl.h"

using namespace std;

class URLGraph
{

public: 
	URLGraph();
	map < string,vector<string> > makeGraph(string, vector<string>);
	void BFS(string,int,string);
	

private:
	//stores the urls and neighbors.   
	map<string,vector<string> > graph;
	//holds the neighbors
	queue<string> Q;
	map<string,string> parent;
	map<string, int> distance;
	map<string,string> color;
	SimpleCurl c;

};
#endif