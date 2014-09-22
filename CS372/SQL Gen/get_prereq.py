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
prereq=[]
title=["Course", "Prereq"]
prereq.append(title)
#files = ["CS.dump",]
count = 0
for x in files:
	path = os.getcwd()+"/final/computer/%s" % x
	info = pickle.load( open(path, 'rb'))
	for y in info:
		if y[1] != '':
			n=[]
			n.append(y[0])
			n.append(y[1])
			prereq.append(n)
			count = count + 1

human=os.getcwd()+"/prereq.txt"
comp=os.getcwd()+"/prereq.dump"
h = open(human, "w")
c = open(comp, "w")


for i in prereq:
	h.write("%s\n" % i)
pickle.dump(prereq, c)

print "%d classes with prerequisites" % count


#pre process note field, looking for prerequisites and moving them to the right field

#then re-save this and generate sql statements

