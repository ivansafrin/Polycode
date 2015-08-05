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

extern SyntaxHighlightTheme *globalSyntaxTheme;
extern UIGlobalMenu *globalMenu;

void SyntaxHighlightTheme::loadFromFile(String themeName) {
	String filePath = "SyntaxThemes/"+themeName+".xml";
	
	this->name =themeName;
	
	Object themeObject;
	if(themeObject.loadFromXML(filePath)) {

		ObjectEntry *hintingEntry = themeObject.root["useStrongHinting"];
		if(hintingEntry) {
			useStrongHinting = hintingEntry->boolVal;
		}
	
		ObjectEntry *bgColorEntry = themeObject.root["bgColor"];		
		if(bgColorEntry) {
			ObjectEntry *r = (*bgColorEntry)["r"];
			ObjectEntry *g = (*bgColorEntry)["g"];
			ObjectEntry *b = (*bgColorEntry)["b"];
			if(r && g && b) {
				bgColor.setColorRGB(r->intVal, g->intVal, b->intVal);
			}		
		}

		ObjectEntry *cursorColorEntry = themeObject.root["cursorColor"];		
		if(cursorColorEntry) {
			ObjectEntry *r = (*cursorColorEntry)["r"];
			ObjectEntry *g = (*cursorColorEntry)["g"];
			ObjectEntry *b = (*cursorColorEntry)["b"];
			if(r && g && b) {
				cursorColor.setColorRGB(r->intVal, g->intVal, b->intVal);
			}		
		}

		ObjectEntry *selectionColorEntry = themeObject.root["selectionColor"];		
		if(selectionColorEntry) {
			ObjectEntry *r = (*selectionColorEntry)["r"];
			ObjectEntry *g = (*selectionColorEntry)["g"];
			ObjectEntry *b = (*selectionColorEntry)["b"];
			if(r && g && b) {
				selectionColor.setColorRGB(r->intVal, g->intVal, b->intVal);
			}		
		}
		
		ObjectEntry *lineNumberColorEntry = themeObject.root["lineNumberColor"];		
		if(lineNumberColorEntry) {
			ObjectEntry *r = (*lineNumberColorEntry)["r"];
			ObjectEntry *g = (*lineNumberColorEntry)["g"];
			ObjectEntry *b = (*lineNumberColorEntry)["b"];
			if(r && g && b) {
				lineNumberColor.setColorRGB(r->intVal, g->intVal, b->intVal);
			}		
		}		
			
		ObjectEntry *textColors = themeObject.root["textColors"];
		if(textColors) {
			for(int i=0; i < textColors->length && i < 8; i++) {
				ObjectEntry *colorEntry = (*textColors)[i];
				if(colorEntry) {
					ObjectEntry *r = (*colorEntry)["r"];
					ObjectEntry *g = (*colorEntry)["g"];
					ObjectEntry *b = (*colorEntry)["b"];
					if(r && g && b) {
						colors[i].setColorRGB(r->intVal, g->intVal, b->intVal);
					}
				}				
			}
		}
	}
}

PolycodeSyntaxHighlighter::PolycodeSyntaxHighlighter(String extension) {
	

	if(extension == "lua") {
		mode = MODE_LUA;

		std::vector<String>separators_s = String("[ * [ ] { } ; . , : # ( ) \t \n = + - / \\ ' \"").split(" ");
		separators_s.push_back(" ");
	
		for(int i=0; i < separators_s.size(); i++) {
			separators.push_back(separators_s[i][0]);
		}
	
		keywords = String("for cast safe_cast and require true false class self break do end else elseif function if local nil not or repeat return then until while").split(" ");
		
	} else if(extension == "vert" || extension == "frag") {
		mode = MODE_GLSL;
		
		std::vector<String>separators_s = String("[ * [ ] { } ; . , : ( ) \t \n = + - / \\ ' \"").split(" ");
		separators_s.push_back(" ");
	
		for(int i=0; i < separators_s.size(); i++) {
			separators.push_back(separators_s[i][0]);
		}
	
		keywords = String("for cast and true falsebreak do end else if notreturn then until while uniform varying sampler2D sampler3D vec2 vec3 vec4 float in inout void mat2 mat3 mat4 bool int #define #ifdef #elif #else #endif").split(" ");
		
	}
	
}

PolycodeSyntaxHighlighter::~PolycodeSyntaxHighlighter() {

}

bool PolycodeSyntaxHighlighter::contains(String part, std::vector<String> *list) {
	for(int i=0; i < list->size(); i++) {
		if((*list)[i] == part)
			return true;
	}
	return false;
}

bool PolycodeSyntaxHighlighter::contains_char(char part, std::vector<char> *list) {
	for(int i=0; i < list->size(); i++) {
		if((*list)[i] == part)
			return true;
	}
	return false;
}

