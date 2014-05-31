from gi.repository import Gtk, Gdk
import texture

class TextureManager:

	def textureExists(self, strName):
		for t in self.textureList:
			if(t.getName == strName):
				return True
		return False

	def getTexture(self, strName, sz):
		for t in self.textureList:
			if(t.getName == strName):
				return t

		return self.loadTexture(strName, sz)

	def loadTexture(self, strName, sz):
		if(self.textureExists(strName) == False):
			newT = texture.Texture(strName, sz)
			self.textureList.append(newT)
			return newT

	def __init__(self):
		self.textureList = [];
		return