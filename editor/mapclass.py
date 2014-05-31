#!/usr/bin/python
# File: map.py

import mapentity

class Map:

	def __init__(self, n):
		self.obj_list = []
		self.name = n
		self.width = 640
		self.height = 480
		return

	def add_obj(self,x,y,n,t):
		# n = n.replace("./data/", '')
		# print(n)
		me = mapentity.MapEntity(x,y,n,t)
		self.obj_list.append(me)

	def get_objs(self):
		return self.obj_list

	def get_name(self):
		return self.name

	def set_name(self, n):
		self.name = n

	def set_size(self, w, h):
		self.width = w
		self.height = h

	def get_size(self):
		return self.width,self.height

	def save(self, path):
		f = open(path+'.map', 'w')
		f.write(self.name+' ')
		for o in self.obj_list:
			a=o.getCoords()
			f.write(str( float(a[0]) - float(self.width)/2)+','+str( -1*(float(a[1])-float(self.height)/2) )+','+o.getName()+' ')
		f.write('mapend')
		f.close()

		return