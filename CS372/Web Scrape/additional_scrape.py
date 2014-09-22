#!/usr/bin/python

import sys
import re
import os
from itertools import islice
import pickle
import time

'''
Gets course Description and Prereqs

'''
try:
	if sys.argv[2] == "False":
		show_desc = False
	else:
		show_desc = True
	semester = sys.argv[3]
except:
	print "Not enough arguements. additional_scrape.py input_file show_desc? semesterNo"
	exit(0)



#make sure the directory for this semester exists
if not os.path.exists(os.getcwd()+"/info/%s/human" % semester):
	os.makedirs(os.getcwd()+"/info/%s/human" % semester)
if not os.path.exists(os.getcwd()+"/info/%s/computer" % semester):
	os.makedirs(os.getcwd()+"/info/%s/computer" % semester)
epath=os.getcwd()+"/info/errors%s.txt" % semester
errors = open(epath, "a")

y = sys.argv[1]
x1 = y.split(".")
path=os.getcwd()+"/info/%s/human/%s.txt" % (semester, x1[0])
path1=os.getcwd()+"/info/%s/computer/%s.dump" % (semester, x1[0])
dump = open(path1, "wb")
temp = open(path, "w")
counter = 0
inpath=os.getcwd()+"/info_html/%s/%s" % (semester, sys.argv[1])
		
with open(inpath, "rb") as f:
	main=[]
	header = ['Course ID', 'PreReq', 'Note']
	if show_desc:
		header.append('Long Description')
	main.append(header)
	while True:
		line = f.readline()
		if not line: break
		#for line in f:
		if 'scope="colgroup"' in line:
			row=[]
			counter = counter + 1
			x = line.split('>')
			y = x[2].split('<')
			y.pop()
			x = y[0].split(' - ')
			row.append(x[0])
			#x[3], x[0] = x[0], x[3]
			#x[1], x[2] = x[2], x[1]
			#x[0], x[1] = x[1], x[0]
			#main.append(x)
			#print "additional read"
			#here we have course ID in row[0]
			while '<TD CLASS="ntdefault">' not in line:
				line = f.readline()
			desc = f.readline()
			desc = desc.replace('\n', '')
			#row.append(line)		#this is class description
			line = f.readline()

			try:
				if '<BR>' not in line:
					if 'Prerequisite' in line:
						try:
							x = line.split(':')
							y = ''.join(x[1].split('*'))
						except:
							print "Initial Prerequisite split fail. Trying alternate..."	
							x = line.split('-')
							y = ''.join(x[1].split('*'))
							print "Alternate succeeded."
						y = y.replace('\n', '')
						row.append(y.strip())
						line = f.readline()
					else:
						row.append('')
					if 'Note:' in line:
						x = line.split(':')
						y = ''.join(x[1].split('*'))
						y = y.replace('\n', '')
						row.append(y.strip())
					else:
						row.append('')
				else:
					row.append('')
					row.append('')
			except:
				print "Manual extract required for class %s" % row[0]
				errors.write("Manual extract required for prerequisites and notes for semester %s, class %s\n" % (semester, row[0]))
				row.append('')
				row.append('')

				#class has additional notes like prereq or notes

			#while 'Attributes' not in line:
			#	line = f.readline()
			#	if 'scope="colgroup"' in line:
			#		break
				

			#x = line.split('>')
			#print len(x)
			#if len(x) == 1:
			#	print line
			#	print x
			#y = ''.join(x[2])
			#row.append(y)
			if show_desc:
				row.append(desc)

			main.append(row)


for i in main:
	temp.write("%s\n" % i)

pickle.dump(main, dump)

print "Found %d %s classes. Wrote to file %s" % (counter, x1[0], path)
