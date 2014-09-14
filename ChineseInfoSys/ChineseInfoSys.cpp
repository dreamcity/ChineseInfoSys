// ChineseInfoSys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "dbinfo.h"
#include "CWMHMM.h"
#include "WordFilter.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> filelist;
	DBinfo DBI;
	filelist = DBI.getDBFileList();
	
	string filename = "../iodata/inputdatapy"+ filelist[31].substr(1);
	string segresult = "../iodata/segdata"+ filelist[31].substr(1);
	string markresult = "../iodata/markdata"+ filelist[31].substr(1);
	
	ifstream infile;
	infile.open(filename.c_str());
	string strtmp;
	if (!infile.is_open())	// 打开输入文件失败则退出程序
	{
		cout << "Unable to open input file: " << filelist[0]
		<< " -- bailing out!" << endl;
		exit(-1);
	}	
	
	CWMHMM CWM;
	string splitHMM = CWM.getMarkHMMfile();
	string markHMM = CWM.getSplitHMMfile();
	if(splitHMM.empty())
	{
		CWM.getSplitHMMModel();
	}	
	if(markHMM.empty())
	{
		CWM.getMarkHMMModel();
	}	
	CWM.splitStentes(filename.c_str(), segresult.c_str());
	cout<<"wordsplit success!!!"<<endl;
	CWM.markWords(segresult.c_str(), markresult.c_str());
	cout<<"wordmark success!!!"<<endl;
	const char* worddict = "../database/stopdict.txt";
	WordFilter WF;
	WF.getKeyWordsTF(markresult.c_str(), worddict);
	map<string, float> keywords = WF.getKeyWordsMap();
	DBI.saveKeywordsTF(markresult,keywords);
	DBI.showdata();
	cout<<"project success!!!"<<endl;
	return 0;
}

