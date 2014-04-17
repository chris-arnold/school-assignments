#!/usr/bin/python
#column names stored in credcols
#dataset stored in credit as a list of lists
#will generate decision tree for Risk factor according to dataset credit
from treelib import *
from collections import Counter
from math import log

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

sort=-1
print credcols
user=raw_input("Choose Column to create Decision tree around:(type the name)")
for i in credcols:
	if user == i:
		sort=credcols.index(i)

if sort == -1:
	print "Invalid input. Choosing default value: ", credcols[0]
	sort=0


tree = Tree()
tallyrisk=Counter()

def subtree(data, columns, parent1, tree):
	cols = list(columns)
	if len(data) == 1:		#only 1 object in dataset. risk type here is end of branch
		print "len(data) is 1, ", parent1, credit[data[0]][sort]+" "+credcols[sort]
		tree.create_node(credit[data[0]][sort]+" "+credcols[sort], credit[data[0]][sort]+" "+credcols[sort], parent=parent1)
		return
	if len(data) == 0:		#no data in set..should never be called
		print "ERROR! SHOULD NOT BE HERE No data passed."
		return 
	tallyrisk.clear()
	for i in credit:
		if credit.index(i) in data:
			tallyrisk[i[sort]] += 1

	if len(tallyrisk) == 1:		#only 1 risk type in dataset. end of branch.
		print "Only 1 risk type. end of branch", credit[data[0]][sort]+" "+credcols[sort]
		tree.create_node(credit[data[0]][sort]+" "+credcols[sort], credit[data[0]][sort]+" "+credcols[sort], parent=parent1)
		return

	inforisk=0.0
	for i in credit:
		tally[i[sort]] += 1
	length = len(credit)
	for i in tally:
		lval = float(tally[i]) / length
		tmp = ( (lval) * log(lval) / log(2))
		inforisk = inforisk - ( (lval) * log(lval) / log(2))

	calc=[]		#holds calculations to find max value
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
				print "Len tally less than 1 for parent, ", parent1
				return
			subtree(vars()[i], cols, parent1+parentnode+i.lower(), tree)
	print "ending subtree @ parent", parent1, len(cols), data
	return
'''
END DEF subtree
'''

columns.remove(sort)

inforisk=0.0
for i in credit:
	tally[i[sort]] += 1
length = len(credit)
for i in tally:
	lval = float(tally[i]) / length
	tmp = ( (lval) * log(lval) / log(2))
	inforisk = inforisk - ( (lval) * log(lval) / log(2))

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
tree.create_node(parentnode+'?', parentnode.lower())

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

for i in tally.keys():			#will print values to go to subtree as list
	subtree(vars()[i], columns, parentnode+i, tree)	

print "FINAL TREE"
tree.show()

