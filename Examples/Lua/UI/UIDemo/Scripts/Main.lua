-- **********************************************************************
-- This demo shows various UI controls you can use in your code
-- **********************************************************************

screen = Screen()
screen.rootEntity.snapToPixels = true
demoShape = ScreenLabel("DEMO", 64, "mono")
demoShape.positionAtBaseline = false
demoShape:setPositionMode(ScreenEntity.POSITION_CENTER)
screen:addChild(demoShape)
demoShape.position.x = 600
demoShape.position.y = 200

-- **********************************************************************
-- UIWindow is a draggable window container
-- **********************************************************************

window = UIWindow("Demo window", 300, 400)
window.position.x = 50
window.position.y = 50
screen:addChild(window)

-- **********************************************************************
-- UIButton lets you create a simple text button
-- and listen to its click event
-- **********************************************************************

button = UIButton("Rotate me", 100, 24)
window:addChild(button)
button.position.x = 20
button.position.y = 40

function onRotateButton(t, event)
	demoShape.rotation.roll = demoShape.rotation.roll + 30
end

button:addEventListener(nil, onRotateButton, UIEvent.CLICK_EVENT)

-- **********************************************************************
-- UITextInput is a text input field
-- **********************************************************************

input = UITextInput(false, 100, 16)
input:setText("DEMO")
window:addChild(input)
input.position.x = 140
input.position.y = 40

function onTextChange(t, event)
	demoShape:setText(input:getText())
end

input:addEventListener(nil, onTextChange, UIEvent.CHANGE_EVENT)

-- **********************************************************************
-- UICheckBox is a simple check box
-- **********************************************************************

checkBox = UICheckBox("Auto rotate", false)
window:addChild(checkBox)
checkBox.position.x = 20
checkBox.position.y = 80

function Update(elapsed)
	if checkBox:isChecked() then
		demoShape.rotation.roll = demoShape.rotation.roll + (elapsed * 100)
	end
end

-- **********************************************************************
-- UIHSlider is a horizontal value slider that changes
-- a value between two preset values
-- **********************************************************************

label = ScreenLabel("Scale me", 12, "sans")
window:addChild(label)
label.position.x = 20
label.position.y = 110

slider = UIHSlider(1.0, 3.0, 100)
window:addChild(slider)
slider.position.x = 115
slider.position.y = 116

function onSliderChange(t, event)
	demoShape.scale.x = slider:getSliderValue()
end

slider:addEventListener(nil, onSliderChange, UIEvent.CHANGE_EVENT)

-- **********************************************************************
-- UIColorBox is a box that lets you pick colors
-- to use it, you must also create a UIColorPicker that should be
-- shared between all UIColorBox instances
-- **********************************************************************

colorPicker = UIColorPicker()
screen:addChild(colorPicker)
colorPicker.position.x = 300
colorPicker.position.y = 300

colorBox = UIColorBox(colorPicker, Color(1.0, 1.0, 1.0, 1.0), 50, 30)
window:addChild(colorBox)
colorBox.position.x = 20
colorBox.position.y = 130

function onColorChange(t, event)
	demoShape.color = colorBox:getSelectedColor()
end

colorBox:addEventListener(nil, onColorChange, UIEvent.CHANGE_EVENT)

-- **********************************************************************
-- UIComboBox lets you create a drop down combo box
-- UIComboBox uses a UIGlobalMenu, which should be shared between all
-- controls that require a menu.
-- **********************************************************************

globalMenu = UIGlobalMenu()
screen:addChild(globalMenu)

comboBox = UIComboBox(globalMenu, 200)
window:addChild(comboBox)
comboBox.position.x = 20
comboBox.position.y = 180

comboBox:addComboItem("No Border")
comboBox:addComboItem("Thin Border")
comboBox:addComboItem("Thick Border")
comboBox:setSelectedIndex(0)

function onBlendingChange(t, event)
	if comboBox:getSelectedIndex() == 0 then
		demoShape.strokeEnabled = false
	elseif comboBox:getSelectedIndex() == 1 then
		demoShape.strokeEnabled = true
		demoShape.strokeWidth = 1.0
	else
		demoShape.strokeEnabled = true
		demoShape.strokeWidth = 3.0
	end
end

comboBox:addEventListener(nil, onBlendingChange, UIEvent.CHANGE_EVENT)
