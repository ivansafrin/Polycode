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


#include "PolyUITextInput.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"
#include "PolyEventHandler.h"

using namespace Polycode;

UITextInput::UITextInput(bool multiLine, Number width, Number height) : ScreenEntity() {
	this->multiLine = multiLine;
	
	isNumberOnly = false;
	
	draggingSelection = false;
	hasSelection = false;
	doSelectToCaret = false;
	
	caretPosition = 0;
	caretImagePosition = 0;
	
	currentLine = NULL;
	
	
	lineOffset = -1;
	numLines = 0;
	
	this->positionMode = ScreenEntity::POSITION_TOPLEFT;
	Config *conf = CoreServices::getInstance()->getConfig();	
	
	if(multiLine)
		fontName = conf->getStringValue("Polycode", "uiTextInputFontNameMultiLine");
	else
		fontName = conf->getStringValue("Polycode", "uiTextInputFontName");
	
	if(multiLine)
		fontSize = conf->getNumericValue("Polycode", "uiTextInputFontSizeMultiline");	
	else
		fontSize = conf->getNumericValue("Polycode", "uiTextInputFontSize");
	
	Number rectHeight = height;
	if(!multiLine) {
		rectHeight = fontSize+12;
	} 
	
	lineSpacing = conf->getNumericValue("Polycode", "textEditLineSpacing");
	
	Number st = conf->getNumericValue("Polycode", "textBgSkinT");
	Number sr = conf->getNumericValue("Polycode", "textBgSkinR");
	Number sb = conf->getNumericValue("Polycode", "textBgSkinB");
	Number sl = conf->getNumericValue("Polycode", "textBgSkinL");
	
	padding = conf->getNumericValue("Polycode", "textBgSkinPadding");	
	
	inputRect = new UIBox(conf->getStringValue("Polycode", "textBgSkin"),
						  st,sr,sb,sl,
						  width+(padding*2), height+(padding*2));	
	
	addChild(inputRect);
	
	
	
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);	
	inputRect->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);		
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);		
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	inputRect->processInputEvents = true;
	
	selectorRectTop = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectTop->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	selectorRectTop->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectTop->visible = false;
	addChild(selectorRectTop);

	selectorRectMiddle = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectMiddle->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	selectorRectMiddle->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectMiddle->visible = false;
	addChild(selectorRectMiddle);

	selectorRectBottom = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectBottom->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	selectorRectBottom->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectBottom->visible = false;
	addChild(selectorRectBottom);
		
	insertLine(true);	
	
	blinkerRect = new ScreenShape(ScreenShape::SHAPE_RECT, 1, fontSize+4,0,0);
	blinkerRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	blinkerRect->setColor(0,0,0,1);
	addChild(blinkerRect);
	blinkerRect->visible = false;
	blinkerRect->setPosition(0,3);
	
	blinkTimer = new Timer(true, 500);
	blinkTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	focusable = true;
	this->width = width;
	this->height = rectHeight;
	setHitbox(width, rectHeight);
	
	updateCaretPosition();
}

void UITextInput::setNumberOnly(bool val) {
	isNumberOnly = val;
}

void UITextInput::clearSelection() {
	hasSelection = false;
	selectorRectTop->visible = false;	
	selectorRectMiddle->visible = false;	
	selectorRectBottom->visible = false;		
}


