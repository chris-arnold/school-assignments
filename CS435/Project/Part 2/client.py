#!/usr/bin/python
from packageFunction import *
from random import shuffle

'''
Client program
Takes message, encrypts with key and sends to reciever.
'''

if __name__ == '__main__':
	#testinput="This is a bunch of text that is exactly 252 bytes long. Its purpose is to test the creation of encrypted packages to be sent via a secure unicast protocol for the CS 435 term project. There is still some text to fill in so there will just be words. 252"
	testinput="Never Gonna Give You Up\n\nWe're no strangers to love\nYou know the rules and so do I\nA full commitment's what I'm thinking of\nYou wouldn't get this from any other guy\n\nI just wanna tell you how I'm feeling\nGotta make you understand\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nWe've known each other for so long\nYour heart's been aching, but\nYou're too shy to say it\nInside, we both know what's been going on\nWe know the game and we're gonna play it\n\nAnd if you ask me how I'm feeling\nDon't tell me you're too blind to see\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie andI need to add."
	testkey="MYTESTKEY"
	key=raw_input("Enter the key: ")
	offset=int(raw_input("Enter the offset: "))
	inmode=raw_input("Would you like to enter a message to send (y/n): ")
	if inmode.upper() == 'Y':
		testinput=raw_input("Enter the message now: ")
	else:
		print "Using default message."
		
	mode=raw_input("Network mode (n)\nTest mode (t):")

	r = client(testinput, key, offset)
	shuffle(r)

	if mode.upper() == 'T':
		useless=raw_input("Packages generated. Press enter to run receiver function..")
		message = receiver(r,key,offset)
		useless=raw_input("Press enter to view the message")
		print message
	elif mode.upper() == "N":
		import socket
		host='carnold.ca'
		port=55000
		custom=raw_input("Port is set to 55000 and a default server has been set. Use this default?(y/n) ")
		if custom.upper() == 'N':
			host=raw_input("Enter the host name you wish to connect to ")
		s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		try:
			s.connect((host, port))
		except IOError:
			print "Could not connect to",host,"on port",port
			print "Closing client."
			exit()
		for p in r:
			s.send(p)
			print "Sending Package", int(p[:4])
		s.close()

	else:
		print "Invalid mode input"
