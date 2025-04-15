from tkinter import Toplevel, Button
from creational.abstractfactory import *

class Extra(Toplevel):
	def __init__(self):
		super().__init__()
		self.title("EQs")
		self.geometry("640x480")
		self.button = Button(self, text="Show EQs", command=self.show_EQs)
	
	def show_EQs(self):
		eqsFactory = EQsFactory()
		for eq in eqsFactory.eqs:
			
			self.button = Button(self, text=f"{eq.name}")
			self.button.pack(expand=True)