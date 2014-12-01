#!/usr/bin/python
from RC4 import KSA
import binascii

def KSA_(M, State):
	j=0
	assert (len(M)==64), "KSA_ Message not long enough. Should be 64 bytes"
	for i in xrange(256):
		j = (j+State[i] + ord(M[i%64]))%256
		State[i], State[j] = State[j], State[i]
	return State

def PRGA_(State, l):
	j=0
	for i in xrange(l):
		i = (i+1) % 256
		j = (j+State[i])%256
		State[i], State[j] = State[j], State[i]
	return State

def PRGAC_(S,i,j):
	i = (i+1) % 256
	j = (j+S[i]) % 256
	S[i], S[j] = S[j], S[i]
	return (S,i,j,chr(S[ (S[i] + S[j]) % 256 ]))

#input - data, a blocksize, the mode	
#mode - h - hash function padding - padd with min the byte 1000 0000 then variable # of chr(0) bytes and 2-8 bytes to indicate msg len
#		m - message padding 	- padd data with 1000000 until multiple of blocksize. 
#2 byte len (16bit) or 8 byte len(64bit)
#output - data thats length is a multiple of blocksize
def padding_Function(data, blocksize, mode):
	padd = blocksize-(len(data)%blocksize)
	if mode == 'm':
		if padd == blocksize: 
			padd = 0
			print "No padding required."
		else:
			data += chr(128)
			print "The Message was padded with", padd, "bytes new length is",len(data)+padd-1
		return data + (chr(0)*(padd-1))
	elif mode == 'h':
		msglen=len(data)*8		#get num of bits in data. max length here is 65536 bits, which fits into 2 bytes
		mlen=bin(msglen)[2:]	#convert msglen to binary, strip '0b' prefix
		mlen=mlen.zfill(16)		#ensure string is 16 bits/2bytes long
		i=chr(int(mlen[:8], 2))
		j=chr(int(mlen[8:16], 2))	#convert mlen to 2 ascii chars, 2 byte rep of msglen
		msglen=i+j
		if padd > 2:
			data = data + chr(128) + (chr(0)*(padd-3)) + msglen
		else:
			data = data + chr(128) + (chr(0)*(61+padd)) + msglen

		assert (len(data)%blocksize == 0), "Padding error."
		return data
	else:
		print "Unknown mode entered. Exiting.."
		exit()

#input some data. Halt if input is bigger than 65536 bits
#output the hash value of data using RC4 Based Hash Function from project definition
def RC4_BHF(data, offset):
	z=compval=out=output=comp=""
	assert (len(data) <= 8192), "Data input to hash function is too big. Max 65536 bits/8192 bytes "
	assert ( offset >= 0), "Offset must be a non negative integer."
	#step 1: padding
	data = padding_Function(data, 64, 'h')
	#step 1: split msg into 64 byte(512bit) chunks
	segments = [data[i:i+64] for i in range(0,len(data),64)]
	#step 2: compression
	State = KSA(segments[0])
	State = PRGA_(State,offset)
	for x in range(0,len(segments)):
		if x != 0:
			State = KSA_(segments[x], State)
		M=0
		for y in xrange(len(segments[x])):
			M += int(y)
		len1=M%256
		if len1 == 0: len1=offset
		State = PRGA_(State,len1)
	#step 3: Output
	for c in State:
		z+=chr(c)
	S = (KSA(z),0,0,'a')

	for x in xrange(512):
		S = PRGAC_(*S[:3])
		out += S[3]
	out = out[-256:]
	State=KSA(z)

	for x in xrange(len(out)):
		output += chr( ord(out[x]) ^ State[x] )
	#output is now 256 byte string. need to just shrink down to 128 bit hash
	for x in range(0,len(output),2):	
		compval+= bin(ord(output[x]))[-1:]		#get lsb of every 2nd byte

	#convert string of bits to string of characters
	for x in range(0,len(compval),8):
		comp+=chr(int(compval[x:x+8], 2))

	assert (len(comp) == 16), "Compression error in RC4_BHF."
	return comp


if __name__ == '__main__':
	strin = raw_input("String to padd:")
	print "length of input", len(strin)
	nstr = padding_Function(strin, 64, 'h')

	print "Padded length", len(nstr)
	print nstr.encode('string_escape')
	offset=int(raw_input("Enter the offest:"))
	#offset=offset%16

	h=RC4_BHF(nstr,offset)
	print "hash value:\n", h.encode('string_escape')
	print binascii.hexlify(h)


