#!/usr/bin/python
import mysql.connector
import pickle
import os

db = mysql.connector.connect(host="XXX", # your host, usually localhost
                     user="root", # your username
                      passwd="XXX", # your password
                      db="CS372") # name of the data base

# you must create a Cursor object. It will let
#  you execute all the query you need
cur = db.cursor() 
path=os.getcwd()+"/prereq/or.dump"
info = pickle.load( open(path, "rb"))
sqlList=[]
for x in info:
	try:
		course = x[0].split(" ")
		# Use all the SQL you like
		query = "SELECT course_id FROM courses where subject = '%s' and course_no = '%s'" % (course[0], course[1])
		cur.execute(query)

		# print all the first cell of all the rows
		for row in cur.fetchall() :
			c = row[0]

		course = x[1].split(" ")
		query = "SELECT course_id FROM courses where subject = '%s' and course_no = '%s'" % (course[0], course[1])
		cur.execute(query)

		for row in cur.fetchall():
			p = row[0]
		statement="INSERT INTO prerequisites (course_id, prereq_course_id, isRequired, optional_no) values (%s, %s, 1, 1);" % (c,p)
		sqlList.append(statement)
	except: 
		pass

newfile=os.getcwd()+"/simpleor.sql"
outfile=open(newfile, "w")

for x in sqlList:
	outfile.write("%s\n" % x)
