datapath = { }
datapath.sep = "."

local function at(s,i)
    return string.sub(s, i,i)
end

function datapath.combine(path1, path2, ...)
    if select('#',...) > 0 then
        local p = datapath.combine(path1,path2)
        local args = {...}
        for i = 1, #args do
            p = datapath.combine(p, args[i])
        end
        return p
    end

    local endOfPath1 = at(path1, #path1)
	local startOfPath2 = at(path2, 1)

	-- Make sure the first string isn't empty and doesn't end in the separator
	-- nor that the second string isn't empty and doesn't start with the separator
    if endOfPath1 ~= datapath.sep and endOfPath1 ~= "" and startOfPath2 ~= datapath.sep and startOfPath2 ~= "" then
        path1 = path1..datapath.sep
    end

    return path1..path2
end

return datapath