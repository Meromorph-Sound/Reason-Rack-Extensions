format_version = "2.0"
PANEL_HEIGHT=345

KNOB_HEIGHT=200
KNOB_WIDTH=200

BUTTON_HEIGHT=160
BUTTON_WIDTH=160

LAMP_HEIGHT=480

MARGIN=50



front = { 
	Bg = {
		{ path = "front" },
	},
	onoffbypass = {
      offset = {185,45},
      {path="Fader_Bypass_3frames", frames = 3},
    },
	deviceName = {
		offset = { 185, 215},
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	{
	 learningRate = {
      offset = { 700, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
  	threshold = {
  		offset = { 1400, 80 },
  		{ path = "Knob_01_63frames", frames = 63 },
  	},
  	rectification = {
  		offset = { 950, 100 },
  		{ path = "Button_23_2frames", frames = 2},
  	},
  	rectificationDisplay =
  	{
  		offset = { 1110, 100 },
  		{ path = "Lamp_18_3frames", frames = 3},
  	},
    thresholdLED = {
      offset = { 1540, 20 },
      { path = "Bicolour_LED_3frames", frames = 3 }
    }
  }
}
back = { 
	Bg = {
		{ path = "back" },
	},
	Placeholder = {
		offset = { 100, 100 },
		{ path = "Placeholder" },
	},
	SignalInputLeft = {
		offset = {500,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	SignalInputRight = {
		offset = {700,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	EnvelopeOutputLeft = {
    offset = {900,100},
    { path = "SharedAudioJack", frames = 3},
  },
  EnvelopeOutputRight = {
    offset = {1100,100},
    { path = "SharedAudioJack", frames = 3},
  },
  GateOutputCV = {
    offset = {1500,110},
    { path = "SharedCVJack", frames = 3},
  },
  deviceName = {
    offset = { 3280, 50},
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  }
folded_front = { 
	Bg = {
		{ path = "Panel_Folded_Front" },
	},
}
folded_back = { 
	Bg = {
		{ path = "Panel_Folded_Back" },
	},
	CableOrigin = {
		offset = { 1885, 75 },
	},
}
