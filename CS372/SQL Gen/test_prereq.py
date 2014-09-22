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
complicated=[]
credit=[]
title=["Course", "Prereq"]
prereq.append(title)
complicated.append(title)
credit.append(title)
#files = ["CS.dump",]
count = 0
count1 = 0
count2 = 0
path = os.getcwd()+"/prereq.dump"
info = pickle.load( open(path, 'rb'))
for y in info:
	if 'or' not in y[1] and 'and' not in y[1] and len(y[1]) < 11:
		if y[1] == "BIOL275":
			y[1] = "BIOL 275"
		prereq.append(y)
		count = count + 1
	else:
		if 'credit hours' in y[1]:
			credit.append(y)
			count1 = count1 + 1
		else:
			complicated.append(y)
			count2 = count2 + 1

human=os.getcwd()+"/prereq/single.txt"
comp=os.getcwd()+"/prereq/single.dump"
h = open(human, "w")
c = open(comp, "w")

human1=os.getcwd()+"/prereq/complicated.txt"
comp1=os.getcwd()+"/prereq/complicated.dump"
h1 = open(human1, "w")
c1 = open(comp1, "w")

human2=os.getcwd()+"/prereq/credit.txt"
comp2=os.getcwd()+"/prereq/credit.dump"
h2 = open(human2, "w")
c2 = open(comp2, "w")

for i in prereq:
	h.write("%s\n" % i)
pickle.dump(prereq, c)

for i in complicated:
	h1.write("%s\n" % i)
pickle.dump(complicated, c1)

for i in credit:
	h2.write("%s\n" % i)
pickle.dump(credit, c2)

print "%d classes with simple prerequisites" % count
print "%d classes with credit hour prerequisites" % count1
print "%d classes with other complex prerequisites" % count2

#pre process note field, looking for prerequisites and moving them to the right field

#then re-save this and generate sql statements

