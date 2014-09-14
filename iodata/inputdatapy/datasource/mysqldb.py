from mysql import connector
class MySqlBase(object):
	"""docstring for MySqlBase"""
	def __init__(self, basename, table1, table2):
		super(MySqlBase, self).__init__()
		self.user = 'dreamcity'
		self.pwd = '304031870'
		self.host = 'localhost'
		self.basename = basename
		self.table1 = table1
		self.table2 = table2

	def createDB(self):
		cnx = connector.connect(user= self.user, password = self.pwd, host = self.host)
		cur = cnx.cursor()
		sqlorder = "CREATE DATABASE IF NOT EXISTS %s" %self.basename
		cur.execute(sqlorder)
		sqlorder = "USE %s" %self.basename
		cur.execute(sqlorder)
		sqlorder = "CREATE TABLE IF NOT EXISTS %s (id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,label VARCHAR(30),labelNum INT(3),filename VARCHAR(100) NOT NULL UNIQUE)" %self.table1
		cur.execute(sqlorder)
		sqlorder = "CREATE TABLE IF NOT EXISTS %s (id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, filename VARCHAR(100) NOT NULL, wordname VARCHAR(20) , tfdata float, UNIQUE KEY(filename,wordname))" %self.table2
		cur.execute(sqlorder)
		cur.close()
		cnx.commit()
		cnx.close()
		print('create database success!!!')
		
	def updateTable1(self,labeldict,filedict):
		cnx = connector.connect(user= self.user, password = self.pwd, host = self.host)
		cur = cnx.cursor()
		sqlorder = "USE %s" %self.basename
		cur.execute(sqlorder)
		# sqlorder = "SELECT * FROM %s WHERE filename = '%s'" %
		labellist = labeldict.keys()
		for x in labellist:
			filelist = filedict[x]
			for y in filelist:
				y2 = y.replace('\\','/')
				sqlorder = "SELECT * FROM %s WHERE filename = '%s'" %(self.table1,y2)
				cur.execute(sqlorder)
				if cur.fetchall():
					pass
				else:
					sqlorder = "INSERT INTO %s VALUES(0,'%s', %d, '%s')" %(self.table1, x, labeldict[x], y2)
					cur.execute(sqlorder)					
		cur.close()
		cnx.commit()
		cnx.close()
		print('updata database success!!!')
		
