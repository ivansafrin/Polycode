class "RenderThread"

RenderThread.JOB_REQUEST_CONTEXT_CHANGE = 0
RenderThread.JOB_DESTROY_TEXTURE = 8
RenderThread.JOB_DESTROY_SHADER = 9
RenderThread.JOB_DESTROY_PROGRAM = 10
RenderThread.JOB_DESTROY_SUBMESH_BUFFER = 11
RenderThread.JOB_DESTROY_RENDER_BUFFER = 13

function RenderThread:RenderThread(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.RenderThread(unpack(arg))
	end
end

function RenderThread:runThread()
	local retVal =  Polycode.RenderThread_runThread(self.__ptr)
end

function RenderThread:beginFrame()
	local retVal =  Polycode.RenderThread_beginFrame(self.__ptr)
end

function RenderThread:endFrame()
	local retVal =  Polycode.RenderThread_endFrame(self.__ptr)
end

function RenderThread:updateRenderThread()
	local retVal =  Polycode.RenderThread_updateRenderThread(self.__ptr)
end

function RenderThread:processJob(job)
	local retVal = Polycode.RenderThread_processJob(self.__ptr, job.__ptr)
end

function RenderThread:clearFrameQueue()
	local retVal =  Polycode.RenderThread_clearFrameQueue(self.__ptr)
end

function RenderThread:getFrameInfo()
	local retVal =  Polycode.RenderThread_getFrameInfo(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["RenderThreadDebugInfo"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function RenderThread:initGlobals()
	local retVal =  Polycode.RenderThread_initGlobals(self.__ptr)
end

function RenderThread:lockRenderMutex()
	local retVal =  Polycode.RenderThread_lockRenderMutex(self.__ptr)
end

function RenderThread:unlockRenderMutex()
	local retVal =  Polycode.RenderThread_unlockRenderMutex(self.__ptr)
end

function RenderThread:__delete()
	if self then Polycode.delete_RenderThread(self.__ptr) end
end
