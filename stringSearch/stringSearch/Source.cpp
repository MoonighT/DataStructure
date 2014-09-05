#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;


int brute_force(string text, string pattern)
{
	int i = 0;
	for (; i < text.size(); ++i){
		int j = 0;
		for (; j < pattern.size() && i + j < text.size(); ++j)
		{
			if (text[i + j] != pattern[j])
				break;
		}
		if (j == pattern.size())
			return i;
	}
	if (i == text.size())
		return -1;
}

void getPartialMatchTable(string pattern, vector<int>& table)
{
	table.clear();
	table.resize(pattern.size());
	for (int index = 0; index < pattern.size(); ++index)
	{
		int longest = 0;
		for (int i = index; i > 0; --i)
		{
			//cout << pattern.substr(0, i) << " " << pattern.substr(index - i + 1, i);
			if (pattern.substr(0, i) == pattern.substr(index - i + 1, i)){
				longest = i;
			}
		}
		table[index] = longest;
	}
}

int kmp(string text, string pattern)
{
	vector<int> ptable;
	getPartialMatchTable(pattern, ptable);
	for (int i = 0; i <= text.size() - pattern.size();)
	{
		int j = 0;
		for (; j < pattern.size(); ++j)
		{
			
			if (pattern[j] != text[i + j])
			{
				if (j == 0)
				{
					++i;
					break;
				}
				i = i + j - ptable[j-1];
				break;
			}
		}
		if (j == pattern.size())
			return i;
	}
	return -1;
}

void test()
{
	vector<int> ptable;
	getPartialMatchTable("ABCDABD", ptable);
	for (int &i : ptable)
	{
		cout << i << " ";
	}
}

int main()
{
	//test();
	string text = "BBC ABCDAB ABCDABCDABDE";
	string pattern = "ABCDABD";
	
	auto start = chrono::system_clock::now();

	for (int i = 0; i < 100000; ++i)
		//kmp(text, pattern);
		text.find(pattern);
	auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);
	cout << duration.count();
		
	return 0;
}