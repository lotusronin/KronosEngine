#!/usr/bin/python
# File: mapedit.py

from gi.repository import Gtk, Gdk, GdkPixbuf
import glob
import os
import objedit
import mapclass
import guimenus
import guisettings
import texturemanager
import dialogs

"""
Map Editor To-Do:

[ ] Finish Implementing load() completely
[x] Allow Size change from the settings tab
[ ] Implement a deleteObj() to remove items from the map
[ ] Fix the runmap()
[ ] Fix Paths for all the scripts
[ ] Update Object.dat list realtime
[ ] Update Object Editor GUI

"""



class MapEditor:

	def runmap(self, widget):
		"""Runs the engine with the current map. Not Working Yet."""
		print("./bin/Debug/Platformer"+" -m "+self.map1.get_name())
		if(os.fork() > 0):
			os.execl("./bin/Debug/Platformer", "-m ", self.map1.get_name())
			# print("./bin/Debug/Platformer"+" -m "+self.map1.get_name())

		# subprocess.call(["./bin/Debug/Platformer", "-m", self.map1.get_name()]) # Use this one instead!

	def newobj(self, widget):
		"""Opens up the Object Editor."""
		obwindow = objedit.ObjectEditor()
		obwindow.show()
		

	def get_value(self, name, value):
		"""Gets the value of any entity."""
		name = "./data/"+name+".dat"
		f = open(name, 'r')
		for line in f:
			if(value in line):
				str1 = line.split(" ", 1)
		f.close()

		return str1[1]

	def printMap(self):
		print(self.map1.get_name())

	def show(self):
		self.map_window.show_all()

	def area_configure_cb(self, area, event):
		'''Notify program to call the drawing events.'''
		area.queue_draw()
		return

	def expose(self, area, context):
		'''internal draw event'''
		self.draw_map(context)

	def destroy(self, widget, data=None):
		Gtk.main_quit()

	def update_mxy(self, widget, event):
		'''Get current mouse coordinants'''
		self.mousexy = [event.x, event.y]

	def add_it(self, widget, event):
		'''Adds a new object to the map object list.'''
		idx = self.obj_select.get_active()
		strname = self.obj_select.get_model()[idx][0]
		strname = strname[:-4]
		tx = self.get_value(strname, 'texture')
		sz = self.get_value(strname, 'size')
		texture = self.texman.getTexture(tx, sz)
		self.map1.add_obj(self.mousexy[0], self.mousexy[1], sz, strname, texture)
		self.selectedObj = self.map1.objExists(self.mousexy[0],self.mousexy[1])
		self.drawing_area.queue_draw()

	def clickEvent(self, widget, event):
		'''Check to see if you clicked on an object'''
		xloc = self.mousexy[0]
		yloc = self.mousexy[1]
		
		if(self.selectedObj != None):
			'''Deselecting old object'''
			self.selectedObj.setSelected(False)
		
		self.selectedObj = self.map1.objExists(xloc, yloc)
		if(self.selectedObj is None):
			self.add_it(widget, event)
		'''Selecting new object'''
		self.selectedObj.setSelected(True)
		self.drawing_area.queue_draw()

	def buttonHandler(self, widget, event):
		if(event.string == 'd'):
			if(self.selectedObj != None):
				self.map1.delete_obj(self.selectedObj)
				self.selectedObj = None
		self.drawing_area.queue_draw()

	def save(self, widget, data=None):
		'''Opens up a Save dialog for saving the current map.'''
		saver = dialogs.Dialog('save', self.map_window)
		saver.setSaveName(self.map1.get_name())
		response = saver.run()
		
		if response == Gtk.ResponseType.OK:
			self.map1.set_name(saver.getFile().replace(saver.getFolder()+'/', ''))
			self.map1.save(saver.getFile())
		else:
			print("No file saved")

		saver.done()

	def draw_map(self, cr):
		'''Draws all objects stored in the current map onto the drawing area.'''
		
		sizes = self.map1.get_size()

		cr.set_source_rgb(0.0, 0.0, 0.0)
		cr.rectangle(0,0,sizes[0],sizes[1])
		cr.fill()
		cr.set_source_rgb(1.0,0.0,0.0)
		cr.rectangle((sizes[0]/2 )- 2,(sizes[1]/2 )-2,5,5)
		cr.fill()

		ol = self.map1.get_objs()
		for o in ol:
			Gdk.cairo_set_source_pixbuf(cr, o.getTexture(), float(o.getx()), float(o.gety()))
			cr.paint()
			if(o.getSelected() == True):
				#print("Objected is selectedObj")
				cr.set_source_rgba(0.0,0.5,0.0,0.5)
				s = float(o.getsz())
				cr.rectangle(float(o.getx()),float(o.gety()),s,s)
				cr.fill()


	def load(self, widget, data=None):
		'''Opens up a Load Dialog for all Map files. Not fully implemented yet.'''
		chooser = dialogs.Dialog('load', self.map_window)
		response = chooser.run()
		chooser.done()


	def __init__(self):

		self.map1 = mapclass.Map("newmap")
		self.selectedObj = None

		#Texture Manager
		self.texman = texturemanager.TextureManager()

		#Window Setup
		self.map_window = Gtk.Window()
		self.map_window.set_size_request(640, 480)
		self.map_window.set_border_width(10)
		self.map_window.set_title("Map Editor")
		self.map_window.connect("destroy", self.destroy)
		
		self.header = Gtk.HeaderBar()
		self.header.props.show_close_button = True
		self.header.props.title = "Map Editor"
		#self.header.set_decoration_layout(":minimize,close")
		self.map_window.set_titlebar(self.header)
		
		# Gui Items for Tabs
		self.settingsgui = guisettings.SettingsGui(self)

		self.obj_select = self.settingsgui.getObjSettingsGui()
		self.settingsvbox = self.settingsgui.getMapSettingsGui()
		self.notebook = Gtk.Notebook()
		self.notebook.append_page(self.obj_select, Gtk.Label("Objects"))
		self.notebook.append_page(self.settingsvbox, Gtk.Label("Settings"))
		
		# Gui Items for menu and toolbar
		self.menus = guimenus.Menus(self)
		self.toolbar = self.menus.getToolbar()
		#self.menubar = self.menus.getMenu()
		
		self.drawing_area = Gtk.DrawingArea()
		self.drawing_area.connect("draw", self.expose)
		self.drawing_area.set_size_request(640, 480)
		self.drawing_area.connect("configure-event", self.area_configure_cb)
		self.drawing_area.connect("motion-notify-event", self.update_mxy)
		self.drawing_area.connect("button-press-event", self.clickEvent)
		self.map_window.connect("key-press-event", self.buttonHandler)
		self.map_window.set_events(Gdk.EventMask.KEY_PRESS_MASK)
		self.drawing_area.set_events(Gdk.EventMask.BUTTON_PRESS_MASK | Gdk.EventMask.POINTER_MOTION_MASK)
		# self.drawing_area.set_events(Gtk.gdk.BUTTON_PRESS_MASK | Gtk.gdk.POINTER_MOTION_MASK | Gtk.gdk.BUTTON_RELEASE_MASK)

		self.sw = Gtk.ScrolledWindow()
		self.sw.add_with_viewport(self.drawing_area)
		self.sw.set_shadow_type(Gtk.ShadowType.ETCHED_IN)

		self.paned = Gtk.Paned()

		self.vbox1 = Gtk.VBox(False, 0)

		self.map_window.add(self.vbox1)
		#self.vbox1.pack_start(self.menubar, False, False, 0)
		#self.header.pack_start(self.toolbar)
		self.vbox1.pack_start(self.toolbar, False, False, 0)
		self.vbox1.add(self.paned)
		self.paned.add1(self.notebook)
		self.paned.add2(self.sw)

		self.drawing_area.realize()
		
		return
