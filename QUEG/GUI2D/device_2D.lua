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
    --{ path = "ABCD", frames=1 }
    { path = "meter_16frames", frames=16 }
  }
  queg["B"..n] = {
    offset = { x0 + 345, 50 },
    { path = "meter_16frames", frames=16 }
  }
  queg["C"..n] = {
    offset = { x0 + 200, 195 },
    { path = "meter_16frames", frames=16 }
  }
  queg["D"..n] = {
    offset = { x0 + 345, 195 },
    { path = "meter_16frames", frames=16 }
  }
  queg["vco"..n] = {
   offset = { x0 + 50,350 },
   { path = "button", frames=2 }
  }
  queg["manual"..n] = {
   offset = { x0 + 242,350 },
   { path = "button", frames=2 }
  }
  queg["bypass"..n] = {
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

function makePopup(name, path, nFrames, xy1, xy2 )
  local tab = {}
  tab[name] = {
    offset = xy1,
    { path = name, frames = nFrames }
  }
  tab[name.."_button"] = {
    offset = xy2,
    path = { "UpDownButton", frames = 2 }
  }
  return tab
end

function VCOFront()
  local table={
    VCOactive = {
      offset = { 1045, 1685 },
      { path = "button", frames=2 }
    },
    VCOfreeze = {
      offset = { 1245, 1580 },
      { path = "button", frames=2 }
    },
    VCOzero = {
      offset = { 1245, 1790 },
      { path = "button", frames=2 }
    },
    VCOfrequency = {
      offset={ 1555, 1605 },
      { path = "Knob_58_64frames", frames=64 }
    },
    VCOwidth = {
      offset={ 1905, 1605 },
      { path = "Knob_58_64frames", frames=64 }
    },
    VCOheight = {
      offset={ 2255, 1605 },
      { path = "Knob_58_64frames", frames=64 }
    }, 
    VCOpattern = {
      offset = { 2595, 1670 },
      { path = "VCOPatterns_8frames", frames=8 }
    },
    VCOpattern_updown = {
      offset = { 2820, 1670 },
      { path = "upDown", frames=3 }
    },
--    VCOstartsBG = {
--      offset = { 2915, 1525 },
--      { path = "starts", frames = 1 }
--    },
    VCOstart1 = {
      offset = { 3005, 1585 },
      { path = "VCOOrder_4frames", frames=4 }
    },
    VCOstart_updown1 = {
      offset = { 3125, 1585 },
      { path = "upDown", frames=3 }
    },
    VCOstart2 = {
      offset = { 3265, 1585 },
      { path = "VCOOrder_4frames", frames=4 }
    },
    VCOstart_updown2 = {
      offset = { 3385, 1585 },
      { path = "upDown", frames=3 }
    },
    VCOstart3 = {
      offset = { 3265, 1785 },
      { path = "VCOOrder_4frames", frames=4 }
    },
    VCOstart_updown3 = {
      offset = { 3385, 1785 },
      { path = "upDown", frames=3 }
    },
    VCOstart4 = {
      offset = { 3005, 1785 },
      { path = "VCOOrder_4frames", frames=4 }
    },
    VCOstart_updown4 = {
      offset = { 3125, 1785 },
      { path = "upDown", frames=3 }
    }
        
  }
  return table
end

function QUEGBackGlobal() 
  local table={}
  local tags={ "A", "B", "C", "D" }
  for n = 1,4 do
    local aX = 120 + 150*(n-1)
    table["SignalInput"..n] = {
      offset = {aX,330},
      { path = "SharedAudioJack", frames = 3},
    }
    table["SignalOutput"..tags[n]] = {
      offset = {aX,600},
      { path = "SharedAudioJack", frames = 3},
    }
  end
  table["vcoXIn"] = {
      offset = {275,890},
      { path = "SharedCVJack", frames = 3},
    }
  table["vcoYIn"] = {
      offset = {525,890},
      { path = "SharedCVJack", frames = 3},
    }
  table["vcoXOut"] = {
      offset = {230,1160},
      { path = "SharedCVJack", frames = 3},
    }
  table["vcoYOut"] = {
      offset = {480,1160},
      { path = "SharedCVJack", frames = 3},
    }
  return table
end

function QUEGBack(n)
  local table={}
  local x0 = 960+500*(n-1)
  local y0 = 450
  local dY = 440
  table["X"..n.."In"] = {
      offset = {x0,y0},
      { path = "SharedCVJack", frames = 3},
    }
  table["Y"..n.."In"] = {
      offset = {x0+150,y0},
      { path = "SharedCVJack", frames = 3},
    }
  table["level"..n.."In"] = {
      offset = {x0,y0+150},
      { path = "SharedCVJack", frames = 3},
    }
  table["mode"..n.."In"] = {
      offset = {x0+150,y0+150},
      { path = "SharedCVJack", frames = 3},
    }
  table["A"..n.."Out"] = {
      offset = {x0,y0+dY},
      { path = "SharedCVJack", frames = 3},
    }
  table["B"..n.."Out"] = {
      offset = {x0+150,y0+dY},
      { path = "SharedCVJack", frames = 3},
    }
  table["C"..n.."Out"] = {
      offset = {x0,y0+dY+150},
      { path = "SharedCVJack", frames = 3},
    }
  table["D"..n.."Out"] = {
      offset = {x0+150,y0+dY+150},
      { path = "SharedCVJack", frames = 3},
    }
  table["X"..n.."Out"] = {
      offset = {x0,y0+dY+300},
      { path = "SharedCVJack", frames = 3},
    }
  table["Y"..n.."Out"] = {
      offset = {x0+150,y0+dY+300},
      { path = "SharedCVJack", frames = 3},
    }
  return table
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
		offset = { 185, 1915 },
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	QUEG(1),
	QUEG(2),
	QUEG(3),
	QUEG(4),
	VCOFront()
}
back = { 
	Bg = {
		{ path = "backPanel" },
	},
	Placeholder = {
		offset = { 3000, 300 },
		{ path = "Placeholder" },
	},
	deviceName = {
    offset = { 3300, 75},
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  QUEGBackGlobal(),
  QUEGBack(1),
  QUEGBack(2),
  QUEGBack(3),
  QUEGBack(4),
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
