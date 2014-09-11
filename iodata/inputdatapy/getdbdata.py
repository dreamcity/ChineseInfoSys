import datasource.dataXML as dataXML
import datasource.mysqldb as mysqldb
inputfolder = r'./datasource/SougouSource'
outputfile = r'./datasource/SougouSourcelist.xml'
XD = dataXML.XMLData(inputfolder,outputfile)
XD.getXMLFile()
# print(XD.filedict)
# print(XD.labeldict)

dbname = 'ChineseInfoSys'
table1 = 'sourcetable'
table2 = 'tfdatatable'
SysDB = mysqldb.MySqlBase(dbname, table1, table2)
SysDB.createDB()
SysDB.updateTable1(XD.labeldict,XD.filedict)