std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseText(String text, SyntaxHighlightToken overrideToken) {
	if(mode == MODE_LUA) {	
		return parseLua(text, overrideToken);
	} else {
		return parseGLSL(text, overrideToken);	
	}
}

	
std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseGLSL(String text, SyntaxHighlightToken overrideToken) {
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
	
	if(text.find_first_of("*/") != -1) {
		if(overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_LINE || overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START ) {
		mode = MODE_COMMENT;
		}
	}
	
	
	String line = "";
	
	char lastSeparator = ' ';

	
	for(int i=0; i < text.length(); i++) {
		char ch = text[i];				
		if(contains_char(ch, &separators)) {			

			unsigned int type = mode;
			unsigned int ch_type = mode;

	
			if(ch == '\"' && mode != MODE_COMMENT)
				ch_type = MODE_STRING;
	
			if(mode != MODE_STRING && ch == '('  && mode != MODE_COMMENT) {
				type = MODE_METHOD;
			}

			if(mode != MODE_STRING  && mode != MODE_COMMENT) {
				if(contains(line, &keywords)) {
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
			tokens.push_back(SyntaxHighlightToken(ch, ch_type));

			if(ch == '/' && lastSeparator == '/' && mode != MODE_STRING) {
				isComment = true;
				tokens[tokens.size()-1].type = MODE_COMMENT;
				tokens[tokens.size()-2].type = MODE_COMMENT;				
			}

			if(ch == '*' && lastSeparator == '/' && mode != MODE_STRING) {
				tokens[tokens.size()-1].type = MODE_COMMENT;
				tokens[tokens.size()-2].type = MODE_COMMENT;				
				mode = MODE_COMMENT;
				tokens[tokens.size()-1].overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START;						
			}
			
			if(ch == '/' && lastSeparator == '*' && mode == MODE_COMMENT) {
				if(mode == MODE_COMMENT) 	
					mode = MODE_GENERAL;
				if(mode != MODE_STRING)
					tokens[tokens.size()-1].overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END;
				
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
			line.append(ch);
		}
	}
	
	for(int i=0; i < tokens.size(); i++) {
		switch(tokens[i].type) {
			case MODE_STRING:
				tokens[i].color = globalSyntaxTheme->colors[4];			
			break;
			case MODE_COMMENT:
				tokens[i].color = globalSyntaxTheme->colors[1];			
			break;			
			case MODE_METHOD:
				tokens[i].color = globalSyntaxTheme->colors[3];			
			break;			
			case MODE_KEYWORD:
				tokens[i].color = globalSyntaxTheme->colors[2];
			break;		
			case MODE_NUMBER:
				tokens[i].color = globalSyntaxTheme->colors[6];
			break;		
			case MODE_MEMBER:
				tokens[i].color = globalSyntaxTheme->colors[5];
			break;															
			default:
				tokens[i].color = globalSyntaxTheme->colors[0];
			break;
		}
	}
	
	return tokens;
}
	
std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseLua(String text, SyntaxHighlightToken overrideToken) {
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
	
	if(text.find_first_of("]]") != -1) {
		if(overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_LINE || overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START ) {
		mode = MODE_COMMENT;
		}
	}
				
	String line = "";
	
	char lastSeparator = ' ';

	for(int i=0; i < text.length(); i++) {
		char ch = text[i];				
		if(contains_char(ch, &separators)) {			

			unsigned int type = mode;
			unsigned int ch_type = mode;
	
			if(ch == '\"' && mode != MODE_COMMENT)
				ch_type = MODE_STRING;
	
			if(mode != MODE_STRING && ch == '('  && mode != MODE_COMMENT) {
				type = MODE_METHOD;
			}

			if(mode != MODE_STRING  && mode != MODE_COMMENT) {
				if(contains(line, &keywords)) {
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
			tokens.push_back(SyntaxHighlightToken(ch, ch_type));

			if(ch == '-' && lastSeparator == '-' && text[i-1] == lastSeparator && mode != MODE_STRING) {
				isComment = true;
				tokens[tokens.size()-1].type = MODE_COMMENT;
				tokens[tokens.size()-2].type = MODE_COMMENT;				
			}

			if(ch == '[' && lastSeparator == '[' && isComment && mode != MODE_STRING) {
				unsigned int old_mode = mode;
				mode = MODE_COMMENT;
				tokens[tokens.size()-1].overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START;
				
				// ugly hack for ---[[, which is not a block comment
				if(tokens.size() > 4) {
					if(tokens[tokens.size()-5].text == "-") {
						mode = old_mode;
						tokens[tokens.size()-1].overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;						
					}
				}
			}
			
			if(ch == ']' && lastSeparator == ']') {
				if(mode == MODE_COMMENT) 
					mode = MODE_GENERAL;
				if(mode != MODE_STRING)
					tokens[tokens.size()-1].overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END;
			}
			
			if(ch == '\n' ) {
				isComment = false;
				mode = MODE_GENERAL;
			}
				

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
			line.append(ch);
		}
	}
	
	for(int i=0; i < tokens.size(); i++) {
		switch(tokens[i].type) {
			case MODE_STRING:
				tokens[i].color = globalSyntaxTheme->colors[4];			
			break;
			case MODE_COMMENT:
				tokens[i].color = globalSyntaxTheme->colors[1];
			break;			
			case MODE_METHOD:
				tokens[i].color = globalSyntaxTheme->colors[3];			
			break;			
			case MODE_KEYWORD:
				tokens[i].color = globalSyntaxTheme->colors[2];
			break;		
			case MODE_NUMBER:
				tokens[i].color = globalSyntaxTheme->colors[6];
			break;		
			case MODE_MEMBER:
				tokens[i].color = globalSyntaxTheme->colors[5];
			break;															
			default:
				tokens[i].color = globalSyntaxTheme->colors[0];
			break;
		}
	}
	
	return tokens;
}

PolycodeTextEditor::PolycodeTextEditor() : PolycodeEditor(true){
	firstTimeResize = true;
	editorType = "PolycodeTextEditor";
}

PolycodeTextEditor::~PolycodeTextEditor() {
    textInput->setOwnsChildrenRecursive(true);
	delete textInput;
    findBar->setOwnsChildrenRecursive(true);
	delete findBar;
	if(syntaxHighligher)
		delete syntaxHighligher;
}

bool PolycodeTextEditor::openFile(OSFileEntry filePath) {
	
	
	isLoading = true;
	
	textInput = new UITextInput(true, 100, 100);
	addChild(textInput);
	textInput->setBackgroundColor(globalSyntaxTheme->bgColor);
	textInput->setCursorColor(globalSyntaxTheme->cursorColor);
	textInput->setSelectionColor(globalSyntaxTheme->selectionColor);
	textInput->useStrongHinting = globalSyntaxTheme->useStrongHinting;
	textInput->setLineNumberColor(globalSyntaxTheme->lineNumberColor);
	textInput->enableLineNumbers(true);
	
	textInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	findBar = new FindBar();
	findBar->visible = false;
	addChild(findBar);
	
	findBar->findInput->addEventListener(this, Event::COMPLETE_EVENT);
	findBar->findInput->addEventListener(this, Event::CANCEL_EVENT);
	findBar->replaceInput->addEventListener(this, Event::CANCEL_EVENT);
	findBar->replaceInput->addEventListener(this, Event::COMPLETE_EVENT);
			
	findBar->closeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	findBar->replaceAllButton->addEventListener(this, UIEvent::CLICK_EVENT);
	findBar->functionList->addEventListener(this, UIEvent::CHANGE_EVENT);
			
	syntaxHighligher = NULL;
	
	if(filePath.extension == "lua" || filePath.extension == "vert" || filePath.extension == "frag") {
		syntaxHighligher = new PolycodeSyntaxHighlighter(filePath.extension);
		textInput->setSyntaxHighlighter(syntaxHighligher);
	} else {
		textInput->setTextColor(globalSyntaxTheme->colors[0]);		
	}
	
	Data *data = new Data();
	if(data->loadFromFile(filePath.fullPath)) {
		textInput->setText(data->getAsString(String::ENCODING_UTF8).replace("\r\n", "\n"));
	}
	delete data;
	
	PolycodeEditor::openFile(filePath);
	
	isLoading = false;	
	return true;
}

ObjectEntry *PolycodeTextEditor::getEditorConfig() {
	ObjectEntry *configEntry = new ObjectEntry();
		
	configEntry->addChild("scroll_offset", textInput->getScrollContainer()->getVScrollBar()->getScrollValue());
			
	return configEntry;
}

void PolycodeTextEditor::applyEditorConfig(ObjectEntry *configEntry) {
	ObjectEntry *scrollEntry = (*configEntry)["scroll_offset"];
	if(scrollEntry) {
		textInput->getScrollContainer()->setScrollValue(0.0, scrollEntry->NumberVal);
	}
}

void PolycodeTextEditor::handleEvent(Event *event) {

	if(event->getDispatcher() == textInput && event->getEventType() == "UIEvent") {
		if(!isLoading) {
			lastFindString = "";
			setHasChanges(true);
		}
	}

	if(event->getDispatcher() == findBar->functionList) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {
			FindMatch *match = (FindMatch*)findBar->functionList->getSelectedItem()->data;
			textInput->showLine(match->lineNumber, true);
		}		
	}

	if(event->getDispatcher() == findBar->replaceAllButton) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			textInput->replaceAll(findBar->findInput->getText(), findBar->replaceInput->getText());
		}
	}


	if(event->getDispatcher() == findBar->closeButton) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			hideFindBar();
		}
	}

	if(event->getDispatcher() == findBar->replaceInput) {
		if(event->getEventType() == "") {
		
			if(event->getEventCode() == Event::CANCEL_EVENT) {
				hideFindBar();
			}
					
			if(event->getEventCode() == Event::COMPLETE_EVENT) {
				textInput->findString(findBar->findInput->getText(), true, findBar->replaceInput->getText());
			}
			
		}
	}	
	
	
	if(event->getDispatcher() == findBar->findInput) {
		if(event->getEventType() == "") {
		
			if(event->getEventCode() == Event::CANCEL_EVENT) {
				hideFindBar();
			}
					
			if(event->getEventCode() == Event::COMPLETE_EVENT) {
				if(findBar->findInput->getText() != "") {
				if(findBar->findInput->getText() != lastFindString) {
					lastFindString = findBar->findInput->getText();
					textInput->findString(lastFindString);
				} else {
					textInput->findNext();
				}
				}
			}
			
		}
	}	
	PolycodeEditor::handleEvent(event);
}

