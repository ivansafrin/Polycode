class "TweenManager"

function TweenManager:TweenManager()
	self.tweens = {}
end

function TweenManager:addTween(tween)
	self.tweens[count(self.tweens)+1] = tween
end

function TweenManager:Update(elapsed)
	for i=#self.tweens,1,-1 do
		self.tweens[i]:Update(elapsed)
		if self.tweens[i].complete == true then
			table.remove(self.tweens, i)
		end
	end
end

class "Tween" (EventDispatcher)

Tween.EASE_NONE = 0
Tween.EASE_IN_QUAD = 1
Tween.EASE_OUT_QUAD = 2
Tween.EASE_INOUT_QUAD = 3
Tween.EASE_IN_CUBIC= 4
Tween.EASE_OUT_CUBIC= 5
Tween.EASE_INOUT_CUBIC= 6
Tween.EASE_IN_QUART= 7
Tween.EASE_OUT_QUART= 8
Tween.EASE_INOUT_QUART= 9
Tween.EASE_IN_QUINT= 10
Tween.EASE_OUT_QUINT= 11
Tween.EASE_INOUT_QUINT= 12
Tween.EASE_IN_SINE= 13
Tween.EASE_OUT_SINE= 14
Tween.EASE_INOUT_SINE= 15
Tween.EASE_IN_EXPO= 16
Tween.EASE_OUT_EXPO= 17
Tween.EASE_INOUT_EXPO= 18
Tween.EASE_IN_CIRC= 19
Tween.EASE_OUT_CIRC= 20
Tween.EASE_INOUT_CIRC= 21
Tween.EASE_IN_BOUNCE= 22
Tween.EASE_OUT_BOUNCE = 23
Tween.EASE_INOUT_BOUNCE = 24

function Tween.fEASE_IN_QUAD(t, startVal, cVal, endTime)
	t = t / endTime
	return cVal*t*t + startVal
end

function Tween.fEASE_OUT_QUAD(t, startVal, cVal, endTime)
	t = t / endTime
	return -cVal * t*(t-2.0) + startVal
end

function Tween.fEASE_INOUT_QUAD(t, startVal, cVal, endTime)
	t = t / (endTime/2.0)
	if t < 1.0 then return cVal/2.0*t*t + startVal end
	t = t - 1
	return -cVal/2.0 * (t*(t-2.0) - 1.0) + startVal
end

function Tween.fEASE_IN_CUBIC(t, startVal, cVal, endTime)
	t = t / endTime
	return cVal*t*t*t + startVal
end

function Tween.fEASE_OUT_CUBIC(t, startVal, cVal, endTime)
	t = t / endTime
	t = t - 1
	return cVal*(t*t*t + 1.0) + startVal
end

function Tween.fEASE_INOUT_CUBIC(t, startVal, cVal, endTime)
	t = t / (endTime/2.0)
	if t < 1.0 then return cVal/2.0*t*t*t + startVal end
	t = t - 2.0
	return cVal/2.0*(t*t*t + 2.0) + startVal
end

function Tween.fEASE_IN_QUART(t, startVal, cVal, endTime)
	t = t / endTime
	return cVal*t*t*t*t + startVal
end

function Tween.fEASE_OUT_QUART(t, startVal, cVal, endTime)
	t = t / endTime
	t = t - 1
	return -cVal * (t*t*t*t - 1.0) + startVal
end

function Tween.fEASE_INOUT_QUART(t, startVal, cVal, endTime)
	t = t / (endTime/2.0)
	if t < 1.0 then return (cVal/2.0*t*t*t*t) + startVal end
	t = t - 2.0
	return -cVal/2.0 * (t*t*t*t - 2.0) + startVal
end

function Tween.fEASE_IN_QUINT(t, startVal, cVal, endTime)
	t = t / endTime
	return cVal*t*t*t*t*t + startVal
end

