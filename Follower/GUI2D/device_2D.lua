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
		{ path = "front1U" },
	},
	onoffbypass = {
      offset = {185,50},
      {path="Fader_Bypass_3frames", frames = 3},
    },
	deviceName = {
		offset = { 3200, 250},
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	{
	 Detail1 = {
      offset = { 1100, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
  	Detail2 = {
  		offset = { 1400, 80 },
  		{ path = "Knob_01_63frames", frames = 63 },
  	},
  	Detail3 = {
      offset = { 1700, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
    Detail4 = {
      offset = { 2000, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
    Approximation = {
      offset = { 2300, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
  	Algorithm = {
  		offset = { 2650, 100 },
  		{ path = "Button_23_2frames", frames = 2},
  	},
  	AlgorithmDisplay =
  	{
  		offset = { 2850, 130 },
  		{ path = "Lamp_18_2frames", frames = 2},
  	}
  }
}
back = { 
	Bg = {
		{ path = "backPanel" },
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
