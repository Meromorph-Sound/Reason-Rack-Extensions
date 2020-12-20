format_version = "3.0"



custom_properties = jbox.property_set{
	document_owner = {
		properties = {
		  GrowthRate = jbox.number {
		    property_tag = 11,
		    default = 0.05,
		    ui_name = jbox.ui_text("propertyname_Detail1"),
		    ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
		  },
		  Barrier = jbox.number {
        property_tag = 12,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Detail2"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      InputScale = jbox.number {
        property_tag = 13,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Detail3"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Amplitude = jbox.number {
        property_tag = 14,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Detail4"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Smoothing = jbox.number {
        property_tag = 15,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Approximation"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Smooth = jbox.number {
        property_tag = 16,
        default = 0,
        steps = 2,
        ui_name = jbox.ui_text("propertyname_Algorithm"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=0}}})
      }
		}
	},
	rtc_owner = {
		properties = { instance = jbox.native_object{} }
	},
	rt_owner = {
	}
}

midi_implementation_chart = {
	midi_cc_chart = {}
}

remote_implementation_chart = {
}

ui_groups = {}

cv_inputs = {
}
cv_outputs = {
}

audio_inputs = {
  audioInL = jbox.audio_input{ ui_name = jbox.ui_text("audioInputL") },
  audioInR = jbox.audio_input{ ui_name = jbox.ui_text("audioInputR") },
}
audio_outputs = {
	audioOutL = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputL") },
	audioOutR = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputR") },
}




