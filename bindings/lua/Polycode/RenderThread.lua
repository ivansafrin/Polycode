class "RenderThread"

RenderThread.JOB_REQUEST_CONTEXT_CHANGE = 0
RenderThread.JOB_CREATE_TEXTURE = 1
RenderThread.JOB_PROCESS_DRAW_BUFFER = 2
RenderThread.JOB_END_FRAME = 3
RenderThread.JOB_CREATE_PROGRAM = 4
RenderThread.JOB_CREATE_SHADER = 5
RenderThread.JOB_BEGIN_FRAME = 6
RenderThread.JOB_CREATE_VERTEX_BUFFERS = 7
RenderThread.JOB_DESTROY_TEXTURE = 8
RenderThread.JOB_DESTROY_SHADER = 9
RenderThread.JOB_DESTROY_PROGRAM = 10
RenderThread.JOB_DESTROY_BUFFER = 11
RenderThread.JOB_CREATE_RENDER_BUFFER = 12
RenderThread.JOB_DESTROY_RENDER_BUFFER = 13
RenderThread.JOB_SET_TEXTURE_PARAM = 14
RenderThread.JOB_DESTROY_SHADER_BINDING = 16
RenderThread.JOB_DESTROY_SHADER_PARAM = 17
RenderThread.JOB_CREATE_MESH = 18
RenderThread.JOB_DESTROY_MESH = 19

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

function RenderThread:setGraphicsInterface(core, graphicsInterface)
	local retVal = Polycode.RenderThread_setGraphicsInterface(self.__ptr, core.__ptr, graphicsInterface.__ptr)
end

function RenderThread:runThread()
	local retVal =  Polycode.RenderThread_runThread(self.__ptr)
end

function RenderThread:enqueueFrame(frame)
	local retVal = Polycode.RenderThread_enqueueFrame(self.__ptr, frame.__ptr)
end

function RenderThread:enqueueJob(jobType, data, data2)
	local retVal = Polycode.RenderThread_enqueueJob(self.__ptr, jobType, data.__ptr, data2.__ptr)
end

function RenderThread:processJob(job)
	local retVal = Polycode.RenderThread_processJob(self.__ptr, job.__ptr)
end

function RenderThread:getShaderBinding()
	local retVal =  Polycode.RenderThread_getShaderBinding(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function RenderThread:processDrawBuffer(buffer)
	local retVal = Polycode.RenderThread_processDrawBuffer(self.__ptr, buffer.__ptr)
end

function RenderThread:getFrameInfo()
	local retVal =  Polycode.RenderThread_getFrameInfo(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["RenderThreadDebugInfo"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function RenderThread:clearFrameQueue()
	local retVal =  Polycode.RenderThread_clearFrameQueue(self.__ptr)
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
