#include "infodig.h"
using namespace std;
InfoDig::InfoDig()
{

}
InfoDig::~InfoDig()
{

}
void InfoDig::getDataPrepare()
{
	vector<string> filelist;
	DBinfo DBI;
	filelist = DBI.getDBFileList();
	for (int i = 0; i < filelist.size(); ++i)
	{
		string filename = "../iodata/inputdatapy"+ filelist[i].substr(1);
		string segresult = "../iodata/segdata"+ filelist[i].substr(1);
		string markresult = "../iodata/markdata"+ filelist[i].substr(1);
		bool flag = DBI.getFileFlag(filename);
		if (flag)
		{
			continue;
		}
		else
		{
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
			// const char* worddict = "../database/stopdict.txt";
			WordFilter WF;
			WF.getKeyWordsTF(markresult.c_str());
			map<string, float> keywords = WF.getKeyWordsMap();
			DBI.saveKeywordsTF(filename,keywords);
			// DBI.showdata();
		}
	}
	cout<<"project success!!!"<<endl;
	return ;
}




	