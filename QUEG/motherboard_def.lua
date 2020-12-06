format_version = "3.0"

function name(tag,n)
  n = n or ""
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
  local props = {
    VCOactive = jbox.number {
     property_tag = 51,
     default = 0,
     steps = 2,
     ui_name = propName("VCOactive"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    },
    VCOfreeze = jbox.number {
     property_tag = 52,
     default = 0,
     steps = 2,
     ui_name = propName("VCOfreeze"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    },
    VCOzero = jbox.number {
     property_tag = 53,
     default = 0,
     steps = 2,
     ui_name = propName("VCOzero"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    },
    VCOfrequency = jbox.number {
     property_tag = 54,
     default = 0,
     ui_name = propName("VCOfrequency"),
     ui_type = jbox.ui_percent({decimals=2}),
    },
    VCOwidth = jbox.number {
     property_tag = 55,
     default = 0.5,
     ui_name = propName("VCOwidth"),
     ui_type = jbox.ui_percent({decimals=2}),
    },
    VCOheight = jbox.number {
     property_tag = 56,
     default = 0.5,
     ui_name = propName("VCOheight"),
     ui_type = jbox.ui_percent({decimals=2}),
    },
    VCOpattern = jbox.number {
     property_tag = 60,
     default = 0,
     steps = 8,
     ui_name = propName("VCOpattern"),
     ui_type = jbox.ui_selector { 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"),
      propName("VCOheight"),
      propName("VCOheight")
      }
    }, 
  }
  
  for n=1,4 do
    props["VCOstart"..n] = jbox.number {
     property_tag = 60+n,
     default = n-1,
     steps = 4,
     ui_name = propName("VCOstart",n),
     ui_type = jbox.ui_selector { 
      jbox.ui_text("A"), 
      jbox.ui_text("B"), 
      jbox.ui_text("C"), 
      jbox.ui_text("D")
      }
    } 
  end
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
    props[name("source",n)] = jbox.number {
     property_tag = 4+base,
     default = 1,
     steps = 3,
     ui_name = propName("source",n),
     ui_type = jbox.ui_selector { jbox.ui_text("VCO"), jbox.ui_text("manual"), jbox.ui_text("bypass") }
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
  jbox.trace("Made GUI properties:")
  for k,v in pairs(props) do
    jbox.trace(k.." : "..tostring(v))
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


function audioIn(tag) 
  return jbox.audio_input{ ui_name = jbox.ui_text(tag) }
end

function audioOut(tag) 
  return jbox.audio_output{ ui_name = jbox.ui_text(tag) }
end

function cvIn(tag) 
  return jbox.cv_input{ ui_name = jbox.ui_text(tag) }
end

function cvOut(tag) 
  return jbox.cv_output{ ui_name = jbox.ui_text(tag) }
end

function ChannelCVOut(channel)
  local tags = { "A", "B", "C", "D", "X", "Y" }
  local table={}
  for index, tag in pairs(tags) do
    local name=tag..channel.."Out"
    table[name] = cvOut(name)
  end
  return table
end

function ChannelCVIn(channel) 
  local tags = { "level", "mode", "X", "Y" }
  local table={}
  for index, tag in pairs(tags) do
    local name=tag..channel.."In"
    table[name] = cvIn(name)
  end
  return table
end

function CVOut(table)
  for n = 1,4 do
    local temp=ChannelCVOut(n)
    for k, v in temp do
      table[k]=v
    end
  end
  return table
end

function CVIn(table)
  for n = 1,4 do
    local temp=ChannelCVIn(n)
    for k, v in temp do
      table[k]=v
    end
  end
  return table
end
  

audio_inputs = {
  in1 = audioIn("audioInput1"),
  in2 = audioIn("audioInput2"),
  in3 = audioIn("audioInput3"),
  in4 = audioIn("audioInput4")
}

audio_outputs = {
  outA = audioOut("audioOutputA"),
  outB = audioOut("audioOutputB"),
  outC = audioOut("audioOutputC"),
  outD = audioOut("audioOutputD")
}

cv_inputs = {}
for n = 1,4 do
  local temp=ChannelCVIn(n)
  for k, v in pairs(temp) do
    cv_inputs[k]=v
  end
end
cv_inputs["vcoXIn"] = cvIn("vcoXIn")
cv_inputs["vcoYIn"] = cvIn("vcoYIn")


cv_outputs = {}
for n = 1,4 do
  local temp=ChannelCVOut(n)
  for k, v in pairs(temp) do
    cv_outputs[k]=v
  end
end
cv_outputs["vcoXOut"] = cvOut("vcoXOut")
cv_outputs["vcoYOut"] = cvOut("vcoYOut")




