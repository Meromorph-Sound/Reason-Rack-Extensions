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
      }
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
			gateCV1 = jbox.number {
       property_tag=15,
       default=1,
       steps=3,
       ui_name = jbox.ui_text("propertyname_GateDisplay"),
       ui_type = jbox.ui_selector { jbox.ui_text("off"), jbox.ui_text("n/a"), jbox.ui_text("on") },
      },
			rectificationDisplay2 = jbox.number {
        property_tag = 24,
        default = 0.0,
        steps = 3,
        ui_name = jbox.ui_text("propertyname_RectificationDisplay"),
        ui_type = jbox.ui_selector { jbox.ui_text("halfwave"), jbox.ui_text("fullwave"), jbox.ui_text("squared") },
      },
      gateCV2 = jbox.number {
       property_tag=25,
       default=1,
       steps=3,
       ui_name = jbox.ui_text("propertyname_GateDisplay"),
       ui_type = jbox.ui_selector { jbox.ui_text("off"), jbox.ui_text("n/a"), jbox.ui_text("on") },
      }
		}
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{},
		}
	},
}

audio_inputs = {
  signalleft1 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
  signalleft2 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
  signalright1 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
  signalright2 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") }
}

audio_outputs = {
  envelopeleft1 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") }, 
  envelopeleft2 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") },
  enveloperight1 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") }, 
  enveloperight2 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") },    
}

cv_outputs = {
  gate1 = jbox.cv_output{ ui_name = jbox.ui_text("gateOutput") },
  gate2 = jbox.cv_output{ ui_name = jbox.ui_text("gateOutput") },
}



