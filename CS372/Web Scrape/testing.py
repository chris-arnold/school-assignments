#!/usr/bin/python

import pickle
from sets import Set
import glob
import os
import sys
import time


files=[]
os.chdir("info_html/")

for root, dirnames, filenames in os.walk('.'):
	for x in dirnames:
		files.append(x)
	break

os.chdir("../")
with open('classcategory.txt') as ff:
    subjs = ff.read().splitlines()



'''

t = pickle.load(open("/Users/Chris/Desktop/temp/info/200810/computer/CS.dump", "rb"))

p = pickle.load(open("/Users/Chris/Desktop/temp/info/200910/computer/CS.dump", "rb"))

f = open("CHECK.txt", "a")


t1 = tuple(t)
p1 = tuple(p)
c1 = t1+p1
c = sorted(c1, key=lambda x: x[1])

#dict((x[0], x) for x in L).values()
p1=[]
for x in p:
	p1.append(x[0])
t1=[]
for x in t:
	t1.append(x[0])

'''

for s in subjs:
	s = s.replace("&","")
	c = []
	fi = open("out/%s.txt" % s, "a")
	for f in files:
		try:
			#print "Opening dump for %s" % f
			t = pickle.load(open("/Users/Chris/Desktop/temp/info/%s/computer/%s.dump" % (f, s), "rb"))
			print "Opening dump for %s" % f
			for z in t:
				c.append(z[0])
			c = list(set(c))
		except:
			pass
	c.sort()
	for x in c:
		if x != "Course ID":
			fi.write("%s\n" % x)


#c1=t+p
#c = dict((x[0], x) for x in c1)
#c = list(set(c1))
#c.sort()

#here c has unique course id. IE(MATH 110) from list t and p
#for x in c:
#	fi.write("%s\n" % x)

