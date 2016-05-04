from BindingsGenerator import *

engines = {}
generator = BindingsGenerator(engines, "bindings.conf")
generator.createBindings()
