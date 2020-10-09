format_version = "1.0"

function insert(table,tag,text) 
  for n=1, 4 do
    table["propertyname_"..tag..n] = text.." "..n
  end
end

texts = {
["on"] = "On",
  ["off"] = "Off",
  ["n/a"] = "N/A",
  ["audioInput1"] = "In 1",
  ["audioInput2"] = "In 2",
  ["audioInput3"] = "In 3",
  ["audioInput4"] = "In 4",
  ["audioOutputA"] = "Out A",
  ["audioOutputB"] = "Out B",
  ["audioOutputC"] = "Out C",
  ["audioOutputD"] = "Out D",
  ["setController"] = "Set controller position",
  ["resetController"] = "Revert controller position"
 }
 
 insert(texts,"x","X")
 insert(texts,"y","Y")
 insert(texts,"level","Level")
 insert(texts,"x_shortest","X")
 insert(texts,"y_shortest","Y")
 insert(texts,"level_shortest","L")
 insert(texts,"manual","Manual")
 insert(texts,"vco","VCO")
 insert(texts,"A","A")
 insert(texts,"B","B")
 insert(texts,"C","C")
 insert(texts,"D","D")
 
