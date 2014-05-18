#!/usr/bin/python
# File: map.py

import mapentity

class Map:

	def __init__(self, n):
		self.obj_list = []
		self.name = n
		return

	def add_obj(self,x,y,n):
		# n = n.replace("./data/", '')
		# print(n)
		me = mapentity.MapEntity(x,y,n)
		self.obj_list.append(me)

	def get_objs(self):
		return self.obj_list

	def get_name(self):
		return self.name

	def set_name(self, n):
		self.name = n

	def save(self):
		f = open(self.name+'.map', 'w')
		f.write(self.name+' ')
		for o in self.obj_list:
			a=o.getCoords()
			f.write(str(a[0])+','+str(a[1])+','+o.getName()+' ')
		f.write('mapend')
		f.close()

		return