format_version = "3.0"



custom_properties = jbox.property_set{
	document_owner = {
		properties = {
		  GrowthRate = jbox.number {
		    property_tag = 21,
		    default = 0.05,
		    ui_name = jbox.ui_text("propertyname_GrowthRate"),
		    ui_type = jbox.ui_linear ({min=0, max=0.1, units={{decimals=5}}})
		  },
		  Barrier = jbox.number {
        property_tag = 22,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Barrier"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      InputScale = jbox.number {
        property_tag = 23,
        default = 1,
        ui_name = jbox.ui_text("propertyname_InputScale"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
		}
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{}
		}
	},
	rt_owner = {
		properties = {}
	}
}

midi_implementation_chart = {
	midi_cc_chart = {}
}

remote_implementation_chart = {
}

ui_groups = {}

cv_inputs = {
  cvIn = jbox.cv_input{ ui_name = jbox.ui_text("cvInput") }
}
cv_outputs = {
  cvOut = jbox.cv_output{ ui_name = jbox.ui_text("cvOutput") }
}

audio_inputs = {}
audio_outputs = {
	audioOut = jbox.audio_output{ ui_name = jbox.ui_text("audioOutput") }
}




