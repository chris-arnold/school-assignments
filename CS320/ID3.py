#!/usr/bin/python
'''
column names stored in credcols
dataset stored in credit as a list of lists
will generate decision tree for Risk factor according to dataset credit
for CS 320, Assignment #3, Question 1
By: Chris Arnold
input file: All items are comma separated
first row is title of columns
First Column is the class that the decicion tree will be generated for

'''
from treelib import *		#for tree structure
from collections import Counter
from math import log
import sys				#for cmd line args

credit=[]
columns=[]
info=0.0
tally=Counter()

if len(sys.argv) != 2:
	print "Invalid Command."
	quit()
with open(sys.argv[1], 'r') as f:
	print "Opening ", sys.argv[1]
	header = f.readline().replace("\n","")
	print header
	credcols=header.split(",")
	for line in f:
		line=line.replace("\n","")
		print line
		obj=line.split(",")
		credit.append(obj)
f.closed

for i in credcols:
	columns.append(credcols.index(i))

tree = Tree()
tallyrisk=Counter()

def subtree(data, columns, parent1, tree):
	cols = list(columns)
	if len(data) == 1:		#only 1 object in dataset. risk type here is end of branch
		tree.create_node(credit[data[0]][0]+" "+credcols[0], credit[data[0]][0]+" "+credcols[0], parent=parent1)
		return
	if len(data) == 0:		#no data in set..should never be called
		print "ERROR! SHOULD NOT BE HERE No data passed."
		return 
	tallyrisk.clear()
	for i in credit:
		if credit.index(i) in data:
			tallyrisk[i[0]] += 1

	if len(tallyrisk) == 1:		#only 1 risk type in dataset. end of branch.
		tree.create_node(credit[data[0]][0]+" "+credcols[0], credit[data[0]][0]+" "+credcols[0], parent=parent1)
		return

	inforisk=0.0
	for i in credit:
		tally[i[0]] += 1
	length = len(credit)
	for i in tally:
		lval = float(tally[i]) / length
		tmp = ( (lval) * log(lval) / log(2))
		inforisk = inforisk - ( (lval) * log(lval) / log(2))

	calc=[]		#holds calculations to find min value
	for l in cols:	#calculate gain for every column in dataset
		tally.clear()
		for i in credit:
			if credit.index(i) in data:
				tally[i[l]] += 1
		info = 0.0
		length = len(credit)

		for i in tally:
			lval = float(tally[i]) / length
			tmp = ( (lval) * log(lval) / log(2))
			vars()[i]=[]
			info = info - ( (lval) * log(lval) / log(2))
		if inforisk-info == 0:		#dont want no gain. set high to never choose
			calc.append(999)
		else:
			calc.append(abs(inforisk-info))

	maximum = min(calc)
	location = calc.index(maximum)
	tally.clear()
	parentnode=credcols[cols[location]]
	tree.create_node(parentnode+'?', parent1+parentnode.lower(), parent=parent1)
	
	for i in data:
		tally[credit[i][cols[location]]] += 1

	for i in tally:
		tree.create_node(i, parent1+parentnode+i.lower(), parent=parent1+parentnode.lower())
		vars()[i]=[]

	for i in data:
		for j in tally:
			if credit[i][cols[location]] == j:
				vars()[j].append(credit.index(credit[i]))

	del cols[location]

	if len(cols) >= 1:
		for i in tally.keys():			#will print values to go to subtree as list
			if len(tally) < 1:		
				return
			subtree(vars()[i], cols, parent1+parentnode+i.lower(), tree)
	return
'''
END DEF subtree
'''
#BEGIN MAIN. FIND ROOT OF DECISION TREE

columns.remove(0)

inforisk=0.0
for i in credit:
	tally[i[0]] += 1
length = len(credit)
for i in tally:
	lval = float(tally[i]) / length
	tmp = ( (lval) * log(lval) / log(2))
	inforisk = inforisk - ( (lval) * log(lval) / log(2))

#get unique Risk values and count them.
calc=[]		#holds calculations to find min value
for l in columns:	#calculate gain for every column in dataset
	tally.clear()
	for i in credit:
		tally[i[l]] += 1
	info = 0.0
	length = len(credit)
	container=[]
	for i in tally:
		container.append(i)
		lval = float(tally[i]) / length
		tmp = ( (lval) * log(lval) / log(2))
		vars()[i]=[]
		info = info - ( (lval) * log(lval) / log(2))
	if inforisk-info == 0:		#dont want no gain. set high to never choose
		calc.append(999)
	else:
		calc.append(abs(inforisk-info))

tally.clear()
for l in columns:
	tally[l] += 1

maximum = min(calc)
loc = calc.index(maximum)
c=0
for i in columns:
	if c == loc:
		location = loc
	else:
		c = c + 1

tally.clear()

parentnode=credcols[columns[location]]
tree.create_node(parentnode+'?', parentnode.lower())	#create root of tree

for i in credit:
	tally[i[columns[location]]] += 1

for i in tally:
	tree.create_node(i, parentnode+i.lower(), parent=parentnode.lower())
	vars()[i]=[]

for i in credit:
	for j in tally:
		if i[columns[location]] ==  j:
			vars()[j].append(credit.index(i))

del columns[location]

for i in tally.keys():			#call subtree for each generated subtree of root
	subtree(vars()[i], columns, parentnode+i, tree)	

print "Decision Tree for", credcols[0], "Assessment."
tree.show()		#print the pretty tree
