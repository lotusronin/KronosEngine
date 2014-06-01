#!/usr/bin/python
# File: mapentity.py

from gi.repository import Gtk, Gdk

class MapEntity:

	def getCoords(self):
		return self.x,self.y

	def getx(self):
		return self.x

	def gety(self):
		return self.y

	def getsz(self):
		return self.sz

	def setCoords(self,xcoord,ycoord):
		self.x = xcoord
		self.y = ycoord

	def getName(self):
		return self.name

	def setName(self, strname):
		self.name = strname

	def getTexture(self):
		return self.texture

	def setTexture(self, t):
		self.texture = t.getImage()

	def setSelected(self, selected):
		self.selected = selected

	def getSelected(self):
		return self.selected

	def __init__(self, xarg, yarg, sarg, namearg, t):
		self.x = xarg
		self.y = yarg
		self.sz = sarg
		self.name = namearg
		self.setTexture(t)
		self.selected = False
		return