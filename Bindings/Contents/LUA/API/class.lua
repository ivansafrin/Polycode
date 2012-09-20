local u = {}

function u.wrongarg(n,expected,got)
  return 'arg '..n..' expected to be '..expected..' (got '..tostring(got)..')'
end

local wrongarg = u.wrongarg

function u.isname(name)
  return type(name)=='string' and string.find(name,'^[_%a][_%w]*$')
end

local isname = u.isname

function u.assert(value,errmsg,...)
  if value then
    return value
  else
    if type(errmsg)=='nil' then
      error('assertion failed!',2)
    elseif type(errmsg)=='string' then
      error(errmsg,2)
    else
      error(errmsg(unpack(arg)),2)
    end
  end
end

local assert = u.assert

function u.fwrongarg(...)
  return function()
    return wrongarg(unpack(arg))
  end
end

local fwrongarg = u.fwrongarg




local INFO = '__info'


function u.isobject(o)
  return type(o)=='table' and rawget(o,INFO)
end

local isobject = u.isobject


local METAMETHODS = {
  '__tostring',
  '__add',
  '__sub',
  '__mul',
  '__div',
  '__pow',
  '__lt',
  '__le',
  '__eq',
  '__call',
  '__unm',
  '__concat',
  '__newindex',
}


local metatable = {}

for _, name in ipairs(METAMETHODS) do
  local name = name
  metatable[name] = function(...)
    local a, b = unpack(arg)
    local f
    if isobject(a) then
      f = a[name]
    end
    if not f and isobject(b) then
      f = b[name]
    end
    if not f then
    local name = name..'__'
    if isobject(a) then
      f = a[name]
    end
    if not f and isobject(b) then
      f = b[name]
    end
    end
    assert(f, function()
                 local class = rawget(a,INFO).__class
                 local cname = rawget(class,INFO).__name
                 return 'meta-method not found: '..cname..':'..name
               end)
    return f(unpack(arg))
  end
end


local
function table2object(t)
  assert(type(t)=='table', fwrongarg(1,'table',t))
  local info = {}
  rawset(t,INFO,info)
  setmetatable(t,metatable)

  local p = newproxy(true)
  local mp = getmetatable(p)
  function mp:__gc()
    if rawget(t,INFO) == info then
      t:finalize()
    end
  end
  rawget(t,INFO).__proxy = p

  return t
end

local
function object2table(o)
  assert(isobject(o), fwrongarg(1,'object',o))
  setmetatable(o,nil)
  rawset(o,INFO,nil)
  return o
end

local
function givename(o,name)
  assert(isobject(o), fwrongarg(1,'object',o))
  assert(isname(name), fwrongarg(2,'name',name))
  rawget(o,INFO).__name = name
  getfenv(2)[name] = o
end

local
function setclass(o,class)
  assert(isobject(o), fwrongarg(1,'object',o))
  assert(isobject(class), fwrongarg(2,'object',class))
  rawget(o,INFO).__class = class
end

local
function setsuper(class,superclass)
  assert(isobject(class), fwrongarg(1,'object',class))
  assert(isobject(superclass), fwrongarg(2,'object',superclass))
  rawget(class,INFO).__super = superclass
end

local
function object2class(o,name)
  assert(isobject(o), fwrongarg(1,'object',o))
  assert(isname(name), fwrongarg(2,'name',name))
  givename(o,name)
  rawget(o,INFO).__methods = {}
  rawget(o,INFO).__isclass = true
  rawget(o,INFO).__cmethods = {}
end

local
function findmethod(class,name,iscmethod)
  local storage = iscmethod and '__cmethods' or '__methods'
  while class do
    local info = rawget(class,INFO)
    value = info[storage][name]
    if value ~= nil then
      return value
    end
    class = info.__super
  end
end



function metatable:__index(name)
  local value

  if rawget(self,INFO).__isclass then
    value = findmethod(self,name,true)
    if value ~= nil then
      return value
    end
  end

  local class = rawget(self,INFO).__class
  value = findmethod(class,name)
  if value ~= nil then
    return value
  end

  if name ~= '__index' and name ~= '__index__' then
    local index = self.__index or self.__index__ 
    if index then
      value = index(self,name)
      if value ~= nil then
        return value
      end
    end
  end
end


local _Object = table2object{}
object2class(_Object,"Object")



