// ChineseInfoSys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "getdbfilelist.h"
#include "CWMHMM.h"
//#include "fstream"
//#include "string"
//#include <time.h>
//#include <windows.h>
//#include <time.h>
//#include "CWMHMM.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> filelist;
	filelist = getDBFileList();
	string filename1 = "../iodata/inputdatapy"+ filelist[31].substr(1);
	string segresult1 = "../iodata/segdata"+ filelist[31].substr(1);
	string markresult1 = "../iodata/markdata"+ filelist[31].substr(1);
	const char* inputdata = filename1.c_str();
	const char* segresult = segresult1.c_str();
	const char* markresult = markresult1.c_str();
	//const char* inputdata = "../iodata/inputfilepy"+ filelist[0].substr(1);
	//const char* segresult = "../iodata/segresult.txt";
	//const char* markresult = "../iodata/markresult.txt";
	
	ifstream infile;
	infile.open(inputdata);
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
	CWM.splitStentes(inputdata, segresult);
	cout<<"wordsplit success!!!"<<endl;
	CWM.markWords(segresult, markresult);
	cout<<"wordmark success!!!"<<endl;
	cout<<"project success!!!"<<endl;
	return 0;


	//cout<<filename<<endl;
	//cout<<filelist[0]<<endl;
	//cout<<filelist.size()<<endl;
	//ifstream infile;
	//infile.open(filename);
	//string strtmp;
	//if (!infile.is_open())	// 打开输入文件失败则退出程序
	//{
	//	cout << "Unable to open input file: " << filelist[0]
	//	<< " -- bailing out!" << endl;
	//	exit(-1);
	//}
	//ofstream outfile;
	//outfile.open("../1.txt");
	//while(getline(infile, strtmp, '\n'))
	//{
	//	cout<<strtmp<<endl;
	//	outfile << strtmp <<endl;
	//	time_t t; 
	//	time(&t);
	//	outfile << "启动系统时间为: " << ctime(&t) <<endl;
	//}
	
	//return 0;
}

