#include "WordSplit.h"
WordSplit::WordSplit()
{
}

WordSplit::~WordSplit()
{
}
int WordSplit::getNum()
{
	return num;
}
int* WordSplit::getT()
{
	return T;
}
int** WordSplit::getO()
{
	return O;
}
vector<string> WordSplit::getVStr()
{
	return vstr;
}
/*string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)     
{     
    while(true)   {     
        string::size_type   pos(0);     
        if(   (pos=str.find(old_value))!=string::npos   )     
            str.replace(pos,old_value.length(),new_value);     
        else   break;     
    }     
    return   str;     
}*/ 
 //对输入的测试文本进行处理，得到按照标点符号分隔之后的句子集合
//每一句话，单独写入一行
void WordSplit::getSplitSegFile(const char* inputfile, const char* outputfile)
{
	ifstream infile;
	infile.open(inputfile);
	ofstream outfile;
	outfile.open(outputfile);
	string strtmp;		//每一个待分割的字符串
	string str1 = "";	//存储分割之后的字符串
	string str2 = "";	//存储未完成的句子的后半部分
	//今天是个好天气，我们
	//去游泳，好不好
	//strtmp = 今天是个好天气，我们
	//str1 = 今天是个好天气，
	//str2 = 我们
	//strtmp = 去游泳，好不好
	//str1 = 我们 + 去游泳，
	//str2 = 好不好
	while(getline(infile, strtmp, '\n'))
	{
		if(strtmp.empty())
		{
			continue;
		}
		while(!strtmp.empty())
		{
			//*****************************
			//中文空格，去除掉
			unsigned char ch00 = strtmp[0];
			unsigned char ch11 = strtmp[1];
			while(ch00 ==161 && ch11==161)
			{
				strtmp= strtmp.substr(2);
				ch00 = strtmp[0];
				ch11 = strtmp[1];
			}
			//****************************
			int len = strtmp.length();
			int index = -1;
			for (int i = 0; i < len-4; )
			{
				unsigned char ch0 = strtmp[i];
				//为英文字符，索引加1，继续索引
				if (ch0 < 128)
				{
					i++;
				}
				else
				{
					unsigned char ch1 = strtmp[i+1];
					//当索引到的字符为，。；：！-?""时，结束索引
					if ((ch0 ==163 && ch1==161)||(ch0 ==161 && ch1==163)||(ch0 ==163 && ch1==187)
						||(ch0 ==163 && ch1==172)||(ch0 ==163 && ch1==191)
						||(ch0 ==163 && ch1==186))
					{
						index = i;
						break;
					}
					//为其他的中文字符，索引加2，继续索引
					else
					{
						unsigned char ch3 = strtmp[i+2];
						unsigned char ch4 = strtmp[i+3];
						if ((ch0 ==161 && ch1==170)&&(ch3 ==161 && ch4 ==170))
						{
							int j =i;
							while(ch3 ==161 && ch4 ==170)
							{
								j+=2;
								ch3 = strtmp[j+2];
								ch4 = strtmp[j+3];
							}
							index = j;
							break;
						}
						i+=2;
					}
				}
			}
			//如果结束索引时，字符串中，没用相应的标点，直接整个字符串赋值给str2
			if (index == -1)
			{
				str2 = strtmp.substr(0, len);
				strtmp = "";
			}
			// 将字符串strtmp按索引号分隔（将标点号包含），同时加上str2，即上一个字符串的末尾
			else
			{
				str1 = str2 + strtmp.substr(0, index+2);
				str2 = "";
				strtmp =strtmp.substr(index+2, len-index-2);
			}

			if (str2.empty())
			{
				outfile << str1 <<endl;
				
			}
		}
	}
	outfile << str2 <<endl;
	return ;
}
//void WordSplit::getSplitSegFile(const char* inputfile, const char* outputfile)
//{
//	ifstream infile;
//	infile.open(inputfile);
//	ofstream outfile;
//	outfile.open(outputfile);
//	string strtmp;		//每一个待分割的字符串
//	string str1 = "";	//存储分割之后的字符串
//	string str2 = "";	//存储未完成的句子的后半部分
//	//今天是个好天气，我们
//	//去游泳，好不好
//	//strtmp = 今天是个好天气，我们
//	//str1 = 今天是个好天气，
//	//str2 = 我们
//	//strtmp = 去游泳，好不好
//	//str1 = 我们 + 去游泳，
//	//str2 = 好不好
//	while(getline(infile, strtmp, '\n'))
//	{
//		if(strtmp.empty())
//		{
//			continue;
//		}
//		while(!strtmp.empty())
//		{
//			strtmp = replace_all(strtmp," ","");
//			int len = strtmp.length();
//			int index = -1;
//			for (int i = 0; i < len -2; )
//			{
// 				unsigned char ch0 = strtmp[i];
//				//为英文字符，索引加1，继续索引
//				if (ch0 < 128)
//				{
//					i++;
//				}
//				else
//				{
//					unsigned char ch1 = strtmp[i+1];
//					//当索引到的字符为，。；：！-?""时，结束索引
//					//||(ch0 ==161 && ch1==177)
//					if ((ch0 ==163 && ch1==161)||(ch0 ==161 && ch1==163)||(ch0 ==163 && ch1==187)
//						||(ch0 ==163 && ch1==172)||(ch0 ==163 && ch1==191)
//						||(ch0 ==163 && ch1==186)||(ch0 ==161 && ch1==170))
//					{
//						index = i;
//						break;
//					}
//					//为其他的中文字符，索引加2，继续索引
//					else
//					{
//						//unsigned char ch3 = strtmp[i+2];
//						//unsigned char ch4 = strtmp[i+3];
//						//if ((ch0 ==161 && ch1==170)&&(ch3 ==161 && ch4 ==170))
//						//{
//						//	int j =i;
//						//	while(ch3 ==161 && ch4 ==170)
//						//	{
//						//		j+=2;
//						//		ch3 = strtmp[j+2];
//						//		ch4 = strtmp[j+3];
//						//	}
//						//	index = j;
//						//	break;
//						//}
//						i+=2;
//					}
//				}
//				index = i;
//			}
//			//begin1************************************
//			//针对实际情况，每一段一句话，一行
//			str1 = strtmp.substr(0, index+2);
//			strtmp =strtmp.substr(index+2, len-index-2);
//
//			//while(str1.length()>40)
//			//{
//			//	outfile << str1.substr(0,40) <<endl;
//			//	str1 =str1.substr(40);
//			//}
//			//if(str1.length()>20)
//			//{
//			//	outfile << str1.substr(0,20) <<endl;
//			//	outfile << str1.substr(20) <<endl;
//			//}
//			//else
//			outfile << str1<<endl;
//			//end1************************************
//			//begin2******************************
//			//如果结束索引时，字符串中，没用相应的标点，直接整个字符串赋值给str2
//			//if (index == -1)
//			//{
//			//	str2 = strtmp.substr(0, len);
//			//	strtmp = "";
//			//}
//			//// 将字符串strtmp按索引号分隔（将标点号包含），同时加上str2，即上一个字符串的末尾
//			//else
//			//{
//			//	str1 = str2 + strtmp.substr(0, index+2);
//			//	str2 = "";
//			//	strtmp =strtmp.substr(index+2, len-index-2);
//			//}
//
//			//if (str2.empty())
//			//{
//			//	outfile << str1 <<endl;
//			//	
//			//}
//			//end2***************************************
//		}
//	}
//	//begin2******************
//	//outfile << str2 <<endl;
//	//end2******************
//	return ;
//}
//加载最初由训练时的观察集生成的map表
// map表的每一行，由一个中文字符和对应的map表标号
void WordSplit::loadMapData(const char* inputfile)
{
	 ifstream infile1;
	 infile1.open(inputfile);
	 string linetmp;
	 int linenum=0;
	 // 统计输入文件的行数
	 while(getline(infile1, linetmp, '\n'))
	 {
		if (linetmp.empty())
		{
			continue ;
		}
	 	linenum++;
	 }
	 infile1.close();
	 //载入新的map表
	 ifstream infile2;
	 infile2.open(inputfile);
	 string line, strtmp;
	 for (int i = 0; i < linenum; ++i)
	 {
	 	infile2 >> line;
	 	infile2 >>strtmp;
		int num = atoi(strtmp.c_str());
	 	wordmap.insert(pair<string,int>(line,num));
	 }
	 infile2.close();
	 return ;
}
//将观测文本的每一行制作成观察序列
void WordSplit::getOSequence(const char* inputfile, const char* outputfile)
{
	//const char* inputfile = "1.txt";
	ifstream infile(inputfile);
	ofstream outfile(outputfile);
	string strtmp;
	num =0;
	while(getline(infile, strtmp, '\n'))
	{
		//m++;
		if (strtmp.empty())
		{
			continue;		
		}
		num++;
		std::vector<string> vs;
		string word;
		while(!strtmp.empty())
		{

			//cout<<"line:"<<m<<endl;
			//cout<<"length:"<<strtmp.length()<<endl;
			unsigned char ch0 = strtmp[0];
			while(ch0 > 128)
			{
				word = strtmp.substr(0,2);
				vs.push_back(word);
				strtmp  = strtmp.substr(2);
				if(!strtmp.empty())
				{
					ch0 = strtmp[0];
				}
				else
				{
					break;
				}
			}

			if(ch0 < 128)
			{
				int i = 0;
				unsigned char ch1 = strtmp[i];
				int len = strtmp.length();
				while(ch1 < 128)
				{
					i++;
					if(i<len)
					{
						ch1 = strtmp[i];
					}
					else
					{
						break;
					}
				}
				word = strtmp.substr(0,i);
				vs.push_back(word);
				strtmp = strtmp.substr(i);

			}


		}
		sentencemap[num] = vs;
		int T = vs.size();
		outfile << T <<endl;
		//cout<<"size : "<<vs.size()<<endl;
		for(int i = 0;i<vs.size();i++)
		{
			//outfile << vs[i]<<" ";
			string str = vs[i];
			int OS;
			map<string,int>::iterator iter;
			iter = wordmap.find(str);
			if(iter != wordmap.end())
			{
				OS = wordmap[str];
			}
			else
			{
				OS = 0;
			}
			outfile << OS <<" ";
		}
		outfile<<endl;
	}
	return ;

}
//
//将所有观察序列制成数组存储
void WordSplit::getOSdata(const char* inputfile)
{
	T = new int [num];
	O = new int* [num];
	ifstream fin;
	fin.open(inputfile);
	for (int i = 0; i < num; ++i)
	{
			
		fin >> T[i];
		O[i] = new int [T[i]];
		for (int j = 0; j < T[i]; ++j)
		{
			fin >> O[i][j];
		}
	}
	fin.close();
	return ;
}

