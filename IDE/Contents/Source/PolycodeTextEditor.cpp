/*
 Copyright (C) 2012 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
	
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "PolycodeTextEditor.h"

PolycodeSyntaxHighlighter::PolycodeSyntaxHighlighter(String extension) {

	colorScheme[0] = Color(0.0, 0.0, 0.0, 1.0);
	colorScheme[1] = Color(0.0/255.0, 112.0/255.0, 0.0, 1.0);
	colorScheme[2] = Color(192.0/255.0, 45.0/255.0, 167.0/255.0, 1.0);
	colorScheme[3] = Color(48.0/255.0, 99.0/255.0, 105.0/255.0, 1.0);
	colorScheme[4] = Color(227.0/255.0, 11.0/255.0, 0.0/255.0, 1.0);
	colorScheme[5] = Color(82.0/255.0, 31.0/255.0, 140.0/255.0, 1.0);	
	colorScheme[6] = Color(39.0/255.0, 41.0/255.0, 215.0/255.0, 1.0);
	
//	String separators = " ;()\t\n=+-/\\'\"";	
//	String keywords = "true,false,";
	
	separators = String("[ [ ] { } ; . , : # ( ) \t \n = + - / \\ ' \"").split(" ");
	separators.push_back(" ");
	
	keywords = String("require true false class self break do end else elseif function if local nil not or repeat return then until while").split(" ");
}

PolycodeSyntaxHighlighter::~PolycodeSyntaxHighlighter() {

}

bool PolycodeSyntaxHighlighter::contains(String part, std::vector<String> list) {
	for(int i=0; i < list.size(); i++) {
		if(list[i] == part)
			return true;
	}
	return false;
}

std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseText(String text) {
	return parseLua(text);
}
	
std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseLua(String text) {
	std::vector<SyntaxHighlightToken> tokens;
	
	text = text+"\n";
	
	const int MODE_GENERAL = 0;
	const int MODE_COMMENT = 1;
	const int MODE_STRING = 2;
	const int MODE_METHOD = 3;
	const int MODE_KEYWORD = 4;
	const int MODE_NUMBER = 5;
	const int MODE_MEMBER = 6;
						
	int mode = MODE_GENERAL;
	
	bool isComment = false;
	
	String line = "";
	
	char lastSeparator = ' ';

	
	for(int i=0; i < text.length(); i++) {
		char ch = text[i];				
		if(contains(String(ch), separators)) {			

			unsigned int type = mode;
			unsigned int ch_type = mode;

	
			if(ch == '\"' && mode != MODE_COMMENT)
				ch_type = MODE_STRING;
	
			if(mode != MODE_STRING && ch == '('  && mode != MODE_COMMENT) {
				type = MODE_METHOD;
			}

			if(mode != MODE_STRING  && mode != MODE_COMMENT) {
				if(contains(line, keywords)) {
					type = MODE_KEYWORD;
				}
			}
	
			if(mode != MODE_STRING && !isComment && mode != MODE_COMMENT) {
			
				if(line.isNumber()) {
					type = MODE_NUMBER;
				} else {
					if(lastSeparator == '.' && ch != '.' && ch != ':') {
						type = MODE_MEMBER;
					}							
				}
			}		
	
			if(isComment) {
				type = MODE_COMMENT;
				ch_type = MODE_COMMENT;
			}
				
			if(mode == MODE_COMMENT) {
				type = MODE_COMMENT;
				ch_type = MODE_COMMENT;
			}
			
	
			if(line != "")
				tokens.push_back(SyntaxHighlightToken(line, type));
			tokens.push_back(SyntaxHighlightToken(String(ch), ch_type));

			if(ch == '-' && lastSeparator == '-' && mode != MODE_STRING) {
				isComment = true;
				tokens[tokens.size()-1].type = MODE_COMMENT;
				tokens[tokens.size()-2].type = MODE_COMMENT;				
			}

			if(ch == '[' && lastSeparator == '[' && isComment && mode != MODE_STRING) {
				unsigned int old_mode = mode;
				mode = MODE_COMMENT;
				
				// ugly hack for ---[[, which is not a block comment
				if(tokens.size() > 4) {
					if(tokens[tokens.size()-5].text == "-") {
						mode = old_mode;
					}
				}
			}
			
			if(ch == ']' && lastSeparator == ']' && mode == MODE_COMMENT) {
				mode = MODE_GENERAL;
			}
			
			if(ch == '\n' )
				isComment = false;
				

			if(ch == '\"'  && mode != MODE_COMMENT) {
				if(mode == MODE_STRING) {
					mode = MODE_GENERAL;	
				} else {
					mode = MODE_STRING;
				}
			}	
						
			line = "";
			lastSeparator = ch;			
		} else {
			line += String(ch);
		}
	}
	
	for(int i=0; i < tokens.size(); i++) {
		switch(tokens[i].type) {
			case MODE_STRING:
				tokens[i].color = colorScheme[4];			
			break;
			case MODE_COMMENT:
				tokens[i].color = colorScheme[1];			
			break;			
			case MODE_METHOD:
				tokens[i].color = colorScheme[3];			
			break;			
			case MODE_KEYWORD:
				tokens[i].color = colorScheme[2];
			break;		
			case MODE_NUMBER:
				tokens[i].color = colorScheme[6];
			break;		
			case MODE_MEMBER:
				tokens[i].color = colorScheme[5];
			break;															
			default:
				tokens[i].color = colorScheme[0];
			break;
		}
//		printf("%s(%d)", tokens[i].text.c_str(), tokens[i].type);		
	}
	
	return tokens;
}

PolycodeTextEditor::PolycodeTextEditor() : PolycodeEditor(true){
	editorType = "PolycodeTextEditor";
}

PolycodeTextEditor::~PolycodeTextEditor() {
	if(syntaxHighligher)
		delete syntaxHighligher;
}

bool PolycodeTextEditor::openFile(OSFileEntry filePath) {
	
	textInput = new UITextInput(true, 100, 100);
	addChild(textInput);	
	
	syntaxHighligher = NULL;
	
	if(filePath.extension == "lua") {
		syntaxHighligher = new PolycodeSyntaxHighlighter(filePath.extension);
		textInput->setSyntaxHighlighter(syntaxHighligher);
	}
	
	Data *data = new Data();
	if(data->loadFromFile(filePath.fullPath)) {
		textInput->setText(data->getAsString(String::ENCODING_UTF8));
	}
	delete data;
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeTextEditor::highlightLine(unsigned int lineNumber) {
	int lineSize = textInput->getLineText(lineNumber-1).length();
	textInput->setSelection(lineNumber-1, lineNumber-1, 0, lineSize);
	textInput->showLine(lineNumber, false);
}

void PolycodeTextEditor::saveFile() {
	Data *data = new Data();
	data->setFromString(textInput->getText(), String::ENCODING_UTF8);
	data->saveToFile(filePath);
	delete data;
}

void PolycodeTextEditor::Resize(int x, int y) {
	textInput->Resize(x,y);
	PolycodeEditor::Resize(x,y);	
}

