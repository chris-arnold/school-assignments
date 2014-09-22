#!/usr/bin/python

import pickle
from sets import Set
import glob
import os
import sys
import time


files=[]
semesters=[]

os.chdir("out/")

for x in glob.glob("*.txt"):
	files.append(x)

os.chdir("../")

os.chdir("info_html/")

for root, dirnames, filenames in os.walk('.'):
	for x in dirnames:
		semesters.append(x)
	break
semesters.sort(reverse=True)

os.chdir("../")

for z in files:
	final=[]
	desc=[]
	short=[]
	finpath = os.getcwd()+"/final/human/%s" % z
	fin = open(finpath, "w")
	with open('out/%s' % z) as ff:
		courses = ff.read().splitlines()
	for c in courses:
		desc=[]
		short=""
		found1 = False
		found2 = False
		for s in semesters:
			if not found1:
				try:
					path = os.getcwd()+"/info/%s/computer/%s.dump" % (s, z[:-4])
					t = pickle.load(open(path,"rb"))
					for k in t:
						if k[0] == c:
							desc = k
							found1 = True
							break
				except:
					#print "Non Existant %s" % path
					pass
			if not found2:
				try:
					path = os.getcwd()+"/data/%s/computer/%s.dump" % (s, z[:-4])
					t = pickle.load(open(path, "rb"))
					for k in t:
						if k[0] == c:
							short = k[3]
							found2 = True
							break
				except:
					#print "Non Existant %s" % path
					pass

		desc.append(short)
		final.append(desc)

	for i in final:
		fin.write("%s\n" % i)
	dump = os.getcwd()+"/final/computer/%s.dump" % z[:-4]
	dumpdir = open(dump, "w")
	pickle.dump(final, dumpdir)




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

'''
#c1=t+p
#c = dict((x[0], x) for x in c1)
#c = list(set(c1))
#c.sort()

#here c has unique course id. IE(MATH 110) from list t and p
#for x in c:
#	fi.write("%s\n" % x)

