#!/usr/bin/python

import glob
import os
import sys
import time

try:
	semester = sys.argv[1]
except:
	print "Not enough arguements. batch_scrape_info.py semesterNo"
	exit(0)

files=[]
os.chdir("info_html/%s" % semester)

for f in glob.glob("*.html"):
	files.append(f)

os.chdir("../..")
if not os.path.exists(os.getcwd()+"/info"):
	os.makedirs(os.getcwd()+"/info")

epath=os.getcwd()+"/info/errors.txt"
errors = open(epath, "w")

errors.write("Date: %s\n\n" % time.strftime("%c"))
errors.close()

for f in files:
	os.system("python additional_scrape.py %s True %s" % (f, semester))

