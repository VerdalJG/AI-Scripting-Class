-- Escribe tu código
-- Declare table:
Vector = {}
Vector.__index = Vector -- index metamethod points to itself. allows inheritance and method resolution

-- Constructor
function Vector:new(x, y)
    local vector = setmetatable({}, self)
    vector.x = x or 0
    vector.y = y or 0
    return obj
end

-- Addition
function Vector:__add(other)
    return Vector:new(self.x + other.x, self.y + other.y)
end

-- Subtraction
function Vector:__sub(other)
    return Vector:new(self.x - other.x, self.y - other.y)
end

-- Multiply by scalar
function Vector:__mul(scalar)
    return Vector:new(self.x * scalar, self.y * scalar)
end

-- Divide by scalar
function Vector:__div(scalar)
    return Vector:new(self.x / scalar, self.y / scalar)
end

-- Dot product
function Vector.dot(vector1, vector2)
    return vector1.x * vector2.x + vector1.y * vector2.y
end

-- Get length
function Vector:length()
    return math.sqrt(self.x^2 + self.y^2)
end

-- Normalize
function Vector:normalize()
    local length = self:length()
    if length == 0 then return Vector:new(0, 0) end
    return Vector:new(self.x / length, self.y / length)
end

-- Print
function Vector:__tostring()
    return "(" .. self.x .. ", " .. self.y .. ")"
end

testV1 = Vector:new(5, 3)
testV2 = Vector:new(2, 6)

-- Print Vectors
print("testV1: ", testV1)
print("testV2: ", testV2)

-- Test Addition
testV3 = testV1 + testV2
print("Adding testV1 and testV2: ", testV3)

--Test Subtraction
testV4 = testV1 - testV2
print("Subtracting testV1 by testV2: ", testV4)

testScalar = 10
--Test Multiplication by scalar
testV5 = testV1 * testScalar
print("Multiplying testV1 and testScalar: ", testV5)

--Test Division by scalar
testV6 = testV1 / testScalar
print("Dividing testV1 by testScalar: ", testV6)

-- Dot Product
print("Dot Product: ", Vector.dot(testV1, testV2))

-- Length of Vector
print("Length: ", testV1:length())

-- Normalize Vector
print("Normalized: ", testV1:normalize())

-- Termina tu código
io.read()