void UITextInput::setSelection(int lineStart, int lineEnd, int colStart, int colEnd) {

	if(lineStart == lineOffset) {
		selectionLine = lineEnd;
	} else {
		selectionLine = lineStart;	
	}

	if(colStart == caretPosition) {
		selectionCaretPosition = colEnd;
	} else {
		selectionCaretPosition = colStart;
	}

	
//	Logger::log("SET lineStart:%d lineEnd:%d colStart:%d colEnd:%d\n", lineStart, lineEnd, colStart, colEnd);
	
	if(lineStart > lineEnd) {
		int tmp = lineStart;
		lineStart = lineEnd;
		lineEnd = tmp;
		
		tmp = colStart;
		colStart = colEnd;
		colEnd = tmp;		
	}	
	
	if(colStart > colEnd && lineStart == lineEnd) {
		int tmp = colStart;
		colStart = colEnd;
		colEnd = tmp;
	}
	
	clearSelection();
	
	if(lineStart > lines.size()-1)
		return;	
	
	ScreenLabel *topLine = lines[lineStart];	
	
	if(colStart+1 > topLine->getText().length())
		return;
	
	Number fColEnd  = colEnd;
	
	if(colEnd > topLine->getText().length() || lineStart != lineEnd)
		fColEnd = topLine->getText().length();

	Number topSize, topHeight, topX;
	
	selectorRectTop->visible = true;	
	topSize = topLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), topLine->getText().substr(colStart,fColEnd-colStart), fontSize) - 4; 
	topHeight = lineHeight+lineSpacing;
	if(colStart > 0) {
		topX = topLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), topLine->getText().substr(0,colStart-1), fontSize); ;
	} else {
		topX = 0;
	}

	selectorRectTop->setScale(topSize, topHeight);
	selectorRectTop->setPosition(topX + padding + (topSize/2.0)+ 1, padding + (lineStart * (lineHeight+lineSpacing)) + (topHeight/2.0));
	
	if(lineEnd > lineStart && lineEnd < lines.size()) {
		ScreenLabel *bottomLine = lines[lineEnd];	
		selectorRectBottom->visible = true;		
		Number bottomSize = bottomLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), bottomLine->getText().substr(0,colEnd), fontSize) - 4; 
		Number bottomHeight = lineHeight+lineSpacing;
		selectorRectBottom->setScale(bottomSize, bottomHeight);
		selectorRectBottom->setPosition(padding + (bottomSize/2.0) + 1, padding + (lineEnd * (lineHeight+lineSpacing)) + (bottomHeight/2.0));
		
		if(lineEnd != lineStart+1) {
			// need filler
			selectorRectMiddle->visible = true;		
			Number midSize = this->width-padding;
			Number midHeight = 0;			
			for(int i=lineStart+1; i < lineEnd;i++) {
				midHeight += lineHeight+lineSpacing;
			}
			selectorRectMiddle->setScale(midSize, midHeight);
			selectorRectMiddle->setPosition(padding + (midSize/2.0), padding + ((lineStart+1) * (lineHeight+lineSpacing)) + (midHeight/2.0));										
			
		}
		
	}
	hasSelection = true;
	
	selectionTop = lineStart;
	selectionBottom = lineEnd;
	selectionL = colStart;
	selectionR = colEnd;	 		
}

void UITextInput::deleteSelection() {
	if(selectionTop == selectionBottom) {
		String ctext = lines[selectionTop]->getText();
		String newText = ctext.substr(0, selectionL);
		int rside = selectionR;
		if(rside > ctext.length()-1)
			rside = ctext.length() - 1;
		newText += ctext.substr(rside,ctext.length() - selectionR); 
		lines[selectionTop]->setText(newText);
	} else {
		
		String ctext = lines[selectionTop]->getText();
		String newText = ctext.substr(0, selectionL);
		lines[selectionTop]->setText(newText);

		ScreenLabel *bottomLine = lines[selectionBottom];
		
		// if whole lines to remove, do it
		vector<ScreenLabel*> linesToRemove;
		if(selectionBottom > selectionTop + 1) {
			for(int i=selectionTop+1; i < selectionBottom; i++) {
				linesToRemove.push_back(lines[i]);
			}
			for(int i=0; i < linesToRemove.size(); i++) {
				removeLine(linesToRemove[i]);
			}
		}
		
		ctext = bottomLine->getText();
		
		int rside = selectionR;
		if(rside > ctext.length()-1)
			rside = ctext.length() - 1;
		newText = ctext.substr(rside,ctext.length() - selectionR); 
		
				
		lineOffset = selectionTop;
		selectLineFromOffset();
		caretPosition = currentLine->getText().length();
		updateCaretPosition();
		currentLine->setText(currentLine->getText() + newText);	
		removeLine(bottomLine);				
		
		
	}
	clearSelection();
	caretPosition = selectionL;
	updateCaretPosition();
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
}

