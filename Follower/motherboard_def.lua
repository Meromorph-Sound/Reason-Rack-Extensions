format_version = "3.0"

custom_properties = jbox.property_set{	
	document_owner = { 
		properties = { 
			learningRate = jbox.number { 
				property_tag = 11,
				default = 0.0,
				ui_name = jbox.ui_text("propertyname_LearningRate"),
				ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
			},
			threshold = jbox.number { 
				property_tag = 12,
				default = 0.5,
				ui_name = jbox.ui_text("propertyname_Threshold"),
				ui_type = jbox.ui_linear({min=0, max=0.9999, units={{decimals=4}}}),
			},
			rectification = jbox.boolean {
				property_tag = 13,
				default = true,
				ui_name = jbox.ui_text("propertyname_Rectification"),
				ui_type = jbox.ui_selector { jbox.ui_text("on"), jbox.ui_text("off") },
			},
		}
	},
	rt_owner = {
		properties = {
			rectificationDisplay = jbox.number {
				property_tag = 14,
				default = 0.0,
				steps = 3,
				ui_name = jbox.ui_text("propertyname_RectificationDisplay"),
				ui_type = jbox.ui_selector { jbox.ui_text("halfwave"), jbox.ui_text("fullwave"), jbox.ui_text("squared") },
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
        signal = jbox.audio_input{
                ui_name = jbox.ui_text("audioInput")
        }
}

audio_outputs = {
        envelope = jbox.audio_output{
                ui_name = jbox.ui_text("envelopeOutput")
        },
        gate = jbox.audio_output{
                ui_name = jbox.ui_text("gateOutput")
        }
}

cv_outputs = {
}

jbox.set_effect_auto_bypass_routing {
  {"/audio_inputs/signal", "/audio_outputs/envelope"}
}


