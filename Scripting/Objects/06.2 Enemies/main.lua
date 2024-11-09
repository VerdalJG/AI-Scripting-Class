-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

Enemy = {}
Enemy.__index = Enemy

enemyTypes = {
    gryphon ={name = "gryphon", max_hp = 70, size = {x = 92, y = 92}},
    mage = {name = "mage", max_hp = 50, size = {x = 64, y = 64}},
    grunt = {name = "grunt", max_hp = 30, size = {x = 72, y = 72}},
    peon = {name = "peon", max_hp = 20, size = {x = 32, y = 32}},
    dragon = {name = "dragon", max_hp = 100, size = {x = 128, y = 128}},
}

enemyKeys = {}
for key in pairs(enemyTypes) do -- allows us to access with numerical values
    table.insert(enemyKeys, key)
end

function getRandomEnemy(isFleeting)
    local randomIndex = math.random(1, #enemyKeys)
    local randomKey = enemyKeys[randomIndex]
    local enemyData = enemyTypes[randomKey]

    if isFleeting then
        return FleetingEnemy:new(enemyData.name, enemyData.max_hp, enemyData.size.x, enemyData.size.y)
    else
        return Enemy:new(enemyData.name, enemyData.max_hp, enemyData.size.x, enemyData.size.y)
    end
end

enemies = {}
spawnRate = 10
spawnTimer = 0

--Constructor
function Enemy:new(name, max_hp, sizeX, sizeY)
    local enemy = setmetatable({}, self)
    enemy.name = name
    enemy.hp = max_hp
    enemy.max_hp = max_hp
    enemy.size = {x = sizeX or 0, y = sizeY or 0}
    enemy.position = {x = math.random(0, 1024 - sizeX / 2), y = math.random(0, 768 - sizeY / 2)}
    enemy.image = nil
    return enemy
end

-- Receiving damage
function Enemy:takeDamage(damage)
    self.hp = self.hp - damage
    if self.hp <= 0 then
       self:die()
    else
    print("Damaged: ".. self.name .. " Health: " .. self.hp)
    end
end

-- Death
function Enemy:die()
    removeImage(self.image)
    self.size.x = self.size.x / 2
    self.size.y = self.size.y / 2
    xDrawPosition = self.position.x - self.size.x / 2
    yDrawPosition = self.position.y - self.size.y / 2
    
    self.hp = self.max_hp
    filePath = "creatures/" .. self.name .. ".png"
    self.image = addImage(filePath, xDrawPosition, yDrawPosition, self.size.x, self.size.y)
    print(self.name .. " died!")
end

-- FleetingEnemy class
FleetingEnemy = setmetatable({}, {__index = Enemy})
FleetingEnemy.__index = FleetingEnemy

-- Constructor
function FleetingEnemy:new(name, max_hp, sizeX, sizeY)
    local enemy = Enemy:new(name, max_hp, sizeX or 0, sizeY or 0)
    setmetatable(enemy, self)
    return enemy
end

-- Override takeDamage
function FleetingEnemy:takeDamage(damage)
    Enemy.takeDamage(self, damage)
    if self.hp > 0 and self.hp < self.max_hp / 2 then
        self:warp()
    end
end

-- Warp to a random position
function FleetingEnemy:warp()
    removeImage(self.image)
    local randomX = math.random(0, 1024)  -- Viewport width
    local randomY = math.random(0, 768)  -- Viewport height
    self.position.x = randomX
    self.position.y = randomY
    xDrawPosition = self.position.x - self.size.x / 2
    yDrawPosition = self.position.y - self.size.y / 2
    
    filePath = "creatures/" .. self.name .. ".png"
    self.image = addImage(filePath, xDrawPosition, yDrawPosition, self.size.x, self.size.y)
    print(self.name .. " flees to position: (" .. randomX .. ", " .. randomY .. ")")
end

function onUpdate(seconds)
    spawnTimer = spawnTimer - seconds
    if spawnTimer <= 0 then
        isFleeting = math.random(0, 1) == 1 -- In Lua, 0 is true
        enemy = getRandomEnemy(isFleeting)
        table.insert(enemies, enemy)
        filePath = "creatures/" .. enemy.name .. ".png"
        xPosition = enemy.position.x - enemy.size.x / 2 
        yPosition = enemy.position.y - enemy.size.y / 2 
        enemy.image = addImage(filePath, xPosition, yPosition, enemy.size.x, enemy.size.y)
        spawnTimer = spawnRate
    end
end

function onClickLeft(down)
    if down then
        for i, enemy in pairs(enemies) do
            local enemyPositionX, enemyPositionY = enemy.position.x, enemy.position.y
            local enemySizeX, enemySizeY = enemy.size.x, enemy.size.y

            if mousePositionX >= enemyPositionX - enemySizeX / 2 and mousePositionX <= (enemyPositionX + enemySizeX / 2) and
               mousePositionY >= enemyPositionY - enemySizeY / 2 and mousePositionY <= (enemyPositionY + enemySizeY / 2) then
                enemy:takeDamage(10)
                break
            end
        end
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

