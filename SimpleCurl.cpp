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
#include <curl/curl.h>
#include "SimpleCurl.h"

 using namespace std;

 int SimpleCurl::writer(char *data, size_t size, size_t nmemb,
 	std::string *buffer)
 {
  // What we will return
 	int result = 0;

  // Is there anything in the buffer?
 	if (buffer != NULL)
 	{
    // Append the data to the buffer
 		buffer->append(data, size * nmemb);

    // How much did we write?
 		result = size * nmemb;
 	}

 	return result;
 }

 SimpleCurl::SimpleCurl(string url)
 {
 	if (getURL(url) == -1) exit(-1);
 }

 int SimpleCurl::getURL(string url)
 {
 	buffer = "";
       // Create our curl handle
 	curl = curl_easy_init();

 	if (curl)
 	{
         // Now set up all of the curl options
 		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
 		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
 		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
 		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
 		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
 		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

         // Attempt to retrieve the remote page
 		result = curl_easy_perform(curl);

         // Always cleanup
 		curl_easy_cleanup(curl);

         // Did we succeed?
 		if (result != CURLE_OK)
 		{
 			cout << "Error: [" << result << "] - " << errorBuffer;
 			return -1;
 		}
 		return buffer.length();
 	}
 	return 0;
 }

 string SimpleCurl::getRetrievedDocument(string)
 { 

 	return buffer;
 }

/*
*	First this fuction uses the static storage class specifier to store 
*	 the information. Subsequent calls will use the object that the first
*	 call created. 
*/ 
bool not_url_char(char c){
    	// characters, in addition to alphanumerics, that can apper in a URL
	static const string url_ch = "~;?/:@=&$-_.+!*'(),";
    	// see wheather c can appear in a URL and return the negative
	return !(isalnum(c))||
	find(url_ch.begin(), url_ch.end(),c) != url_ch.end();
}
/*
*	This fuction forwards its work to the library find_if fuction
*/
string::const_iterator url_end(string::const_iterator b, string::const_iterator e){
	return find_if(b,e, not_url_char);
}


string::const_iterator url_beg(string::const_iterator b, string::const_iterator e){
	static const string sep = "://";
	typedef string::const_iterator iter;
    	// i marks where the separator was found
	iter i = b;
	while((i = search(i,e,sep.begin(), sep.end())) !=e){
			// make sure the separator isn't at the beginning or end of the line
		if(i != b && i + sep.size() !=e){
			// beg marks the beginning of the protocol-name
			iter beg = i;
			while(beg != b && isalpha(beg[-1]))
				--beg;
			//is there at least one appropriate character before and after the segment
			if(beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}
		//the separator we found wasn't part of a URL advance i past this separate
		i+= sep.size();
	}
	return e;
}

/*
*	We start by declaring ret, which is the vector into which we put the
*	URLs as we find them, and by obtaining iterators that delimit the strings.
*/
vector<string> SimpleCurl::find_urls(const string& s){
	vector<string> ret;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();

  	//look through the entire input
	while (b != e){
  		//look for one or more letterd followed by://
		b = url_beg(b,e);

  		// if found
		if (b != e){
  			//get the rest of the URl
			iter after = url_end(b, e);
  			//remember the URL
			ret.push_back(string(b,after));
  			//advance b and check for more URLs on this line
			b = after;
		}
	}
	return ret;
}
