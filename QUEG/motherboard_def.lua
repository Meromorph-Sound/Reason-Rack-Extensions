format_version = "3.0"

function makeN(n,item)
  local out={}
  for i = 1, n do
    table.insert(out,item)
  end
  return out
end
    

custom_properties = jbox.property_set{	
	document_owner = { 
		properties = { 
			x1 = jbox.number { 
				property_tag = 1,
				default = 0.5,
				ui_name = jbox.ui_text("propertyname_X"),
				ui_type = jbox.ui_linear({min=-1, max=1, units={{decimals=4}}}),
			},
			y1 = jbox.number { 
				property_tag = 2,
				default = 0.5,
				ui_name = jbox.ui_text("propertyname_Y"),
				ui_type = jbox.ui_linear({min=-1, max=1, units={{decimals=4}}}),
			},
			level1 = jbox.number {
			 property_tag = 3,
			 default = 0.5,
			 ui_name = jbox.ui_text("propertyname_level"),
			 ui_type = jbox.ui_percent({decimals=2}),
			},
			manual1 = jbox.boolean {
			 property_tag = 4,
			 default = true,
			 ui_name = jbox.ui_text("propertyname_manual"),
			 ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
			},
			vco1 = jbox.boolean {
       property_tag = 5,
       default = false,
       ui_name = jbox.ui_text("propertyname_vco"),
       ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
      },
	    A1 = jbox.number { 
        property_tag = 6,
        default = 0.5,
        ui_name = jbox.ui_text("propertyname_A"),
        ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
      }, 
      B1 = jbox.number { 
        property_tag = 7,
        default = 0.5,
        ui_name = jbox.ui_text("propertyname_B"),
        ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
      }, 
      C1 = jbox.number { 
        property_tag = 8,
        default = 0.5,
        ui_name = jbox.ui_text("propertyname_C"),
        ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
      }, 
      D1 = jbox.number { 
        property_tag = 9,
        default = 0.5,
        ui_name = jbox.ui_text("propertyname_D"),
        ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
      },  
	  }
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



