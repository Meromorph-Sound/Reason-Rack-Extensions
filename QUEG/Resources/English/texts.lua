format_version = "1.0"
 

function insert(table,tags) 
  for tag, text in pairs(tags) do
    for n=1, 4 do
      table["propertyname_"..tag..n] = text.." "..n
    end
  end
end

function properties(table,tags) 
  for k, tag in pairs(tags) do
    table[tag]=string.upper(tag)
    for n=1, 4 do
      table["propertyname_"..tag..n] = tag.." "..n
      table[tag..n]=string.upper(tag).." "..n
    end
  end
end

function cvs(table,tags)
  for idx,tag in pairs(tags) do
    for n=1, 4 do
      table[tag..n.."In"] = tag.." "..n.." input"
      table[tag..n.."Out"] = tag.." "..n.." output"
    end
  end
end

function vco(table,tags)
  for k, tag in pairs(tags) do
    table["propertyname_VCO"..tag] = "VCO "..tag
  end
end
  

texts = {
  ["on"] = "On",
  ["off"] = "Off",
  ["n/a"] = "N/A",
  ["VCO"] = "VCO",
  ["manual"] = "Manual",
  ["bypass"] = "Bypass",
  ["audioInput1"] = "In 1",
  ["audioInput2"] = "In 2",
  ["audioInput3"] = "In 3",
  ["audioInput4"] = "In 4",
  ["audioOutputA"] = "Out A",
  ["audioOutputB"] = "Out B",
  ["audioOutputC"] = "Out C",
  ["audioOutputD"] = "Out D",
  ["setController"] = "Set controller position",
  ["resetController"] = "Revert controller position",
  ["vcoXIn"] = "VCO X input",
  ["vcoYIn"] = "VCO Y input",
  ["vcoXOut"] = "VCO X output",
  ["vcoYOut"] = "VCO Y output",
 }
 
 properties(texts,{ "x", "y", "A", "B", "C", "D", "source", "level" } )
 cvs(texts,{ "X", "Y", "A", "B", "C", "D", "level", "mode"})
 vco(texts,{ "active", "freeze", "zero", "frequency", "width", "height", "pattern", 
             "start1", "start2", "start3", "start4" })
 insert(texts,{ ["x_shortest"] = "X", ["y_shortest"] = "Y", ["level_shortest"] = "L"} )
 
 
