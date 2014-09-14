#include <iostream>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <winsock2.h>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
class DBinfo
{
public:
	DBinfo();
	~DBinfo();
	vector<string> getDBFileList();
	bool getFileFlag(string filename);
	void saveKeywordsTF(string filename, map<string, float> keywords);
	void showdata();
private:
	const char* user ;
    const char* pwd ;         //password
    const char* host ;    //or"127.0.0.1"
    const char* dbname ;        //database
    unsigned int port ;           //server port        
};