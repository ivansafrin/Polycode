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

UITextInput::UITextInput(bool multiLine, Number width, Number height) : UIElement() {
	this->multiLine = multiLine;
	processInputEvents = true;
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
	
	linesContainer = new ScreenEntity();	
	linesContainer->processInputEvents = true;
	
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
	inputRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	
	selectorRectTop = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectTop->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	selectorRectTop->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectTop->visible = false;
	linesContainer->addChild(selectorRectTop);

	selectorRectMiddle = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectMiddle->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	selectorRectMiddle->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectMiddle->visible = false;
	linesContainer->addChild(selectorRectMiddle);

	selectorRectBottom = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectBottom->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	selectorRectBottom->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectBottom->visible = false;
	linesContainer->addChild(selectorRectBottom);
		
	
	blinkerRect = new ScreenShape(ScreenShape::SHAPE_RECT, 1, fontSize+4,0,0);
	blinkerRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	blinkerRect->setColor(0,0,0,1);
	linesContainer->addChild(blinkerRect);
	blinkerRect->visible = false;
	blinkerRect->setPosition(0,3);
	
	blinkTimer = new Timer(true, 500);
	blinkTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	focusable = true;
	this->width = width;
	this->height = rectHeight;
	setHitbox(width, rectHeight);
	
	updateCaretPosition();
		
	
	scrollContainer = NULL;
	
	if(multiLine) {
		scrollContainer = new UIScrollContainer(linesContainer, false, true, 200, 200);
		addChild(scrollContainer);
	} else {
		addChild(linesContainer);
	}
	
	undoStateIndex = 0;
	maxRedoIndex = 0;
	
	syntaxHighliter = NULL;
	
	insertLine(true);		
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
	
	//printf("SET lineStart:%d lineEnd:%d colStart:%d colEnd:%d\n", lineStart, lineEnd, colStart, colEnd);
	
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
	
	if(colStart+1 > topLine->getText().length()) {
		colStart = topLine->getText().length();
	}
		
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
		if(bottomSize < 0)
			bottomSize = this->width-padding;
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
	changedText();
}

void UITextInput::changedText() {

	if(syntaxHighliter) {
		std::vector<SyntaxHighlightToken> tokens = syntaxHighliter->parseText(getText());
		
		for(int i=0; i < lines.size(); i++) {
			lines[i]->getLabel()->clearColors();
		}
		
		int lineIndex = 0;
		int rangeStart = 0;
		int rangeEnd = 0;
				
		for(int i=0; i < tokens.size(); i++) {			
			if(tokens[i].text == "\n") {
				lineIndex++;
				rangeStart = 0;
				rangeEnd = 0;
			} else {
			
				if(lineIndex < lines.size()) {
					int textLength = tokens[i].text.length();
					if(tokens[i].text.length() > 1) {
						rangeEnd = rangeStart + textLength-1;
						lines[lineIndex]->getLabel()->setColorForRange(tokens[i].color, rangeStart, rangeEnd);	
						rangeStart = rangeStart + textLength; 
					} else {
						rangeEnd = rangeStart;
						lines[lineIndex]->getLabel()->setColorForRange(tokens[i].color, rangeStart, rangeEnd);	
						rangeStart++;
					}				
				}
			}
		}
		
		for(int i=0; i < lines.size(); i++) {
			lines[i]->setText(lines[i]->getText());
			lines[i]->setColor(1.0, 1.0, 1.0, 1.0);
		}
		
	}

	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
}

void UITextInput::setSyntaxHighlighter(UITextInputSyntaxHighlighter *syntaxHighliter) {
	this->syntaxHighliter = syntaxHighliter;
}

void UITextInput::Resize(Number width, Number height) {
	inputRect->resizeBox(width, height);
	this->width = width;
	this->height = height;	
	matrixDirty = true;	
	setHitbox(width,height);
	
	if(multiLine) {
		inputRect->setHitbox(width - scrollContainer->getVScrollWidth(), height);
	}

	if(scrollContainer) {
		scrollContainer->Resize(width, height);
	}
}

