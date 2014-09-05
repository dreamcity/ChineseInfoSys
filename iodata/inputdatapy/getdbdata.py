import datasource.baiduNewsXML as baiduNewsXML
import datasource.mysqldb as mysqldb
inputfolder = r'./datasource/baidunews'
outputfile = r'./datasource/baidunewslist.xml'
XD = baiduNewsXML.XMLData(inputfolder,outputfile)
XD.getXMLFile()
# print(XD.filedict)
# print(XD.labeldict)

dbname = 'ChineseInfoSys'
table1 = 'sourcetable'
table2 = 'tfdatatable'
SysDB = mysqldb.MySqlBase(dbname, table1, table2)
SysDB.createDB()
SysDB.updateTable1(XD.labeldict,XD.filedict)