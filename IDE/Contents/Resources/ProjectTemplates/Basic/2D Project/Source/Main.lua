-- Generated from the basic screen template

screen = Screen()

font = Font("Resources/deutsche.ttf")

image = ScreenImage("Resources/Substance.png")
image.xscale = 0.5
image.yscale = 0.5
image.x = (640-(image.width*0.5))/2
image.y = (380-(image.height*0.5))/2
screen:addChild(image)

label = ScreenLabel(font, "Hello World!", 72, 0)
label.x = (640-label.width)/2
label.y = (750-label.height)/2
screen:addChild(label)
