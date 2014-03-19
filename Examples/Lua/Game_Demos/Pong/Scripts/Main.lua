------------------------------------------------
-- Polycode Pong example by Ivan Safrin, 2013
------------------------------------------------

-- create a new Screen and set its height to 480
scene = PhysicsScene2D(1.0, 30)
scene:getDefaultCamera():setOrthoSize(0.0, 4.0)

-- load the playing field from the entity file and add it to the scene
field = SceneEntityInstance(scene, "Resources/field.entity")
scene:addChild(field)

-- get a handle to the player paddles and ball in the scene file and begin tracking collision

ball = field:getEntityById("ball", true)
scene:trackCollisionChild(ball, PhysicsScene2DEntity.ENTITY_RECT)

p1 = field:getEntityById("p1", true)
scene:trackCollisionChild(p1, PhysicsScene2DEntity.ENTITY_RECT)

p2 = field:getEntityById("p2", true)
scene:trackCollisionChild(p2, PhysicsScene2DEntity.ENTITY_RECT)

topWall = field:getEntityById("topWall", true)
scene:trackCollisionChild(topWall, PhysicsScene2DEntity.ENTITY_RECT)

bottomWall = field:getEntityById("bottomWall", true)
scene:trackCollisionChild(bottomWall, PhysicsScene2DEntity.ENTITY_RECT)

--load sounds
hitSound = Sound("Resources/hit.wav")
scoreSound = Sound("Resources/score.wav")

ballSpeed = 4.0
ballDirection = Vector2(1.0, 0.0)

-- initialize scores and get references to the player score labels on the field
p1scoreLabel = cast(field:getEntityById("p1ScoreLabel", true), SceneLabel)
p2scoreLabel = cast(field:getEntityById("p2ScoreLabel", true), SceneLabel)
p1Score = 0
p2Score = 0

function onCollision(t, event)
	-- we need to cast the event to PhysicsScreenEvent because this is a PhysicsScreen event
	physicsEvent = cast(event, PhysicsScene2DEvent)

	-- check if the colliding entity is the ball
	if physicsEvent.entity1 == ball then

		-- if colliding with player 1 or player 2 paddle
		if physicsEvent.entity2 == p1 or physicsEvent.entity2 == p2 then

			-- reverse the horizontal direction
			ballDirection.x = ballDirection.x * -1 

			-- adjust the vertical direction based on where on the paddle it hit
			ballDirection.y = (ball:getPosition().y - physicsEvent:getSecondEntity():getPosition().y)/1.0
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
scene:addEventListener(nil, onCollision, PhysicsScene2DEvent.EVENT_NEW_SHAPE_COLLISION)

-- Update is called automatically every frame
function Update(elapsed)

	-- check player 1 input
	if Services.Input:getKeyState(KEY_a) == true then
		p1:setPositionY( p1:getPosition().y + (3.0 * elapsed))
	elseif Services.Input:getKeyState(KEY_z) == true then
		p1:setPositionY( p1:getPosition().y - (3.0 * elapsed))
	end

	-- check player 2 input
	if Services.Input:getKeyState(KEY_UP) == true then
		p2:setPositionY( p2:getPosition().y + (3.0 * elapsed))
	elseif Services.Input:getKeyState(KEY_DOWN) == true then
		p2:setPositionY( p2:getPosition().y - (3.0 * elapsed))
	end

	-- limit the paddle positions so they don't go offscreen
	if p1:getPosition().y < -1.3 then p1:setPositionY(-1.3) end
	if p1:getPosition().y > 1.3 then p1:setPositionY(1.3) end
	if p2:getPosition().y < -1.3 then p2:setPositionY(-1.3) end
	if p2:getPosition().y > 1.3 then p2:setPositionY(1.3) end

	-- update the ball position
	ball:setPositionX(ball:getPosition().x + (ballDirection.x * ballSpeed * elapsed))
	ball:setPositionY( ball:getPosition().y + (ballDirection.y * ballSpeed * elapsed))

	-- check if the ball beyond player 1's paddle and increment player 2's score
	if ball:getPosition().x < -3 then
		ball:setPosition(0.0, 0.0)
		ballDirection.x = 1.0
		ballDirection.y = 0.0
		scoreSound:Play()
		p2Score = p2Score + 1
		p2scoreLabel:setText(""..p2Score)
	end

	-- check if the ball beyond player 2's paddle and increment player 1's score
	if ball:getPosition().x > 3 then
		ball:setPosition(0.0, 0.0)
		ball:setPositionY(0)
		ballDirection.x = -1.0
		ballDirection.y = 0.0
		scoreSound:Play()
		p1Score = p1Score + 1
		p1scoreLabel:setText(""..p1Score)
	end
end