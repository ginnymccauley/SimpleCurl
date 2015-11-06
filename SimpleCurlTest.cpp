/**
All code here adapted (modified as little as possible) from 
www.luckyspin.org
Adaptation by Gary Lewandowski, 14 October 2007.

Original header comments follow.
**/

/*
 * This is a very simple example of how to use libcurl from within 
 * a C++  program. The basic idea is that you want to retrieve the 
 * contents of a web page as a string. Obviously, you can replace 
 * the buffer object with anything you want and adjust elsewhere 
 * accordingly.
 * 
 * Hope you find it useful..
 * 
 * Todd Papaioannou 
 * edited by Ginny McCauley
 */

#include <string>
#include <iostream>
#include "SimpleCurl.h"
#include "URLGraph.h"

using namespace std;

int main(int argc, char *argv[])
{
	/** one way to use SimpleCurl: via a constuctor. Give a string and it
	  tries to retrieve the document.
	  **/
	SimpleCurl httpGrabber(argv[1]);
	string doc = httpGrabber.getRetrievedDocument("");
	//cout << "*************************************"<< endl;
	//cout << httpGrabber.findURLS()<< end;
	cout << doc << endl;

	URLGraph *g = new URLGraph();
	//g-> makeGraph(argv[1], httpGrabber.find_urls(argv[1]));

	//testing URLGraph.cpp
	g->BFS(argv[1],3, "www.isitchristmas.com");



    /** Here is a second way -- the more likely way you'll use it.
        After creating an httpGrabber, invoke the getURL method.
        It returns -1 on failure.
        
	if (httpGrabber.getURL("http://www.cs.xu.edu/~lewandow") !=-1)
        	cout << httpGrabber.getRetrievedDocument() << endl;
	else
		cout << "Could not retrieve document" << endl;
}**/
}
