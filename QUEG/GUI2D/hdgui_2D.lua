format_version = "2.0"

local utils={}

function utils.insert(array,extra) 
  for k, item in pairs(extra) do
    table.insert(array,item)
  end
end

function utils.append(array,extra) 
  for k, item in pairs(extra) do
    array[k]=item
  end
end

function utils.copy(array)
  local out = {}
  utils.append(out,array)
  return out
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





--function makeWidget(kind,channel,nodeName,propName)
--  local prop = propName or nodeName
--  return jbox[kind] { 
--    graphics = { node = nodeName..channel },
--    value = "/custom_properties/"..prop..channel
--  }
--end

function utils.propname(property)
  return "/custom_properties/"..property
end

function utils.widget(kind,node,property,extras)
  property=property or node
  local params = {
    graphics = { node = node },
    value = utils.propname(property)
  }
  utils.append(params,extras or {})
  return jbox[kind](params)
end

function utils.knob(node,extras)
  return utils.widget('analog_knob',node,node,extras)
end

function utils.toggle(node,extras)
  return utils.widget('toggle_button',node,node,extras)
end

function utils.radio(property,idx,target)
  local extra = {
    index = idx
  } 
  return utils.widget('radio_button',target,property,extra)
end

function utils.sequence(node,extras)
  return utils.widget('sequence_meter',node,node,extras)
end

function utils.updown(property,node,extras)
  local p = { show_automation_rect = false }
  utils.append(p,extras or {})
  return utils.widget('up_down_button',node,property,p)
end


function makeWidgets()
  local widgets = {
    jbox.device_name { graphics = { node = "deviceName" } },
    utils.widget("sequence_fader","onoffbypass","builtin_onoffbypass", { handle_size = 0 }),
    utils.knob("VCOpattern"),
    utils.updown("VCOpattern","VCOpattern_updown"),
     utils.toggle("VCOactive"),
    utils.toggle("VCOfreeze"),
    utils.widget("momentary_button","VCOzero"),
    utils.knob("VCOfrequency"),
    utils.knob("VCOwidth"),
    utils.knob("VCOheight")
  }
  
  local visibility = {
    visibility_switch = utils.propname("VCOpattern"),
    visibility_values = { 0,1 }
  }
  for n=1,4 do 
    local prop="VCOstart"..n
    table.insert(widgets, utils.updown(prop,"VCOstart_updown"..n,visibility))
    table.insert(widgets, utils.knob(prop,visibility))
  end

  for n=1, 4 do
    table.insert(widgets,jbox.custom_display {
      graphics = {
        node = "controller"..n 
      },
      display_width_pixels = 400,
      display_height_pixels = 400,
      values = { 
        utils.propname("x"..n), 
        utils.propname("y"..n),
         },
      draw_function = "drawController",
      gesture_function = "handleControllerInput"
    })
    --table.insert(widgets,jbox.analog_knob {
    --  graphics = { node = "level"..n },
    --  value = "/custom_properties/level"..n
    --})
    table.insert(widgets,utils.knob("level"..n))
    
    table.insert(widgets,utils.radio("source"..n,0,"vco"..n))
    table.insert(widgets,utils.radio("source"..n,1,"manual"..n))
    table.insert(widgets,utils.radio("source"..n,2,"bypass"..n))
    table.insert(widgets,utils.sequence("A"..n))
    table.insert(widgets,utils.sequence("B"..n))
    table.insert(widgets,utils.sequence("C"..n))
    table.insert(widgets,utils.sequence("D"..n))
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