void PolycodeTextEditor::showFindBar() {
	findBar->visible = true;
	findBar->focusChild(findBar->findInput);
	findBar->findInput->selectAll();
	lastFindString = "";
	
	for(int i=0; i < findBar->functionList->getNumItems(); i++) {
		FindMatch *match = (FindMatch*)findBar->functionList->getItemAtIndex(i)->data;
		findBar->functionList->getItemAtIndex(i)->data = NULL;
		delete match;
	}
	
	findBar->functionList->clearItems();
	
	std::vector<FindMatch> functionMatches = textInput->getFindMatches("function ");
	for(int i=0; i < functionMatches.size(); i++) {
		FindMatch *match = new FindMatch();
		(*match) = functionMatches[i];
        String lineText = textInput->getLineText(functionMatches[i].lineNumber);
        if (lineText.substr(0,8) == "function") {
            findBar->functionList->addComboItem(lineText.replace("function ", ""), (void*) match);
        }
	}
	
	Resize(editorSize.x, editorSize.y);
}

void PolycodeTextEditor::hideFindBar() {
	findBar->visible = false;
	focusChild(textInput);
	Resize(editorSize.x, editorSize.y);
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
	setHasChanges(false);
}

void PolycodeTextEditor::Resize(int x, int y) {

	findBar->setBarWidth(x);	
	
	if(findBar->visible) {
		textInput->Resize(x,y-findBar->getHeight());
		textInput->setPosition(0,findBar->getHeight());
	} else {
		textInput->Resize(x,y);
		textInput->setPosition(0,0);
	}
	if(firstTimeResize) {
		textInput->doMultilineResize();
		firstTimeResize = false;
	}
	PolycodeEditor::Resize(x,y);
}

