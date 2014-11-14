#!/usr/bin/python
from RC4 import *
from  RC4_BHF import *
import re
'''
CS 435 Project Part 2
Due December 4
Chris Arnold
200276366

Function definitions for client.py and server.py
Function names are self explanatory, with I/O & requirements listed above their definitions.
'''

#input the sequence counter, data, and hash value. Will error check lengths
#Contains almost all length checking. If package size becomes incorrect, should be caught here.
#This is a fatal error, and will terminate runtime
#output a string of length 272 bytes. The package
def merge_package(sc, data, hv):
	assert (len(sc)==4), "Invalid Sequence Counter Length"
	assert (len(data)==252), "Invalid Data Segment Length"
	assert (len(hv)==16), "Invalid Hash Value Length"
	return ''.join([sc, data, hv])		#since each part is correct len, output will also be

#input the package
#return tuple of sequence counter, data segment, hash value
def expand_package(package):
	return (package[:4],package[4:256],package[-16:])

#input - data(padded)
#should check data looking for padding. If padding is detected, it should be removed. 
#output - data with padding stripped off

#this should also remove the padding, and send a response of if it detected end of message padding.
#currently just detects the padding. 
def remove_padding(data):
	r1 = re.compile("\x80\x00+$")
	if r1.search(data):
		print "Last package",
		if data[len(data)-1] == "\x80":
			data = data[:len(data)]
		else:
			for x in reversed(range(0,len(data)-1)):
				if data[x] == "\x00":
					data = data[:x]
				else:
					break
			data = data[:len(data)-1]
	return data

#align the keystate to correct position according to SC
#return the aligned state
def state_aligner(State, SC):
	if State[3] == SC:		#state aligned. No work required
		return State
	S=State[:3]
	if State[3] < SC:		#must adjust forward
		diff = (SC - State[3]) * 268		#each SC does 268 bytes of enc/dec. num of IPRGA to run
		for x in range(0,diff):
			S = PRGA(*S)
	else:					#must adjust in reverse
		diff = (State[3] - SC) * 268
		for x in range(0,diff):
			S = IPRGA(*S)
	return S + (SC,)

#Takes in 268 byte data and a State. Encrypts data with the given state
#Returns encrypted data and Resultant State
def RC4_Encrypt(data, State):
	assert (len(data)==268), "RC4_Encrypt requires 268 bytes of data"
	out=State[:3]
	retVal=""
	for x in data:
		out=out[:3] + (x,)
		out=PRGA_C(*out)
		retVal+=out[3]
	newState= out[:3] + (State[3]+1,)		#update the state.
	return (retVal,newState)

#input the entire message, and the encryption key, keystate tuple, and the offset
#output a list of packages to be send to the receiver
def generate_packages(message, key, State, offset):
	packageList=[]
	sc=0
	message = padding_Function(message,252,'m')
	segments=[message[i:i+252] for i in range(0,len(message),252)]		#split input into segments of 252 bytes
	for data in segments:
		State = State[:3] + (sc,)		#set sequence counter in state
		sequence = str(sc).zfill(4)		#convert sc to string. Fill to len 4
		hashval = RC4_BHF(sequence+data,offset)
		encMsgTup = RC4_Encrypt(data+hashval,State)
		encMsg = encMsgTup[0]			#save the encrypted msg. This contains both the data & hash portions (268 bytes)
		State = encMsgTup[1]			#save updated state
		packageList.append(merge_package(sequence, encMsg[:252], encMsg[252:268])) #Create the package and append to list of completed packages
		sc = sc+1
	return packageList

#Takes a package, splits it up, decrypts it, and checks hash value
#input - a package, a state, the offset
#output - the package number, the decrypted message, a state
def decrypt_package(package,State,offset):
	expack = expand_package(package)
	package_number = int(expack[0])
	State = state_aligner(State, package_number)
	ret = RC4_Encrypt(expack[1]+expack[2],State)
	State = ret[1]			#save returned state
	msg=ret[0][:252]
	hv=ret[0][-16:]
	hashcheck=RC4_BHF(expack[0]+msg,offset)
	if (hashcheck!=hv):
		print "Hash check failed." # HashCheck:", hashcheck.encode('string_escape'), "Hash Val:", hv.encode('string_escape')
		return (package_number, "Hash Check failed\n", State)
		#exit()			#if hashes don't match, quit program
	else:
		print "Hash check passed. Package",package_number,"received."

	return (package_number, remove_padding(msg), State)

'''
Input - List of package strings, the key
responsible for receiving the packages, calling decrypt_package on packages
should determine what the last package of the message is based upon padding in decrypted message
assemble decrypted messages from packages into the final readable message
will display this decrypted message
Output - The decrypted message
'''	
def receiver(packages, key, offset):
	state=(KSA(key),0,0,0)	#generate an initial state
	msgParts={}		#storing decrypted messages in a dictionary with key of sequence counter
	
	for x in packages:
		ret = decrypt_package(x,state,offset)
		state = ret[2]					#save returned state for next run
		msgParts[ret[0]] = ret[1]		#place results into dictionary

	#assemble final message
	message=""
	for key in sorted(msgParts):
		message += msgParts[key]

	print "Message length", len(message)
	return message

'''
Input - the message, and the key
Gets the message and key
Prepares message to be sent to receiver
Output - A list of package strings, encrypted and ready to be sent to receiver

'''
def client(message, key, offset):
	keyState=(KSA(key),0,0,0)	#contains Permutation, i, j, stateAlignment
	packList = generate_packages(message, key, keyState,offset)
	return packList