//begin******************************************************************
//将输入文件的每一行压入vector中
//输入文件为按标点符号分隔之后的句子
void WordSplit::file2Vector(const char* inputfile)
{	
	ifstream fin;
	string strtmp;
	fin.open(inputfile);
	while(getline(fin, strtmp, '\n'))
	{
		if (strtmp.empty())
		{
			continue ;
		}
		vstr.push_back(strtmp);
	}
	return ;
}
//根据viterbi算法得到的输出状态序列（编号），对输入的测试文件进行标记
// getVStrSegResult
//		path:viterbi算法得到的状态标记序列
//		vector<string>& vstr ，按标点符号重新提取为句子之后的文件的字符串集合
//		str:标记之后的字符串
//   ***getsplitstr()
void getSplitStr(int* path, string str1, string& str2)
{
	int i =-1;
	int j =0;
	int m ;
	int L = str1.length();
	while(!str1.empty())
	{
		int len = str1.length();
		//if(i<len)
		switch(path[++i])
		{
			case 0:
				str2 += str1.substr(0,2) + Separator;
				str1 = str1.substr(2,len-2);
				break;
			case 1: j = i; break;
			case 2:  break;
			case 3:
				m = (i-j+1)*2;
				str2 += str1.substr(0,m) + Separator;
				str1 = str1.substr(m,len-m);
				break;
			default : cout<<"ERROR"<<endl; break;
		}
		//考虑到，分词结果不理想的时候的处理方法，ungly
		//当句子以BM结尾时
		//即忽略句子最后一个字的状态，直接作为结尾。
		if (i == L/2 -2)
		{
			str2 += str1 + Separator;
			str1 = "";
		}
		//cout<<"str1len:"<<str1.length()<<endl;
	}
	return ;
}
void getSplitStr1(int* path, vector<string> vs, string& str)
{
	int L = vs.size();//序列的长度
	for(int i = 0; i<L; i++)
	{
		switch(path[i])
		{
			case 0:
				str += vs[i] + Separator; 
				//str2 += str1.substr(0,2) + Separator;
				//str1 = str1.substr(2,len-2);
				break;
			case 1: str += vs[i]; break;
			case 2: str += vs[i]; break;
			case 3:
				str += vs[i] + Separator;
				//m = (i-j+1)*2;
				//str2 += str1.substr(0,m) + Separator;
				//str1 = str1.substr(m,len-m);
				break;
			default : cout<<"ERROR"<<endl; break;
		}
	}
	return ;
}
void WordSplit::getVStrSegResult(int* path,  string & str, int index)
{
	index++;
	vector<string> sentence = sentencemap[index];
	string strout = "";
	getSplitStr1(path,sentence,strout);
	str= strout;
	//ofstream outfile(outputfile);
	//if(!vstr.empty())
	//{
	//	string strtmp = vstr[0];//得到vector<string>中的第一个字符串
	//	vector<string>::iterator v_it;
	//	v_it = vstr.begin();
	//	vstr.erase(v_it);//删除vector<string>中的第一个字符串
	//	string strout = "";
	//	getSplitStr( path, strtmp, strout);
	//	str= strout;
	//	//outfile<<strout<<endl;
	//}
	return ;
}