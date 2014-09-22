#!/usr/bin/python

import sys
import re
import os
from itertools import islice
import pickle

'''
looks in html dir for passed in file name. Extracts
['Short Description', 'CRN', 'Course ID', 'Section Number']
from the html file, re-orders and writes it in data/filename.txt
Also extracts additional information about class times/locations and final exam info

'''
try:
	semester = sys.argv[2]
except:
	print "Not enough arguements. batch_scrape_semester.py semesterNo"
	exit(0)


if not os.path.exists(os.getcwd()+"/data/%s/human" % semester):
	os.makedirs(os.getcwd()+"/data/%s/human" % semester)
if not os.path.exists(os.getcwd()+"/data/%s/computer" % semester):
	os.makedirs(os.getcwd()+"/data/%s/computer" % semester)

y = sys.argv[1]
x1 = y.split(".")
path=os.getcwd()+"/data/%s/human/%s.txt" % (semester, x1[0])
path1=os.getcwd()+"/data/%s/computer/%s.dump" % (semester, x1[0])
dump = open(path1, "wb")

temp = open(path, "w")
counter = 0
inpath=os.getcwd()+"/html/%s/%s" % (semester, sys.argv[1])
		
with open(inpath, "rb") as f:
	main=[]
	header = ['Course ID', 'Section Number', 'CRN', 'Short Description', 'Type', 'Time', 'Days', 'Location', 'Date Range', 'Schedule Type', 'Instructors', 'Final Exam Time', 'Final Exam Day', 'Final Exam Date']
	main.append(header)
	while True:
		line = f.readline()
		if not line: break
		#for line in f:
		if 'scope="colgroup"' in line:
			counter = counter + 1
			x = line.split('>')
			y = x[2].split('<')
			y.pop()
			x = y[0].split(' - ')
			x[3], x[0] = x[0], x[3]
			x[1], x[2] = x[2], x[1]
			x[0], x[1] = x[1], x[0]
			#main.append(x)
			#print "additional read"
			line = f.readline()
			while '<TH CLASS="ddheader" scope="col" >Instructors</TH>' not in line:
				line = f.readline()

			for i in range(0,3):
				line = f.readline()		#dont care about these 

			while '<TD CLASS="dddefault">' in line:
				z = line.split('>')
				y = z[1].split('<')
				y.pop()
				y = ''.join(y)
				y = y.replace("(","")
				y = y.replace("&nbsp;", " ")
				x.append(y)
				line = f.readline()
			line = f.readline()
			if '<tr>' or '<TR>' in line:
				f.readline()
				#extract time and then day of the week and date of the final
				for i in range(0,4):	
					line = f.readline()
					if i == 2: 
						continue
					z = line.split('>')
					y = z[1].split('<')
					y.pop()
					y = ''.join(y)
					x.append(y)
			main.append(x)


for i in main:
	temp.write("%s\n" % i)

pickle.dump(main, dump)

print "Found %d %s classes. Wrote to file %s" % (counter, x1[0], path)
