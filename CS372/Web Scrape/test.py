#!/usr/bin/python
import sys
print "Test script",sys.argv[1]

x = sys.argv[1]
x = x.replace('&', '')
print x