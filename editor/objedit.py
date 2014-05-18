#!/usr/bin/python
# File: objedit.py

# import pyGtk
# pyGtk.require('2.0')
from gi.repository import Gtk, Gdk
import os


class ObjectEditor:
	
	hidden = True
		
	def save(self, widget, data=None):
		
		s = './data/'+self.entry_name.get_text() + '.dat'
		f = open(s, 'w')
		f.write("entity "+self.entry_name.get_text()+"\n")
		# s = self.combobox.get_active_text()
		idx = self.combobox.get_active()
		s = self.combobox.get_model()[idx][0]
		f.write("entity_type "+s+"\n")
		f.write("size "+self.entry_size.get_text()+"\n")
		f.write("texture "+self.imgpath)
		
		print('Saved!')
	
	def show(self):
		self.edit_window.show_all()

	def hide(self):
		self.edit_window.hide_all()
		
	# def show_hide(self, widget, data=None):
	# 	global hidden
	# 	global edit_window
		
	# 	if(self.hidden):
	# 		edit_window.show_all()
	# 		self.hidden = False
	# 	else:
	# 		edit_window.hide_all()
	# 		self.hidden = True

	def update_preview(self, c, p):
		fname = c.get_preview_filename()
		try:
			p.set_from_file(fname)
			have_preview = True
		except:
			have_preview = False
		c.set_preview_widget_active(have_preview)
		return

	def chooseImage(self, widget):

		self.preview = Gtk.Image()
		self.chooser = Gtk.FileChooserDialog("Open", self.edit_window, Gtk.FileChooserAction.OPEN, buttons=(Gtk.STOCK_CANCEL,Gtk.ResponseType.CANCEL,Gtk.STOCK_OPEN,Gtk.ResponseType.OK))
		self.chooser.set_preview_widget(self.preview)
		self.chooser.connect("update-preview", self.update_preview, self.preview)


		self.filter_tex = Gtk.FileFilter()
		self.filter_tex.set_name("Image Files")
		self.filter_tex.add_mime_type("xpm/xpm")
		self.filter_tex.add_pattern("*.xpm")
		self.chooser.add_filter(self.filter_tex)
		self.chooser.set_current_folder(os.getcwd())
		self.response = self.chooser.run()
		if self.response == Gtk.ResponseType.OK:
			self.imgpath = self.chooser.get_filename()
			self.imgfile = (self.imgpath)
			self.loadImage(self.imgfile)
		self.chooser.destroy()

	def loadImage(self, path):
		self.image.set_from_file(path)
		# print(path)

	def destroy(self, widget):
		self.hidden = True
		#self.edit_window.hide()
		return True
		
	def __init__(self):
	
		self.edit_window = Gtk.Window()
		self.edit_window.set_size_request(250, 400)
		self.edit_window.set_border_width(10)
		self.edit_window.set_title("Object Editor")
		self.edit_window.connect("destroy", self.destroy)
		
		self.vbox = Gtk.VBox(False, 0)
		self.table = Gtk.Table(3,2)
		self.entry_name = Gtk.Entry()
		self.entry_name.set_max_length(30)
		self.entry_name.set_text("new_obj")
		self.entry_size = Gtk.Entry()
		self.entry_size.set_max_length(3)
		self.entry_size.set_text("10")

		self.types = ['Character', 'Decal', 'Ground', 'Item']
		self.liststore = Gtk.ListStore(str)
		for item in self.types:
			self.liststore.append([item])
		self.combobox = Gtk.ComboBox()
		self.combobox.set_model(self.liststore)
		self.combobox.set_active(0)
		self.renderer = Gtk.CellRendererText()
		self.combobox.pack_start(self.renderer, True)
		self.combobox.add_attribute(self.renderer, "text", 0)

		self.image = Gtk.Image()
		self.image.set_from_file("../Platformer/res/tex_ground.xpm")
		self.button_save = Gtk.Button("save")
		self.button_save.connect("clicked", self.save, None)
		
		self.button_image = Gtk.Button()
		self.button_image.add(self.image)
		self.button_image.connect("clicked", self.chooseImage)

		self.table.attach(Gtk.Label("Name:"), 1, 2, 1, 2, 0, 0, 0, 10)
		self.table.attach(Gtk.Label("Type:"), 1, 2, 2, 3, 0, 0, 0, 0)
		self.table.attach(Gtk.Label("Size:"), 1, 2, 3, 4, 0, 0, 10, 10)
		self.table.attach(self.entry_name, 2, 3, 1, 2, 0, 0, 10, 10)
		self.table.attach(self.combobox, 2, 3, 2, 3, 0, 0, 10, 10)
		self.table.attach(self.entry_size, 2, 3, 3, 4, 0, 0, 10, 10)
		
		self.imgpath = ""

		self.edit_window.add(self.vbox)
		self.vbox.add(self.button_image)
		self.vbox.add(self.table)
		self.vbox.add(self.button_save)
		

		return
