#include "WordFilter.h"
using namespace std;
WordFilter::WordFilter()
{
	stopworddict = "../database/stopdict.txt";
}
WordFilter::~WordFilter()
{
}
map<string, float> WordFilter::getKeyWordsMap()
{
	return keywordsmap;
}
vector<string> wfsplit(string str,string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size(); 
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            if (s.length()>0)
            {
                result.push_back(s);
                i=pos+pattern.size()-1;
            }
        }
    }
    return result;
}

void WordFilter::getWordMap(const char* inputfile)
{
    int val = 0;
    WordNum = 0;
    string strtmp1;
    ifstream infile1(inputfile);
    while(getline(infile1, strtmp1, '\n'))
    {
        if (strtmp1.empty())
        {
            continue;
        }
        string pattern = separate;
        vector<string> result = wfsplit(strtmp1,pattern);
        WordNum +=result.size();
        for (int i = 0; i < result.size(); ++i)
        {
            string str = result[i].c_str();
            map<string, int>::iterator m_it_w;
            m_it_w = wordmap.find(str);
            if (m_it_w == wordmap.end())
            {
                wordmap.insert(pair<string, int>(str, val));
                val++;
            }
        }
    }
    MaxVal = val;
    infile1.close();

    int valnum = wordmap.size();
    int* value = new int [val];
    for(int i= 0;i<valnum; i++)
    {
        value[i] = 0.0;
    }
    string strtmp2;
    ifstream infile2(inputfile);
    while(getline(infile2, strtmp2, '\n'))
    {
        if (strtmp2.empty())
        {
            continue ;
        }
        string pattern = " ";
        vector<string> result = wfsplit(strtmp2,pattern);
        for (int i = 0; i < result.size(); ++i)
        {
            string str = result[i].c_str();
			//cout<<"index:"<<wordmap[str]<<endl;
            value[wordmap[str]]++;
        }
    }

    map<string,int>::iterator it=wordmap.begin();
    for(;it!=wordmap.end();++it)
    {
        tfmap.insert(pair<string, int>(it->first, value[wordmap[it->first]]));
    }
	infile2.close();
    return ;
}

void WordFilter::getFilterWord()
{
    string strtmp;
    ifstream infile(stopworddict);
    while(getline(infile, strtmp, '\n'))
    {
        if (strtmp.empty())
        {
            continue ;
        }
        stopword.insert(strtmp); 
    }
    string arr_pos[] = { 
        "/a",       //形容词
        "/b",    //    区别词 区别语素
        "/l",    //    习语
        "/m",    //    数词 数语素
        "/an",      //名形词
        "/ag",      //形容词性语素
        "/al",      //形容词性惯用语
        "/r",    //    代词 代语素
        "/s",    //    处所词
        "/t",    //    时间词
        "/n",    //名词
        //"/nr",   //    人名
        "/ns",   //    地名
        "/nt",   //    机构团体
        "/nx",   //    外文字符
        "/nz",   //    其他专名
        "/v",       //动词
        "/vd",      //副动词
        "/vn",      //名动词
        "/vl",      //动词性惯用语
        "/vg",      //动词性语素
        ""
    };
    for (int i = 0; arr_pos[i] != ""; ++i)
    {
        posword.insert(arr_pos[i]);
    }
    return ; 
}

void WordFilter::updateWordMap()
{
    map<string, int>::iterator m_it;
    m_it = tfmap.begin();
    for (; m_it !=tfmap.end();)
    {
        string word = m_it->first;
        string::size_type position;
        position = word.find('/');       
        string pureword = word.substr(0,position);
        string wordpos = word.substr(position);
        set<string>::iterator s_it1;
        set<string>::iterator s_it2;
        s_it1 = stopword.find(pureword);
        s_it2 = posword.find(wordpos);
        if (s_it1 != stopword.end()|| s_it2 == posword.end() )
        {
			tfmap.erase(m_it++);
        }
		else
		{
			m_it++;
		}
    }
	int val = tfmap.size();
	map<string,int>::iterator it=tfmap.begin();
	for(;it!=tfmap.end();++it)
	{
		int tmp = tfmap[it->first];
		if(tmp<2)
		{
			continue;
		}
		string word = it->first;
		string::size_type position;
        position = word.find('/');       
        string pureword = word.substr(0,position);
		float value = (float)tfmap[it->first]/val;
		keywordsmap.insert(pair<string,float>(pureword, value));
	}
    return ;
}

void WordFilter::getKeyWordsTF(const char* inputfile)
{
    getWordMap(inputfile);
    getFilterWord();
    updateWordMap();
    return ;
}