#include <iostream>
#include "Lexicon.h"

Lexicon::~Lexicon()
{

}

void Lexicon::addWord(string word)
{
	addWord(root, word);
}

void Lexicon::addWord(Trie* vertex, string word)
{
	if (word.size() == 0)
		vertex->words++;
	else
	{
		vertex->prefixes++;
		char ch = word[0];
		int index = ch - 'a';
		if (vertex->edges[index] == nullptr)
			vertex->edges[index] = new Trie();
		word = word.substr(1);
		addWord(vertex->edges[index], word);
	}
}
int Lexicon::countWord(Trie *vertex, string word)
{
	if (word.empty())
		return vertex->words;
	else{
		char ch = word[0];
		if (vertex->edges[ch - 'a'] == nullptr)
			return 0;
		else
			return countWord(vertex->edges[ch - 'a'], word.substr(1));
	}
}

int Lexicon::countWord(string word)
{
	return countWord(root, word);
}

int Lexicon::countPrefix(Trie *vertex, string prefix)
{
	if (prefix.empty())
		return vertex->prefixes;
	else{
		char ch = prefix[0];
		if (vertex->edges[ch - 'a'] == nullptr)
			return 0;
		else
			return countPrefix(vertex->edges[ch - 'a'], prefix.substr(1));
	}
}

int Lexicon::countPrefix(string prefix)
{
	return countPrefix(root, prefix);
}

void Lexicon::containsPrefix(Trie *vertex, string prefix, vector<string>& list)
{
	if (vertex->words > 0)
		list.push_back(prefix);

	if (vertex->prefixes > 0)
	{
		for (int i = 0; i < 26; ++i)
		{
			if (vertex->edges[i] != nullptr)
			{
				containsPrefix(vertex->edges[i], prefix + string(1, char('a' + i)), list);
			}
		}
	}
}

Lexicon::Trie* Lexicon::getVertex(Trie *vertex, string prefix)
{
	if (prefix.empty())
		return vertex;
	else{
		char ch = prefix[0];
		if (vertex->edges[ch - 'a'] != nullptr)
			return getVertex(vertex->edges[ch - 'a'], prefix.substr(1));
		else
		{
			return nullptr;
		}
	}
}

vector<string> Lexicon::containsPrefix(string prefix)
{
	vector<string> list;
	Trie* start;
	start = getVertex(root, prefix);
	if (start == nullptr)
		return list;
	containsPrefix(start, prefix, list);
	return list;
}