function Tween.fEASE_OUT_QUINT(t, startVal, cVal, endTime)
	t = t / endTime
	t = t - 1
	return cVal*(t*t*t*t*t + 1.0) + startVal
end

function Tween.fEASE_INOUT_QUINT(t, startVal, cVal, endTime)
	t = t / (endTime / 2.0)
	if t < 1.0 then
		return (cVal/2.0*t*t*t*t*t) + startVal
	else
		t = t - 2.0
		return ((cVal/2.0)*((t*t*t*t*t) + 2.0)) + startVal
	end
end

function Tween.fEASE_IN_SINE(t, startVal, cVal, endTime)
	return -cVal * cos(t/endTime * (pi/2.0)) + cVal + startVal
end

function Tween.fEASE_OUT_SINE(t, startVal, cVal, endTime)
	return cVal * sin(t/endTime * (pi/2.0)) + startVal
end

function Tween.fEASE_INOUT_SINE(t, startVal, cVal, endTime)
	return -cVal/2.0 * (cos(pi*t/endTime) - 1.0) + startVal
end

function Tween.fEASE_IN_EXPO(t, startVal, cVal, endTime)
	return (cVal * pow( 2.0, 10.0 * (t/endTime - 1.0) ) + startVal)
end

function Tween.fEASE_OUT_EXPO(t, startVal, cVal, endTime)
	return cVal * ( -pow( 2.0, -10.0 * t/endTime ) + 1.0 ) + startVal
end

function Tween.fEASE_INOUT_EXPO(t, startVal, cVal, endTime)
	t = t / (endTime/2.0)
	if t < 1.0 then return cVal/2.0 * pow( 2.0, 10.0 * (t - 1.0) ) + startVal end
	t = t - 1
	return cVal/2.0 * ( -pow( 2.0, -10.0 * t) + 2.0 ) + startVal
end

function Tween.fEASE_IN_CIRC(t, startVal, cVal, endTime)
	t = t / endTime
	return -cVal * (sqrt(1.0 - t*t) - 1.0) + startVal
end	

function Tween.fEASE_OUT_CIRC(t, startVal, cVal, endTime)
	t = t/endTime
	t = t - 1
	return cVal * sqrt(1.0 - t*t) + startVal
end

function Tween.fEASE_INOUT_CIRC(t, startVal, cVal, endTime)
	t = t/(endTime/2.0)
	if t < 1.0 then return -cVal/2.0 * (sqrt(1.0 - t*t) - 1.0) + startVal end
	t = t - 2.0
	return cVal/2.0 * (sqrt(1.0 - t*t) + 1.0) + startVal
end

function Tween.fEASE_IN_BOUNCE(t, startVal, cVal, endTime)
	t  = t / endTime
	if t < 1/2.75 then
		return cVal*(7.5625*t*t) + startVal
	elseif t < (2/2.75) then
		t = t - (1.5/2.75)
		return cVal*(7.5625*(t)*t + .75) + startVal
	elseif (t < (2.5/2.75)) then
		t = t - (2.25/2.75)
		return cVal*(7.5625*(t)*t + .9375) + startVal
	else
		t = t - (2.625/2.75)
		return cVal*(7.5625*(t)*t + .984375) + startVal
	end
end	

function Tween.fEASE_NONE(t, startVal, cVal, endTime)
	return cVal*t/endTime+startVal
end

Tween.fEASE_OUT_BOUNCE = Tween.fEASE_IN_BOUNCE
Tween.fEASE_INOUT_BOUNCE = Tween.fEASE_IN_BOUNCE

Tween.interpolateFunctions = {}


