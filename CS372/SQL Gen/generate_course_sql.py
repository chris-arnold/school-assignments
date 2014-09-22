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

os.chdir("clean/computer")

for x in glob.glob("*.dump"):
	files.append(x)

os.chdir("../..")
#print files

#files = ["CS.dump", "CS1.dump"]
count = 0

for x in files:
	sqlList=[]
	path = os.getcwd()+"/clean/computer/%s" % x
	info = pickle.load( open(path, 'rb'))
	for y in info:
		flag = False
		sub = y[0].split(" ")
		if '"' in y[2]:
			y[2] = y[2].replace('"', '')
		if '"' in y[3]:
			y[3] = y[3].replace('"', '')
		if '"' in y[4]:
			y[4] = y[4].replace('"', '')
		sql = 'INSERT INTO courses (subject, course_no, short_description, long_description, note) values ("%s","%s","%s","%s","%s");' % (sub[0], sub[1], y[4], y[3], y[2])
		sqlList.append(sql)
	
	s = sqlpath+"%s.sql" % x[:-5]
	sq = open(s, "w")
	print "Writing %s" % s
	for i in sqlList:
		sq.write("%s\n" % i)
'''
print "Count %d" % count
newfile=os.getcwd()+"/courses1.sql"
course = open(newfile, "w")
for x in sqlList:
	course.write("%s\n" % x)
'''

print "SQL Files written."
print "Now gathering them into one file..."

os.chdir("sql")
files=[]
for x in glob.glob("*.sql"):
	files.append(x)

os.chdir("../")
newfile=os.getcwd()+"/courses.sql"
course = open(newfile, "w")

for x in files:
	path = os.getcwd()+"/sql/%s" % x
	with open(path, "rb") as f:
		s = f.read().splitlines()
	for k in s:
		course.write("%s\n" % k)

print "Wrote %s" % newfile




