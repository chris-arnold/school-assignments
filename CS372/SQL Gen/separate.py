#!/usr/bin/python
import glob
import os
import sys
import time
import pickle
import re
#Remove prerequisite listing from Long description and place it in 
#prerequisite column

#print files
prereq=[]

andList=[]
orList=[]
other=[]
title=["Course", "Prereq"]

andList.append(title)
orList.append(title)
other.append(title)

#files = ["CS.dump",]

path = os.getcwd()+"/prereq/complicated.dump"
info = pickle.load( open(path, 'rb'))
for y in info:
	x = y[1].split(" ")
	if len(x) == 5:
		if 'and' in x:
			andList.append(y)
		if 'or' in x:
			orList.append(y)
	else:
		other.append(y)

human=os.getcwd()+"/prereq/andlist.txt"
comp=os.getcwd()+"/prereq/andlist.dump"
h = open(human, "w")
c = open(comp, "w")

human1=os.getcwd()+"/prereq/orlist.txt"
comp1=os.getcwd()+"/prereq/orlist.dump"
h1 = open(human1, "w")
c1 = open(comp1, "w")

human2=os.getcwd()+"/prereq/other.txt"
comp2=os.getcwd()+"/prereq/other.dump"
h2 = open(human2, "w")
c2 = open(comp2, "w")

for i in andList:
	h.write("%s\n" % i)
pickle.dump(andList, c)

for i in orList:
	h1.write("%s\n" % i)
pickle.dump(orList, c1)

for i in other:
	h2.write("%s\n" % i)
pickle.dump(other, c2)


#pre process note field, looking for prerequisites and moving them to the right field

#then re-save this and generate sql statements

