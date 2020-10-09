format_version = "3.0"

function name(tag,n)
  return tag..n
end

function propName(tag,n) 
  return jbox.ui_text("propertyname_"..name(tag,n))
end

function makeN(n,item)
  local out={}
  for i = 1, n do
    table.insert(out,item)
  end
  return out
end

function makeGUIProperties()
  local props = {}
  for n = 1,4 do
    local base=(n-1)*10
    props[name("x",n)] = jbox.number {
      property_tag = 1+base,
      default = 0.5,
      ui_name = propName("x",n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
    }
    props[name("y",n)] = jbox.number {
      property_tag = 2+base,
      default = 0.5,
      ui_name = propName("y",n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),    
    }
    props[name("level",n)] = jbox.number {
     property_tag = 3+base,
     default = 0.5,
     ui_name = propName("level",n),
     ui_type = jbox.ui_percent({decimals=2}),
    }
    props[name("manual",n)] = jbox.number {
     property_tag = 4+base,
     default = 1,
     steps = 2,
     ui_name = propName("manual",n),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    }
    props[name("vco",n)] = jbox.number {
     property_tag = 5+base,
     steps = 2,
     default = 0,
     ui_name = propName("vco",n),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    }
--    props[name("A",n)] = jbox.number { 
--      property_tag = 6+base,
--      default = 0.5,
--      ui_name = propName("A",n),
--      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
--    } 
--    props[name("B",n)] = jbox.number { 
--      property_tag = 7+base,
--      default = 0.5,
--      ui_name = propName("B",n),
--      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
--    } 
--    props[name("C",n)] = jbox.number { 
--      property_tag = 8+base,
--      default = 0.5,
--      ui_name = propName("C",n),
--      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
--    } 
--    props[name("D",n)] = jbox.number { 
--      property_tag = 9+base,
--      default = 0.5,
--      ui_name = propName("D",n),
--      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
--    }
  end
  return props
end

function makeRTProperties()
  local props = {}
  for n = 1,4 do
    local base=(n-1)*10
    props[name("A",n)] = jbox.number { 
      property_tag = 6+base,
      default = 0.5,
      ui_name = propName("A",n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props[name("B",n)] = jbox.number { 
      property_tag = 7+base,
      default = 0.5,
      ui_name = propName("B",n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props[name("C",n)] = jbox.number { 
      property_tag = 8+base,
      default = 0.5,
      ui_name = propName("C",n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props[name("D",n)] = jbox.number { 
      property_tag = 9+base,
      default = 0.5,
      ui_name = propName("D",n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    }
  end
  jbox.trace("Made RT properties:")
  for k,v in pairs(props) do
    jbox.trace(k.." : "..tostring(v))
  end
  return props
end
    

custom_properties = jbox.property_set{	
  
	document_owner = { 
		properties =  makeGUIProperties()
	},
	rt_owner = {
	 properties = makeRTProperties()
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{},
		}
	},
}

function makeMIDI(base,properties)
  local out={}
  local cc=base
  for channel = 1,4 do
    for k,tag in pairs(properties) do
      out[base] = "/custom_properties/"..name(tag,channel)
      base=base+1
    end
  end
  return out
end

function makeRemote(properties)
  local out = {}
  for k, tag in pairs(properties) do
    for channel = 1, 4 do
      local nm=name(tag,channel)
      local pn=propName(tag,channel)
      out["/custom_properties/"..nm] = {
        internal_name=nm,
        short_ui_name=propName(tag,channel),
        shortest_ui_name=propName(tag.."_shortest",channel)
      }
    end
  end
  return out
end
    

midi_implementation_chart = {
  midi_cc_chart = makeMIDI(39,{"level","x","y"})
}

remote_implementation_chart = makeRemote({"level","x","y"})


audio_inputs = {
  in1 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput1") },
  in2 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput2") },
  in3 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput3") },
  in4 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput4") },
}

audio_outputs = {
  outA = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputA") },
  outB = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputB") },
  outC = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputC") },
  outD = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputD") },
}

cv_inputs = {
}

cv_outputs = {
}



