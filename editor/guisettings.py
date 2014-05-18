from gi.repository import Gtk, Gdk
import glob

class SettingsGui:

	def __init__(self, widget):

		self.settingsvbox = Gtk.VBox(False, 0)


		self.loadObjs()
		self.obj_select = Gtk.ComboBox()
		self.obj_select.set_model(self.store)
		self.obj_select.set_active(0)
		self.renderer = Gtk.CellRendererText()
		self.obj_select.pack_start(self.renderer, True)
		self.obj_select.add_attribute(self.renderer, "text", 0)

		self.b = Gtk.Button("Update")
		self.b.connect("clicked", self.update, widget)
		
		self.settingsname = Gtk.Entry()
		self.settingsname.set_max_length(30)
		self.settingswidth = Gtk.Entry()
		self.settingswidth.set_max_length(5)
		self.settingsheight = Gtk.Entry()
		self.settingsheight.set_max_length(5)

		self.settingslabelname = Gtk.Label(widget.map1.get_name())
		self.settingslabelwidth = Gtk.Label("Width: ")
		self.settingslabelheight = Gtk.Label("Height: ")
		self.settingsvbox.add(self.settingslabelname)
		self.settingsvbox.add(self.settingsname)
		self.settingsvbox.add(self.settingslabelwidth)
		self.settingsvbox.add(self.settingswidth)
		self.settingsvbox.add(self.settingslabelheight)
		self.settingsvbox.add(self.settingsheight)
		self.settingsvbox.add(self.b)

	def getMapSettingsGui(self):
		return self.settingsvbox

	def getObjSettingsGui(self):
		return self.obj_select

	def update(self, widget, parent):
		parent.map1.set_name(self.settingsname.get_text())
		# parent.printMap()
		self.settingslabelname.set_text(self.settingsname.get_text())
		w = int(self.settingswidth.get_text())
		h = int(self.settingsheight.get_text())
		parent.drawing_area.set_size_request(w,h)
		self.settingslabelwidth.set_text("Width: "+self.settingswidth.get_text())
		self.settingslabelheight.set_text("Height: "+self.settingsheight.get_text())

	def loadObjs(self):
		self.obj_list = []
		for file in glob.glob("../Platformer/data/*.dat"):
			# print(file[file.rfind("/")+1:])
			self.obj_list.append(file[file.rfind("/")+1:])
		self.store = Gtk.ListStore(str)
		for i in self.obj_list:
			self.store.append([i])
		return
