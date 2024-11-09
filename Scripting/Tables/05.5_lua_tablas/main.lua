-- Escribe codigo
require "library"
require "xml"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = readXML("creatures.xml")
gameMap = readXML("map.xml")
hasAttributes = false
---- Fin de tus variables globales

-- Define tus funciones y llamadas

function begin()
    if hasAttributes then
        creatures = readXML("creaturesWithAttributes.xml")
        gameMap = readXML("mapWithAttributes.xml")
    else 
        creatures = readXML("creatures.xml")
        gameMap = readXML("map.xml")
    end
end


function addCreature(creature_name, posX, posY)
    -- No Attributes -- 1 is creature name, 2 is the texture, 3 is the size
    if not hasAttributes then
        for i = 1, #creatures do
            if creatures[i][1][1] == creature_name then
                texture_name = creatures[i][2][1]
                sizeX = tonumber(creatures[i][3][1][1])
                sizeY = tonumber(creatures[i][3][2][1])
                positionX = tonumber(posX) - sizeX / 2
                positionY = tonumber(posY) - sizeY / 2
                addImage(texture_name, positionX, positionY, sizeX, sizeY)
                break
            end
        end
    else
    -- Has Attributes
        for i = 1, #creatures do
            if creatures[i].attr.name == creature_name then
                texture_name = creatures[i].attr.texture
                sizeX = tonumber(creatures[i].attr.sizeX)
                sizeY = tonumber(creatures[i].attr.sizeX)
                positionX = tonumber(posX) - sizeX / 2
                positionY = tonumber(posY) - sizeY / 2
                addImage(texture_name, positionX, positionY, sizeX, sizeY)
                break
            end
        end
    end
end

function drawMap(map)
    -- No Attributes --
    if not hasAttributes then
        for i = 1, #gameMap do
            addCreature(gameMap[i][1][1], gameMap[i][2][1][1], gameMap[i][2][2][1])
        end
    -- Has Attributes
    else
        for i = 1, #gameMap do
            addCreature(gameMap[i].attr.name, gameMap[i].attr.positionX, gameMap[i].attr.positionY)
        end
    end
end

-- Call functions
begin()
drawMap(gameMap)
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