void UITextInput::Resize(int x, int y) {
	inputRect->resizeBox(x, y);
}

int UITextInput::insertLine(bool after) {
	
	numLines++;	
	
	ScreenLabel *newLine = new ScreenLabel(L"", fontSize, fontName, Label::ANTIALIAS_FULL);
	newLine->setColor(0,0,0,1);
	lineHeight = newLine->getHeight();
	addChild(newLine);
	
	if(after) {	
		
		if(currentLine) {
			String ctext = currentLine->getText();
			String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
			ctext = ctext.substr(0,caretPosition);
			currentLine->setText(ctext);
			newLine->setText(text2);
			caretPosition=0;
		}
		
		currentLine = newLine;		
		
		vector<ScreenLabel*>::iterator it;
		it = lines.begin();
		
		for(int i=0; i < lineOffset+1; i++) {
			it++;
		}
		
		lineOffset = lineOffset + 1;	
		lines.insert(it,newLine);
		
		restructLines();
	} else {	
		// do we even need that? I don't think so.
	}	
	
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
	return 1;	
}

void UITextInput::restructLines() {
	for(int i=0; i < lines.size(); i++) {
		lines[i]->setPosition(padding,padding + (i*(lineHeight+lineSpacing)) ,0.0f);		
	}
}

void UITextInput::setText(String text) {
	if(!multiLine) {
		currentLine->setText(text);
		caretPosition = text.length();
		clearSelection();				
		updateCaretPosition();		
	} else {
	}
		
//	this->text = text;
//	currentLine->setText(text);	
}

void UITextInput::onLoseFocus() {
	blinkerRect->visible  = false;
}

String UITextInput::getText() {
	
	if(!multiLine) {
		return currentLine->getText();
	} else {
		String totalText = L"";
		for(int i=0; i < lines.size(); i++) {
				totalText += lines[i]->getText();					
				totalText += L"\n";
		}	
		return totalText;
	}
}

void UITextInput::updateCaretPosition() {
	caretImagePosition = padding;
	if(caretPosition == 0) {
		caretImagePosition = padding;
	} else if(caretPosition > currentLine->getText().length()) {
		caretPosition = currentLine->getText().length();
		String caretSubString = currentLine->getText().substr(0,caretPosition);
		caretImagePosition = currentLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), caretSubString, fontSize);		
		caretImagePosition = caretImagePosition - 4.0f + padding;		
	} else {
		String caretSubString = currentLine->getText().substr(0,caretPosition);
		caretImagePosition = currentLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), caretSubString, fontSize);
		caretImagePosition = caretImagePosition - 4.0f + padding;		
	}
	blinkerRect->visible  = true;
	blinkTimer->Reset();
	
	if(doSelectToCaret) {
		doSelectToCaret = false;
		
	}
	
}

void UITextInput::selectLineFromOffset() {
	for(int i=0; i < lines.size(); i++) {
		if(i == lineOffset) {
			currentLine = lines[i];					
			return;
		}
	}
}

void UITextInput::dragSelectionTo(Number x, Number y) {
	x -= padding;
	y -= padding;
	int lineOffset = y  / (lineHeight+lineSpacing);
	if(lineOffset > lines.size()-1)
		lineOffset = lines.size()-1;

	ScreenLabel *selectToLine = lines[lineOffset];
	
	int len = selectToLine->getText().length();
	Number slen;
	int caretPosition = selectToLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), selectToLine->getText().substr(0,len), fontSize);
	for(int i=0; i < len; i++) {
		slen = selectToLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), selectToLine->getText().substr(0,i), fontSize);
		if(slen > x) {
			caretPosition = i;
			break;
		}
	}
	if(x > slen)
		caretPosition = len;
	
	if(caretPosition < 0)
		caretPosition = 0;

	setSelection(this->lineOffset, lineOffset, this->caretPosition, caretPosition);
}

