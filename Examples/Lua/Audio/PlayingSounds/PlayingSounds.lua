class "SoundApp" (EventHandler)

function SoundApp:SoundApp(image)
        self.sound = Sound("test.wav")
        self:EventHandler()
end

function SoundApp:handleEvent(e)
        if e:getDispatcher() == Services.Core:getInput() then
               if e:getEventCode() == EVENT_MOUSEDOWN then
                        self.sound:Play(false)
                end
        end
end

app = SoundApp()
Services.Core:getInput():addEventListener(app, EVENT_MOUSEDOWN)