Tween.interpolateFunctions[Tween.EASE_NONE] = Tween.fEASE_NONE
Tween.interpolateFunctions[Tween.EASE_IN_QUAD] = Tween.fEASE_IN_QUAD
Tween.interpolateFunctions[Tween.EASE_OUT_QUAD] = Tween.fEASE_OUT_QUAD
Tween.interpolateFunctions[Tween.EASE_INOUT_QUAD] = Tween.fEASE_INOUT_QUAD
Tween.interpolateFunctions[Tween.EASE_IN_CUBIC] = Tween.fEASE_IN_CUBIC
Tween.interpolateFunctions[Tween.EASE_OUT_CUBIC] = Tween.fEASE_OUT_CUBIC
Tween.interpolateFunctions[Tween.EASE_INOUT_CUBIC] = Tween.fEASE_INOUT_CUBIC
Tween.interpolateFunctions[Tween.EASE_IN_QUART] = Tween.fEASE_IN_QUART
Tween.interpolateFunctions[Tween.EASE_OUT_QUART] = Tween.fEASE_OUT_QUART
Tween.interpolateFunctions[Tween.EASE_INOUT_QUART] = Tween.fEASE_INOUT_QUART
Tween.interpolateFunctions[Tween.EASE_IN_QUINT] = Tween.fEASE_IN_QUINT
Tween.interpolateFunctions[Tween.EASE_OUT_QUINT] = Tween.fEASE_OUT_QUINT
Tween.interpolateFunctions[Tween.EASE_INOUT_QUINT] = Tween.fEASE_INOUT_QUINT
Tween.interpolateFunctions[Tween.EASE_IN_SINE] = Tween.fEASE_IN_SINE
Tween.interpolateFunctions[Tween.EASE_OUT_SINE] = Tween.fEASE_OUT_SINE
Tween.interpolateFunctions[Tween.EASE_INOUT_SINE] = Tween.fEASE_INOUT_SINE
Tween.interpolateFunctions[Tween.EASE_IN_EXPO] = Tween.fEASE_IN_EXPO
Tween.interpolateFunctions[Tween.EASE_OUT_EXPO] = Tween.fEASE_OUT_EXPO
Tween.interpolateFunctions[Tween.EASE_INOUT_EXPO] = Tween.fEASE_INOUT_EXPO
Tween.interpolateFunctions[Tween.EASE_IN_CIRC] = Tween.fEASE_IN_CIRC
Tween.interpolateFunctions[Tween.EASE_OUT_CIRC] = Tween.fEASE_OUT_CIRC
Tween.interpolateFunctions[Tween.EASE_INOUT_CIRC] = Tween.fEASE_INOUT_CIRC
Tween.interpolateFunctions[Tween.EASE_IN_BOUNCE] = Tween.fEASE_IN_BOUNCE
Tween.interpolateFunctions[Tween.EASE_OUT_BOUNCE] = Tween.fEASE_OUT_BOUNCE 
Tween.interpolateFunctions[Tween.EASE_INOUT_BOUNCE] = Tween.fEASE_INOUT_BOUNCE

function Tween.fEASE_NONE(t, startVal, cVal, endTime)
	return cVal*t/endTime+startVal
end

function Tween:Tween(target, key, easeType, startVal, endVal, time, repeating, waitTime)
	EventDispatcher.EventDispatcher(self)
	self.target = target
	self.key = key
	self.easeType = easeType
	self.startVal = startVal
	self.endVal = endVal
	self.endTime = time
	self.repeating = repeating
	self.waitTime =waitTime
	self.cVal = endVal - startVal
	self.tweenTime = 0
	self.complete = false
	Services.TweenManager:addTween(self)
end

function Tween:Reset()
	self.tweenTime = 0
	self.complete = false
end

function Tween:Update(elapsed)
	if self.tweenTime >= self.endTime + self.waitTime then
		if self.repeating == true then
			self:Reset()
		else
			self.target[self.key] = self.endVal
			self.complete = true
			return
		end
	end
	
	if self.tweenTime > self.waitTime then
		self.target[self.key] = self:interpolateTween()
	end
	self.tweenTime = self.tweenTime + elapsed
end

function Tween:interpolateTween()
	return Tween.interpolateFunctions[self.easeType](self.tweenTime - self.waitTime, self.startVal, self.cVal, self.endTime)
end