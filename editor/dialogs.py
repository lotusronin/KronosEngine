from gi.repository import Gtk, Gdk, GdkPixbuf
import os

class Dialog:

	def __init__(self, dialogtype, map_window):
		if(dialogtype is "load"):
			self.Action = Gtk.FileChooserAction.OPEN
			self.Icon = Gtk.STOCK_OPEN
			self.str = "Open"
		elif(dialogtype is 'save'):
			self.Action = Gtk.FileChooserAction.SAVE
			self.Icon = Gtk.STOCK_SAVE
			self.str = "Save"

		self.dialog = Gtk.FileChooserDialog(self.str, map_window, self.Action, buttons=(Gtk.STOCK_CANCEL,Gtk.ResponseType.CANCEL,self.Icon,Gtk.ResponseType.OK))
		self.filter_map = Gtk.FileFilter()
		self.filter_map.set_name("Map Files")
		self.filter_map.add_mime_type("text/rtf")
		self.filter_map.add_pattern("*.map")

		self.dialog.add_filter(self.filter_map)
		self.dialog.set_current_folder(os.getcwd())

		return

	def run(self):
		self.response = self.dialog.run()
		return self.response

	def getFolder(self):
		return self.dialog.get_current_folder()

	def getFile(self):
		return self.dialog.get_filename()
	
	def setSaveName(self, name):
		self.dialog.set_current_name(name)

	def done(self):
		self.dialog.destroy();