-- Escribe codigo
require "library"
window_layer = prepareWindow()
require "prepare"

player_health = 50
max_player_health = 200

start_health_bar = 118
end_health_bar = 222

function onUpdate(seconds)
    healthPositionX, healthPositionY = getPropPosition(health_prop)
    -- Empieza tu código
    healthBarSizeX = end_health_bar - start_health_bar
    percentagePlayerHealth = player_health / max_player_health
    
    healthPositionX = start_health_bar + (percentagePlayerHealth * healthBarSizeX)
    -- Termina tu código
    setPropPosition(health_prop, healthPositionX, healthPositionY)
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
        -- Empieza tu código para botón izquierdo
        player_health = player_health - 10 -- Add 10 hp
        
        if player_health < 0 then
        player_health = 0
        end
        -- Termina tu código para botón izquierdo
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
        -- Empieza tu código para botón derecho
        player_health = player_health + 10 -- Add 10 hp
        
        if player_health > max_player_health then
        player_health = max_player_health
        end
        -- Termina tu código para botón derecho
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

