format_version = "1.0"

function append(list1,list2)
  for k, v in pairs(list2) do
    table.insert(list1,v)
  end
  return list1
end  

function notificationsFor(base) 
  local out={}
  for n = 1,4 do
    table.insert(out,base..n)
  end
  return out
end

function notifications(bases) 
  local out={}
  for k,v in pairs(bases) do
    append(out,notificationsFor("/custom_properties/"..v))
  end
  jbox.trace("Made notifications:")
  jbox.trace(table.concat(out,', '))
  return out
end



  

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

--rt_input_setup = { 
--	notify = notifications({
--	   "/custom_properties/A",
--	   "/custom_properties/B",
--	   "/custom_properties/C",
--	   "/custom_properties/D"
-- })
--}
rt_input_setup = {
  notify = notifications({"x","y","level"})
}
