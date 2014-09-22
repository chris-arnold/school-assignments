#!/usr/bin/python
import glob
import os
import sys
import time
import pickle
#generate sql for courses

files=[]
sqlpath=os.getcwd()+"/sql/"
sqlList=[]


if not os.path.exists(sqlpath):
	os.makedirs(sqlpath)

os.chdir("final/computer")

for x in glob.glob("*.dump"):
	files.append(x)

os.chdir("../..")
print files

files = ["CS.dump",]

for x in files:
	path = os.getcwd()+"/final/computer/%s" % x
	info = pickle.load( open(path, 'rb'))
	for y in info:
		sub = y[0].split(" ")
		sql = 'INSERT INTO courses (subject, course_no, short_description, long_description, note) values ("%s","%s","%s","%s","%s");' % (sub[0], sub[1], y[4], y[3], y[2])
		sqlList.append(sql)

	s = sqlpath+"%s.sql" % x[:-5]
	sq = open(s, "w")
	for i in sqlList:
		sq.write("%s\n" % i)

