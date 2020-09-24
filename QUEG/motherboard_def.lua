format_version = "3.0"
  

custom_properties = jbox.property_set{	
	document_owner = { 
		properties = { 
			x1 = jbox.number { 
				property_tag = 1,
				default = 0.0,
				ui_name = jbox.ui_text("propertyname_X"),
				ui_type = jbox.ui_linear({min=-1, max=1, units={{decimals=4}}}),
			},
			y1 = jbox.number { 
				property_tag = 2,
				default = 0.0,
				ui_name = jbox.ui_text("propertyname_Y"),
				ui_type = jbox.ui_linear({min=-1, max=1, units={{decimals=4}}}),
			},
		}
	},
	rt_owner = {
	  properties = {}
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