int UITextInput::insertLine(bool after) {
	
	numLines++;	
	
	ScreenLabel *newLine = new ScreenLabel(L"", fontSize, fontName, Label::ANTIALIAS_FULL);
	newLine->setColor(0,0,0,1);
	lineHeight = newLine->getHeight();
	linesContainer->addChild(newLine);
	
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
		
	changedText();
	return 1;	
}

void UITextInput::restructLines() {
	for(int i=0; i < lines.size(); i++) {
		lines[i]->setPosition(padding,padding + (i*(lineHeight+lineSpacing)) ,0.0f);		
	}
	
	if(scrollContainer) {
		scrollContainer->setContentSize(width,  (((lines.size()+1) * ((lineHeight+lineSpacing)))) - padding);
	}	
	
	if(multiLine) {
		inputRect->setHitbox(width - scrollContainer->getVScrollWidth(), height);
	}	
	
}

void UITextInput::setText(String text) {
	if(!multiLine) {
		currentLine->setText(text);
		caretPosition = text.length();
		clearSelection();				
		updateCaretPosition();		
	} else {
		selectAll();
		insertText(text);
		clearSelection();
	}
		
//	this->text = text;
//	currentLine->setText(text);	
}

void UITextInput::onLoseFocus() {
	blinkerRect->visible  = false;
	clearSelection();
}

