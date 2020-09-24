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
		{ path = "Panel_Front_2U" },
	},
	onoffbypass = {
      		offset = {185,45},
      		{path="Fader_Bypass_3frames", frames = 3},
    	},
	deviceName = {
		offset = { 185, 215},
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	controller1 = {
	 offset={ 1000, 50 },
	 { path = "controller", frames=1 }
	}
}
back = { 
	Bg = {
		{ path = "Panel_Back_2U" },
	},
	Placeholder = {
		offset = { 100, 100 },
		{ path = "Placeholder" },
	},
	SignalInput1 = {
		offset = {500,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	SignalInput2 = {
		offset = {700,100},
		{ path = "SharedAudioJack", frames = 3},
	},
   SignalInput3 = {
            offset = {900,100},
            { path = "SharedAudioJack", frames = 3},
    },
   SignalInput4 = {
            offset = {1100,100},
            { path = "SharedAudioJack", frames = 3},
    },
   SignalOutputA = {
            offset = {500,500},
            { path = "SharedAudioJack", frames = 3},
    },
    SignalOutputB = {
            offset = {700,500},
            { path = "SharedAudioJack", frames = 3},
    },
   SignalOutputC = {
            offset = {900,500},
            { path = "SharedAudioJack", frames = 3},
    },
   SignalOutputD = {
            offset = {1100,500},
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
