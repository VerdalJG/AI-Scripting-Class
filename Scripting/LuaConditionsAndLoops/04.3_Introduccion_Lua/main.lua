-- Escribe codigo
require "library"
prepareWindow()

carta, carta_image = drawImage(layer, "cards\\A_C.png", 256, 256, 79, 123)
mousePositionX = 0
mousePositionY = 0
numberKeyPressed = nil

function onUpdate(seconds)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
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
    image_file = nil
    if down then
        key_pressed = string.upper(convertKeyToChar(key))
        print("Key pressed: ", key_pressed)
        
        -- Escribe tu código para gestion de teclado
        if not numberKeyPressed then
            numberKeyPressed = key_pressed
        else
            card_code = numberKeyPressed .. "_" .. key_pressed
            numberKeyPressed = nil -- reset for next card
            root = "cards\\"
            file_extension = ".png"
            image_file = root .. card_code .. file_extension
        end
        -- Termina tu código
        
        if image_file then
            setImage(carta_image, image_file)
        end
    end
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()