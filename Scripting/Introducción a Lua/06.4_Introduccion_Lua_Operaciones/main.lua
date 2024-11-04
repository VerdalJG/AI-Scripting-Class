-- Escribe codigo
require "library"
prepareWindow()

pointA_X = 0
pointA_Y = 0
pointB_X = 0
pointB_Y = 0

creature = drawCreature(layer, "griphon", 256, 256)
pointA = drawCreature(layer, "blue_pin", pointA_X, pointA_Y)
pointB = drawCreature(layer, "green_pin", pointB_X, pointB_Y)

mousePositionX = nil
mousePositionY = nil

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu c�digo
    
    -- Termina tu c�digo
    setPropPosition(creature, creaturePositionX, creaturePositionY)
    setPropPosition(pointA, pointA_X, pointA_Y)
    setPropPosition(pointB, pointB_X, pointB_Y)
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
        -- Escribe tu c�digo para el bot�n izquierdo
        
        -- Termina tu c�digo
        setPropPosition(creature, pointA_X, pointA_Y)
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
        -- Escribe tu c�digo para el bot�n derecho
        
        -- Termina tu c�digo
        setPropPosition(creature, pointA_X, pointA_Y)
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

