from gi.repository import Gtk, Gdk

UI_INFO = """
<ui>
	<menubar name='MenuBar'>
		<menu action='FileMenu'>
			<menuitem action='FileQuit' />
		</menu>
	</menubar>
	<toolbar name='ToolBar'>
		<toolitem action='AddObj' />
		<toolitem action='RunMap' />
		<toolitem action='SaveMap' />
		<toolitem action='LoadMap' />
	</toolbar>
</ui>
"""

class Menus:
	
	def __init__(self, widget):

		self.action_group = Gtk.ActionGroup("my_actions")
		self.add_file_menu_actions(self.action_group)
		self.add_toolbar_actions(self.action_group, widget)

		self.uimanager = self.create_ui_manager()
		self.uimanager.insert_action_group(self.action_group)

		self.menubar = self.uimanager.get_widget("/MenuBar")
		self.toolbar = self.uimanager.get_widget("/ToolBar")
		self.toolbar.set_style(Gtk.ToolbarStyle.BOTH_HORIZ)
		# self.menubar = Gtk.MenuBar()
		# self.menuitem = Gtk.MenuItem(label="File")
		# self.menuitem.set_submenu(self.create)
		# self.toolbar = Gtk.Toolbar()


	def getMenu(self):
		return self.menubar

	def getToolbar(self):
		return self.toolbar

	def create_ui_manager(self):
		uim = Gtk.UIManager()

		uim.add_ui_from_string(UI_INFO)

		return uim

	def on_menu_file_quit(self, widget):
		Gtk.main_quit()

	def add_file_menu_actions(self, action_group):
		action_filemenu = Gtk.Action("FileMenu", "File", None, None)
		action_group.add_action(action_filemenu)

		action_filequit = Gtk.Action("FileQuit", "Quit", None, None)
		action_filequit.connect("activate", Gtk.main_quit)
		action_group.add_action(action_filequit)

	def add_toolbar_actions(self, action_group, widget):
		action_addobj = Gtk.Action("AddObj", "New Object", "New Object", Gtk.STOCK_ADD)
		action_addobj.connect("activate", widget.newobj)
		action_group.add_action(action_addobj)

		action_runmap = Gtk.Action("RunMap", "Run Map", "Run Map", Gtk.STOCK_EXECUTE)
		action_group.add_action(action_runmap)

		action_savemap = Gtk.Action("SaveMap", "Save Map", "Save Map", Gtk.STOCK_FLOPPY)
		action_savemap.connect("activate", widget.save)
		action_group.add_action(action_savemap)

		action_loadmap = Gtk.Action("LoadMap", None, "Load Map", Gtk.STOCK_OPEN)
		action_loadmap.connect("activate", widget.load)
		action_group.add_action(action_loadmap)
