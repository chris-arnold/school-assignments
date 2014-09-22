#!/usr/bin/python

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

for f in files:
	os.system("python batch_scrape_info.py %s" % f)
