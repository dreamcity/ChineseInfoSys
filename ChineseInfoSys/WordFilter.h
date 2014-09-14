#include "iostream"
#include "fstream"
#include "string"
#include "set"
#include "vector"
#include "map"
using namespace std;
#define separate " "
class WordFilter
{
public:
	WordFilter();
	~WordFilter();
	map<string, float> getKeyWordsMap();
	void getWordMap(const char* inputfile);
	void getFilterWord();
	void updateWordMap();
	void getKeyWordsTF(const char* inputfile);
private:
	map<string, int> wordmap;
	map<string, int> tfmap;
	map<string, float>keywordsmap;
	set<string> stopword;
	set<string> posword;
	int MaxVal;	  //输入的map表的数据个数，不含重复
	int WordNum;  //输入数据的最大数目，包含重复元素
	const char* stopworddict; 

};