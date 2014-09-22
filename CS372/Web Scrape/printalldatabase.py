#!/usr/bin/python

import mysql.connector

config = {
  'user': 'root',
  'password': 'supersecret',
  'host': '172.16.1.88',
  'database': 'CS372',
  'raise_on_warnings': True,
}

config1 = {
	'user': 'root',
	'password': 'supersecret',
	'host': '204.83.93.143',
	'port': '13306',
	'database': 'CS372',
	'raise_on_warnings': True,
}

dbconnection = mysql.connector.connect(**config1)
cursor = dbconnection.cursor()

tables=[]
query = 'show tables'
cursor.execute(query)
for row in cursor:
	tables.append(row)

for element in tables:
	query = "select * from %s" % element
	print query
	cursor.execute(query)
	for row in cursor:
		print row
	print

cursor.close()
dbconnection.close()

'''query = "select * from class_listing"
cursor.execute(query)
existing=[]
pre=[]

for cid, subj, num, desc in cursor:
	print "ID: %s, SUBJ: %s%s: %s" % (cid, subj, num, desc)
	existing.append("%s" % (cid))

print "existing list:"
print existing

query = "select * from subjects"
cursor.execute(query)
for row in cursor:
	print row
'''
