#!/usr/bin/python
#define objects and place into the list set
from treelib import *
from collections import Counter
from math import log
import re

credit=[]
columns=[]
info=0.0
tally=Counter()
credcols=['Risk', 'Credit History', 'Debt', 'Collateral', 'Income']
obj1=['high', 'bad', 'high', 'none', '$0 to $15k']
obj2=['high', 'unknown', 'high', 'none', '$15 to $35k']
obj3=['moderate', 'unknown', 'low', 'none', '$15 to $35k']
obj4=['high', 'unknown', 'low', 'none', '$0 to $15k']
obj5=['low', 'unknown', 'low', 'none', 'over $35k']
obj6=['low', 'unknown', 'low', 'adequate', 'over $35k']
obj7=['high', 'bad', 'low', 'none', '$0 to $15k']
obj8=['moderate', 'bad', 'low', 'adequate', 'over $35k']
obj9=['low', 'good', 'low', 'none', 'over $35k']
obj10=['low', 'good', 'high', 'adequate', 'over $35k']
obj11=['high', 'good', 'high', 'none', '$0 to $15k']
obj12=['moderate', 'good', 'high', 'none', '$15 to $35k']
obj13=['low', 'good', 'high', 'none', 'over $35k']
obj14=['high', 'bad', 'high', 'none', '$15 to $35k']

for i in range(1,15):
	credit.append(vars()['obj'+str(i)])

for i in credcols:
	columns.append(credcols.index(i))

tree = Tree()
tallyrisk=Counter()

def subtree(data, columns, parent1, tree):
	print "in subtree"
	print "data: ",data
	print "columns: ",columns
	print "parent: ",parent1
	cols = list(columns)
	if len(data) == 1:		#only 1 object in dataset. risk type here is end of branch
		print "Creating node: ", credit[data[0]][0]+" Risk", credit[data[0]][0]+" Risk", parent1
		print "^^^^^^^^^^^^^^^^^^", data[0],credit[data[0]] ,credit[data[0]][0]
		tree.create_node(credit[data[0]][0]+" Risk", credit[data[0]][0]+" Risk", parent=parent1)
		return
	if len(data) == 0:		#no data in set..should never be called
		print "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!! SHOULD NOT BE HERE"
		#print "END OF LEAFLETT! Appending %s", credit[data[0]]
		#tree.create_node(credit[data[0]], credit[data[0]], parent=parent1)
		return 
	tallyrisk.clear()
	for i in credit:
		if credit.index(i) in data:
			tallyrisk[i[0]] += 1

	if len(tallyrisk) == 1:		#only 1 risk type in dataset. end of branch.
		print "~~~~~~~~~ENDING BRANCH~~~~~~~~~~~", credit[data[0]][0]
		tree.create_node(credit[data[0]][0]+" Risk", credit[data[0]][0]+" Risk", parent=parent1)
		return

	inforisk=0.0
	for i in credit:
		tally[i[0]] += 1
	length = len(credit)
	for i in tally:
		lval = float(tally[i]) / length
		tmp = ( (lval) * log(lval) / log(2))
		inforisk = inforisk - ( (lval) * log(lval) / log(2))

	print "info risk: ",inforisk

	calc=[]		#holds calculations to find max value
	for l in cols:	#calculate entrope for every column in dataset
		tally.clear()
		for i in credit:
			if credit.index(i) in data:
				tally[i[l]] += 1
		info = 0.0
		length = len(credit)
		#container=[]
		#print tally
		#calculate I[C] in info
		for i in tally:
			#container.append(i)
			lval = float(tally[i]) / length
			tmp = ( (lval) * log(lval) / log(2))
			#print i, tmp
			vars()[i]=[]
			info = info - ( (lval) * log(lval) / log(2))
		print credcols[int(l)], info
		calc.append(abs(inforisk-info))

	maximum = min(calc)
	location = calc.index(maximum)
	tally.clear()

	print "Minimum value: ",credcols[cols[location]] ,maximum
	parentnode=credcols[cols[location]]
	tree.create_node(parentnode+'?', parent1+parentnode.lower(), parent=parent1)
	print "location", location
	
	for i in data:
		tally[credit[i][cols[location]]] += 1
	#for i in credit:
	#	print i, credit.index(i)
	#	if credit.index(i) in data:
	#		tally[i[cols[location]]] += 1
	#if parentnode == 'Debt':	#for some reason if this is true, infinite recursion..
	#	return
		#print i
	print "Tally: ",tally
	for i in tally:
		tree.create_node(i, parent1+parentnode+i.lower(), parent=parent1+parentnode.lower())
		vars()[i]=[]
		#vars()[i.replace(" ","")+'col']=list(cols)
		#create new list sorted on values in i
		#pass these values into this function as a subtree

	# from here on, need to generate lists for subtrees containing values 
	#held in location cols[location] in credit rows specifed by data
	#tree.show()
	#tally.clear()
	#for i in credit:
	#	tally[i[cols[location]]] += 1
	print "**********************************"
	#print data
	for i in data:
		#print credit[i]
		for j in tally:
			#print "trying to match:",credit[i][cols[location]], j
			if credit[i][cols[location]] == j:
				#print "TRUE!!"
				print "matched: ",credit[i][cols[location]], j
				vars()[j].append(credit.index(credit[i]))

	print "removing location:", location
	#for i in tally:
	#	del vars()[i.replace(" ","")+'col'][location]
	del cols[location]
	#cols.remove(location)
	#print cols

	if len(cols) >= 1:
		print "TALLY: ", tally
		for i in tally.keys():			#will print values to go to subtree as list
			print "TALLY[i]: and len(tally:) ", tally[i], len(tally)
			if len(tally) < 1:		
				print "#######TALLY = 0##########", tally
				return
			#if tally[i] >= 1:	
			print "Call subtree for", i, vars()[i]
			subtree(vars()[i], cols, parent1+parentnode+i.lower(), tree)	
			print "BACK!!!. from parentnode",parentnode, tally[i], tally
	else:
		#assign risk type to each tally for location
		print "@@@@@@@@@len(cols)=0@@@@@@@@@@", data, tally
		return
	return
