#!/usr/bin/python
import mysql.connector
import pickle
import os

#no realistic way to add credit hour requirement to prerequisite
#So appending the info to note field.

db = mysql.connector.connect(host="XXX", # your host, usually localhost
                     user="root", # your username
                      passwd="XXX", # your password
                      db="CS372") # name of the data base

# you must create a Cursor object. It will let
#  you execute all the query you need

cur = db.cursor() 
path=os.getcwd()+"/prereq/addToNote.dump"
info = pickle.load( open(path, "rb"))
sqlList=[]
for x in info:
	try:
		course = x[0].split(" ")
		# Use all the SQL you like
		query = "SELECT course_id, note FROM courses where subject = '%s' and course_no = '%s'" % (course[0], course[1])
		cur.execute(query)

		# print all the first cell of all the rows
		for row in cur.fetchall() :
			c = row[0]
			note = row[1]
		if note == "":
			note = "Require: "+x[1]
		else:
			note = note + " ***REQUIRED: "+x[1]+"***"
			note = note.strip()
		#print "%d. Note: %s" % (c, note)
		sql='UPDATE courses SET note = "%s" where course_id = %s;' % (note, c)
		sqlList.append(sql)
	except: 
		pass

newfile=os.getcwd()+"/prereq_permission_undef.sql"
outfile=open(newfile, "w")

for x in sqlList:
	outfile.write("%s\n" % x)


