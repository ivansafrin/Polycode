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

std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseText(String text) {
	if(mode == MODE_LUA) {	
		return parseLua(text);
	} else {
		return parseGLSL(text);	
	}
}


std::vector<SyntaxHighlightToken> PolycodeSyntaxHighlighter::parseGLSL(String text) {
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
		if(contains_char(ch, &separators)) {

			unsigned int type = mode;
			unsigned int ch_type = mode;


			if(ch == '\"' && mode != MODE_COMMENT)
				ch_type = MODE_STRING;

			if(mode != MODE_STRING && ch == '('  && mode != MODE_COMMENT) {
				type = MODE_METHOD;
			}

			if(mode != MODE_STRING  && mode != MODE_COMMENT && contains(line, &keywords)) {
				type = MODE_KEYWORD;
			}

			if(mode != MODE_STRING && !isComment && mode != MODE_COMMENT) {

				if(line.isNumber()) {
					type = MODE_NUMBER;
				} else if(lastSeparator == '.' && ch != '.' && ch != ':') {
					type = MODE_MEMBER;
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
				unsigned int old_mode = mode;
				tokens[tokens.size()-1].type = MODE_COMMENT;
				tokens[tokens.size()-2].type = MODE_COMMENT;
				mode = MODE_COMMENT;
			}

			if(ch == '/' && lastSeparator == '*' && mode == MODE_COMMENT) {
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
		if(contains_char(ch, &separators)) {

			unsigned int type = mode;
			unsigned int ch_type = mode;


			if(ch == '\"' && mode != MODE_COMMENT)
				ch_type = MODE_STRING;

			if(mode != MODE_STRING && ch == '('  && mode != MODE_COMMENT) {
				type = MODE_METHOD;
			}

			if(mode != MODE_STRING  && mode != MODE_COMMENT && contains(line, &keywords)) {
				type = MODE_KEYWORD;
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

			if(ch == '-' && lastSeparator == '-' && mode != MODE_STRING) {
				isComment = true;
				tokens[tokens.size()-1].type = MODE_COMMENT;
				tokens[tokens.size()-2].type = MODE_COMMENT;
			}

			if(ch == '[' && lastSeparator == '[' && isComment && mode != MODE_STRING) {
				unsigned int old_mode = mode;
				mode = MODE_COMMENT;

				// ugly hack for ---[[, which is not a block comment
				if(tokens.size() > 4 && tokens[tokens.size()-5].text == "-") {
					mode = old_mode;
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
	editorType = "PolycodeTextEditor";
}

PolycodeTextEditor::~PolycodeTextEditor() {
	delete textInput;
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

void PolycodeTextEditor::handleEvent(Event *event) {

	if(event->getDispatcher() == textInput && event->getEventType() == "UIEvent" && !isLoading) {
		setHasChanges(true);
	}

	if(event->getDispatcher() == findBar->replaceAllButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		textInput->replaceAll(findBar->findInput->getText(), findBar->replaceInput->getText());
	}


	if(event->getDispatcher() == findBar->closeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			hideFindBar();
	}

	if(event->getDispatcher() == findBar->replaceInput && event->getEventType() == "") {
		if(event->getEventCode() == Event::CANCEL_EVENT) {
			hideFindBar();
		}

		if(event->getEventCode() == Event::COMPLETE_EVENT) {
			textInput->findString(findBar->findInput->getText(), true, findBar->replaceInput->getText());
		}

	}


	if(event->getDispatcher() == findBar->findInput && event->getEventType() == "") {
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
	PolycodeEditor::handleEvent(event);
}

void PolycodeTextEditor::showFindBar() {
	findBar->visible = true;
	findBar->focusChild(findBar->findInput);
	findBar->findInput->selectAll();
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
	PolycodeEditor::Resize(x,y);
}

FindBar::FindBar() : UIElement() {
	barBg = new ScreenShape(ScreenShape::SHAPE_RECT, 30,30);
	barBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	barBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	addChild(barBg);
	this->height = 30;

	ScreenLabel *findLabel = new ScreenLabel("FIND", 18, "section");
	addChild(findLabel);
	findLabel->setColor(1.0, 1.0, 1.0, 0.6);
	findLabel->setPosition(10,3);

	ScreenLabel *replaceLabel = new ScreenLabel("REPLACE", 18, "section");
	addChild(replaceLabel);
	replaceLabel->setColor(1.0, 1.0, 1.0, 0.6);
	replaceLabel->setPosition(200,3);

	processInputEvents = true;

	findInput = new UITextInput(false, 120, 12);
	addChild(findInput);
	findInput->setPosition(60, 4);

	replaceInput = new UITextInput(false, 120, 12);
	addChild(replaceInput);
	replaceInput->setPosition(280, 4);

	replaceAllButton = new UIButton("Replace All", 100);
	addChild(replaceAllButton);
	replaceAllButton->setPosition(420, 3);

	closeButton = new UIImageButton("Images/barClose.png");
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
	delete findInput;
	delete replaceInput;
	delete closeButton;
	delete replaceAllButton;
	delete barBg;
}

void FindBar::setBarWidth(int width) {
	barBg->setShapeSize(width, 30);
	closeButton->setPosition(width - 30, 5);
}