int UITextInput::caretSkipWordBack(int caretLine, int caretPosition) {
	for(int i=caretPosition; i > 0; i--) {
		String bit = lines[caretLine]->getText().substr(i,1);
		char chr = ((char*)bit.c_str())[0]; 		
		if(((chr > 0 && chr < 48) || (chr > 57 && chr < 65) || (chr > 90 && chr < 97) || (chr > 122 && chr < 127)) && i < caretPosition-1) {
			return i+1;
		}
	}	
	return 0;
}

int UITextInput::caretSkipWordForward(int caretLine, int caretPosition) {
	int len = lines[caretLine]->getText().length();
	for(int i=caretPosition; i < len; i++) {
		String bit = lines[caretLine]->getText().substr(i,1);
		char chr = ((char*)bit.c_str())[0]; 
		if(((chr > 0 && chr < 48) || (chr > 57 && chr < 65) || (chr > 90 && chr < 97) || (chr > 122 && chr < 127)) && i > caretPosition) {
			return i;
		}
	}
	return lines[caretLine]->getText().length();	
}

void UITextInput::selectWordAtCaret() {
	
	int selectStart = 0;
	int len  = currentLine->getText().length();
	int selectEnd = len;
	
	for(int i=this->caretPosition; i > 0; i--) {
		String bit = currentLine->getText().substr(i,1);
		wchar_t chr = ((wchar_t*)bit.c_str())[0]; 
		if( (chr > 0 && chr < 48) || (chr > 57 && chr < 65) || (chr > 90 && chr < 97) || (chr > 122 && chr < 127)) {
			selectStart = i+1;
			break;
		}
	}	

	for(int i=this->caretPosition; i < len; i++) {
		String bit = currentLine->getText().substr(i,1);
		wchar_t chr = ((wchar_t*)bit.c_str())[0]; 
		if( (chr > 0 && chr < 48) || (chr > 57 && chr < 65) || (chr > 90 && chr < 97) || (chr > 122 && chr < 127)) {
			selectEnd = i;
			break;			
		}
	}	
	
	
	setSelection(this->lineOffset, this->lineOffset, selectStart, selectEnd);
}

void UITextInput::setCaretToMouse(Number x, Number y) {
	clearSelection();
	x -= padding;
	y -= padding;
	//if(lines.size() > 1) {
		lineOffset = y  / (lineHeight+lineSpacing);
		if(lineOffset > lines.size()-1)
			lineOffset = lines.size()-1;
		selectLineFromOffset();	
	//}
	
	int len = currentLine->getText().length();
	Number slen;
	for(int i=0; i < len; i++) {
		slen = currentLine->getLabel()->getTextWidth(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), currentLine->getText().substr(0,i), fontSize);
		if(slen > x) {
			caretPosition = i;
			break;
		}
	}
	if(x > slen)
		caretPosition = len;
	updateCaretPosition();	
}

void UITextInput::removeLine(ScreenLabel *line) {
	for(int i=0;i<lines.size();i++) {
		if(lines[i] == line) {
			lines.erase(lines.begin()+i);
		}
	}
	removeChild(line);
	delete line;
	restructLines();
}

void UITextInput::selectAll() {
	setSelection(0, lines.size()-1, 0, lines[lines.size()-1]->getText().length());
}

void UITextInput::insertText(String text) {
	vector<String> strings = text.split("\n");
	int numLines = lines.size();
	for(int i=0; i < strings.size(); i++) {
		if(i < numLines) {
			lines[i]->setText(strings[i]);
		} else {
			numLines++;		
			ScreenLabel *newLine = new ScreenLabel(L"", fontSize, fontName, Label::ANTIALIAS_FULL);
			newLine->setColor(0,0,0,1);
			addChild(newLine);			
			lines.push_back(newLine);
			newLine->setText(strings[i]);
		}
	}
	restructLines();	
}

