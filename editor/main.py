#!/usr/bin/python
# File: main.py

import mapedit
import objedit
from gi.repository import Gtk, Gdk
import gc

gc.enable()
map_editor = mapedit.MapEditor()
map_editor.show()
Gtk.main()
gc.disable()