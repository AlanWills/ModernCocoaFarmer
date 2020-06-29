local Loading = 
{
    SCENE_PATH = path.combine("Scenes", "Loading.scene"),
    LOADING_ROOT_NAME = "LoadingScene",
    TIME_NOTIFIER_NAME = "TimeNotifier",
    CONSTANTS_NAME = "Constants",
    MIN_LOADING_TIME = 5,
    FACT_NAME = "Fact",
    FACTS = 
    {
        "Go to www.moderncocoafarmer.org to find out more",
        "The events depicted in this game occur in real life every day",
        "Modern Cocoa Farmer has been designed by carefully studying the impact of child trafficking in Mali",
        "As much as possible, monetary values in this game are the real averages for people living in Mali",
        "Some monetary values could not be based on real averages - using them made the game impossible",
    }
}

---------------------------------------------------------------------------------
function Loading.new()
    -- Scene Initialization
    Scene.load(Loading.SCENE_PATH)

    Loading._currentFactIndex = 0
    Loading._numFacts = #Loading.FACTS
    Loading._root = GameObject.find(Loading.LOADING_ROOT_NAME)
    Loading._root:setActive(false)
end

---------------------------------------------------------------------------------
function Loading.getFact()
    local factIndex = Loading._currentFactIndex

    while factIndex == Loading._currentFactIndex do
        factIndex = math.random(Loading._numFacts)
    end

    Loading._currentFactIndex = factIndex
    return Loading.FACTS[Loading._currentFactIndex]
end

---------------------------------------------------------------------------------
function Loading.update(deltaTime)
    Loading._loadingTime = Loading._loadingTime + deltaTime

    if coroutine.status(Loading._loadCoroutine) ~= 'dead' then
        local result, error = coroutine.resume(Loading._loadCoroutine)
        if not result then
            log(error or "Undetermined Error")
        end
    elseif Loading._loadingTime >= Loading.MIN_LOADING_TIME then
        Loading.hide()
    end
end

---------------------------------------------------------------------------------
function Loading.show(loadFunction, loadCompleteFunction)
    local fact = Loading._root:findChild(Loading.CONSTANTS_NAME):findChild(Loading.FACT_NAME)
    fact:findComponent("Constant"):setValue(Loading.getFact())

    Loading._timeNotifierHandle = System.getTimeNotifierSystem():subscribe(Loading.update)
    Loading._root:setActive(true)
    Loading._loadCoroutine = coroutine.create(loadFunction)
    Loading._loadCompleteFunction = loadCompleteFunction
    Loading._loadingTime = 0
end

---------------------------------------------------------------------------------
function Loading.hide()
    if Loading._loadCompleteFunction ~= nil then
        Loading._loadCompleteFunction()
    end
    
    System.getTimeNotifierSystem():unsubscribe(Loading._timeNotifierHandle)

    Loading._timeNotifierHandle = 0
    Loading._root:setActive(false)
    --[[Loading._loadCompleteFunction = nil
    Loading._loadCoroutine = nil
    Loading._loadingTime = 0--]]
end

return Loading