local _Class = table2object{}
object2class(_Class,"Class")


setclass(Object,Class)
setclass(Class,Class)
setsuper(Class,Object)


local
function makesupermethod(self,name,iscmethod)
  return function(...)
    local method
    local classinfo
    if iscmethod then
      classinfo = rawget(self,INFO)
    else
      local class = rawget(self,INFO).__class
      classinfo = rawget(class,INFO)
    end
    local super = classinfo.__super
    if super then
      method = findmethod(super,name,iscmethod)
    end
    assert(method, "no super method for "..classinfo.__name..":"..name)
    return method(self,unpack(arg))
  end
end

local methodsmeta = {}

function methodsmeta:__call(object,...)
  local env = getfenv(self.__f)
  local metafenv = {
    __newindex = env,
    __index = env,
  }
  local fenv = {
    super = makesupermethod(object,self.__name,self.__iscmethod),
  }
  setmetatable(fenv,metafenv)
  setfenv(self.__f,fenv)
  local result = {self.__f(object,unpack(arg))}
  setfenv(self.__f,env)
  return unpack(result)
end

local
function storemethod(storage,name,iscmethod,method)
  if type(method) == 'function' then
    local t = {
      __name = name,
      __f = method,
      __iscmethod = iscmethod,
    }
    setmetatable(t,methodsmeta)
    storage[name] = t
  else
    storage[name] = method
  end
end

rawget(Class,INFO).__methods.__newindex =
  function(self,name,method)	
    storemethod(rawget(self,INFO).__methods,name,false,method)
  end


function Class:__call__(...)
  local instance = self:new(unpack(arg))
  instance:initialize(unpack(arg))
  instance.__cbody = nil
  local constructor = instance[rawget(self,INFO).__name]
  if constructor ~= nil then
  	constructor(instance, unpack(arg))
  	constructor = nil
  end
  return instance
end

function Class:initialize(name,superclass)
  assert(isname(name), fwrongarg(1,'name',name))
  object2class(self,name)
  superclass = superclass or Object
  assert(isobject(superclass), fwrongarg(2,'object',superclass))
  setsuper(self,superclass or Object)
end

function Class:name()
  return rawget(self,INFO).__name
end

function Class:super()
  return rawget(self,INFO).__super
end

function Class:classtable()
  local t = {}
  local mt = {}
  function mt.__newindex(_,name,method)
    storemethod(rawget(self,INFO).__cmethods,name,true,method)
  end
  setmetatable(t,mt)
  return t
end

function Class:__tostring__()
  return self:name()
end

function Class:derives(class)
  local superclass = self:super()
  if superclass then
    return superclass == class or superclass:derives(class)
  end
end

function Class:adopt(t,initialize,...)
  assert(type(t)=='table', wrongarg(1,'table',t))
  local o = table2object(t)
  setclass(o,self)
  if initialize then
    o:initialize(unpack(arg))
  end
  return o
end


local Objectclass = Object:classtable()

function Objectclass:new()
  local o = table2object{}
  setclass(o,self)
  return o
end


function Object:initialize()
end

function Object:finalize()
end

function Object:class()
  return rawget(self,INFO).__class
end

function Object:__eq__(other)
  return rawequal(self,other) or (self.__ptr and other.__ptr and self.__ptr == other.__ptr)
end

function Object:__newindex__(name,value)
  if self.__set_callback(self,name,value) == true then
  	return
  end
  rawset(self,name,value)
end

function Object:instanceof(class)
  return self:class() == class
end

function Object:__set_callback(name,value)
	return false
end

function Object:inherits(class)
  local _class = self:class()
  return _class == class or _class:derives(class)
end

function Object:__tostring__()
  return 'instance of '..self:class():name()
end

function Object:__concat__(other)
  if isobject(self) then
    self = tostring(self)
  elseif isobject(other) then
    other = tostring(other)
  end
  return self..other
end

function Object:totable(finalize)
  if finalize then
    self:finalize()
  end
  setmetatable(self,nil)
  local info = rawget(self,INFO)
  rawset(self,INFO,nil)
  return self, info
end


function class(name)
  assert(isname(name), fwrongarg(1,'name',name))
  local _class = Class(name)
  return function(superclass)
    assert(isobject(superclass), fwrongarg(1,'object',superclass))
    setsuper(_class,superclass)
  end
end

classu = u