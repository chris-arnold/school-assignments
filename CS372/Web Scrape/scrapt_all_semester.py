#!/usr/bin/python

import glob
import os
import sys
import time

#scrape all semester
semesterList = ["201430","201420","201415", "201410", "201335","201330","201325","201320","201315","201310"]

for semester in semesterList:
	files=[]
	os.chdir("html/%s" % semester)

	for f in glob.glob("*.html"):
		files.append(f)

	os.chdir("../..")
	if not os.path.exists(os.getcwd()+"/data"):
		os.makedirs(os.getcwd()+"/data")

	epath=os.getcwd()+"/data/errors.txt"
	errors = open(epath, "w")

	errors.write("Date: %s\n\n" % time.strftime("%c"))
	errors.close()

	for f in files:
		os.system("python scrape_semester.py %s %s" % (f, semester))

