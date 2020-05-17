local Inspect = require 'Core.Utils.Inspect'

local CommandParsing = {}

---------------------------------------------------------------------------------
function CommandParsing.parse(str)
    local words = {}
    local next = 0
    local subStr = ""

    while true do
        subStr, next = CommandParsing.next(str, next)
        table.insert(words, subStr)

        if next == nil or next > str:len() then
            break
        end
    end

    return words
end

---------------------------------------------------------------------------------
function CommandParsing.next(str, currentIndex)
    if str:sub(currentIndex, currentIndex) == '"' then
        local next = str:find('"', currentIndex + 1)

        if next ~= nil then
            return str:sub(currentIndex + 1, next - 1), next + 2
        else
            return str:sub(currentIndex + 1), next
        end
    else
        local next = str:find(' ', currentIndex)

        if next ~= nil then
            return str:sub(currentIndex, next - 1), next + 1
        else
            return str:sub(currentIndex), next
        end
    end
end

return CommandParsing