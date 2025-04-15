class EQsFactory:
	def __init__(self):
		self._eqsfactory: list = [FabFilter(5, "Pro Q"), UAD(4, "UAD")] # and some more, but i can't see it
	
	@property
	def eqs(self) -> list:
		return self._eqsfactory

class EQ:
	def __init__(self, bands, name):
		self.bands = bands
		self.name = name
	
	def getBands(self):
		return self.bands

class FabFilter(EQ):
	def __init__(self, bands, name):
		super().__init__(bands, name)

class Waves(EQ):
	def __init__(self, bands, name):
		super().__init__(bands, name)

class UAD(EQ):
	def __init__(self, bands, name):
		super().__init__(bands, name)