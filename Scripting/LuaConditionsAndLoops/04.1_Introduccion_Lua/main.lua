-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0
speed = 10
direction = 0 -- 0 = right, 1 = up, 2 = left, 3 = down

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu código para mover a la criatura
    
    -- Move the creature based on the current direction
    if direction == 0 then
        creaturePositionX = creaturePositionX + speed  -- Move right
    elseif direction == 1 then
        creaturePositionY = creaturePositionY - speed  -- Move up
    elseif direction == 2 then
        creaturePositionX = creaturePositionX - speed  -- Move left
    elseif direction == 3 then
        creaturePositionY = creaturePositionY + speed  -- Move down
    end
    -- creaturePositionX = creaturePositionX + speed  -- Move right
    -- Termina tu código
    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        creaturePositionX, creaturePositionY = getPropPosition(creature)
        -- Escribe tu código aqui para botón izquierdo ratón
        --speed = speed * -1
        direction = (direction + 1) % 4
        -- Termina tu código
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

