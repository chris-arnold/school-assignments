#!/usr/bin/python

import glob
import os
import sys

try:
	semester = sys.argv[1]
except:
	print "Not enough arguements. batch_scrape_semester.py semesterNo"
	exit(0)

files=[]
os.chdir("html/%s" % semester)

for f in glob.glob("*.html"):
	files.append(f)

os.chdir("../..")

for f in files:
	os.system("python scrape_semester.py %s %s" % (f, semester))