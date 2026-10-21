tab = {}
function text_devive(text)
	local pos = string.find(text,'=')
	tab[1] = string.sub(text,1,pos-1)
	tab[2] = string.sub(text,pos+1,-1)
	return ""
end
function roundCoordinates(input)
    local rounded = {}
    for token in string.gmatch(input, "[^%s]+") do
        local number = tonumber(token)
        if number then

            local roundedNumber = math.floor(number + 0.5)
            table.insert(rounded, roundedNumber)
        else

            table.insert(rounded, token)
        end
    end
    return table.concat(rounded, " ")
end
print(roundCoordinates("m 33.344 81.031 l 25.484 81.031 25.484 30.891 b 23.594 32.703 21.109 34.516 18.031 36.313 14.953 38.125 12.188 39.484 9.75 40.391 l 9.75 32.781 b 14.141 30.703 18 28.203 21.281 25.266 24.578 22.313 26.906 19.469 28.281 16.688 l 33.344 16.688 33.344 81.031 c0"))
