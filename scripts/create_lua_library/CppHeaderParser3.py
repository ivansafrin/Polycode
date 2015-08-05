#!/usr/bin/python
#
# Author: Jashua R. Cloutier (contact via https://bitbucket.org/senex)
# Project: http://senexcanis.com/open-source/cppheaderparser/
#
# Copyright (C) 2011, Jashua R. Cloutier
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in
#   the documentation and/or other materials provided with the
#   distribution.
#
# * Neither the name of Jashua R. Cloutier nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.  Stories,
#   blog entries etc making reference to this project may mention the
#   name Jashua R. Cloutier in terms of project originator/creator etc.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#
# The CppHeaderParser.py script is written in Python 2.4 and released to
# the open source community for continuous improvements under the BSD
# 2.0 new license, which can be found at:
#
#   http://www.opensource.org/licenses/bsd-license.php
#
"""Parse C++ header files and generate a data structure
representing the class
"""

import ply.lex as lex
import os
import sys
import re

import inspect

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno

version = __version__ = "2.3"

tokens = [
    'NUMBER',
    'NAME',
    'OPEN_PAREN',
    'CLOSE_PAREN',
    'OPEN_BRACE',
    'CLOSE_BRACE',
    'OPEN_SQUARE_BRACKET',
    'CLOSE_SQUARE_BRACKET',
    'COLON',
    'SEMI_COLON',
    'COMMA',
    'TAB',
    'BACKSLASH',
    'PIPE',
    'PERCENT',
    'EXCLAMATION',
    'CARET',
    'COMMENT_SINGLELINE',
    'COMMENT_MULTILINE',
    'PRECOMP_MACRO',
    'PRECOMP_MACRO_CONT', 
    'ASTERISK',
    'AMPERSTAND',
    'EQUALS',
    'MINUS',
    'PLUS',  
    'DIVIDE', 
    'CHAR_LITERAL', 
    'STRING_LITERAL',
    'NEW_LINE',
    'SQUOTE',
]

t_ignore = " \r.?@\f"
t_NUMBER = r'[0-9][0-9XxA-Fa-f]*'
t_NAME = r'[<>A-Za-z_~][A-Za-z0-9_]*'
t_OPEN_PAREN = r'\('
t_CLOSE_PAREN = r'\)'
t_OPEN_BRACE = r'{'
t_CLOSE_BRACE = r'}'
t_OPEN_SQUARE_BRACKET = r'\['
t_CLOSE_SQUARE_BRACKET = r'\]'
t_SEMI_COLON = r';'
t_COLON = r':'
t_COMMA = r','
t_TAB = r'\t'
t_BACKSLASH = r'\\'
t_PIPE = r'\|'
t_PERCENT = r'%'
t_CARET = r'\^'
t_EXCLAMATION = r'!'
t_PRECOMP_MACRO = r'\#.*'
t_PRECOMP_MACRO_CONT = r'.*\\\n'
def t_COMMENT_SINGLELINE(t):
    r'\/\/.*\n'
    global doxygenCommentCache
    if t.value.startswith("///") or t.value.startswith("//!"):
        if doxygenCommentCache:
            doxygenCommentCache += "\n"
        if t.value.endswith("\n"):
            doxygenCommentCache += t.value[:-1]
        else:
            doxygenCommentCache += t.value
    t.lexer.lineno += len([a for a in t.value if a=="\n"])
t_ASTERISK = r'\*'
t_MINUS = r'\-'
t_PLUS = r'\+'
t_DIVIDE = r'/[^/]'
t_AMPERSTAND = r'&'
t_EQUALS = r'='
t_CHAR_LITERAL = "'.'"
t_SQUOTE = "'"
#found at http://wordaligned.org/articles/string-literals-and-regular-expressions
#TODO: This does not work with the string "bla \" bla"
t_STRING_LITERAL = r'"([^"\\]|\\.)*"'
#Found at http://ostermiller.org/findcomment.html
def t_COMMENT_MULTILINE(t):
    r'/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/'
    global doxygenCommentCache
    if t.value.startswith("/**") or t.value.startswith("/*!"):
        #not sure why, but get double new lines
        v = t.value.replace("\n\n", "\n")
        #strip prefixing whitespace
        v = re.sub("\n[\s]+\*", "\n*", v)
        doxygenCommentCache += v
    t.lexer.lineno += len([a for a in t.value if a=="\n"])
