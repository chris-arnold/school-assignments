#!/usr/bin/python
from packageFunction import *
from random import shuffle

'''
Client program
Takes message, encrypts with key and sends to reciever.
'''

if __name__ == '__main__':
	#testinput="This is a bunch of text that is exactly 252 bytes long. Its purpose is to test the creation of encrypted packages to be sent via a secure unicast protocol for the CS 435 term project. There is still some text to fill in so there will just be words. 252"
	#t1="Never Gonna Give You Up\n\nWe're no strangers to love\nYou know the rules and so do I\nA full commitment's what I'm thinking of\nYou wouldn't get this from any other guy\n\nI just wanna tell you how I'm feeling\nGotta make you understand\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nWe've known each other for so long\nYour heart's been aching, but\nYou're too shy to say it\nInside, we both know what's been going on\nWe know the game and we're gonna play it\n\nAnd if you ask me how I'm feeling\nDon't tell me you're too blind to see\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie andI need to add."
	t1="\"Never Gonna Give You Up\"\n\nOooh\n\nWe're no strangers to love\nYou know the rules and so do I\nA full commitment's what I'm thinking of\nYou wouldn't get this from any other guy\n\nI just wanna tell you how I'm feeling\nGotta make you understand\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nWe've known each other for so long\nYour heart's been aching, but\nYou're too shy to say it\nInside, we both know what's been going on\nWe know the game and we're gonna play it\n\nAnd if you ask me how I'm feeling\nDon't tell me you're too blind to see\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\n(Ooh, give you up)\n(Ooh, give you up)\nNever gonna give, never gonna give\n(Give you up)\nNever gonna give, never gonna give\n(Give you up)\n\nWe've known each other for so long\nYour heart's been aching, but\nYou're too shy to say it\nInside, we both know what's been going on\nWe know the game and we're gonna play it\n\nI just wanna tell you how I'm feeling\nGotta make you understand\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you"
	t2="Girls That have said no :(\n\nAt the local swimming pool canteen, not realising until afterwards that my penis was caught in the elastic of my swimming shorts with the tip sticking out, I purchased a packet of twisties and a can of coke before asking out the girl who served me but she said no.\n\nGirls That have said no :(\n\nA lady (aged one hundred and ninety) at the counter at Myers in front of me yelled \"My purse\" then looked at me and proclaimed \"You took my purse\" so I said \"yes, I took your purse, I collect them.\" and she started yelling at me and the department manager came over and I had to explain that I was not admitting to the theft, I was being sarcastic. Her purse ended up in one of the many bags she was carrying but she continued to glare at me without so much as an apology. When the girl served me she apologised and I asked her \"Why, did you arrange someone to act like an old crazy woman for me?\" and she laughed and said that I was funny so I asked her out but she said no...\n"
	testkey="MYTESTKEY"
	key=raw_input("Enter the key: ")
	offset=int(raw_input("Enter the offset: "))
	#offset=offset%16
	inmode=raw_input("Input type:\nTerminal input (Y)\nFile input (F)\nUse a Default(N): ")
	if inmode.upper() == 'Y':
		testinput=raw_input("Enter the message now: ")
	elif inmode.upper() == 'F':
		filename=raw_input("Enter file name now: ")
		try:
			with open(filename, "rb") as myfile:
				testinput=myfile.read()
		except IOError:
			print "Could not open", filename, "\nUsing default message."
			testinput = t2
	else:
		if random.getrandbits(1):
			testinput=t1
		else:
			testinput=t2
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
		host='localhost'
		port=55000
		custom=raw_input("Server is set to localhost and port is set to 55000.\nUse this default?(y/n) ")
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
