#include "Lexicon.h"
#include <iostream>
using namespace std;


int main()
{
	Lexicon l;
	l.addWord("hello");
	l.addWord("world");
	l.addWord("hello");
	l.addWord("he");

	vector<string> temp;
	temp = l.containsPrefix("w");

	for (string& s : temp)
		cout << s << " ";

	return 0;
}