def t_NEWLINE(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_error(v):
    print(( "Lex error: ", v ))

lex.lex()
# Controls error_print
print_errors = 1
# Controls warning_print
print_warnings = 1
# Controls debug_print
debug = 0
# Controls trace_print
debug_trace = 0

def error_print(arg):
    if print_errors: print(("[%4d] %s"%(inspect.currentframe().f_back.f_lineno, arg)))

def warning_print(arg):
    if print_warnings: print(("[%4d] %s"%(inspect.currentframe().f_back.f_lineno, arg)))

def debug_print(arg):
    global debug
    if debug: print(("[%4d] %s"%(inspect.currentframe().f_back.f_lineno, arg)))

def trace_print(*arg):
    global debug_trace
    if debug_trace:
        sys.stdout.write("[%s] "%(inspect.currentframe().f_back.f_lineno))
        for a in arg: sys.stdout.write("%s "%a)
        sys.stdout.write("\n")

supportedAccessSpecifier = [
    'public',
    'protected', 
    'private'
]

#Symbols to ignore, usually special macros
ignoreSymbols = [
    'Q_OBJECT',
]

doxygenCommentCache = ""

#Track what was added in what order and at what depth
parseHistory = []

def is_namespace(nameStack):
    """Determines if a namespace is being specified"""
    if len(nameStack) == 0:
        return False
    if nameStack[0] == "namespace":
        return True
    return False

def is_enum_namestack(nameStack):
    """Determines if a namestack is an enum namestack"""
    if len(nameStack) == 0:
        return False
    if nameStack[0] == "enum":
        return True
    if len(nameStack) > 1 and nameStack[0] == "typedef" and nameStack[1] == "enum":
        return True
    return False

def is_fundamental(s):
    for a in s.split():
        if a not in ["size_t", "struct", "union", "unsigned", "signed", "bool", "char", "short", "int", "float", "double", "long", "void", "*"]: return False
    return True

def is_function_pointer_stack(stack):
    """Count how many non-nested paranthesis are in the stack.  Useful for determining if a stack is a function pointer"""
    paren_depth = 0
    paren_count = 0
    star_after_first_paren = False
    last_e = None
    for e in stack:
        if e == "(":
            paren_depth += 1
        elif e == ")" and paren_depth > 0:
            paren_depth -= 1
            if paren_depth == 0:
                paren_count += 1
        elif e == "*" and last_e == "(" and paren_count == 0 and paren_depth == 1:
            star_after_first_paren = True
        last_e = e
        
    if star_after_first_paren and paren_count == 2:
        return True
    else:
        return False

def is_method_namestack(stack):
    r = False
    if '(' not in stack: r = False
    elif stack[0] == 'typedef': r = False    # TODO deal with typedef function prototypes
    #elif '=' in stack and stack.index('=') < stack.index('(') and stack[stack.index('=')-1] != 'operator': r = False    #disabled July6th - allow all operators
    elif 'operator' in stack: r = True    # allow all operators
    elif '{' in stack and stack.index('{') < stack.index('('): r = False    # struct that looks like a method/class
    elif '(' in stack and ')' in stack:
        if '{' in stack and '}' in stack: r = True
        elif stack[-1] == ';':
            if is_function_pointer_stack(stack):
                r = False
            else:
                r = True
        elif '{' in stack: r = True    # ideally we catch both braces... TODO
    else: r = False
    #Test for case of property set to something with parens such as "static const int CONST_A = (1 << 7) - 1;"
    if r and "(" in stack and "=" in stack and 'operator' not in stack:
        if stack.index("=") < stack.index("("): r = False
    return r

def is_property_namestack(nameStack):
    r = False
    if '(' not in nameStack and ')' not in nameStack: r = True
    elif "(" in nameStack and "=" in nameStack and nameStack.index("=") < nameStack.index("("): r = True
    #See if we are a function pointer
    if not r and is_function_pointer_stack(nameStack): r = True
    return r

def detect_lineno(s):
    """Detect the line number for a given token string"""
    try:
        rtn = s.lineno()
        if rtn != -1:
            return rtn
    except: pass
    global curLine
    return curLine 

class TagStr(str):
    """Wrapper for a string that allows us to store the line number associated with it"""
    lineno_reg = {}
    def __new__(cls,*args,**kw):
        new_obj =  str.__new__(cls,*args)
        if "lineno" in kw:
            TagStr.lineno_reg[id(new_obj)] = kw["lineno"]
        return new_obj
    
    def __del__(self):
        try:
            del TagStr.lineno_reg[id(self)]
        except: pass
    
    def lineno(self):
        return TagStr.lineno_reg.get(id(self), -1)

class CppParseError(Exception): pass
    
class CppClass(dict):
    """Takes a name stack and turns it into a class
    
    Contains the following Keys:
    self['name'] - Name of the class
    self['doxygen'] - Doxygen comments associated with the class if they exist
    self['inherits'] - List of Classes that this one inherits where the values
        are of the form {"access": Anything in supportedAccessSpecifier
                                  "class": Name of the class
    self['methods'] - Dictionary where keys are from supportedAccessSpecifier
        and values are a lists of CppMethod's
    self['properties'] - Dictionary where keys are from supportedAccessSpecifier
        and values are lists of CppVariable's 
    self['enums'] - Dictionary where keys are from supportedAccessSpecifier and
        values are lists of CppEnum's
    self['structs'] - Dictionary where keys are from supportedAccessSpecifier and
        values are lists of nested Struct's
    
    An example of how this could look is as follows:
    #self =
    {
        'name': ""
        'inherits':[]
        'methods':
        {
            'public':[],
            'protected':[], 
            'private':[]
        }, 
        'properties':
        {
            'public':[],
            'protected':[], 
            'private':[]
        },
        'enums':
        {
            'public':[],
            'protected':[], 
            'private':[]
        }
    }
    """

    def get_all_methods(self):
        r = []
        for typ in supportedAccessSpecifier: r += self['methods'][typ]
        return r

    def get_all_method_names( self ):
        r = []
        for typ in supportedAccessSpecifier: r += self.get_method_names(typ)        # returns list
        return r

    def get_all_pure_virtual_methods( self ):
        r = {}
        for typ in supportedAccessSpecifier: r.update(self.get_pure_virtual_methods(typ))        # returns dict
        return r


    def get_method_names( self, type='public' ): return [ meth['name'] for meth in self['methods'][ type ] ]

    def get_pure_virtual_methods( self, type='public' ):
        r = {}
        for meth in self['methods'][ type ]:
            if meth['pure_virtual']: r[ meth['name'] ] = meth
        return r

    def __init__(self, nameStack):
        self['nested_classes'] = []
        self['parent'] = None
        self['abstract'] = False
        self._public_enums = {}
        self._public_structs = {}
        self._public_typedefs = {}
        self._public_forward_declares = []
        self['namespace'] = ""

        debug_print( "Class:   %s"%nameStack )
        if (len(nameStack) < 2):
            nameStack.insert(1, "")#anonymous struct
        global doxygenCommentCache
        if len(doxygenCommentCache):
            self["doxygen"] = doxygenCommentCache
            doxygenCommentCache = ""
        self["name"] = nameStack[1]
        self["line_number"] = detect_lineno(nameStack[0])
        
        #Handle template classes
        if len(nameStack) > 3 and nameStack[2].startswith("<"):
            open_template_count = 0
            param_separator = 0
            found_first = False
            i = 0
            for elm in nameStack:
                if '<' in elm :
                    open_template_count += 1
                    found_first = True
                elif '>' in elm:
                    open_template_count -= 1
                if found_first and open_template_count == 0:
                    self["name"] = "".join(nameStack[1:i + 1])
                    break;
                i += 1
        elif ":" in nameStack:
            self['name'] = nameStack[ nameStack.index(':') - 1 ]

        inheritList = []

        if nameStack.count(':') == 1:
            nameStack = nameStack[nameStack.index(":") + 1:]
            while len(nameStack):
                tmpStack = []
                tmpInheritClass = {"access":"private", "virtual": False}
                if "," in nameStack:
                    tmpStack = nameStack[:nameStack.index(",")]
                    nameStack = nameStack[nameStack.index(",") + 1:]
                else:
                    tmpStack = nameStack
                    nameStack = []
                
                # Convert template classes to one name in the last index
                for i in range(0, len(tmpStack)):
                    if '<' in tmpStack[i]:
                        tmpStack2 = tmpStack[:i-1]
                        tmpStack2.append("".join(tmpStack[i-1:]))
                        tmpStack = tmpStack2
                        break
                if len(tmpStack) == 0:
                    break;
                elif len(tmpStack) == 1:
                    tmpInheritClass["class"] = tmpStack[0]
                elif len(tmpStack) == 2:
                    tmpInheritClass["access"] = tmpStack[0]
                    tmpInheritClass["class"] = tmpStack[1]
                elif len(tmpStack) == 3 and "virtual" in tmpStack:
                    tmpInheritClass["access"] = tmpStack[1] if tmpStack[1] != "virtual" else tmpStack[0]
                    tmpInheritClass["class"] = tmpStack[2]
                    tmpInheritClass["virtual"] = True
                else:
                    warning_print( "Warning: can not parse inheriting class %s"%(" ".join(tmpStack)))
                    if '>' in tmpStack: pass    # allow skip templates for now
                    else: raise NotImplemented

                if 'class' in tmpInheritClass: inheritList.append(tmpInheritClass)

        elif nameStack.count(':') == 2: self['parent'] = self['name']; self['name'] = nameStack[-1]

        elif nameStack.count(':') > 2 and nameStack[0] in ("class", "struct"):
            tmpStack = nameStack[nameStack.index(":") + 1:]
            
            superTmpStack = [[]]
            for tok in tmpStack:
                if tok == ',':
                    superTmpStack.append([])
                else:
                    superTmpStack[-1].append(tok)
            
            for tmpStack in superTmpStack:
                tmpInheritClass = {"access":"private"}
                
                if len(tmpStack) and tmpStack[0] in supportedAccessSpecifier:
                    tmpInheritClass["access"] = tmpStack[0]
                    tmpStack = tmpStack[1:]
                
                inheritNSStack = []
                while len(tmpStack) > 3:
                    if tmpStack[0] == ':': break;
                    if tmpStack[1] != ':': break;
                    if tmpStack[2] != ':': break;
                    inheritNSStack.append(tmpStack[0])
                    tmpStack = tmpStack[3:]
                if len(tmpStack) == 1 and tmpStack[0] != ':':
                     inheritNSStack.append(tmpStack[0])
                tmpInheritClass["class"] = "::".join(inheritNSStack)
                inheritList.append(tmpInheritClass)

        self['inherits'] = inheritList

        methodAccessSpecificList = {}
        propertyAccessSpecificList = {}
        enumAccessSpecificList = {}
        structAccessSpecificList = {}
        typedefAccessSpecificList = {}
        forwardAccessSpecificList = {}
        
        for accessSpecifier in supportedAccessSpecifier:
            methodAccessSpecificList[accessSpecifier] = []
            propertyAccessSpecificList[accessSpecifier] = []
            enumAccessSpecificList[accessSpecifier] = []
            structAccessSpecificList[accessSpecifier] = []
            typedefAccessSpecificList[accessSpecifier] = []
            forwardAccessSpecificList[accessSpecifier] = []

        self['methods'] = methodAccessSpecificList
        self['properties'] = propertyAccessSpecificList
        self['enums'] = enumAccessSpecificList
        self['structs'] = structAccessSpecificList
        self['typedefs'] = typedefAccessSpecificList
        self['forward_declares'] = forwardAccessSpecificList

 
    def show(self):
        """Convert class to a string"""
        namespace_prefix = ""
        if self["namespace"]: namespace_prefix = self["namespace"] + "::"
        rtn = "%s %s"%(self["declaration_method"], namespace_prefix + self["name"])
        if self['abstract']: rtn += '    (abstract)\n'
        else: rtn += '\n'

        if 'doxygen' in list(self.keys()): rtn += self["doxygen"] + '\n'
        if 'parent' in list(self.keys()) and self['parent']: rtn += 'parent class: ' + self['parent'] + '\n'

        if "inherits" in list(self.keys()):
            rtn += "  Inherits: "
            for inheritClass in self["inherits"]:
                if inheritClass["virtual"]: rtn += "virtual "
                rtn += "%s %s, "%(inheritClass["access"], inheritClass["class"])
            rtn += "\n"
        rtn += "  {\n"
        for accessSpecifier in supportedAccessSpecifier:
            rtn += "    %s\n"%(accessSpecifier)
            #Enums
            if (len(self["enums"][accessSpecifier])):
                rtn += "        <Enums>\n"
            for enum in self["enums"][accessSpecifier]:
                rtn += "            %s\n"%(repr(enum))
            #Properties
            if (len(self["properties"][accessSpecifier])):
                rtn += "        <Properties>\n"
            for property in self["properties"][accessSpecifier]:
                rtn += "            %s\n"%(repr(property))
            #Methods
            if (len(self["methods"][accessSpecifier])):
                rtn += "        <Methods>\n"
            for method in self["methods"][accessSpecifier]:
                rtn += "\t\t" + method.show() + '\n'
        rtn += "  }\n"
        print(rtn)
    
    def __repr__(self):
        """Convert class to a string"""
        namespace_prefix = ""
        if self["namespace"]: namespace_prefix = self["namespace"] + "::"
        rtn = "%s %s"%(self["declaration_method"], namespace_prefix + self["name"])
        if self['abstract']: rtn += '    (abstract)\n'
        else: rtn += '\n'

        if 'doxygen' in list(self.keys()): rtn += self["doxygen"] + '\n'
        if 'parent' in list(self.keys()) and self['parent']: rtn += 'parent class: ' + self['parent'] + '\n'

        if "inherits" in list(self.keys()) and len(self["inherits"]):
            rtn += "Inherits: "
            for inheritClass in self["inherits"]:
                if inheritClass.get("virtual", False): rtn += "virtual "
                rtn += "%s %s, "%(inheritClass["access"], inheritClass["class"])
            rtn += "\n"
        rtn += "{\n"
        for accessSpecifier in supportedAccessSpecifier:
            rtn += "%s\n"%(accessSpecifier)
            #Enums
            if (len(self["enums"][accessSpecifier])):
                rtn += "    // Enums\n"
            for enum in self["enums"][accessSpecifier]:
                rtn += "    %s\n"%(repr(enum))
            #Properties
            if (len(self["properties"][accessSpecifier])):
                rtn += "    // Properties\n"
            for property in self["properties"][accessSpecifier]:
                rtn += "    %s\n"%(repr(property))
            #Methods
            if (len(self["methods"][accessSpecifier])):
                rtn += "    // Methods\n"
            for method in self["methods"][accessSpecifier]:
                rtn += "   %s\n"%(repr(method))
        rtn += "}\n"
        return rtn


class CppUnion( CppClass ):
    """Takes a name stack and turns it into a union
    
    Contains the following Keys:
    self['name'] - Name of the union
    self['doxygen'] - Doxygen comments associated with the union if they exist
    self['members'] - List of members the union has 
    
    An example of how this could look is as follows:
    #self =
    {
        'name': ""
        'members': []
    }
    """
    
    def __init__(self, nameStack):
        CppClass.__init__(self, nameStack)
        self["name"] = "union " + self["name"]
        self["members"] = self["properties"]["public"]
    
    def transform_to_union_keys(self):
        print("union keys: %s"%list(self.keys()))
        for key in ['inherits', 'parent', 'abstract', 'namespace', 'typedefs', 'methods']:
            del self[key] 
        
    def show(self):
        """Convert class to a string"""
        print(self)
    
    
    def __repr__(self):
        """Convert class to a string"""
        namespace_prefix = ""
        if self["namespace"]: namespace_prefix = self["namespace"] + "::"
        rtn = "%s %s"%(self["declaration_method"], namespace_prefix + self["name"])
        if self['abstract']: rtn += '    (abstract)\n'
        else: rtn += '\n'

        if 'doxygen' in list(self.keys()): rtn += self["doxygen"] + '\n'
        if 'parent' in list(self.keys()) and self['parent']: rtn += 'parent class: ' + self['parent'] + '\n'

        rtn += "{\n"
        for member in self["members"]:
            rtn += "    %s\n"%(repr(member))
        rtn += "}\n"
        return rtn

       

class _CppMethod( dict ):
    def _params_helper1( self, stack ):
        # deal with "throw" keyword
        if 'throw' in stack: stack = stack[ : stack.index('throw') ]

        ## remove GCC keyword __attribute__(...) and preserve returns ##
        cleaned = []
        hit = False; hitOpen = 0; hitClose = 0
        for a in stack:
            if a == '__attribute__': hit = True
            if hit:
                if a == '(': hitOpen += 1
                elif a == ')': hitClose += 1
                if a==')' and hitOpen == hitClose:
                    hit = False
            else:
                cleaned.append( a )
        stack = cleaned

        # also deal with attribute((const)) function prefix #
        # TODO this needs to be better #
        if len(stack) > 5:
            a = ''.join(stack)
            if a.startswith('((__const__))'): stack = stack[ 5 : ]
            elif a.startswith('__attribute__((__const__))'): stack = stack[ 6 : ]

        stack = stack[stack.index('(') + 1: ]
        if not stack: return []
        if len(stack)>=3 and stack[0]==')' and stack[1]==':':    # is this always a constructor?
            self['constructor'] = True
            return []

        stack.reverse(); _end_ = stack.index(')'); stack.reverse()
        stack = stack[ : len(stack)-(_end_+1) ]
        if '(' not in stack: return stack    # safe to return, no defaults that init a class

        # transforms ['someclass', '(', '0', '0', '0', ')'] into "someclass(0,0,0)'"
        r = []; hit=False
        for a in stack:
            if a == '(': hit=True
            elif a == ')': hit=False
            if hit or a == ')': r[-1] = r[-1] + a
            else: r.append( a )
        return r

    def _params_helper2( self, params ):
        for p in params:
            p['method'] = self        # save reference in variable to parent method
            if '::' in p['type']:
                ns = p['type'].split('::')[0]
                if ns not in Resolver.NAMESPACES and ns in Resolver.CLASSES:
                    p['type'] = self['namespace'] + p['type']
            else: p['namespace'] = self[ 'namespace' ]

class CppMethod( _CppMethod ):
    """Takes a name stack and turns it into a method
    
    Contains the following Keys:
    self['rtnType'] - Return type of the method (ex. "int")
    self['name'] - Name of the method (ex. "getSize")
    self['doxygen'] - Doxygen comments associated with the method if they exist
    self['parameters'] - List of CppVariables
    """
    def show(self):
        r = ['method name: %s (%s)' %(self['name'],self['debug']) ]
        if self['returns']: r.append( 'returns: %s'%self['returns'] )
        if self['parameters']: r.append( 'number arguments: %s' %len(self['parameters']))
        if self['pure_virtual']: r.append( 'pure virtual: %s'%self['pure_virtual'] )
        if self['constructor']: r.append( 'constructor' )
        if self['destructor']: r.append( 'destructor' )
        return '\n\t\t  '.join( r )

    def __init__(self, nameStack, curClass, methinfo):
        debug_print( "Method:   %s"%nameStack )
        global doxygenCommentCache
        if len(doxygenCommentCache):
            self["doxygen"] = doxygenCommentCache
            doxygenCommentCache = ""
        if "operator" in nameStack:
            self["rtnType"] = " ".join(nameStack[:nameStack.index('operator')])
            self["name"] = "".join(nameStack[nameStack.index('operator'):nameStack.index('(')])
        else:
            self["rtnType"] = " ".join(nameStack[:nameStack.index('(') - 1])
            self["name"] = " ".join(nameStack[nameStack.index('(') - 1:nameStack.index('(')])
        if self["rtnType"].startswith("virtual"):
           self["rtnType"] = self["rtnType"][len("virtual"):].strip()
        if len(self["rtnType"]) == 0 or self["name"] == curClass:
            self["rtnType"] = "void"
        
        self["rtnType"] = self["rtnType"].replace(' : : ', '::' )
        self["rtnType"] = self["rtnType"].replace(" <","<")
        self["rtnType"] = self["rtnType"].replace(" >",">").replace(">>", "> >").replace(">>", "> >")
        self["rtnType"] = self["rtnType"].replace(" ,",",")
        
        self["const"] = False
        for i in reversed(nameStack):
            if i == "const":
                self["const"] = True
                break
            elif i == ")":
                break        

        self.update( methinfo )
        self["line_number"] = detect_lineno(nameStack[0])

        #Filter out initializer lists used in constructors
        try:
            paren_depth_counter = 0
            for i in range(0, len(nameStack)):
                elm = nameStack[i]
                if elm == "(":
                    paren_depth_counter += 1
                if elm == ")":
                    paren_depth_counter -=1
                    if paren_depth_counter == 0 and nameStack[i+1] == ':':
                        debug_print("Stripping out initializer list")
                        nameStack = nameStack[:i+1]
                        break
        except: pass
        
        paramsStack = self._params_helper1( nameStack )
        

        params = []
        #See if there is a doxygen comment for the variable
        doxyVarDesc = {}
        
        if "doxygen" in self:
            doxyLines = self["doxygen"].split("\n")
            lastParamDesc = ""
            for doxyLine in doxyLines:
                if " @param " in doxyLine or " \param " in doxyLine:
                    try:
                        #Strip out the param
                        doxyLine = doxyLine[doxyLine.find("param ") + 6:]
                        (var, desc) = doxyLine.split(" ", 1)
                        doxyVarDesc[var] = desc.strip()
                        lastParamDesc = var
                    except: pass
                elif " @return " in doxyLine or " \return " in doxyLine:
                    lastParamDesc = ""
                    # not handled for now
                elif lastParamDesc:
                    try:
                        doxyLine = doxyLine.strip()
                        if " " not in doxyLine:
                            lastParamDesc = ""
                            continue
                        doxyLine = doxyLine[doxyLine.find(" ") + 1:]
                        doxyVarDesc[lastParamDesc] += " " + doxyLine
                    except: pass
        
        #Create the variable now
        while (len(paramsStack)):
            # Find commas that are not nexted in <>'s like template types
            open_template_count = 0
            param_separator = 0
            i = 0
            for elm in paramsStack:
                if '<' in elm :
                    open_template_count += 1
                elif '>' in elm:
                    open_template_count -= 1
                elif elm == ',' and open_template_count == 0:
                    param_separator = i
                    break
                i += 1
            
            if param_separator:
                param = CppVariable(paramsStack[0:param_separator],  doxyVarDesc=doxyVarDesc)
                if len(list(param.keys())): params.append(param)
                paramsStack = paramsStack[param_separator + 1:]
            else:
                param = CppVariable(paramsStack,  doxyVarDesc=doxyVarDesc)
                if len(list(param.keys())): params.append(param)
                break


        self["parameters"] = params
        self._params_helper2( params )    # mods params inplace

    def __repr__(self):
        filter_keys = ("parent", "defined", "operator", "returns_reference")
        cpy = dict((k,v) for (k,v) in list(self.items()) if k not in filter_keys)
        return "%s"%cpy


class _CppVariable(dict):
    def _name_stack_helper( self, stack ):
        stack = list(stack)
        if '=' not in stack:        # TODO refactor me
            # check for array[n] and deal with funny array syntax: "int myvar:99"
            array = []
            while stack and stack[-1].isdigit(): array.append( stack.pop() )
            if array: array.reverse(); self['array'] = int(''.join(array))
            if stack and stack[-1].endswith(':'): stack[-1] = stack[-1][:-1]

        while stack and not stack[-1]: stack.pop()            # can be empty
        return stack

    def init(self):
        #assert self['name']    # allow unnamed variables, methods like this: "void func(void);"
        a = []
        self['aliases'] = []; self['parent'] = None; self['typedef'] = None
        for key in 'constant reference pointer static typedefs class fundamental unresolved'.split():
            self[ key ] = 0
        for b in self['type'].split():
            if b == '__const__': b = 'const'
            a.append( b )
        self['type'] = ' '.join( a )


class CppVariable( _CppVariable ):
    """Takes a name stack and turns it into a method
    
    Contains the following Keys:
    self['type'] - Type for the variable (ex. "const string &")
    self['name'] - Name of the variable (ex. "numItems")
    self['namespace'] - Namespace containing the enum
    self['desc'] - Description of the variable if part of a method (optional)
    self['doxygen'] - Doxygen comments associated with the method if they exist
    self['defaltValue'] - Default value of the variable, this key will only
        exist if there is a default value
    """
    Vars = []
    def __init__(self, nameStack,  **kwargs):
        _stack_ = nameStack
        if "[" in nameStack: #strip off array informatin
            arrayStack = nameStack[nameStack.index("["):]
            if len(arrayStack) == 3:
                self["array_size"] = arrayStack[1] 
            nameStack = nameStack[:nameStack.index("[")]
            self["array"] = 1
        else:
            self["array"] = 0
        nameStack = self._name_stack_helper( nameStack )
        global doxygenCommentCache
        if len(doxygenCommentCache):
            self["doxygen"] = doxygenCommentCache
            doxygenCommentCache = ""

        debug_print( "Variable: %s"%nameStack )

        self["line_number"] = detect_lineno(nameStack[0])
        self["function_pointer"] = 0

        if (len(nameStack) < 2):    # +++
            if len(nameStack) == 1: self['type'] = nameStack[0]; self['name'] = ''
            else: error_print(_stack_); assert 0

        elif is_function_pointer_stack(nameStack): #function pointer
            self["type"] = " ".join(nameStack[:nameStack.index("(") + 2] + nameStack[nameStack.index(")")  :])
            self["name"] = " ".join(nameStack[nameStack.index("(") + 2 : nameStack.index(")")])
            self["function_pointer"] = 1

        elif ("=" in nameStack):
            self["type"] = " ".join(nameStack[:nameStack.index("=") - 1])
            self["name"] = nameStack[nameStack.index("=") - 1]
            self["defaltValue"] = " ".join(nameStack[nameStack.index("=") + 1:])    # deprecate camelCase in dicts
            self['default'] = " ".join(nameStack[nameStack.index("=") + 1:])

        elif is_fundamental(nameStack[-1]) or nameStack[-1] in ['>', '<' , ':', '.']:
            #Un named parameter
            self["type"] = " ".join(nameStack)
            self["name"] = ""

        else:    # common case
            self["type"] = " ".join(nameStack[:-1])
            self["name"] = nameStack[-1]

        self["type"] = self["type"].replace(" :",":")
        self["type"] = self["type"].replace(": ",":")
        self["type"] = self["type"].replace(" <","<")
        self["type"] = self["type"].replace(" >",">").replace(">>", "> >").replace(">>", "> >")
        self["type"] = self["type"].replace(" ,",",")
        #Optional doxygen description
        try:
            self["desc"] = kwargs["doxyVarDesc"][self["name"]]
        except: pass

        self.init()
        CppVariable.Vars.append( self )        # save and resolve later
    
    def __repr__(self):
        keys_white_list = ['constant','name','reference','type','static','pointer','desc', 'line_number']
        cpy = dict((k,v) for (k,v) in list(self.items()) if k in keys_white_list)
        if "array_size" in self: cpy["array_size"] = self["array_size"]
        return "%s"%cpy

class _CppEnum(dict):
    def resolve_enum_values( self, values ):
        """Evaluates the values list of dictionaries passed in and figures out what the enum value
        for each enum is editing in place:
        
        Example:
        From: [{'name': 'ORANGE'},
               {'name': 'RED'},
               {'name': 'GREEN', 'value': '8'}]
        To:   [{'name': 'ORANGE', 'value': 0},
               {'name': 'RED', 'value': 1},
               {'name': 'GREEN', 'value': 8}]
        """
        t = int; i = 0
        names = [ v['name'] for v in values ]
        for v in values:
            if 'value' in v:
                a = v['value'].strip()
                # Remove single quotes from single quoted chars (unless part of some expression
                if len(a) == 3 and a[0] == "'" and a[2] == "'":
                    a = v['value'] = a[1]
                if a.lower().startswith("0x"):
                    try:
                        i = a = int(a , 16)
                    except:pass
                elif a.isdigit():
                    i = a = int( a )
                elif a in names:
                    for other in values:
                        if other['name'] == a:
                            v['value'] = other['value']
                            break

                elif '"' in a or "'" in a: t = str # only if there are quotes it this a string enum
                else:
                    try:
                        a = i = ord(a)
                    except: pass
                #Allow access of what is in the file pre-convert if converted
                if v['value'] != str(a):
                    v['raw_value'] = v['value']
                v['value'] = a
            else: v['value'] = i
            try:
                v['value'] = v['value'].replace(" < < ", " << ").replace(" >> ", " >> ")
            except: pass
            i += 1
        return t

class CppEnum(_CppEnum):
    """Takes a name stack and turns it into an Enum
    
    Contains the following Keys:
    self['name'] - Name of the enum (ex. "ItemState")
    self['namespace'] - Namespace containing the enum
    self['values'] - List of values where the values are a dictionary of the
        form {"name": name of the key (ex. "PARSING_HEADER"),
                  "value": Specified value of the enum, this key will only exist
                    if a value for a given enum value was defined
                }
    """
    def __init__(self, nameStack):
        global doxygenCommentCache
        if len(doxygenCommentCache):
            self["doxygen"] = doxygenCommentCache
            doxygenCommentCache = ""
        if len(nameStack) == 3 and nameStack[0] == "enum":
            debug_print("Created enum as just name/value")
            self["name"] = nameStack[1]
            self["instances"]=[nameStack[2]]
        if len(nameStack) < 4 or "{" not in nameStack or "}" not in nameStack:
            #Not enough stuff for an enum
            debug_print("Bad enum")
            return
        valueList = []
        self["line_number"] = detect_lineno(nameStack[0])
        #Figure out what values it has
        valueStack = nameStack[nameStack.index('{') + 1: nameStack.index('}')]
        while len(valueStack):
            tmpStack = []
            if "," in valueStack:
                tmpStack = valueStack[:valueStack.index(",")]
                valueStack = valueStack[valueStack.index(",") + 1:]
            else:
                tmpStack = valueStack
                valueStack = []
            d = {}
            if len(tmpStack) == 1: d["name"] = tmpStack[0]
            elif len(tmpStack) >= 3 and tmpStack[1] == "=":
                d["name"] = tmpStack[0]; d["value"] = " ".join(tmpStack[2:])
            elif len(tmpStack) == 2 and tmpStack[1] == "=":
                debug_print( "WARN-enum: parser missed value for %s"%tmpStack[0] )
                d["name"] = tmpStack[0]

            if d: valueList.append( d )

        if len(valueList):
            self['type'] = self.resolve_enum_values( valueList )    # returns int for standard enum
            self["values"] = valueList
        else:
            warning_print( 'WARN-enum: empty enum %s'%nameStack )
            return
        #Figure out if it has a name
        preBraceStack = nameStack[:nameStack.index("{")]
        postBraceStack = nameStack[nameStack.index("}") + 1:]
        if (len(preBraceStack) == 2 and "typedef" not in nameStack):
            self["name"] = preBraceStack[1]           
        elif len(postBraceStack) and "typedef" in nameStack:
                self["name"] = " ".join(postBraceStack)
        else: warning_print( 'WARN-enum: nameless enum %s'%nameStack )
        #See if there are instances of this
        if "typedef" not in nameStack and len(postBraceStack):
            self["instances"] = []
            for var in postBraceStack:
                if "," in var:
                    continue
                self["instances"].append(var)
        self["namespace"] = ""


class CppStruct(dict):
    Structs = []
    def __init__(self, nameStack):
        if len(nameStack) >= 2: self['type'] = nameStack[1]
        else: self['type'] = None
        self['fields'] = []
        self.Structs.append( self )
        global curLine
        self["line_number"] = curLine

C99_NONSTANDARD = {
    'int8' : 'signed char',
    'int16' : 'short int',
    'int32' : 'int',
    'int64' : 'int64_t',        # this can be: long int (64bit), or long long int (32bit)
    'uint' : 'unsigned int',
    'uint8' : 'unsigned char',
    'uint16' : 'unsigned short int',
    'uint32' : 'unsigned int',
    'uint64' : 'uint64_t',    # depends on host bits
}


def standardize_fundamental( s ):
    if s in C99_NONSTANDARD: return C99_NONSTANDARD[ s ]
    else: return s


class Resolver(object):
    C_FUNDAMENTAL = 'size_t unsigned signed bool char wchar short int float double long void'.split()
    C_FUNDAMENTAL += 'struct union enum'.split()


    SubTypedefs = {}        # TODO deprecate?
    NAMESPACES = []
    CLASSES = {}
    STRUCTS = {}

    def initextra(self):
        self.typedefs = {}
        self.typedefs_order = []
        self.classes_order = []
        self.structs = Resolver.STRUCTS
        self.structs_order = []
        self.namespaces = Resolver.NAMESPACES        # save all namespaces
        self.curStruct = None
        self.stack = []    # full name stack, good idea to keep both stacks? (simple stack and full stack)
        self._classes_brace_level = {}    # class name : level
        self._structs_brace_level = {}        # struct type : level
        self._method_body = None
        self._forward_decls = []
        self._template_typenames = []    # template<typename XXX>

    def current_namespace(self): return self.cur_namespace(True)

    def cur_namespace(self, add_double_colon=False):
        rtn = ""
        i = 0
        while i < len(self.nameSpaces):
            rtn += self.nameSpaces[i]
            if add_double_colon or i < len(self.nameSpaces) - 1: rtn += "::"
            i+=1
        return rtn


    def guess_ctypes_type( self, string ):
        pointers = string.count('*')
        string = string.replace('*','')

        a = string.split()
        if 'unsigned' in a: u = 'u'
        else: u = ''
        if 'long' in a and 'double' in a: b = 'longdouble'    # there is no ctypes.c_ulongdouble (this is a 64bit float?)
        elif a.count('long') == 2 and 'int' in a: b = '%sint64' %u
        elif a.count('long') == 2: b = '%slonglong' %u
        elif 'long' in a: b = '%slong' %u
        elif 'double' in a: b = 'double'    # no udouble in ctypes
        elif 'short' in a: b = '%sshort' %u
        elif 'char' in a: b = '%schar' %u
        elif 'wchar' in a: b = 'wchar'
        elif 'bool' in a: b = 'bool'
        elif 'float' in a: b = 'float'

        elif 'int' in a: b = '%sint' %u
        elif 'int8' in a: b = 'int8'
        elif 'int16' in a: b = 'int16'
        elif 'int32' in a: b = 'int32'
        elif 'int64' in a: b = 'int64'

        elif 'uint' in a: b = 'uint'
        elif 'uint8' in a: b = 'uint8'
        elif 'uint16' in a: b = 'uint16'
        elif 'uint32' in a: b = 'uint32'
        elif 'uint64' in a: b = 'uint64'

        elif 'size_t' in a: b = 'size_t'
        elif 'void' in a: b = 'void_p'

        elif string in 'struct union'.split(): b = 'void_p'    # what should be done here? don't trust struct, it could be a class, no need to expose via ctypes
        else: b = 'void_p'

        if not pointers: return 'ctypes.c_%s' %b
        else:
            x = ''
            for i in range(pointers): x += 'ctypes.POINTER('
            x += 'ctypes.c_%s' %b
            x += ')' * pointers
            return x

    def resolve_type( self, string, result ):    # recursive
        '''
        keeps track of useful things like: how many pointers, number of typedefs, is fundamental or a class, etc...
        '''
        ## be careful with templates, what is inside <something*> can be a pointer but the overall type is not a pointer
        ## these come before a template
        s = string.split('<')[0]
        result[ 'constant' ] += s.split().count('const')
        result[ 'static' ] += s.split().count('static')
        result[ 'mutable' ] = 'mutable' in s.split()

        ## these come after a template
        s = string.split('>')[-1]
        result[ 'pointer' ] += s.count('*')
        result[ 'reference' ] += s.count('&')


        x = string; alias = False
        for a in '* & const static mutable'.split(): x = x.replace(a,'')
        for y in x.split():
            if y not in self.C_FUNDAMENTAL: alias = y; break

        #if alias == 'class':
        #    result['class'] = result['name']    # forward decl of class
        #    result['forward_decl'] = True
        if alias == '__extension__': result['fundamental_extension'] = True
        elif alias:
            result['aliases'].append( alias )
            if alias in C99_NONSTANDARD:
                result['type'] = C99_NONSTANDARD[ alias ]
                result['typedef'] = alias
                result['typedefs'] += 1
            elif alias in self.typedefs:
                result['typedefs'] += 1
                result['typedef'] = alias
                self.resolve_type( self.typedefs[alias], result )
            elif alias in self.classes:
                klass = self.classes[alias]; result['fundamental'] = False
                result['class'] = klass
                result['unresolved'] = False
            else: result['unresolved'] = True
        else:
            result['fundamental'] = True
            result['unresolved'] = False


    def finalize_vars(self):
        for s in CppStruct.Structs:    # vars within structs can be ignored if they do not resolve
            for var in s['fields']: var['parent'] = s['type']
        #for c in self.classes.values():
        #    for var in c.get_all_properties(): var['parent'] = c['name']

        ## RESOLVE ##
        for var in CppVariable.Vars:
            self.resolve_type( var['type'], var )
            #if 'method' in var and var['method']['name'] ==  '_notifyCurrentCamera': print(var); assert 0

        # then find concrete type and best guess ctypes type #
        for var in CppVariable.Vars:    
            if not var['aliases']:    #var['fundamental']:
                var['ctypes_type'] = self.guess_ctypes_type( var['type'] )
            else:
                var['unresolved'] = False    # below may test to True
                if var['class']:
                    var['ctypes_type'] = 'ctypes.c_void_p'
                else:
                    assert var['aliases']
                    tag = var['aliases'][0]

                    klass = None
                    nestedEnum = None
                    nestedStruct = None
                    nestedTypedef = None
                    if 'method' in var and 'parent' in list(var['method'].keys()):
                        klass = var['method']['parent']
                        if tag in var['method']['parent']._public_enums:
                            nestedEnum = var['method']['parent']._public_enums[ tag ]
                        elif tag in var['method']['parent']._public_structs:
                            nestedStruct = var['method']['parent']._public_structs[ tag ]
                        elif tag in var['method']['parent']._public_typedefs:
                            nestedTypedef = var['method']['parent']._public_typedefs[ tag ]


                    if '<' in tag:    # should also contain '>'
                        var['template'] = tag        # do not resolve templates
                        var['ctypes_type'] = 'ctypes.c_void_p'
                        var['unresolved'] = True

                    elif nestedEnum:
                        enum = nestedEnum
                        if enum['type'] is int:
                            var['ctypes_type'] = 'ctypes.c_int'
                            var['raw_type'] = 'int'

                        elif enum['type'] is str:
                            var['ctypes_type'] = 'ctypes.c_char_p'
                            var['raw_type'] = 'char*'

                        var['enum'] = var['method']['path'] + '::' + enum['name']
                        var['fundamental'] = True

                    elif nestedStruct:
                        var['ctypes_type'] = 'ctypes.c_void_p'
                        var['raw_type'] = var['method']['path'] + '::' + nestedStruct['type']
                        var['fundamental'] = False

                    elif nestedTypedef:
                        var['fundamental'] = is_fundamental( nestedTypedef )
                        if not var['fundamental']:
                            var['raw_type'] = var['method']['path'] + '::' + tag

                    else:
                        _tag = tag
                        if '::' in tag and tag.split('::')[0] in self.namespaces: tag = tag.split('::')[-1]
                        con = self.concrete_typedef( _tag )
                        if con:
                            var['concrete_type'] = con
                            var['ctypes_type'] = self.guess_ctypes_type( var['concrete_type'] )

                        elif tag in self.structs:
                            trace_print( 'STRUCT', var )
                            var['struct'] = tag
                            var['ctypes_type'] = 'ctypes.c_void_p'
                            var['raw_type'] = self.structs[tag]['namespace'] + '::' + tag

                        elif tag in self._forward_decls:
                            var['forward_declared'] = tag
                            var['ctypes_type'] = 'ctypes.c_void_p'

                        elif tag in self.global_enums:
                            enum = self.global_enums[ tag ]
                            if enum['type'] is int:
                                var['ctypes_type'] = 'ctypes.c_int'
                                var['raw_type'] = 'int'
                            elif enum['type'] is str:
                                var['ctypes_type'] = 'ctypes.c_char_p'
                                var['raw_type'] = 'char*'
                            var['enum'] = enum['namespace'] + enum['name']
                            var['fundamental'] = True


                        elif var['parent']:
                            warning_print( 'WARN unresolved %s'%_tag)
                            var['ctypes_type'] = 'ctypes.c_void_p'
                            var['unresolved'] = True


                        elif tag.count('::')==1:
                            trace_print( 'trying to find nested something in', tag )
                            a = tag.split('::')[0]
                            b = tag.split('::')[-1]
                            if a in self.classes:    # a::b is most likely something nested in a class
                                klass = self.classes[ a ]
                                if b in klass._public_enums:
                                    trace_print( '...found nested enum', b )
                                    enum = klass._public_enums[ b ]
                                    if enum['type'] is int:
                                        var['ctypes_type'] = 'ctypes.c_int'
                                        var['raw_type'] = 'int'
                                    elif enum['type'] is str:
                                        var['ctypes_type'] = 'ctypes.c_char_p'
                                        var['raw_type'] = 'char*'
                                    try:
                                        if 'method' in var: var['enum'] = var['method']['path'] + '::' + enum['name']
                                        else:    # class property
                                            var['unresolved'] = True
                                    except:
                                        var['unresolved'] = True
                                        
                                    var['fundamental'] = True

                                else: var['unresolved'] = True    # TODO klass._public_xxx

                            elif a in self.namespaces:    # a::b can also be a nested namespace
                                if b in self.global_enums:
                                    enum = self.global_enums[ b ]
                                    trace_print(enum)
                                trace_print(var)
                                assert 0

                            elif b in self.global_enums:        # falling back, this is a big ugly
                                enum = self.global_enums[ b ]
                                assert a in enum['namespace'].split('::')
                                if enum['type'] is int:
                                    var['ctypes_type'] = 'ctypes.c_int'
                                    var['raw_type'] = 'int'
                                elif enum['type'] is str:
                                    var['ctypes_type'] = 'ctypes.c_char_p'
                                    var['raw_type'] = 'char*'
                                var['fundamental'] = True

                            else:    # boost::gets::crazy
                                trace_print('NAMESPACES', self.namespaces)
                                trace_print( a, b )
                                trace_print( '---- boost gets crazy ----' )
                                var['ctypes_type'] = 'ctypes.c_void_p'
                                var['unresolved'] = True


                        elif 'namespace' in var and self.concrete_typedef(var['namespace']+tag):
                            #print( 'TRYING WITH NS', var['namespace'] )
                            con = self.concrete_typedef( var['namespace']+tag )
                            if con:
                                var['typedef'] = var['namespace']+tag
                                var['type'] = con
                                if 'struct' in con.split():
                                    var['raw_type'] = var['typedef']
                                    var['ctypes_type'] = 'ctypes.c_void_p'
                                else:
                                    self.resolve_type( var['type'], var )
                                    var['ctypes_type'] = self.guess_ctypes_type( var['type'] )

                        elif '::' in var:
                            var['ctypes_type'] = 'ctypes.c_void_p'
                            var['unresolved'] = True

                        elif tag in self.SubTypedefs:    # TODO remove SubTypedefs
                            if 'property_of_class' in var or 'property_of_struct' in var:
                                trace_print( 'class:', self.SubTypedefs[ tag ], 'tag:', tag )
                                var['typedef'] = self.SubTypedefs[ tag ]    # class name
                                var['ctypes_type'] = 'ctypes.c_void_p'
                            else:
                                trace_print( "WARN-this should almost never happen!" )
                                trace_print( var ); trace_print('-'*80)
                                var['unresolved'] = True

                        elif tag in self._template_typenames:
                            var['typename'] = tag
                            var['ctypes_type'] = 'ctypes.c_void_p'
                            var['unresolved'] = True    # TODO, how to deal with templates?

                        elif tag.startswith('_'):    # assume starting with underscore is not important for wrapping
                            warning_print( 'WARN unresolved %s'%_tag)
                            var['ctypes_type'] = 'ctypes.c_void_p'
                            var['unresolved'] = True

                        else:
                            trace_print( 'WARN: unknown type', var )
                            assert 'property_of_class' in var or 'property_of_struct'    # only allow this case
                            var['unresolved'] = True


                    ## if not resolved and is a method param, not going to wrap these methods  ##
                    if var['unresolved'] and 'method' in var: var['method']['unresolved_parameters'] = True


        # create stripped raw_type #
        p = '* & const static mutable'.split()        # +++ new July7: "mutable"
        for var in CppVariable.Vars:
            if 'raw_type' not in var:
                raw = []
                for x in var['type'].split():
                    if x not in p: raw.append( x )
                var['raw_type'] = ' '.join( raw )

                #if 'AutoConstantEntry' in var['raw_type']: print(var); assert 0
                if var['class']:
                    if '::' not in var['raw_type']:
                        if not var['class']['parent']:
                            var['raw_type'] = var['class']['namespace'] + '::' + var['raw_type']
                        elif var['class']['parent'] in self.classes:
                            parent = self.classes[ var['class']['parent'] ]
                            var['raw_type'] = parent['namespace'] + '::' + var['class']['name'] + '::' + var['raw_type']
                        else:
                            var['unresolved'] = True

                    elif '::' in var['raw_type'] and var['raw_type'].split('::')[0] not in self.namespaces:
                        var['raw_type'] = var['class']['namespace'] + '::' + var['raw_type']
                    else:
                        var['unresolved'] = True

                elif 'forward_declared' in var and 'namespace' in var:
                    if '::' not in var['raw_type']:
                        var['raw_type'] = var['namespace'] + var['raw_type']
                    elif '::' in var['raw_type'] and var['raw_type'].split('::')[0] in self.namespaces:
                        pass
                    else: trace_print('-'*80); trace_print(var); raise NotImplemented


            ## need full name space for classes in raw type ##
            if var['raw_type'].startswith( '::' ):
                #print(var)
                #print('NAMESPACE', var['class']['namespace'])
                #print( 'PARENT NS', var['class']['parent']['namespace'] )
                #assert 0
                var['unresolved'] = True
                if 'method' in var: var['method']['unresolved_parameters'] = True
                #var['raw_type'] = var['raw_type'][2:]
        
        # Take care of #defines and #pragmas etc
        trace_print("Processing precomp_macro_buf: %s"%self._precomp_macro_buf)
        for m in self._precomp_macro_buf:
            macro = m.replace("<CppHeaderParser_newline_temp_replacement>\\n", "\n")
            try:
                if macro.lower().startswith("#define"):
                    trace_print("Adding #define %s"%macro)
                    self.defines.append(macro.split(" ", 1)[1].strip())
                elif macro.lower().startswith("#pragma"):
                    trace_print("Adding #pragma %s"%macro)
                    self.pragmas.append(macro.split(" ", 1)[1].strip())
                elif macro.lower().startswith("#include"):
                    trace_print("Adding #include %s"%macro)
                    self.includes.append(macro.split(" ", 1)[1].strip())
                else:
                    debug_print("Cant detect what to do with precomp macro '%s'"%macro)
            except: pass
        self._precomp_macro_buf = None
        

    def concrete_typedef( self, key ):
        if key not in self.typedefs:
            #print( 'FAILED typedef', key )
            return None
        while key in self.typedefs:
            prev = key
            key = self.typedefs[ key ]
            if '<' in key or '>' in key: return prev        # stop at template
            if key.startswith('std::'): return key        # stop at std lib
        return key


class _CppHeader( Resolver ):
    def finalize(self):
        self.finalize_vars()
        # finalize classes and method returns types
        for cls in list(self.classes.values()):
            for meth in cls.get_all_methods():
                if meth['pure_virtual']: cls['abstract'] = True

                if not meth['returns_fundamental'] and meth['returns'] in C99_NONSTANDARD:
                    meth['returns'] = C99_NONSTANDARD[meth['returns']]
                    meth['returns_fundamental'] = True

                elif not meth['returns_fundamental']:    # describe the return type
                    con = None
                    if cls['namespace'] and '::' not in meth['returns']:
                        con = self.concrete_typedef( cls['namespace'] + '::' + meth['returns'] )
                    else: con = self.concrete_typedef( meth['returns'] )


                    if con:
                        meth['returns_concrete'] = con
                        meth['returns_fundamental'] = is_fundamental( con )

                    elif meth['returns'] in self.classes:
                        trace_print( 'meth returns class:', meth['returns'] )
                        meth['returns_class'] = True

                    elif meth['returns'] in self.SubTypedefs:
                        meth['returns_class'] = True
                        meth['returns_nested'] = self.SubTypedefs[ meth['returns'] ]

                    elif meth['returns'] in cls._public_enums:
                        enum = cls._public_enums[ meth['returns'] ]
                        meth['returns_enum'] = enum['type']
                        meth['returns_fundamental'] = True
                        if enum['type'] == int: meth['returns'] = 'int'
                        else: meth['returns'] = 'char*'

                    elif meth['returns'] in self.global_enums:
                        enum = self.global_enums[ meth['returns'] ]
                        meth['returns_enum'] = enum['type']
                        meth['returns_fundamental'] = True
                        if enum['type'] == int: meth['returns'] = 'int'
                        else: meth['returns'] = 'char*'

                    elif meth['returns'].count('::')==1:
                        trace_print( meth )
                        a,b = meth['returns'].split('::')
                        if a in self.namespaces:
                            if b in self.classes:
                                klass = self.classes[ b ]
                                meth['returns_class'] = a + '::' + b
                            elif '<' in b and '>' in b:
                                warning_print( 'WARN-can not return template: %s'%b )
                                meth['returns_unknown'] = True
                            elif b in self.global_enums:
                                enum = self.global_enums[ b ]
                                meth['returns_enum'] = enum['type']
                                meth['returns_fundamental'] = True
                                if enum['type'] == int: meth['returns'] = 'int'
                                else: meth['returns'] = 'char*'

                            else: trace_print( a, b); trace_print( meth); meth['returns_unknown'] = True    # +++

                        elif a in self.classes:
                            klass = self.classes[ a ]
                            if b in klass._public_enums:
                                trace_print( '...found nested enum', b )
                                enum = klass._public_enums[ b ]
                                meth['returns_enum'] = enum['type']
                                meth['returns_fundamental'] = True
                                if enum['type'] == int: meth['returns'] = 'int'
                                else: meth['returns'] = 'char*'

                            elif b in klass._public_forward_declares:
                                meth['returns_class'] = True

                            elif b in klass._public_typedefs:
                                typedef = klass._public_typedefs[ b ]
                                meth['returns_fundamental'] = is_fundamental( typedef )

                            else:
                                trace_print( meth )    # should be a nested class, TODO fix me.
                                meth['returns_unknown'] = True

                    elif '::' in meth['returns']:
                        trace_print('TODO namespace or extra nested return:', meth)
                        meth['returns_unknown'] = True
                    else:
                        trace_print( 'WARN: UNKNOWN RETURN', meth['name'], meth['returns'])
                        meth['returns_unknown'] = True

        for cls in list(self.classes.values()):
            methnames = cls.get_all_method_names()
            pvm = cls.get_all_pure_virtual_methods()

            for d in cls['inherits']:
                c = d['class']
                a = d['access']    # do not depend on this to be 'public'
                trace_print( 'PARENT CLASS:', c )
                if c not in self.classes: trace_print('WARN: parent class not found')
                if c in self.classes and self.classes[c]['abstract']:
                    p = self.classes[ c ]
                    for meth in p.get_all_methods():    #p["methods"]["public"]:
                        trace_print( '\t\tmeth', meth['name'], 'pure virtual', meth['pure_virtual'] )
                        if meth['pure_virtual'] and meth['name'] not in methnames: cls['abstract'] = True; break





    def evaluate_struct_stack(self):
        """Create a Struct out of the name stack (but not its parts)"""
        #print( 'eval struct stack', self.nameStack )
        #if self.braceDepth != len(self.nameSpaces): return
        struct = CppStruct(self.nameStack)
        struct["namespace"] = self.cur_namespace()
        self.structs[ struct['type'] ] = struct
        self.structs_order.append( struct )
        if self.curClass:
            struct['parent'] = self.curClass
            klass = self.classes[ self.curClass ]
            klass['structs'][self.curAccessSpecifier].append( struct )
            if self.curAccessSpecifier == 'public': klass._public_structs[ struct['type'] ] = struct
        self.curStruct = struct
        self._structs_brace_level[ struct['type'] ] = self.braceDepth

    
    def parse_method_type( self, stack ):
        trace_print( 'meth type info', stack )
        if stack[0] in ':;': stack = stack[1:]
        info = { 
            'debug': ' '.join(stack).replace(' : : ', '::' ).replace(' < ', '<' ).replace(' > ', '> ' ).replace(" >",">").replace(">>", "> >").replace(">>", "> >"), 
            'class':None, 
            'namespace':self.cur_namespace(add_double_colon=True),
        }

        for tag in 'defined pure_virtual operator constructor destructor extern template virtual static explicit inline friend returns returns_pointer returns_fundamental returns_class'.split(): info[tag]=False
        header = stack[ : stack.index('(') ]
        header = ' '.join( header )
        header = header.replace(' : : ', '::' )
        header = header.replace(' < ', '<' )
        header = header.replace(' > ', '> ' )
        header = header.strip()

        if '{' in stack:
            info['defined'] = True
            self._method_body = self.braceDepth + 1
            trace_print( 'NEW METHOD WITH BODY', self.braceDepth )
        elif stack[-1] == ';':
            info['defined'] = False
            self._method_body = None    # not a great idea to be clearing here
        else: assert 0

        if len(stack) > 3 and stack[-1] == ';' and stack[-2] == '0' and stack[-3] == '=':
            info['pure_virtual'] = True

        r = header.split()
        name = None
        if 'operator' in stack:    # rare case op overload defined outside of class
            op = stack[ stack.index('operator')+1 : stack.index('(') ]
            op = ''.join(op)
            if not op:
                if " ".join(['operator', '(', ')', '(']) in " ".join(stack):
                    op = "()"
                else:
                    trace_print( 'Error parsing operator')
                    return None
            
            info['operator'] = op
            name = 'operator' + op
            a = stack[ : stack.index('operator') ]

        elif r:
            name = r[-1]
            a = r[ : -1 ]    # strip name

        if name is None: return None
        #if name.startswith('~'): name = name[1:]

        while a and a[0] == '}':    # strip - can have multiple } }
            a = a[1:]


        if '::' in name:
            #klass,name = name.split('::')    # methods can be defined outside of class
            klass = name[ : name.rindex('::') ]
            name = name.split('::')[-1]
            info['class'] = klass
            if klass in self.classes and not self.curClass:
                 #Class function defined outside the class
                return None
        #    info['name'] = name
        #else: info['name'] = name

        if name.startswith('~'):
            info['destructor'] = True
            name = name[1:]
        elif not a or (name == self.curClass and len(self.curClass)):
            info['constructor'] = True

        info['name'] = name

        for tag in 'extern virtual static explicit inline friend'.split():
            if tag in a: info[ tag ] = True; a.remove( tag )    # inplace
        if 'template' in a:
            a.remove('template')
            b = ' '.join( a )
            if '>' in b:
                info['template'] = b[ : b.index('>')+1 ]
                info['returns'] = b[ b.index('>')+1 : ]    # find return type, could be incorrect... TODO
                if '<typename' in info['template'].split():
                    typname = info['template'].split()[-1]
                    typname = typname[ : -1 ]    # strip '>'
                    if typname not in self._template_typenames: self._template_typenames.append( typname )
            else: info['returns'] = ' '.join( a )
        else: info['returns'] = ' '.join( a )
        info['returns'] = info['returns'].replace(' <', '<').strip()

        ## be careful with templates, do not count pointers inside template
        info['returns_pointer'] = info['returns'].split('>')[-1].count('*')
        if info['returns_pointer']: info['returns'] = info['returns'].replace('*','').strip()

        info['returns_reference'] = '&' in info['returns']
        if info['returns']: info['returns'] = info['returns'].replace('&','').strip()

        a = []
        for b in info['returns'].split():
            if b == '__const__': info['returns_const'] = True
            elif b == 'const': info['returns_const'] = True
            else: a.append( b )
        info['returns'] = ' '.join( a )

        info['returns_fundamental'] = is_fundamental( info['returns'] )
        return info

    def evaluate_method_stack(self):
        """Create a method out of the name stack"""

        if self.curStruct:
            trace_print( 'WARN - struct contains methods - skipping' )
            trace_print( self.stack )
            assert 0

        info = self.parse_method_type( self.stack )
        if info:
            if info[ 'class' ] and info['class'] in self.classes:     # case where methods are defined outside of class
                newMethod = CppMethod(self.nameStack, info['name'], info)
                klass = self.classes[ info['class'] ]
                klass[ 'methods' ][ 'public' ].append( newMethod )
                newMethod['parent'] = klass
                if klass['namespace']: newMethod['path'] = klass['namespace'] + '::' + klass['name']
                else: newMethod['path'] = klass['name']
                
            elif self.curClass:    # normal case
                newMethod = CppMethod(self.nameStack, self.curClass, info)
                klass = self.classes[self.curClass]
                klass['methods'][self.curAccessSpecifier].append(newMethod)
                newMethod['parent'] = klass
                if klass['namespace']: newMethod['path'] = klass['namespace'] + '::' + klass['name']
                else: newMethod['path'] = klass['name']
            else: #non class functions
                debug_print("FREE FUNCTION")
                newMethod = CppMethod(self.nameStack, None, info)
                self.functions.append(newMethod)
            global parseHistory
            parseHistory.append({"braceDepth": self.braceDepth, "item_type": "method", "item": newMethod})
        else:
            trace_print( 'free function?', self.nameStack )

        self.stack = []

    def _parse_typedef( self, stack, namespace='' ):
        if not stack or 'typedef' not in stack: return
        stack = list( stack )    # copy just to be safe
        if stack[-1] == ';': stack.pop()

        while stack and stack[-1].isdigit(): stack.pop()    # throw away array size for now

        idx = stack.index('typedef')
        name = namespace + stack[-1]
        s = ''
        for a in stack[idx+1:-1]:
            if a == '{': break
            if not s or s[-1] in ':<>' or a in ':<>': s += a    # keep compact
            else: s += ' ' + a    # spacing

        r = {'name':name, 'raw':s, 'type':s}
        if not is_fundamental(s):
            if 'struct' in s.split(): pass        # TODO is this right? "struct ns::something"
            elif '::' not in s: s = namespace + s         # only add the current name space if no namespace given
            r['type'] = s
        if s: return r


    def evaluate_typedef(self):
        ns = self.cur_namespace(add_double_colon=True)
        res = self._parse_typedef( self.stack, ns )
        if res:
            name = res['name']
            self.typedefs[ name ] = res['type']
            if name not in self.typedefs_order: self.typedefs_order.append( name )


    def evaluate_property_stack(self):
        """Create a Property out of the name stack"""
        global parseHistory
        assert self.stack[-1] == ';'
        if self.nameStack[0] == 'typedef':
            if self.curClass:
                typedef = self._parse_typedef( self.stack )
                name = typedef['name']
                klass = self.classes[ self.curClass ]
                klass[ 'typedefs' ][ self.curAccessSpecifier ].append( name )
                if self.curAccessSpecifier == 'public': klass._public_typedefs[ name ] = typedef['type']
                Resolver.SubTypedefs[ name ] = self.curClass
            else: assert 0
        elif self.curStruct or self.curClass:
            if len(self.nameStack) == 1:
                #See if we can de anonymize the type
                filteredParseHistory = [h for h in parseHistory if h["braceDepth"] == self.braceDepth]
                if len(filteredParseHistory) and filteredParseHistory[-1]["item_type"] == "class":
                    self.nameStack.insert(0, filteredParseHistory[-1]["item"]["name"])
                    debug_print("DEANONYMOIZING %s to type '%s'"%(self.nameStack[1], self.nameStack[0]))
            newVar = CppVariable(self.nameStack)
            newVar['namespace'] = self.current_namespace()
            if self.curStruct:
                self.curStruct[ 'fields' ].append( newVar )
                newVar['property_of_struct'] = self.curStruct
            elif self.curClass:
                klass = self.classes[self.curClass]
                klass["properties"][self.curAccessSpecifier].append(newVar)
                newVar['property_of_class'] = klass['name']
            parseHistory.append({"braceDepth": self.braceDepth, "item_type": "variable", "item": newVar})

        self.stack = []        # CLEAR STACK

    def evaluate_class_stack(self):
        """Create a Class out of the name stack (but not its parts)"""
        #dont support sub classes today
        #print( 'eval class stack', self.nameStack )
        parent = self.curClass
        if self.braceDepth > len( self.nameSpaces) and parent:
            trace_print( 'HIT NESTED SUBCLASS' )
            self.accessSpecifierStack.append(self.curAccessSpecifier)
        elif self.braceDepth != len(self.nameSpaces):
            error_print( 'ERROR: WRONG BRACE DEPTH' )
            return
        
        if self.nameStack[0] == "class":
            self.curAccessSpecifier = 'private'
        else:#struct
            self.curAccessSpecifier = 'public'
        debug_print("curAccessSpecifier changed/defaulted to %s"%self.curAccessSpecifier)
        if self.nameStack[0] == "union":
            newClass = CppUnion(self.nameStack)
            self.anon_union_counter = [self.braceDepth, 2]
            trace_print( 'NEW UNION', newClass['name'] )
        else:
            newClass = CppClass(self.nameStack)
            trace_print( 'NEW CLASS', newClass['name'] )
        newClass["declaration_method"] = self.nameStack[0]
        self.classes_order.append( newClass )    # good idea to save ordering
        self.stack = []        # fixes if class declared with ';' in closing brace
        if parent:
            newClass["namespace"] = self.classes[ parent ]['namespace'] + '::' + parent
            newClass['parent'] = parent
            self.classes[ parent ]['nested_classes'].append( newClass )
            ## supports nested classes with the same name ##
            self.curClass = key = parent+'::'+newClass['name']
            self._classes_brace_level[ key ] = self.braceDepth

        elif newClass['parent']:        # nested class defined outside of parent.  A::B {...}
            parent = newClass['parent']
            newClass["namespace"] = self.classes[ parent ]['namespace'] + '::' + parent
            self.classes[ parent ]['nested_classes'].append( newClass )
            ## supports nested classes with the same name ##
            self.curClass = key = parent+'::'+newClass['name']
            self._classes_brace_level[ key ] = self.braceDepth

        else:
            newClass["namespace"] = self.cur_namespace()
            key = newClass['name']
            self.curClass = newClass["name"]
            self._classes_brace_level[ newClass['name'] ] = self.braceDepth

        if not key.endswith("::") and not key.endswith(" ") and len(key) != 0:
            if key in self.classes:
                trace_print( 'ERROR name collision:', key )
                self.classes[key].show()
                trace_print('-'*80)
                newClass.show()            
                assert key not in self.classes    # namespace collision
        self.classes[ key ] = newClass
        global parseHistory
        parseHistory.append({"braceDepth": self.braceDepth, "item_type": "class", "item": newClass})
    

    def evalute_forward_decl(self):
        trace_print( 'FORWARD DECL', self.nameStack )
        assert self.nameStack[0] in ('class', 'struct')
        name = self.nameStack[-1]
        if self.curClass:
            klass = self.classes[ self.curClass ]
            klass['forward_declares'][self.curAccessSpecifier].append( name )
            if self.curAccessSpecifier == 'public': klass._public_forward_declares.append( name )
        else: self._forward_decls.append( name )

class CppHeader( _CppHeader ):
    """Parsed C++ class header
    
    Variables produced:
    self.classes - Dictionary of classes found in a given header file where the
        key is the name of the class
    """
    IGNORE_NAMES = '__extension__'.split()
   
    def show(self):
        for className in list(self.classes.keys()):self.classes[className].show()

    def __init__(self, headerFileName, argType="file", **kwargs):
        """Create the parsed C++ header file parse tree
        
        headerFileName - Name of the file to parse OR actual file contents (depends on argType)
        argType - Indicates how to interpret headerFileName as a file string or file name
        kwargs - Supports the following keywords
        """
        ## reset global state ##
        global doxygenCommentCache
        doxygenCommentCache = ""
        CppVariable.Vars = []
        CppStruct.Structs = []

        if (argType == "file"):
            self.headerFileName = os.path.expandvars(headerFileName)
            self.mainClass = os.path.split(self.headerFileName)[1][:-2]
            headerFileStr = ""
        elif argType == "string":
            self.headerFileName = ""
            self.mainClass = "???"
            headerFileStr = headerFileName
        else:
            raise Exception("Arg type must be either file or string")
        self.curClass = ""
       
        # nested classes have parent::nested, but no extra namespace,
        # this keeps the API compatible, TODO proper namespace for everything. 
        Resolver.CLASSES = {}
        self.classes = Resolver.CLASSES
        #Functions that are not part of a class
        self.functions = []
        
        self.pragmas = []
        self.defines = []
        self.includes = []
        self._precomp_macro_buf = [] #for internal purposes, will end up filling out pragmras and defines at the end

        self.enums = []
        self.global_enums = {}
        self.nameStack = []
        self.nameSpaces = []
        self.curAccessSpecifier = 'private'    # private is default
        self.accessSpecifierStack = []
        self.accessSpecifierScratch = []
        debug_print("curAccessSpecifier changed/defaulted to %s"%self.curAccessSpecifier)
        self.initextra()
    
        self.anon_union_counter = [-1, 0]
    
        if (len(self.headerFileName)):
            fd = open(self.headerFileName)
            headerFileStr = "".join(fd.readlines())
            fd.close()     
        
        # Make sure supportedAccessSpecifier are sane
        for i in range(0, len(supportedAccessSpecifier)):
            if " " not in supportedAccessSpecifier[i]: continue
            supportedAccessSpecifier[i] = re.sub("[ ]+", " ", supportedAccessSpecifier[i]).strip()
        
        # Strip out template declarations
        headerFileStr = re.sub("template[\t ]*<[^>]*>", "", headerFileStr)

        # Change multi line #defines and expressions to single lines maintaining line nubmers
        # Based from http://stackoverflow.com/questions/2424458/regular-expression-to-match-cs-multiline-preprocessor-statements
        matches = re.findall(r'(?m)^(?:.*\\\r?\n)+.*$', headerFileStr)
        is_define = re.compile(r'[ \t\v]*#[Dd][Ee][Ff][Ii][Nn][Ee]')
        for m in matches:
            #Keep the newlines so that linecount doesnt break
            num_newlines = len([a for a in m if a=="\n"])
            if is_define.match(m):
                new_m = m.replace("\n", "<CppHeaderParser_newline_temp_replacement>\\n")
            else:
                # Just expression taking up multiple lines, make it take 1 line for easier parsing
                new_m = m.replace("\\\n", " ")
            if (num_newlines > 1):
                new_m += "\n"*(num_newlines)
            headerFileStr = headerFileStr.replace(m, new_m)
        
        #Filter out Extern "C" statements.  These are order dependent
        matches = re.findall(re.compile(r'extern[\t ]+"[Cc]"[\t \n\r]*{', re.DOTALL), headerFileStr)
        for m in matches:
            #Keep the newlines so that linecount doesnt break
            num_newlines = len([a for a in m if a=="\n"])
            headerFileStr = headerFileStr.replace(m, "\n" * num_newlines)        
        headerFileStr = re.sub(r'extern[ ]+"[Cc]"[ ]*', "", headerFileStr)
                
        self.braceDepth = 0
        lex.lex()
        lex.input(headerFileStr)
        global curLine
        global curChar
        curLine = 0
        curChar = 0
        try:
            while True:
                tok = lex.token()
                if not tok: break
                if self.anon_union_counter[0] == self.braceDepth and self.anon_union_counter[1]:
                    self.anon_union_counter[1] -= 1
                tok.value = TagStr(tok.value, lineno=tok.lineno)
                #debug_print("TOK: %s"%tok)
                if tok.type == 'NAME' and tok.value in self.IGNORE_NAMES: continue
                self.stack.append( tok.value )
                curLine = tok.lineno
                curChar = tok.lexpos
                if (tok.type in ('PRECOMP_MACRO', 'PRECOMP_MACRO_CONT')):
                    debug_print("PRECOMP: %s"%tok)
                    self._precomp_macro_buf.append(tok.value)
                    continue
                if (tok.type == 'OPEN_BRACE'):
                    if len(self.nameStack) >= 2 and is_namespace(self.nameStack):    # namespace {} with no name used in boost, this sets default?
                        if self.nameStack[1] == "__IGNORED_NAMESPACE__CppHeaderParser__":#Used in filtering extern "C"
                            self.nameStack[1] = ""
                        self.nameSpaces.append(self.nameStack[1])
                        ns = self.cur_namespace(); self.stack = []
                        if ns not in self.namespaces: self.namespaces.append( ns )
                    if len(self.nameStack) and not is_enum_namestack(self.nameStack):
                        self.evaluate_stack()
                    else:
                        self.nameStack.append(tok.value)
                    if self.stack and self.stack[0] == 'class': self.stack = []
                    self.braceDepth += 1
                    
                elif (tok.type == 'CLOSE_BRACE'):
                    if self.braceDepth == 0:
                        continue
                    if (self.braceDepth == len(self.nameSpaces)):
                        tmp = self.nameSpaces.pop()
                        self.stack = []    # clear stack when namespace ends?
                    if len(self.nameStack) and is_enum_namestack(self.nameStack):
                        self.nameStack.append(tok.value)
                    elif self.braceDepth < 10:
                        self.evaluate_stack()
                    else:
                        self.nameStack = []
                    self.braceDepth -= 1
                    #self.stack = []; print 'BRACE DEPTH', self.braceDepth, 'NS', len(self.nameSpaces)
                    if self.curClass: debug_print( 'CURBD %s'%self._classes_brace_level[ self.curClass ] )

                    if (self.braceDepth == 0) or (self.curClass and self._classes_brace_level[self.curClass]==self.braceDepth):
                        trace_print( 'END OF CLASS DEF' )
                        if self.accessSpecifierStack:
                            self.curAccessSpecifier = self.accessSpecifierStack[-1]
                            self.accessSpecifierStack = self.accessSpecifierStack[:-1] 
                        if self.curClass and self.classes[ self.curClass ]['parent']: self.curClass = self.classes[ self.curClass ]['parent']
                        else: self.curClass = ""; #self.curStruct = None
                        self.stack = []

                    #if self.curStruct: self.curStruct = None
                    if self.braceDepth == 0 or (self.curStruct and self._structs_brace_level[self.curStruct['type']]==self.braceDepth):
                        trace_print( 'END OF STRUCT DEF' )
                        self.curStruct = None

                    if self._method_body and (self.braceDepth + 1) <= self._method_body:
                        self._method_body = None; self.stack = []; self.nameStack = []; trace_print( 'FORCE CLEAR METHBODY' )
                
                if (tok.type == 'OPEN_PAREN'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'CLOSE_PAREN'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'OPEN_SQUARE_BRACKET'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'CLOSE_SQUARE_BRACKET'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'TAB'): pass
                elif (tok.type == 'EQUALS'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'COMMA'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'BACKSLASH'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'PIPE'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'PERCENT'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'CARET'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'EXCLAMATION'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'SQUOTE'): pass
                elif (tok.type == 'NUMBER'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'MINUS'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'PLUS'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'STRING_LITERAL'):
                    self.nameStack.append(tok.value)
                elif (tok.type == 'NAME' or tok.type == 'AMPERSTAND' or tok.type == 'ASTERISK' or tok.type == 'CHAR_LITERAL'):
                    if tok.value in ignoreSymbols:
                        debug_print("Ignore symbol %s"%tok.value)
                    elif (tok.value == 'class'):
                        self.nameStack.append(tok.value)
                    elif tok.value in supportedAccessSpecifier:
                        if len(self.nameStack) and self.nameStack[0] in ("class", "struct", "union"):
                            self.nameStack.append(tok.value)
                        elif self.braceDepth == len(self.nameSpaces) + 1 or self.braceDepth == (len(self.nameSpaces) + len(self.curClass.split("::"))):
                            self.curAccessSpecifier = tok.value;
                            self.accessSpecifierScratch.append(tok.value)
                            debug_print("curAccessSpecifier updated to %s"%self.curAccessSpecifier)
                        self.stack = []
                    else:
                        self.nameStack.append(tok.value)
                        if self.anon_union_counter[0] == self.braceDepth:
                            self.anon_union_counter = [-1, 0]
                elif (tok.type == 'COLON'):
                    #Dont want colon to be first in stack
                    if len(self.nameStack) == 0:
                        self.accessSpecifierScratch = []
                        continue
                    
                    # Handle situation where access specifiers can be multi words such as "public slots"
                    jns = " ".join(self.accessSpecifierScratch + self.nameStack)
                    if jns in supportedAccessSpecifier:
                        self.curAccessSpecifier = jns;
                        debug_print("curAccessSpecifier updated to %s"%self.curAccessSpecifier)
                        self.stack = []
                        self.nameStack = []
                    else:
                        self.nameStack.append(tok.value)
                    self.accessSpecifierScratch = []

                elif (tok.type == 'SEMI_COLON'):
                    if self.anon_union_counter[0] == self.braceDepth and self.anon_union_counter[1]:
                        debug_print("Creating anonymous union")
                        #Force the processing of an anonymous union
                        saved_namestack = self.nameStack[:] 
                        saved_stack = self.stack[:]
                        self.nameStack = [""]
                        self.stack = self.nameStack + [";"]
                        self.nameStack = self.nameStack[0:1]
                        debug_print("pre eval anon stack")
                        self.evaluate_stack( tok.type )
                        debug_print("post eval anon stack")
                        self.nameStack = saved_namestack
                        self.stack = saved_stack
                        self.anon_union_counter = [-1, 0];
                    
                    
                    if (self.braceDepth < 10): self.evaluate_stack( tok.type )
                    if not self.stack: continue
                    if self.stack[0]=='typedef' and ( '{' not in self.stack or '}' in self.stack ): self.stack = []; trace_print( "REAL CLEAR")
                    elif self.stack[0] != 'typedef': self.stack = []; trace_print('CLEAR STACK')

        except:
            if (debug): raise
            raise CppParseError("Not able to parse %s on line %d evaluating \"%s\"\nError around: %s"
                                % (self.headerFileName, tok.lineno, tok.value, " ".join(self.nameStack)))

        self.finalize()
        global parseHistory
        parseHistory = []

    def evaluate_stack(self, token=None):
        """Evaluates the current name stack"""
        global doxygenCommentCache
        debug_print( "Evaluating stack %s\n       BraceDepth: %s (called from %d)" %(self.nameStack,self.braceDepth, inspect.currentframe().f_back.f_lineno))
        
        #Handle special case of overloading operator ()
        if "operator()(" in "".join(self.nameStack):
            operator_index = self.nameStack.index("operator")
            self.nameStack.pop(operator_index + 2)
            self.nameStack.pop(operator_index + 1)
            self.nameStack[operator_index] = "operator()"
        
        if (len(self.curClass)):
            debug_print( "%s (%s) "%(self.curClass, self.curAccessSpecifier))

        #Filter special case of array with casting in it
        try:
            bracePos = self.nameStack.index("[")
            parenPos = self.nameStack.index("(")
            if bracePos == parenPos - 1:
                endParen = self.nameStack.index(")")
                self.nameStack = self.nameStack[:bracePos + 1] + self.nameStack[endParen + 1:]
                debug_print("Filtered namestack to=%s"%self.nameStack)
        except: pass

        #if 'typedef' in self.nameStack: self.evaluate_typedef()        # allows nested typedefs, probably a bad idea
        if not self.curClass and 'typedef' in self.nameStack:
            trace_print('STACK', self.stack)
            if token == 'SEMI_COLON' and ('{' not in self.stack or '}' in self.stack): self.evaluate_typedef()
            else: return
        
        elif (len(self.nameStack) == 0):
            debug_print( "trace" )
            debug_print( "(Empty Stack)" )
            return
        elif (self.nameStack[0] == "namespace"):
            #Taken care of outside of here
            pass
        elif self.nameStack[0] == "friend":
            pass
        elif len(self.nameStack) >= 2 and self.nameStack[0] == 'using' and self.nameStack[1] == 'namespace': pass    # TODO

        elif is_enum_namestack(self.nameStack):
            debug_print( "trace" )
            self.evaluate_enum_stack()

        elif self._method_body and (self.braceDepth + 1) > self._method_body: trace_print( 'INSIDE METHOD DEF' )
        elif is_method_namestack(self.stack) and not self.curStruct and '(' in self.nameStack:
            debug_print( "trace" )
            if self.braceDepth > 0:
                if "{" in self.stack and self.stack[0] != '{' and self.stack[-1] == ';' and self.braceDepth == 1:
                    #Special case of a method defined outside a class that has a body
                    pass
                else: 
                    self.evaluate_method_stack()
            else:
                #Free function
                self.evaluate_method_stack()
        elif is_property_namestack(self.nameStack) and self.stack[-1] == ';':
            debug_print( "trace" )
            if self.nameStack[0] in ('class', 'struct') and len(self.stack) == 3: self.evalute_forward_decl()
            elif len(self.nameStack) >= 2 and (self.nameStack[0]=='friend' and self.nameStack[1]=='class'): pass
            else: self.evaluate_property_stack()    # catches class props and structs in a namespace

        elif self.nameStack[0] in ("class", "struct", "union"):
            #Parsing a union can reuse much of the class parsing
            debug_print( "trace" )
            self.evaluate_class_stack()
        #elif (self.nameStack[0] == "struct"):
        #    debug_print( "trace" )
            ##this causes a bug when structs are nested in protected or private##self.curAccessSpecifier = "public"
        #    self.evaluate_struct_stack()


        elif not self.curClass:
            debug_print( "trace" )
            if is_enum_namestack(self.nameStack): self.evaluate_enum_stack()
            elif self.curStruct and self.stack[-1] == ';': self.evaluate_property_stack()    # this catches fields of global structs
            self.nameStack = []
            doxygenCommentCache = ""
            return
        elif (self.braceDepth < 1):
            debug_print( "trace" )
            #Ignore global stuff for now
            debug_print( "Global stuff: %s"%self.nameStack )
            self.nameStack = []
            doxygenCommentCache = ""
            return
        elif (self.braceDepth > len(self.nameSpaces) + 1):
            debug_print( "trace" )
            self.nameStack = []
            doxygenCommentCache = ""
            return

        self.nameStack = []        # its a little confusing to have some if/else above return and others not, and then clearning the nameStack down here
        doxygenCommentCache = ""
    

    def evaluate_enum_stack(self):
        """Create an Enum out of the name stack"""
        debug_print( "evaluating enum" )
        newEnum = CppEnum(self.nameStack)
        if len(list(newEnum.keys())):
            if len(self.curClass):
                newEnum["namespace"] = self.cur_namespace(False)
                klass = self.classes[self.curClass]
                klass["enums"][self.curAccessSpecifier].append(newEnum)
                if self.curAccessSpecifier == 'public' and 'name' in newEnum: klass._public_enums[ newEnum['name'] ] = newEnum
            else:
                newEnum["namespace"] = self.cur_namespace(True)
                self.enums.append(newEnum)
                if 'name' in newEnum and newEnum['name']: self.global_enums[ newEnum['name'] ] = newEnum

            #This enum has instances, turn them into properties
            if "instances" in newEnum:
                instanceType = "enum"
                if "name" in newEnum:
                    instanceType = newEnum["name"]
                for instance in newEnum["instances"]:
                    self.nameStack = [instanceType,  instance]
                    self.evaluate_property_stack()
                del newEnum["instances"]


    def __repr__(self):
        rtn = ""
        for className in list(self.classes.keys()):
            rtn += "%s\n"%self.classes[className]
        if self.functions:
            rtn += "// functions\n"
            for f in self.functions:
                rtn += "%s\n"%f
        if self.enums:
            rtn += "// enums\n"
            for f in self.enums:
                rtn += "%s\n"%f
        return rtn
