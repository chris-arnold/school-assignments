#!/usr/bin/python

import glob
import os
import sys
import time

#semesterClass=["201430","201420","201415","201335","201330","201325","201320","201315","201310"]
semesterCat=["201230","201225","201220","201215","201210","201135","201130","201125","201120","201110","201030","201020","201010","200930","200920","200910","200830","200820","200810"]


for s in semesterCat:
	#print "python getAllClasses.py %s" % s
	os.system("python getAllClasses.py %s" % s)
	time.sleep(15)

'''

for s in semesterCat:
	#print "python getClassBySemester.py %s" % s
	os.system("python getClassBySemester.py %s" % s)
	time.sleep(15)
'''
