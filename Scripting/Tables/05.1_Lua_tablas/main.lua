-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
squarePositionX = 500
squarePositionY = 400
squareSizeX = 80
squareSizeY = 80
-- Termina tu definicion de variables

function pintarPunto(punto)
    -- Rellenar código para pintar un punto en la pantalla
    drawPoint(punto.X, punto.Y)
    -- Fin de código
end

function onUpdate(seconds)
end

function onDraw()
    -- Empieza tu código, que debe emplear la funcion pintarPunto
    for i = 0, squareSizeY, 1 do
        for j = 0, squareSizeX, 1 do
            punto = { X = (squarePositionX - squareSizeX / 2) + i, Y = (squarePositionY - squareSizeY / 2) + j }
            pintarPunto(punto)
        end
    end
    -- Termina tu código
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress, onDraw, window_layer)
mainLoop()