String UITextInput::getText() {
	
	if(!multiLine) {
		return currentLine->getText();
	} else {
		String totalText = L"";
		for(int i=0; i < lines.size(); i++) {
				totalText += lines[i]->getText();					
				if(i < lines.size()-1)
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
	
	if(multiLine && currentLine) {	
	
	
		if(linesContainer->getPosition().y + currentLine->getPosition2D().y < 0.0) {
			scrollContainer->scrollVertical(-(lineHeight+lineSpacing+padding)/(scrollContainer->getContentSize().y));

		} else if(linesContainer->getPosition().y + currentLine->getPosition2D().y > scrollContainer->getHeight()) {
		scrollContainer->scrollVertical((lineHeight+lineSpacing+padding)/(scrollContainer->getContentSize().y));

		}
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
	linesContainer->removeChild(line);
	linesToDelete.push_back(line);
	restructLines();
}

void UITextInput::selectAll() {
	setSelection(0, lines.size()-1, 0, lines[lines.size()-1]->getText().length());
}

void UITextInput::insertText(String text) {	
	vector<String> strings = text.split("\n");

	if(hasSelection)
		deleteSelection();

	if(strings.size() > 1) {
		String ctext = currentLine->getText();		
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += strings[0];
		currentLine->setText(ctext);		
		caretPosition = ctext.length();
		
		for(int i=1; i < strings.size()-1; i++) {
			insertLine(true);
			ctext = strings[i];
			currentLine->setText(ctext);
			caretPosition = ctext.length();			
		}
		
		insertLine(true);
		ctext = strings[strings.size()-1] + text2;
		caretPosition = ctext.length();
		currentLine->setText(ctext);		
		
	} else {
		String ctext = currentLine->getText();		
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += text + text2;
		caretPosition += text.length();
		currentLine->setText(ctext);			
	}
	
	changedText();
	updateCaretPosition();		
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

UIScrollContainer *UITextInput::getScrollContainer() {
	return scrollContainer;
}

void UITextInput::saveUndoState() {
	UITextInputUndoState newState;
	newState.content = getText();
	newState.caretPosition = caretPosition;
	newState.lineOffset = lineOffset;
	newState.hasSelection = hasSelection;
	if(hasSelection) {
		newState.selectionLine = selectionLine;
		newState.selectionCaretPosition = selectionCaretPosition;
	}
	undoStates[undoStateIndex] = newState;
	
	// if we hit undo state capacity, shift the whole stack
	if(undoStateIndex == MAX_TEXTINPUT_UNDO_STATES-1) {
		for(int i=0; i < MAX_TEXTINPUT_UNDO_STATES-1; i++) {
			undoStates[i] = undoStates[i+1];
		}
	} else {
		undoStateIndex++;
	}
	
	maxRedoIndex = undoStateIndex;
}

void UITextInput::setUndoState(UITextInputUndoState state) {
	clearSelection();
	setText(state.content);
	currentLine = lines[state.lineOffset];
	caretPosition = state.caretPosition;
	lineOffset = state.lineOffset;
	updateCaretPosition();
	
	if(state.hasSelection) {
		setSelection(lineOffset, state.selectionLine, caretPosition, state.selectionCaretPosition);
	}
}

void UITextInput::Undo() {
	if(undoStateIndex > 0) {
		undoStateIndex--;
		setUndoState(undoStates[undoStateIndex]);
	}
}

void UITextInput::Redo() {
	if(undoStateIndex < MAX_TEXTINPUT_UNDO_STATES-1 && undoStateIndex < maxRedoIndex) {
		undoStateIndex++;
		setUndoState(undoStates[undoStateIndex]);
	}
}

void UITextInput::Cut() {
	saveUndoState();
	Copy();
	if(hasSelection) {
		deleteSelection();
	}	
}

void UITextInput::Copy() {
	CoreServices::getInstance()->getCore()->copyStringToClipboard(getSelectionText());	
}

void UITextInput::Paste() {
	saveUndoState();
	insertText(CoreServices::getInstance()->getCore()->getClipboardString());
}

void UITextInput::showLine(unsigned int lineNumber, bool top) {
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
		Copy();
		return;
	}

	if(key == KEY_x && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		Cut();
		return;
	}
	
	if(key == KEY_z  && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		Undo();
		return;
	}

	if(key == KEY_z  && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) && (input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT))) {
		Redo();
		return;
	}


	if(key == KEY_y  && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		Redo();
		return;
	}

	if(key == KEY_v && (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER))) {
		Paste();
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
	
	if(key == KEY_PAGEUP) {
		if(multiLine) {
			scrollContainer->scrollVertical(-(scrollContainer->getHeight())/(scrollContainer->getContentSize().y));
		
		}
		return;
	}

	if(key == KEY_PAGEDOWN) {
		if(multiLine) {
			scrollContainer->scrollVertical((scrollContainer->getHeight())/(scrollContainer->getContentSize().y));
		
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
		if(multiLine) {	
			saveUndoState();
			if(hasSelection) {
				deleteSelection();		
			}			
			insertLine(true);
			updateCaretPosition();
		} else {
			dispatchEvent(new Event(), Event::COMPLETE_EVENT);
		}
		return;
	}	
	
	String ctext = currentLine->getText();
	
	
//	if(1) {
	if((charCode > 31 && charCode < 127) || charCode > 127) {	
		if(!isNumberOnly || (isNumberOnly && (charCode > 47 && charCode < 58))) {
			saveUndoState();
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
		saveUndoState();
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
			saveUndoState();
			deleteSelection();
			return;
		} else {
		ctext = currentLine->getText();					
		if(caretPosition > 0) {
			saveUndoState();
			if(ctext.length() > 0) {
				String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
				ctext = ctext.substr(0,caretPosition-1);
				ctext += text2;
				caretPosition--;
			}
		} else {
			if(lineOffset > 0) {
				saveUndoState();			
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
	changedText();
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
	
	for(int i=0; i < linesToDelete.size(); i++) {
		delete linesToDelete[i];
	}
	linesToDelete.clear();
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
				setCaretToMouse(((InputEvent*)event)->mousePosition.x, ((InputEvent*)event)->mousePosition.y - linesContainer->getPosition().y);
				draggingSelection = true;
			break;
			case InputEvent::EVENT_MOUSEUP:
				draggingSelection = false;
			break;
			case InputEvent::EVENT_DOUBLECLICK:
				selectWordAtCaret();
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				CoreServices::getInstance()->getCore()->setCursor(CURSOR_TEXT);			
				if(draggingSelection) {
					dragSelectionTo(((InputEvent*)event)->mousePosition.x, ((InputEvent*)event)->mousePosition.y - linesContainer->getPosition().y);		
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