local SelectSingleChildCommand = {}

---------------------------------------------------------------------------------
function SelectSingleChildCommand.execute(familyManager, childToSelect)
    for k, child in ipairs(familyManager.children) do
        if child == childToSelect then
            child:select()
        elseif child:isSelected() then
            child:deselect()
        end
    end
end

return SelectSingleChildCommand