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
      Amplitude = jbox.number {
        property_tag = 24,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Amplitude"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Smoothing = jbox.number {
        property_tag = 25,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Smoothing"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Smooth = jbox.number {
        property_tag = 26,
        default = 0,
        steps = 2,
        ui_name = jbox.ui_text("propertyname_Smooth"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=0}}})
      },
      Zero = jbox.number {
        property_tag = 27,
        default = 0,
        steps = 2,
        ui_name = jbox.ui_text("propertyname_Zero"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=0}}})
      },
		}
	},
	rtc_owner = {
		properties = { instance = jbox.native_object{} }
	},
	rt_owner = {
		properties = {
		InMode = jbox.number {
        property_tag = 11,
        default = 0,
        steps = 4,
        ui_name = jbox.ui_text("inMode"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=0}}})
      },
		OutMode = jbox.number {
        property_tag = 12,
        default = 0,
        steps = 4,
        ui_name = jbox.ui_text("outMode"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=0}}})
      }
		},
		
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

audio_inputs = {
  audioIn = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") }
}
audio_outputs = {
	audioOut = jbox.audio_output{ ui_name = jbox.ui_text("audioOutput") }
}