'''
END DEF subtree
'''

columns.remove(credcols.index('Risk'))

print columns

inforisk=0.0
for i in credit:
	tally[i[0]] += 1
length = len(credit)
for i in tally:
	lval = float(tally[i]) / length
	tmp = ( (lval) * log(lval) / log(2))
	inforisk = inforisk - ( (lval) * log(lval) / log(2))

print "info risk: ",inforisk

#get unique Risk values and count them.
calc=[]		#holds calculations to find max value
for l in columns:	#calculate entrope for every column in dataset
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
	print credcols[int(l)], info
	calc.append(abs(inforisk-info))
tally.clear()
for l in columns:
	tally[l] += 1

maximum = min(calc)
loc = calc.index(maximum)
print "loc: ", loc
c=0
for i in columns:
	print i, c, loc
	if c == loc:
		location = loc
		print "Location ", location
	else:
		c = c + 1

tally.clear()

print "MINIMUM value: ",credcols[columns[location]] ,maximum
parentnode=credcols[columns[location]]
tree.create_node(parentnode+'?', parentnode.lower())
print "location", location
print "Columns location: ", credcols[columns[location]]
for i in credit:
	tally[i[columns[location]]] += 1
	#print i

for i in tally:
	tree.create_node(i, parentnode+i.lower(), parent=parentnode.lower())
	vars()[i]=[]
	#create new list sorted on values in i
	#pass these values into this function as a subtree

tree.show()

#print container
for i in credit:
	for j in tally:
		print i[columns[location]], j
		if i[columns[location]] ==  j:
			print "Matched %s, %s", i[columns[location]], j
			vars()[j].append(credit.index(i))
			#print i, j

print "removing location:", location
print columns
del columns[location]

for j in tally:
	print vars()[j]

for i in tally.keys():			#will print values to go to subtree as list
	print "Calling subtree"
	print vars()[i], columns, parentnode+i
	subtree(vars()[i], columns, parentnode+i, tree)	


print "FINAL TREE"
tree.show()

