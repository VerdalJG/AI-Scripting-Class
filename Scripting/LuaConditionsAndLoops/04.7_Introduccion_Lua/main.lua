-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

number_cards_X = 4
number_cards_Y = 4
card_sizeX = 79
card_sizeY = 123

card_init_X = 20
card_init_Y = 20

-- Define tus variables globales

-- Termina tu definicion de variables

-- Escribe código para funciones necesarias

-- Termina tu código

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        -- Termina tu código
        resetGame()
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

