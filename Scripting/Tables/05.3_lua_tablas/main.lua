-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = {
{name = "gryphon"},
{name = "mage"},
{name = "grunt"},
{name = "peon"},
{name = "dragon"}
}
currentCreatureIndex = 1
-- Writing it like this prevents numeric access, as they are treated as string keys
--creatures.gryphon = {name = "gryphon"}
--creatures.mage = {name = "mage"}
--creatures.grunt = {name = "grunt"}
--creatures.peon = {name = "peon"}
--creatures.dragon = {name = "dragon"}
folder = "creatures/"
fileExtension = ".png"
-- Fin de tus variables globales

-- Define tus funciones y llamadas
function addCreature(name, positionX, positionY)
    fileName = folder..name..fileExtension
    addImage(fileName, positionX, positionY)    
end
-- Fin de tus funciones

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creature_name = creatures[currentCreatureIndex].name
        addCreature(creature_name, mousePositionX - 32, mousePositionY - 32)
        print("Previous: "..currentCreatureIndex)
        currentCreatureIndex = (currentCreatureIndex % 5) + 1
        print("NewIndex: "..currentCreatureIndex)

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

