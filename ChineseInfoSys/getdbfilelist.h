#include <iostream>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <winsock2.h>
#include <vector>
using namespace std;

vector<string> getDBFileList()
{
	vector<string> filelist;
	const char* user = "dreamcity";
    const char* pwd = "304031870";         //password
    const char* host = "localhost";    //or"127.0.0.1"
    const char* dbname = "chineseinfosys";        //database
    unsigned int port = 3306;           //server port        
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
	int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pwd,dbname,port,NULL,0))
    {
        cout<<"connect database succeed!"<<endl;
        // mysql_query(&myCont, "SET NAMES utf-8"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,"select filename from sourcetable where label = 'C000022'");//查询
		if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            if(result)
			{
    			while(sql_row=mysql_fetch_row(result))//获取具体的数据
				{
					filelist.push_back(sql_row[0]);
				}
			}
		}
		else
		{
			cout<<"query sql failed!"<<endl;			}
		}
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
    return filelist;
}