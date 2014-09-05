#include <string>
#include <vector>
using namespace std;

class Lexicon
{
public:
	struct Trie
	{
		int words;
		int prefixes;
		Trie *edges[26];

		Trie()
		{
			words = 0;
			prefixes = 0;
			for (int i = 0; i < 26; ++i)
				edges[i] = nullptr;
		}
	};

	Lexicon()
	{
		root = new Trie();
	};

	~Lexicon();

	void addWord(string word);
	int countWord(string word);
	int countPrefix(string prefix);
	vector<string> containsPrefix(string prefix);

private:
	void addWord(Trie *vertex, string word);
	int countWord(Trie *vertex, string word);
	int countPrefix(Trie *vertex, string prefix);
	void containsPrefix(Trie *vertex, string prefix, vector<string> &list);
	Trie* getVertex(Trie *root, string prefix);
	

	Trie *root;
};

