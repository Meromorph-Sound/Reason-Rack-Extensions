format_version = "2.0"

PANEL_HEIGHT = 1380
PANEL_WIDTH = 3770

KNOB_HEIGHT=200
KNOB_WIDTH=200

BUTTON_HEIGHT=160
BUTTON_WIDTH=160

LAMP_HEIGHT=480

MARGIN=40
MARGIN_TOP=50
MARGIN_LEFT=1000

BLOCK_WIDTH=600
JOYSTICK_WIDTH=400
ARRAY_WIDTH=200

LED_W=55
LED_H=55
SWITCH_W=115
SWITCH_H=125
KNOB_W=265
KNOB_H=290
STICK_W=400
STICK_H=400

function centred(n,y,width)
  local offset = MARGIN_LEFT+n*BLOCK_WIDTH
  local x0 = math.floor((BLOCK_WIDTH-width)/2)
  return { offset+x0, y }
end

function QUEG(n)
local x0 = 1000 + 650*(n-1)
  local queg={}
  queg["A"..n] = {
    offset = { x0 + 200, 50 },
    { path = "ABCD", frames=1 }
  }
  queg["B"..n] = {
    offset = { x0 + 345, 50 },
    { path = "ABCD", frames=1 }
  }
  queg["C"..n] = {
    offset = { x0 + 200, 195 },
    { path = "ABCD", frames=1 }
  }
  queg["D"..n] = {
    offset = { x0 + 345, 195 },
    { path = "ABCD", frames=1 }
  }
  queg["vco"..n] = {
   offset = { x0 + 50,350 },
   { path = "button", frames=2 }
  }
  queg["manual"..n] = {
   offset = { x0 + 435,350 },
   { path = "button", frames=2 }
  }
  queg["controller"..n] = {
   offset={ x0 + 100,550 },
   { path = "controller", frames=1 }
  }
  queg["level"..n] = {
   offset={ x0 + 180,1033 },
   { path = "Knob_58_64frames", frames=64 }
  }
  return queg
end

front = { 
	Bg = {
		{ path = "frontPanel" },
	},
	onoffbypass = {
      		offset = { 185,50 },
      		{path="Fader_Bypass_3frames", frames = 3},
    	},
	deviceName = {
		offset = { 185, 1265 },
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	QUEG(1),
	QUEG(2),
	QUEG(3),
	QUEG(4)
}
back = { 
	Bg = {
		{ path = "Panel_Back_4U" },
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
    offset = { 3280, MARGIN},
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
