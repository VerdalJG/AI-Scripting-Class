-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
creatureSizeX, creatureSizeY = getCreatureSize("griphon")
mousePositionX = 0
mousePositionY = 0
gameOver = false

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu c�digo para mover a la criatura
    -- Termina tu c�digo
    setPropPosition(creature, creaturePositionX, creaturePositionY)
    
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
        creaturePositionX, creaturePositionY = getPropPosition(creature)
        -- Escribe tu c�digo aqui para bot�n izquierdo rat�n
        -- Termina tu c�digo
    end
end

function onClickRight(down)
    print("Clicked Right")
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

