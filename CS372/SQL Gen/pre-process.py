#!/usr/bin/python
import glob
import os
import sys
import time
import pickle
import re
#Remove prerequisite listing from Long description and place it in 
#prerequisite column

files=[]

os.chdir("final/computer")

for x in glob.glob("*.dump"):
	files.append(x)

os.chdir("../..")
#print files

#files = ["CS.dump",]

for x in files:
	path = os.getcwd()+"/final/computer/%s" % x
	info = pickle.load( open(path, 'rb'))
	for y in info:
		z = re.split('\s*[Pp]rerequisite.', y[3])
		try:
			y[1] = y[1] + z[1]
		except:
			pass
		y[3] = re.sub(r'([^\s\w\.-]|_)+', '', z[0])
		q = re.split('\s*[Nn]ote.', y[3])
		try:
			y[2] = y[2] + q[1]
		except:
			pass
		y[3] = q[0]
		y[0] = y[0].strip()
		y[1] = y[1].strip()
		y[2] = y[2].strip()
		y[3] = y[3].strip()
		y[4] = y[4].strip()
	human=os.getcwd()+"/clean/human/%s.txt" % x[:-5]
	comp=os.getcwd()+"/clean/computer/%s" % x
	h = open(human, "w")
	c = open(comp, "w")
	for i in info:
		h.write("%s\n" % i)
	pickle.dump(info, c)




#pre process note field, looking for prerequisites and moving them to the right field

#then re-save this and generate sql statements