String UITextInput::getSelectionText() {
	String totalText = L"";
	if(selectionTop == selectionBottom) {
		totalText = lines[selectionTop]->getText().substr(selectionL, selectionR-selectionL);	
		return totalText;
	} else {
		totalText += lines[selectionTop]->getText().substr(selectionL, lines[selectionTop]->getText().length()-selectionL);
		totalText += L"\n";		
	}
	
	if(selectionBottom > selectionTop+1) {
		for(int i=selectionTop+1; i <= selectionBottom; i++) {
			totalText += lines[i]->getText();			
			totalText += L"\n";
		}
	}
	
	totalText += lines[selectionBottom]->getText().substr(0, selectionL);
	
	return totalText;
}

void UITextInput::onKeyDown(PolyKEY key, wchar_t charCode) {
	
	if(!hasFocus)
		return;
	
	
//	Logger::log("UCHAR: %d\n", charCode);	
	
	CoreInput *input = CoreServices::getInstance()->getCore()->getInput();	

	if(key == KEY_a && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		selectAll();
		return;
	}

	if(key == KEY_c && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		CoreServices::getInstance()->getCore()->copyStringToClipboard(getSelectionText());
		return;
	}

	if(key == KEY_x && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		return;
	}

	if(key == KEY_v && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		insertText(CoreServices::getInstance()->getCore()->getClipboardString());
		return;
	}	
	
	
	if(key == KEY_LEFT) {
		if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				if(hasSelection) {
					setSelection(this->lineOffset, selectionLine, this->caretPosition, 0);					
				} else {
					setSelection(this->lineOffset, this->lineOffset, this->caretPosition, 0);
				}
			} else {
				caretPosition = 0;
				clearSelection();				
				updateCaretPosition();
			}
		} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				if(hasSelection) {
					setSelection(this->lineOffset, selectionLine, this->caretPosition, caretSkipWordBack(selectionLine, selectionCaretPosition));
				} else {
					setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretSkipWordBack(this->lineOffset, caretPosition));					
				}
			} else {				
				caretPosition = caretSkipWordBack(this->lineOffset,caretPosition);
				clearSelection();				
				updateCaretPosition();			
			}
		} else {
			if(caretPosition > 0) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						if(selectionCaretPosition > 0)
							setSelection(this->lineOffset, selectionLine, this->caretPosition, selectionCaretPosition-1);
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretPosition-1);					
					}					
				} else {									
					caretPosition--;
					clearSelection();					
					updateCaretPosition();
				}
			}
		}
		return;
	}
	
	if(key == KEY_RIGHT) {
		if(caretPosition < currentLine->getText().length()) {			
			if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, lines[selectionLine]->getText().length());					
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, currentLine->getText().length());
					}
				} else {
					caretPosition = currentLine->getText().length();
					clearSelection();
				}				
			} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, caretSkipWordForward(selectionLine, selectionCaretPosition));
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretSkipWordForward(this->lineOffset, caretPosition));					
					}
				} else {				
					caretPosition = caretSkipWordForward(this->lineOffset,caretPosition);
					clearSelection();					
				}				
			} else {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, selectionCaretPosition+1);
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretPosition+1);					
					}					
				} else {									
					caretPosition++;
					clearSelection();					
				}				
			}
			updateCaretPosition();			
		}
		return;
	}
	
	if(key == KEY_UP) {		
		if(multiLine) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {			
				if(hasSelection) {
					if(selectionLine > 0)
						setSelection(this->lineOffset, selectionLine-1, this->caretPosition, selectionCaretPosition);
				} else {
					if(this->lineOffset > 0)					
						setSelection(this->lineOffset, this->lineOffset-1, this->caretPosition, caretPosition);					
				}				
			} else {
				clearSelection();				
				if(lineOffset > 0) {
					lineOffset--;
					selectLineFromOffset();
					updateCaretPosition();							
				}
			}
		}
		blinkerRect->visible  = true;
		return;
	}
	
	if(key == KEY_DOWN) {
		if(multiLine) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {			
				if(hasSelection) {
					if(selectionLine < lines.size()-1)
						setSelection(this->lineOffset, selectionLine+1, this->caretPosition, selectionCaretPosition);
				} else {
					if(this->lineOffset < lines.size()-1)					
						setSelection(this->lineOffset, this->lineOffset+1, this->caretPosition, caretPosition);					
				}				
			} else {				
				clearSelection();
				if(lineOffset < lines.size()-1) {
					lineOffset++;
					selectLineFromOffset();
					updateCaretPosition();										
				}
			}
		}
		blinkerRect->visible  = true;		
		return;
	}
	
	
	if(key == KEY_RETURN) {
		if(hasSelection)
			deleteSelection();		
		if(multiLine) {
			insertLine(true);
			updateCaretPosition();
		}
		return;
	}	
	
	String ctext = currentLine->getText();
	
	
