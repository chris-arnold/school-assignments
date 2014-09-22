#!/usr/bin/python
import re
import StringIO
import os
from mechanize import Browser
import mechanize
import cookielib
import time
import sys


try:
	semester = sys.argv[1]
except:
	print "Not enough arguements. getClassBySemester.py semesterNo"
	exit(0)

classtype = open('classcategory.txt', 'w')
class_type=[]

browser = Browser()
browser.addheaders = [('User-agent', 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1) Gecko/2008071615 Fedora/3.0.1-1.fc9 Firefox/3.0.1')]

# Cookie Jar
cj = cookielib.LWPCookieJar()
browser.set_cookiejar(cj)
browser.set_handle_robots(False)

browser.open("https://banner.uregina.ca/prod/sct/bwckschd.p_disp_dyn_sched") #to get semester specifics
browser.select_form(nr=0)
item = browser.find_control(id="term_input_id").get("%s" % semester)
item.selected = True

response = browser.submit()
content = response.read()

flag = 0

for line in StringIO.StringIO(content):
	if flag == 0:
		if '<SELECT NAME="sel_subj" SIZE="10" MULTIPLE ID="subj_id">' in line:
			flag = 1
	else:
		if '</SELECT>' not in line:
			x = line.split('"')
			try:
				classtype.write(x[1])
				classtype.write('\n')
				class_type.append(x[1])
			except:
				break

#make sure the directory for this semester exists
if not os.path.exists(os.getcwd()+"/html/%s" % semester):
	os.makedirs(os.getcwd()+"/html/%s" % semester)

for c in class_type:
	time.sleep(5)
	f = ''.join(c)
	path=os.getcwd()+"/html/%s/%s.html" % (semester, f.replace('&', ''))
	temp = open(path, "w")
	browser.select_form(nr=0)
	item = browser.find_control(id="subj_id").get("%s" % c)
	item.selected = True
	response = browser.submit()
	content = response.read()
	temp.write(content)
	print "Wrote %s" % path
	temp.close()
	time.sleep(5)
	browser.back()