FindBar::FindBar() : UIElement() {
	barBg = new UIRect(30,30);
	barBg->setAnchorPoint(-1.0, -1.0, 0.0);
	barBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	addChild(barBg);
	setHeight(30);
	
	UILabel *findLabel = new UILabel("FIND", 18, "section");
	addChild(findLabel);
	findLabel->setColor(1.0, 1.0, 1.0, 0.6);
	findLabel->setPosition(10,3);

	UILabel *replaceLabel = new UILabel("REPLACE", 18, "section");
	addChild(replaceLabel);
	replaceLabel->setColor(1.0, 1.0, 1.0, 0.6);
	replaceLabel->setPosition(200,3);
	
	processInputEvents = true;
	
	findInput = new UITextInput(false, 120, 12);
	addFocusChild(findInput);
	findInput->setPosition(60, 4);

	replaceInput = new UITextInput(false, 120, 12);
	addFocusChild(replaceInput);
	replaceInput->setPosition(280, 4);
	
	replaceAllButton = new UIButton("Replace All", 100);
	addFocusChild(replaceAllButton);
	replaceAllButton->setPosition(420, 3);

	UIImage *functionIcon = new UIImage("main/function_icon.png", 11, 17);
	addChild(functionIcon);
	functionIcon->setPosition(540, 6);
	
	functionList = new UIComboBox(globalMenu, 200);
	addChild(functionList);
	functionList->setPosition(560, 4);	
		
	closeButton = new UIImageButton("main/barClose.png", 1.0, 17, 17);
	addChild(closeButton);
}

void FindBar::onKeyDown(PolyKEY key, wchar_t charCode) {
	if(key == KEY_TAB) {
		focusNextChild();
	}
	
	if(key == KEY_ESCAPE) {
	
	}	
}

FindBar::~FindBar(){

}

void FindBar::setBarWidth(int width) {
	barBg->Resize(width, 30);
	closeButton->setPosition(width - 30, 6);
	functionList->Resize(width-560-40, functionList->getHeight());
}
