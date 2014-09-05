#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <vector>
#include "WRRMMap.h"
using namespace std;

//#define LOCK
WRRMMap_Lock<string, int> myMap;
//WRRMMap<string, int> myMap;

void lookup(){
	for (int i = 0; i < 26 * 10000; ++i){
		int temp = myMap.Lookup(to_string(i % 26));
	}
}

int main(int argc, char *argv[])
{
	//test with lock
	clock_t begin = clock();

	for (int i = 0; i < 26; ++i){
		myMap.Update(to_string(i), 1);
	}
	
	std::thread threads[20];
	for (int i = 0; i < 20; ++i){
		threads[i] = std::thread(lookup);
	}
	for (int i = 0; i < 20; ++i){
		threads[i].join();
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time is " << elapsed_secs << endl;
	return 0;
}