-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creaturesLoaded = {}
numberOfCreatures = 0
-- Termina tu definicion de variables

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        creatureProp = addCreature("griphon", mousePositionX - creatureSizeX / 2, mousePositionY - creatureSizeY / 2)
        creature = { prop = creatureProp , hp = 25}
        table.insert(creaturesLoaded, creature)  --New Creature
        numberOfCreatures = numberOfCreatures + 1
        --table.insert(creaturesInGameHP,numberOfCreatures, 25)           --Creature Health
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    if not down then
        print("Mouse Pos: ", mousePositionX,", ",mousePositionY)
        -- Escribe tu código para el botón derecho
        for num = 1, numberOfCreatures, 1 do
            creature = creaturesLoaded[num]
            creatureProp = creature.prop
            creatureX, creatureY = getPropPosition(creatureProp)
            if  mousePositionX >= (creatureX) and
                mousePositionX <= (creatureX  + creatureSizeX) and
                mousePositionY >= (creatureY) and
                mousePositionY <= (creatureY + creatureSizeY)
                then
                creature.hp = creature.hp - 5
                print("Creature HP: ", creature.hp," in pos: ",creatureX,", ",creatureY)
                if creature.hp == 0 then
                    removeCreature(creature.prop)
                    removed = table.remove(creaturesLoaded, num)
                    numberOfCreatures = numberOfCreatures - 1
                    break;
                end
            end
        end
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