//	if(1) {
	if((charCode > 31 && charCode < 127) || charCode > 127) {	
		if(!isNumberOnly || (isNumberOnly && (charCode > 47 && charCode < 58))) {
			if(hasSelection)
				deleteSelection();
			ctext = currentLine->getText();		
			String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
			ctext = ctext.substr(0,caretPosition);
			ctext += charCode + text2;
			caretPosition++;
		}
	}
	
	if(key == KEY_TAB && multiLine) {
		if(hasSelection)
			deleteSelection();		
		ctext = currentLine->getText();				
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += (wchar_t)'\t' + text2;
		caretPosition++;		
	}
	
	if(key == KEY_BACKSPACE) {
		if(hasSelection) {
			deleteSelection();
			return;
		} else {
		ctext = currentLine->getText();					
		if(caretPosition > 0) {
			if(ctext.length() > 0) {
				String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
				ctext = ctext.substr(0,caretPosition-1);
				ctext += text2;
				caretPosition--;
			}
		} else {
			if(lineOffset > 0) {
				ScreenLabel *lineToRemove = currentLine;
				lineOffset--;
				selectLineFromOffset();
				caretPosition = currentLine->getText().length();
				updateCaretPosition();
				currentLine->setText(currentLine->getText() + ctext);	
				removeLine(lineToRemove);				
				return;
			}
		}
		}
	}
	
	currentLine->setText(ctext);	
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
	updateCaretPosition();
}

void UITextInput::Update() {
	if(hasSelection) {
		blinkerRect->visible = false;
	}
	blinkerRect->setPosition(caretImagePosition,currentLine->getPosition2D().y);
	if(hasFocus) {
//		inputRect->setStrokeColor(1.0f, 1.0f, 1.0f, 0.25f);	
	} else {
		blinkerRect->visible = false;		
//		inputRect->setStrokeColor(1.0f, 1.0f, 1.0f, 0.1f);
	}
	
}

UITextInput::~UITextInput() {

}
		
void UITextInput::handleEvent(Event *event) {
	if(event->getDispatcher() == inputRect) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(parentEntity) {
					((ScreenEntity*)parentEntity)->focusChild(this);
				} else {
					hasFocus = true;
				}
				setCaretToMouse(((InputEvent*)event)->mousePosition.x, ((InputEvent*)event)->mousePosition.y);
				draggingSelection = true;
			break;
			case InputEvent::EVENT_MOUSEUP:
				draggingSelection = false;
			break;
			case InputEvent::EVENT_DOUBLECLICK:
				selectWordAtCaret();
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				if(draggingSelection) {
					dragSelectionTo(((InputEvent*)event)->mousePosition.x, ((InputEvent*)event)->mousePosition.y);		
				}
			break;
			case InputEvent::EVENT_MOUSEOVER:
				CoreServices::getInstance()->getCore()->setCursor(CURSOR_TEXT);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				CoreServices::getInstance()->getCore()->setCursor(CURSOR_ARROW);
			break;				
		}
	}
	
	if(event->getDispatcher() == blinkTimer) {
		if(hasSelection || draggingSelection) {
				blinkerRect->visible  = false;
		} else {
			if(hasFocus)
				blinkerRect->visible  = !blinkerRect->visible;
			else
				blinkerRect->visible  = false;
		}
	}
	
}