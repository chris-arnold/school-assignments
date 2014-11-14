#!/usr/bin/python
from packageFunction import *
import socket

if __name__ == '__main__':
	key="MYTESTKEY"
	host=""
	port=55000

	s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((host, port))
	print "Bind successful.",
	while 1:
		packages=[]
		print "Waiting for connection on port", port
		try:		#Allow keyboard interrupt to be caught and have server gracefully shutdown
			s.listen(1)
			conn, addr = s.accept()
			print 'Connected by', addr
		except KeyboardInterrupt:
			print "\nInterupt detected. Shutting down server"
			try:
				conn.close()
				print "Socket closed."
			except:
				pass
			exit()

		while 1:
			data = conn.recv(272)		#packages are 272 bytes long. Put these into a list
			if not data: break
			packages.append(data)	

		print len(packages),"Packages have been received."
		key=raw_input("Enter the key: ")
		offset=int(raw_input("Enter the offset: "))

		msg = receiver(packages, key,offset)
		nothin=raw_input("Press enter to view message")
		print '~'*30, "Begin Message", "~"*30
		print msg, '\n', '~'*30, 'End Message', '~'*32,'\n'

