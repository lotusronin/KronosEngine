from gi.repository import Gtk, Gdk, GdkPixbuf

class Texture:

	def getImage(self):
		return self.image

	def getName(self):
		return self.name

	def __init__(self, strname, sz):

		self.name = strname
		strname = "./res/texture/" + strname
		self.image = GdkPixbuf.Pixbuf.new_from_file_at_size(strname, int(sz), int(sz))
		return