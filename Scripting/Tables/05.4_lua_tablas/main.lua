-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = {
    gryphon ={name = "gryphon", size = {x = 92, y = 92}},
    mage = {name = "mage", size = {x = 64, y = 64}},
    grunt = {name = "grunt", size = {x = 72, y = 72}},
    peon = {name = "peon", size = {x = 32, y = 32}},
    dragon = {name = "dragon", size = {x = 128, y = 128}},
}

gameMap = {
    {
        name = "gryphon",
        position = { x = 200, y = 100},
    },
    {
        name = "mage",
        position = { x = 100, y = 200},
    },
    {
        name = "mage",
        position = { x = 100, y = 400},
    },
    {
        name = "peon",
        position = { x = 400, y = 100},
    },
    {
        name = "dragon",
        position = { x = 400, y = 400},
    },
    {
        name = "dragon",
        position = { x = 600, y = 400},
    },
    {
        name = "dragon",
        position = { x = 800, y = 400},
    },
}
    
-- Fin de tus variables globales

-- Define tus funciones y llamadas
function addCreature(creature_name, posX, posY)
    texture_name = "creatures/"..creatures[creature_name].name..".png"
    addImage(texture_name, posX, posY, creatures[creature_name].size.x, creatures[creature_name].size.y)
end

function drawMap(map)
    for iCreature = 1, #gameMap do
        creature_name = gameMap[iCreature].name
        creaturePositionX = gameMap[iCreature].position.x - creatures[creature_name].size.x / 2
        creaturePositionY = gameMap[iCreature].position.y - creatures[creature_name].size.y / 2
        addCreature(creature_name, creaturePositionX, creaturePositionY)
    end
end

drawMap(mapa)

-- Fin de tus funciones

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    if not down then
        -- Escribe tu código para el botón derecho
        -- Termina tu código
    end
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

