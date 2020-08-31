format_version = "3.0"

custom_properties = jbox.property_set{	
	document_owner = { 
		properties = { 
			learningRate1 = jbox.number { 
				property_tag = 11,
				default = 0.0,
				ui_name = jbox.ui_text("propertyname_LearningRate"),
				ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
			},
			threshold1 = jbox.number { 
				property_tag = 12,
				default = 0.5,
				ui_name = jbox.ui_text("propertyname_Threshold"),
				ui_type = jbox.ui_linear({min=0, max=0.9999, units={{decimals=4}}}),
			},
			rectification1 = jbox.boolean {
				property_tag = 13,
				default = true,
				ui_name = jbox.ui_text("propertyname_Rectification"),
				ui_type = jbox.ui_selector { jbox.ui_text("on"), jbox.ui_text("off") },
			},
			learningRate2 = jbox.number { 
        property_tag = 21,
        default = 0.0,
        ui_name = jbox.ui_text("propertyname_LearningRate"),
        ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
      },
      threshold2 = jbox.number { 
        property_tag = 22,
        default = 0.5,
        ui_name = jbox.ui_text("propertyname_Threshold"),
        ui_type = jbox.ui_linear({min=0, max=0.9999, units={{decimals=4}}}),
      },
      rectification2 = jbox.boolean {
        property_tag = 23,
        default = true,
        ui_name = jbox.ui_text("propertyname_Rectification"),
        ui_type = jbox.ui_selector { jbox.ui_text("on"), jbox.ui_text("off") },
      },
      learningRate3 = jbox.number { 
        property_tag = 31,
        default = 0.0,
        ui_name = jbox.ui_text("propertyname_LearningRate"),
        ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
      },
      threshold3 = jbox.number { 
        property_tag = 32,
        default = 0.5,
        ui_name = jbox.ui_text("propertyname_Threshold"),
        ui_type = jbox.ui_linear({min=0, max=0.9999, units={{decimals=4}}}),
      },
      rectification3 = jbox.boolean {
        property_tag = 33,
        default = true,
        ui_name = jbox.ui_text("propertyname_Rectification"),
        ui_type = jbox.ui_selector { jbox.ui_text("on"), jbox.ui_text("off") },
      },
		}
	},
	rt_owner = {
		properties = {
			rectificationDisplay1 = jbox.number {
				property_tag = 14,
				default = 0.0,
				steps = 3,
				ui_name = jbox.ui_text("propertyname_RectificationDisplay"),
				ui_type = jbox.ui_selector { jbox.ui_text("halfwave"), jbox.ui_text("fullwave"), jbox.ui_text("squared") },
			},
			rectificationDisplay2 = jbox.number {
        property_tag = 24,
        default = 0.0,
        steps = 3,
        ui_name = jbox.ui_text("propertyname_RectificationDisplay"),
        ui_type = jbox.ui_selector { jbox.ui_text("halfwave"), jbox.ui_text("fullwave"), jbox.ui_text("squared") },
      },
      rectificationDisplay3 = jbox.number {
        property_tag = 34,
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
  signal1 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
  signal2 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
  signal3 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") }
}

audio_outputs = {
  envelope1 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") }, 
  envelope2 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") },
  envelope3 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") },    
}

cv_outputs = {
  gate1 = jbox.cv_output{ ui_name = jbox.ui_text("gateOutput") },
  gate2 = jbox.cv_output{ ui_name = jbox.ui_text("gateOutput") },
  gate3 = jbox.cv_output{ ui_name = jbox.ui_text("gateOutput") },
}

jbox.set_effect_auto_bypass_routing {
  {"/audio_inputs/signal", "/audio_outputs/envelope"}
}


