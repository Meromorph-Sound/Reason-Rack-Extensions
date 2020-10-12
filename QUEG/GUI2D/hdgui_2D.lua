format_version = "2.0"

local utils={}


function utils.makeWidget(kind,channel,nodeName,propName)
  local prop = propName or nodeName
  return jbox[kind] { 
    graphics = { node = nodeName..channel },
    value = "/custom_properties/"..prop..channel
  }
end

function utils.makeCV(name,direction) 
  local func = "cv_"..direction.."_socket"
 return jbox[func] {
      graphics = { node = name },
      socket = "/cv_"..direction.."s/"..name
    }
end

function utils.allCVNames(tab,suffix,list) 
    for n = 1, 4 do
      for k, tag in pairs(list) do
        table.insert(tab,tag..n..suffix)
      end
    end
end

function utils.makePanel(widg,extras)
  widg = widg or {} 
  extras = extras or {}
  local args = { 
    graphics = { node = "Bg" },
    widgets = widg
  }
  for k, v in pairs(extras) do
    table.insert(args,v)
  end
  return jbox.panel(args)
end




--function makeWidget(kind,channel,nodeName,propName)
--  local prop = propName or nodeName
--  return jbox[kind] { 
--    graphics = { node = nodeName..channel },
--    value = "/custom_properties/"..prop..channel
--  }
--end

function makeWidgets()
  local widgets = {
    jbox.device_name { graphics = { node = "deviceName" } },
    jbox.sequence_fader{
            graphics = { node = "onoffbypass" },
            handle_size = 0,
            value = "/custom_properties/builtin_onoffbypass",
    }
  }
  for n=1, 4 do
    table.insert(widgets,jbox.custom_display {
      graphics = {
        node = "controller"..n 
      },
      display_width_pixels = 400,
      display_height_pixels = 400,
      values = { 
        "/custom_properties/x"..n, 
        "/custom_properties/y"..n,
         },
      draw_function = "drawController",
      gesture_function = "handleControllerInput"
    })
    --table.insert(widgets,jbox.analog_knob {
    --  graphics = { node = "level"..n },
    --  value = "/custom_properties/level"..n
    --})
    table.insert(widgets,utils.makeWidget('analog_knob',n,"level"))
    table.insert(widgets,utils.makeWidget('toggle_button',n,"manual"))
    table.insert(widgets,utils.makeWidget('toggle_button',n,"vco"))
    table.insert(widgets,utils.makeWidget('sequence_meter',n,"A"))
    table.insert(widgets,utils.makeWidget('sequence_meter',n,"B"))
    table.insert(widgets,utils.makeWidget('sequence_meter',n,"C"))
    table.insert(widgets,utils.makeWidget('sequence_meter',n,"D"))
    -- {
    --  graphics = { node = "manual"..n },
    --  value = "/custom_properties/manual"..n,
    --})
--    table.insert(widgets,jbox.toggle_button {
--      graphics = { node = "vco"..n },
--      
--      value = "/custom_properties/vco"..n,
--    })
--    table.insert(widgets,jbox.sequence_meter {
--      value = "/custom_properties/A"..n,
--      graphics = { node = "A"..n }
--    })
--    table.insert(widgets,jbox.sequence_meter {
--      value = "/custom_properties/B"..n,
--      graphics = { node = "B"..n }
--    })
--    table.insert(widgets,jbox.sequence_meter {
--      value = "/custom_properties/C"..n,
--      graphics = { node = "C"..n }
--    })
--    table.insert(widgets,jbox.sequence_meter {
--      value = "/custom_properties/D"..n,
--      graphics = { node = "D"..n }
--    })
  end
  return widgets
end

front = jbox.panel { 
	graphics = { node = "Bg" },
	widgets = makeWidgets()
}

function allCVNames(tab,suffix,list) 
    for n = 1, 4 do
      for k, tag in pairs(list) do
        table.insert(tab,tag..n..suffix)
      end
    end
end

--function makeCVOut(tab,names) 
--  for k, name in pairs(names) do
--    local cv = jbox.cv_output_socket {
--      graphics = { node = name },
--      socket = "/cv_outputs/"..name
--    }
--    table.insert(tab,cv)
--  end
--end

--function makeCVs(tab,names,direction) 
--  local func = "cv_"..direction.."_socket"
--  for k, name in pairs(names) do
--    local cv = jbox[func] {
--      graphics = { node = name },
--      socket = "/cv_"..direction.."s/"..name
--    }
--    table.insert(tab,cv)
--  end
--end

--function makeCVIn(tab,names) 
--  for k, name in pairs(names) do
--    local cv = jbox.cv_input_socket {
--      graphics = { node = name },
--      socket = "/cv_inputs/"..name
--    }
--    table.insert(tab,cv)
--  end
--end

function allCVIn(tab,base,names)
  utils.allCVNames(base,"In",names)
  for k, name in pairs(base) do
    table.insert(tab,utils.makeCV(name,"input"))
  end
  --makeCVs(tab,base,"input")
end

function allCVOut(tab,base,names)
  utils.allCVNames(base,"Out",names)
  for k, name in pairs(base) do
    table.insert(tab,utils.makeCV(name,"output"))
  end
  --makeCVs(tab,base,"output")
end

local w = {
    jbox.placeholder { graphics = { node = "Placeholder" } },
    jbox.device_name { graphics = { node = "deviceName" } }
  }
for n=1,4 do
  table.insert(w, jbox.audio_input_socket {
      graphics = { node = "SignalInput"..n },
      socket = "/audio_inputs/in"..n
    })
end
local channels={'A','B','C','D' }
for k,v in pairs(channels) do
  table.insert(w, jbox.audio_output_socket {
      graphics = { node = "SignalOutput"..v },
      socket = "/audio_outputs/out"..v
    })
end
--    jbox.audio_input_socket {
--      graphics = { node = "SignalInput2" },
--      socket = "/audio_inputs/in2",
--    },
--    jbox.audio_input_socket {
--      graphics = { node = "SignalInput3" },
--      socket = "/audio_inputs/in3",
--    },
--    jbox.audio_input_socket {
--      graphics = { node = "SignalInput4" },
--      socket = "/audio_inputs/in4",
--    },
--    jbox.audio_output_socket {
--      graphics = { node = "SignalOutputA" },
--      socket = "/audio_outputs/outA",
--    },
--    jbox.audio_output_socket {
--      graphics = { node = "SignalOutputB" },
--      socket = "/audio_outputs/outB",
--    },
--    jbox.audio_output_socket {
--      graphics = { node = "SignalOutputC" },
--      socket = "/audio_outputs/outC",
--    },
--    jbox.audio_output_socket {
--      graphics = { node = "SignalOutputD" },
--      socket = "/audio_outputs/outD",
--    }
--  }
  

    
local tagsIn={ "vcoXIn", "vcoYIn" }
allCVIn(w,tagsIn,{"level", "mode", "X", "Y"})
local tagsOut={ "vcoXOut", "vcoYOut" }
allCVOut(w,tagsOut,{"A", "B", "C", "D", "X", "Y"})


back = jbox.panel { 
	graphics = { node = "Bg" },
	widgets = w
}

folded_front = jbox.panel { 
	graphics = { node = "Bg" },
	widgets = { }
}
folded_back = jbox.panel { 
	graphics = { node = "Bg" },
	cable_origin = { node = "CableOrigin" },
	widgets = { }
}
