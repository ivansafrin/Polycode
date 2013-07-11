------------------------------------------------
-- Polycode Pong example by Ivan Safrin, 2013
------------------------------------------------

-- create a new Screen and set its height to 480
screen = PhysicsScreen(1.0, 30)
screen:setNormalizedCoordinates(true, 480)

-- load the playing field from the entity file and add it to the screen
field = ScreenEntityInstance("Resources/field.entity2d")
screen:addChild(field)

-- get a handle to the player paddles and ball in the screen file and begin tracking collision

ball = field:getScreenEntityById("ball", true)
screen:trackCollisionChild(ball, PhysicsScreenEntity.ENTITY_RECT)

p1 = field:getScreenEntityById("p1", true)
screen:trackCollisionChild(p1, PhysicsScreenEntity.ENTITY_RECT)

p2 = field:getScreenEntityById("p2", true)
screen:trackCollisionChild(p2, PhysicsScreenEntity.ENTITY_RECT)

topWall = field:getScreenEntityById("topWall", true)
screen:trackCollisionChild(topWall, PhysicsScreenEntity.ENTITY_RECT)

bottomWall = field:getScreenEntityById("bottomWall", true)
screen:trackCollisionChild(bottomWall, PhysicsScreenEntity.ENTITY_RECT)

--load sounds
hitSound = Sound("Resources/hit.wav")
scoreSound = Sound("Resources/score.wav")

ballSpeed = 400.0
ballDirection = Vector2(1.0, 0.0)

-- initialize scores and get references to the player score labels on the field
p1scoreLabel = cast(field:getScreenEntityById("p1scoreLabel", true), ScreenLabel)
p2scoreLabel = cast(field:getScreenEntityById("p2scoreLabel", true), ScreenLabel)
p1Score = 0
p2Score = 0

function onCollision(t, event)
	-- we need to cast the event to PhysicsScreenEvent because this is a PhysicsScreen event
	physicsEvent = cast(event, PhysicsScreenEvent)

	-- check if the colliding entity is the ball
	if physicsEvent.entity1 == ball then

		-- if colliding with player 1 or player 2 paddle
		if physicsEvent.entity2 == p1 or physicsEvent.entity2 == p2 then

			-- reverse the horizontal direction
			ballDirection.x = ballDirection.x * -1 

			-- adjust the vertical direction based on where on the paddle it hit
			ballDirection.y = (ball.position.y - physicsEvent:getSecondEntity().position.y)/80.0
			if ballDirection.y > 1.0 then ballDirection.y = 1.0 end
			if ballDirection.y < -1.0 then ballDirection.y = -1.0 end
		else
			-- if collliding with the walls, simply reverse the vertical direction
			ballDirection.y = ballDirection.y * -1
		end

		-- play the hit sound
		hitSound:Play()
	end
end

-- add a collision listener to the Physics Screen
-- onCollision will now be called every time there is a collion between
-- entities that we are tracking
screen:addEventListener(nil, onCollision, PhysicsScreenEvent.EVENT_NEW_SHAPE_COLLISION)

-- Update is called automatically every frame
function Update(elapsed)

	-- check player 1 input
	if Services.Input:getKeyState(KEY_a) == true then
		p1.position.y = p1.position.y - (300 * elapsed)
	elseif Services.Input:getKeyState(KEY_z) == true then
		p1.position.y = p1.position.y + (300 * elapsed)
	end

	-- check player 2 input
	if Services.Input:getKeyState(KEY_UP) == true then
		p2.position.y = p2.position.y - (300 * elapsed)
	elseif Services.Input:getKeyState(KEY_DOWN) == true then
		p2.position.y = p2.position.y + (300 * elapsed)
	end

	-- limit the paddle positions so they don't go offscreen
	if p1.position.y < -180 then p1.position.y = -180 end
	if p1.position.y > 180 then p1.position.y = 180 end
	if p2.position.y < -180 then p2.position.y = -180 end
	if p2.position.y > 180 then p2.position.y = 180 end

	-- update the ball position
	ball.position.x = ball.position.x + (ballDirection.x * ballSpeed * elapsed)
	ball.position.y = ball.position.y + (ballDirection.y * ballSpeed * elapsed)

	-- check if the ball beyond player 1's paddle and increment player 2's score
	if ball.position.x < -328 then
		ball.position.x = -200
		ball.position.y = 0
		ballDirection.x = 1.0
		ballDirection.y = 0.0
		scoreSound:Play()
		p2Score = p2Score + 1
		p2scoreLabel:setText(""..p2Score)
	end

	-- check if the ball beyond player 2's paddle and increment player 1's score
	if ball.position.x > 328 then
		ball.position.x = 200
		ball.position.y = 0
		ballDirection.x = -1.0
		ballDirection.y = 0.0
		scoreSound:Play()
		p1Score = p1Score + 1
		p1scoreLabel:setText(""..p1Score)
	end
end