format_version = "1.0"

rtc_bindings = { 
  { source = "/environment/system_sample_rate", dest = "/global_rtc/init_instance" },
  { source = "/environment/instance_id", dest = "/global_rtc/init_instance" },
}

global_rtc = { 

  init_instance = function(source_property_path, instance_id)
    local new_no = jbox.make_native_object_rw("Instance", {instance_id})
    jbox.store_property("/custom_properties/instance", new_no);
  end,
}

sample_rate_setup = { 
native = {
    22050,
    44100,
    48000,
    88200,
    96000,
    192000
  },
}

rt_input_setup = { 
  notify = {
  "/custom_properties/builtin_onoffbypass",
  "/custom_properties/GrowthRate",
  "/custom_properties/Barrier",
  "/custom_properties/InputScale",
  "/custom_properties/Amplitude",
  "/custom_properties/Smoothing",
  "/custom_properties/Smooth",
  "/custom_properties/Zero",
  "/audio_inputs/audioIn/connected",
  "/cv_inputs/cvIn/connected",
  "/audio_outputs/audioOut/connected",
  "/cv_outputs/cvOut/connected",
  }
}