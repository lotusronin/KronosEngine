#!/usr/bin/python
# File: mapentity.py

# import pygtk
# pygtk.require('2.0')
from gi.repository import Gtk, Gdk

class MapEntity:
	# self.x = None
	# self.y = None
	# self.name = None
	# self.texture = None

	def getCoords(self):
		return self.x,self.y

	def getx(self):
		return self.x

	def gety(self):
		return self.y

	def setCoords(self,xcoord,ycoord):
		self.x = xcoord
		self.y = ycoord

	def getName(self):
		return self.name

	def setName(self, strname):
		self.name = strname

	def __init__(self, xarg, yarg, namearg):
		self.x = xarg
		self.y = yarg
		self.name = namearg
		return