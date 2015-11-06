/* This class takes the URLS that we find in SimpleCurl 
and puts them into an easiy readable graph to be able 
to better read the URLS that were found
Created by Ginny McCauley

**       **   *********    **          **********
**       **   **           **          **      **
**       **   **           **          **      **
***********   ******       **          **********
**       **   **           **          **        
**       **   **           **          **        
**       **   *********    *********   **         


How do you keep your feet on the ground when you know that you were born to fly??

*/

#include <iostream>
#include <queue>
#include <vector>
#include "SimpleCurl.h"
#include "URLGraph.h"

URLGraph::URLGraph(){

}
//stores the urls and neighbors into the graph and return the graph.   
map < string,vector<string> > URLGraph::makeGraph(string url, vector<string> neighbor){
	
	//graph pair<url, neighbor>;
	return graph;
}

/*
*	Breadth – first searches are performed by exploring 
*	all nodes at a given depth before proceeding to the next level.
*	explores the neighbors of the url and then moves on to the next level
*/
void URLGraph::BFS(string url,int length, string target){
	//cout << "works"<< endl;
	bool found = false;
	//initallizing 
	if(url != target){
		string u;
		color[u]="white";
		parent[u]= "";
		distance[u]=0;
		//adding to the queue
		Q.push(url); 
		distance[url] = 0;
		color[url] = "grey";//haven't seen it yet
		parent[url] = "";

		int levelsdone = 0;
		//to make sure you don't go over levels you want to see

		while(!Q.empty() && levelsdone<length){
			string u = Q.front();//grabs variable from front
			Q.pop();//removes from front
			//loops through to change and find neighbors
			for(int i=0; i<Q.size(); i++){
				if(color[url] == "white" && url != target){
					color[url] = "gray";//working on it...
					parent[url] = u;
					distance[url] = distance[u] + 1;//lower in the graph
					//string doc = SimpleCurl::getRetrievedDocument(); // returns document
					//string n = c.find_urls(doc);//finds neighbors 
					Q.push(u); // puts neighbors in queue
				}
			}
			levelsdone = levelsdone + 1;//adds how many levels you've seen
			color[url]="black";//your done change color
		}
	}else{
		//target was not found 
		cout<< "target found"<< endl;
		found = true;
	}	
	if(found == false){
		//target was found
		cout<< "target not found"<< endl;
	}
}

