format_version = "3.0"

function makeN(n,item)
  local out={}
  for i = 1, n do
    table.insert(out,item)
  end
  return out
end

function makeProperties(n)
  local props = {}
  for n = 1,4 do
    local base=(n-1)*10
    props["x"..n] = jbox.number {
      property_tag = 1+base,
      default = 0.5,
      ui_name = jbox.ui_text("propertyname_X"),
      ui_type = jbox.ui_linear({min=-1, max=1, units={{decimals=4}}}),
    }
    props["y"..n] = jbox.number {
      property_tag = 2+base,
      default = 0.5,
      ui_name = jbox.ui_text("propertyname_Y"),
      ui_type = jbox.ui_linear({min=-1, max=1, units={{decimals=4}}}),    
    }
    props["level"..n] = jbox.number {
     property_tag = 3+base,
     default = 0.5,
     ui_name = jbox.ui_text("propertyname_level"),
     ui_type = jbox.ui_percent({decimals=2}),
    }
    props["manual"..n] = jbox.boolean {
     property_tag = 4+base,
     default = true,
     ui_name = jbox.ui_text("propertyname_manual"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    }
    props["vco"..n] = jbox.boolean {
     property_tag = 5+base,
     default = false,
     ui_name = jbox.ui_text("propertyname_vco"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    }
    props["A"..n] = jbox.number { 
      property_tag = 6+base,
      default = 0.5,
      ui_name = jbox.ui_text("propertyname_A"),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props["B"..n] = jbox.number { 
      property_tag = 7+base,
      default = 0.5,
      ui_name = jbox.ui_text("propertyname_B"),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props["C"..n] = jbox.number { 
      property_tag = 8+base,
      default = 0.5,
      ui_name = jbox.ui_text("propertyname_C"),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props["D"..n] = jbox.number { 
      property_tag = 9+base,
      default = 0.5,
      ui_name = jbox.ui_text("propertyname_D"),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    }
  end
  return props
end
    

custom_properties = jbox.property_set{	
  
	document_owner = { 
		properties =  makeProperties(),
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{},
		}
	},
}

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



