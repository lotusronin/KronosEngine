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
		print(self.mousexy[0],", ",self.mousexy[1])
		self.map1.add_obj(self.mousexy[0], self.mousexy[1], strname, texture)
		self.drawing_area.queue_draw()

	def save(self, widget, data=None):
		'''Opens up a Save dialog for saving the current map.'''
		self.saver = Gtk.FileChooserDialog("Save", self.map_window, Gtk.FileChooserAction.SAVE, buttons=(Gtk.STOCK_CANCEL,Gtk.ResponseType.CANCEL,Gtk.STOCK_SAVE,Gtk.ResponseType.OK))
		self.filter_map = Gtk.FileFilter()
		self.filter_map.set_name("Map Files")
		self.filter_map.add_mime_type("text/rtf")
		self.filter_map.add_pattern("*.map")
		self.saver.add_filter(self.filter_map)
		self.saver.set_current_folder(os.getcwd())
		self.saver.set_current_name(self.map1.get_name())
		self.response = self.saver.run()
		
		if self.response == Gtk.ResponseType.OK:
			self.map1.set_name(self.saver.get_filename().replace(self.saver.get_current_folder()+'/', ''))
			self.map1.save(self.saver.get_filename())
		else:
			print("No file saved")

		self.saver.destroy()

	def draw_map(self, cr):
		'''Draws all objects stored in the current map onto the drawing area.'''
		
		sizes = self.map1.get_size()

		cr.identity_matrix()
		cr.scale(2,2)
		cr.set_source_rgb(0.0, 0.0, 0.0)
		cr.rectangle(0,0,sizes[0],sizes[1])
		cr.fill()
		cr.set_source_rgb(1.0,0.0,0.0)
		cr.rectangle((sizes[0]/2 )- 2,(sizes[1]/2 )-2,5,5)
		cr.fill()

		ol = self.map1.get_objs()
		for o in ol:
			Gdk.cairo_set_source_pixbuf(cr, o.getTexture(), int(o.getx()), int(o.gety()))
			cr.paint()


	def load(self, widget, data=None):
		'''Opens up a Load Dialog for all Map files. Not fully implemented yet.'''
		self.chooser = Gtk.FileChooserDialog("Open", self.map_window, Gtk.FileChooserAction.OPEN, buttons=(Gtk.STOCK_CANCEL,Gtk.ResponseType.CANCEL,Gtk.STOCK_OPEN,Gtk.ResponseType.OK))
		self.filter_map = Gtk.FileFilter()
		self.filter_map.set_name("Map Files")
		self.filter_map.add_mime_type("text/rtf")
		self.filter_map.add_pattern("*.map")
		self.chooser.add_filter(self.filter_map)
		self.chooser.set_current_folder(os.getcwd())
		self.response = self.chooser.run()
		self.chooser.destroy()


	def __init__(self):
		
		# self.obwindow = objedit.ObjectEditor()
		self.hidden = True

		self.map1 = mapclass.Map("newmap")

		#Texture Manager
		self.texman = texturemanager.TextureManager()

		#Window Setup
		self.map_window = Gtk.Window()
		self.map_window.set_size_request(640, 480)
		self.map_window.set_border_width(10)
		self.map_window.set_title("Map Editor")
		self.map_window.connect("destroy", self.destroy)
		

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
		self.menubar = self.menus.getMenu()
		
		self.drawing_area = Gtk.DrawingArea()
		self.drawing_area.connect("draw", self.expose)
		self.drawing_area.set_size_request(640, 480)
		self.drawing_area.connect("configure-event", self.area_configure_cb)
		self.drawing_area.connect("motion-notify-event", self.update_mxy)
		self.drawing_area.connect("button-press-event", self.add_it)
		self.drawing_area.set_events(Gdk.EventMask.BUTTON_PRESS_MASK | Gdk.EventMask.POINTER_MOTION_MASK)
		# self.drawing_area.set_events(Gtk.gdk.BUTTON_PRESS_MASK | Gtk.gdk.POINTER_MOTION_MASK | Gtk.gdk.BUTTON_RELEASE_MASK)

		self.sw = Gtk.ScrolledWindow()
		self.sw.add_with_viewport(self.drawing_area)
		self.sw.set_shadow_type(Gtk.ShadowType.ETCHED_IN)

		self.vbox1 = Gtk.VBox(False, 0)
		self.hbox1 = Gtk.HBox(False, 0)

		self.map_window.add(self.vbox1)
		self.vbox1.pack_start(self.menubar, False, False, 0)
		self.vbox1.pack_start(self.toolbar, False, False, 0)
		self.vbox1.add(self.hbox1)
		self.hbox1.pack_start(self.notebook, False, False, 0)
		self.hbox1.add(self.sw)

		self.drawing_area.realize()
		
		return
