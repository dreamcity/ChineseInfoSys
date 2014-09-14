#include "dbinfo.h"
using namespace std;
DBinfo::DBinfo()
{
	user = "dreamcity";
    pwd = "304031870";         //password
    host = "localhost";    //or"127.0.0.1"
    dbname = "chineseinfosys";        //database
    port = 3306;           //server 
}
DBinfo::~DBinfo()
{

}
vector<string> DBinfo::getDBFileList()
{
	vector<string> filelist;	
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
	int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pwd,dbname,port,NULL,0))
    {
        cout<<"connect database succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES utf-8"); //设置编码格式,否则在cmd下无法显示中文
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
			if(result!=NULL) mysql_free_result(result);//释放结果资源
		}
		else
		{
			cout<<"query sql failed!"<<endl;			}
		}
    else
    {
        cout<<"connect database failed!"<<endl;
    }
    
    mysql_close(&myCont);//断开连接
    return filelist;
}
bool DBinfo::getFileFlag(string filename)
{
	bool flag;
	MYSQL myCont;
    MYSQL_RES *result;
	int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pwd,dbname,port,NULL,0))
    {
        cout<<"connect database succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES utf-8"); //设置编码格式,否则在cmd下无法显示中文
        string sqlorder =  "select filename from tfdatatable where filename ='" + filename + "'";
        res=mysql_query(&myCont,sqlorder.c_str());//查询
    	if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
			unsigned int rowcount=mysql_num_rows(result); 
            if(rowcount)
			{
				flag = TRUE; 
			}
			else
			{
				flag = FALSE; 
			}
			if(result!=NULL) mysql_free_result(result);//释放结果资源
		}
		else
		{
			cout<<"query sql failed!"<<endl;			}
		}
    else
    {
        cout<<"connect database failed!"<<endl;
    }
	
	mysql_close(&myCont);//断开连接
	return flag;
}
void DBinfo::saveKeywordsTF(string filename, map<string, float> keywords)
{
    MYSQL myCont;
    MYSQL_RES *result;
	int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pwd,dbname,port,NULL,0))
    {
        cout<<"connect database succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES utf-8"); //设置编码格式,否则在cmd下无法显示中文
        map<string, float>::iterator m_it;
        m_it = keywords.begin();
        for (; m_it != keywords.end(); ++m_it)
        {
        	string word = m_it->first;
        	float tfvalue = m_it->second;
        	string sqlorder =  "select wordname from tfdatatable where wordname ='" + word + "'";
			res=mysql_query(&myCont,sqlorder.c_str());//查询
        	if(!res)
	        {
            	result=mysql_store_result(&myCont);//保存查询到的数据到result
            	unsigned int rowcount=mysql_num_rows(result); 
				if(rowcount !=0)
				{
					continue;
				}
				else
				{
					string str1 = "'" + filename + "'";
					string str2 = "'" + word + "'";
					stringstream ss;
					ss<<tfvalue;
					string str3;
					str3 = ss.str();
					string sqlorder = "INSERT INTO tfdatatable VALUES(0," + str1 +"," + str2 +","+ str3 +")";
					const char* sql = sqlorder.c_str();
					int restemp;
					restemp = mysql_query(&myCont, sql);
					if (!restemp)
					{
						cout<<"data insert success"<<endl;
					}
					else
					{
						cout<<"data insert failed"<<endl;
					}

				}
				if(result!=NULL) mysql_free_result(result);//释放结果资源

			}
			else
			{
				cout<<"query sql failed!"<<endl;			
			}
		}
		
	}
    else
    {
        cout<<"connect database failed!"<<endl;
    }
    
    mysql_close(&myCont);//断开连接
	return ;
}

void DBinfo::showdata()
{
		//vector<string> filelist;	
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
	int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pwd,dbname,port,NULL,0))
    {
        cout<<"connect database succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES utf-8"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,"select wordname from tfdatatable ");//查询
		if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            if(result)
			{
    			while(sql_row=mysql_fetch_row(result))//获取具体的数据
				{
					cout<<sql_row[0]<<endl;
				}
			}
		}
		else
		{
			cout<<"query sql failed!"<<endl;			}
		}
    else
    {
        cout<<"connect database failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
    return ;
}
