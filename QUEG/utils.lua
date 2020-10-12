local utils={}


function utils.makeWidget(kind,channel,nodeName,propName)
  local prop = propName or nodeName
  return jbox[kind] { 
    graphics = { node = nodeName..channel },
    value = "/custom_properties/"..prop..channel
  }
end

function utils.makeCV(name,direction) 
  local func = "cv_"..direction.."_socket"
 return jbox[func] {
      graphics = { node = name },
      socket = "/cv_"..direction.."s/"..name
    }
end

function utils.allCVNames(tab,suffix,list) 
    for n = 1, 4 do
      for k, tag in pairs(list) do
        table.insert(tab,tag..n..suffix)
      end
    end
end

function utils.makePanel(widg,extras)
  widg = widg or {} 
  extras = extras or {}
  local args = { 
    graphics = { node = "Bg" },
    widgets = widg
  }
  for k, v in pairs(extras) do
    table.insert(args,v)
  end
  return jbox.panel(args)
end


return utils