#!/usr/bin/python
import binascii
import random
import string
'''
CS 435 Project Part 1
Due October 21
Chris Arnold
200276366

Web interface available for demonstration purpose of KSA, PRGA and IPRGA is available. Link is in part 1 of the project report

This file implements functions required for RC4 encryption and decryption.

Verified with the following:
Test cases:
key 	| plaintext			| ciphertext
pwd12 	| Math 310 Proves!	| 6CA86FE3CBC33C162595C3E78B9C97BC
Key		| Plaintext			| BBF316E8D940AF0AD3
Wiki	| pedia				| 1021BF0420
Secret 	| Attack at dawn	| 45A01F645FC35B383552544B9BF5

When running though the command line, option 2 will allow you to run various different test cases to further verify the functionality
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'''
#This function performs PRGA on a character input. Also acts as the inverse due to the properties of the encryption
#input -> keystates, i, j, character to be encrypted
#output -> new keystate, new i, new i, encrypted character
def PRGA_C(S, i, j, Pk):
	i = (i+1) % 256
	j = (j+S[i]) % 256
	S[i], S[j] = S[j], S[i]
	return (S,i,j,chr(ord(Pk) ^ S[ (S[i] + S[j]) % 256 ]))

#The given PRGA function. Returns the modified State, i and j values. 
#input -> keystate, i, j
#output -> new keystate, new i, new j
def PRGA(S, i, j):
	i = (i+1) % 256
	j = (j+S[i]) % 256
	S[i], S[j] = S[j], S[i]
	return (S,i,j)

#Take an input key
#Return len 256 list scrambled by KSA
#Tested with:
#http://www.math.washington.edu/~nichifor/310_2008_Spring/Pres_RC4%20Encryption.pdf
def KSA(key):
	S=range(0,256)
	keylength = len(key)
	j=0
	for i in range(0,256):
		try:
			j = (j + S[i] + ord(key[i % keylength])) % 256
		except:
			j = (j + S[i] + int(key[i % keylength])) % 256
		S[i], S[j] = S[j], S[i]

	return S

#given IPRGA algorithm. Reverts action done by PRGA
#input -> keystate, i, j
#output -> new keystate, new i, new j
def IPRGA(S, i, j):
	S[i], S[j] = S[j], S[i]
	j = (j-S[i]+256) % 256
	i = (i-1) % 256
	return (S,i,j)

#will encrypt plaintext text, with key key and return the ciphertext
#input -> key, plaintext
#output -> ciphertext
def encrpyt(key, text):
	retval=""
	S=KSA(key)
	out=(S,0,0,"i")
	for x in range(0,len(text)):
		out=out[:3]+(text[x],)
		out=PRGA_C(*out)
		retval+=out[3]
	return retval

if __name__ == '__main__':
	mode=int(raw_input("Choose one of the follwing modes:\n\t1: Key & Plaintext input\n\t2: Test mode\nEnter choice now:"))
	if mode == 1:
		key=raw_input("Enter the key: ")
		userin=raw_input("Enter test case: ")
		crypt = encrpyt(key, userin)
		
		print "Hex encoded ciphertext:", binascii.hexlify(crypt)
		print "Converting back to plain text"

		out=(KSA(key),0,0,"k")
		plain = encrpyt(key, crypt)

		print plain
	elif mode == 2:
		count=0
		print "This mode will generate a number of test cases based on your input. It will run PRGA and IPRGA a random number of times, and return a successful test if we get back to the initial state value."
		testruns=int(raw_input("Enter the number of test runs to generate: "))
		keylen=int(raw_input("Enter the length of key to be used: "))
		maxruns=int(raw_input("Enter the max number of PRGA iterations to test: "))
		print "Test Number\tRuns\tKey"+" "*keylen+"\tOutput"
		for x in range(0,testruns):
			key=''.join(random.choice(string.ascii_uppercase + string.digits + string.ascii_lowercase) for _ in range(keylen))
			KState=KSA(key)
			out=(KSA(key), 0, 0)
			runs=random.randrange(1,maxruns)
			print x+1,'\t\t',runs,'\t',key,
			for y in range(0, runs):
				out = PRGA(*out)
			for y in range(0,runs):
				out = IPRGA(*out)
			if KState == out[0]:
				count += 1
				print "\tTest Successful"
			else:
				print "\tTest Failed"
		print "%d/%d test cases were successful" % (count, testruns)
	else:
		print "Invalid input. Exiting program"


