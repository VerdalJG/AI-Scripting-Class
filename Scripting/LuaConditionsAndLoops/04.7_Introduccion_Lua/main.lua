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

-- Escribe c�digo para funciones necesarias

-- Termina tu c�digo

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu c�digo para el bot�n izquierdo
        -- Termina tu c�digo
        resetGame()
    end
end



function onClickRight(down)
    print("Clicked Right")
    if not down then
        -- Escribe tu c�digo para el bot�n derecho
        -- Termina tu c�digo
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

