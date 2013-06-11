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

UITextInput::UITextInput(bool multiLine, Number width, Number height) : UIElement(width, height) {
	this->multiLine = multiLine;
	processInputEvents = true;
	isNumberOnly = false;
	
	decoratorOffset = 0;
	lineOffset = -1;
	
	useStrongHinting = false;
	
	draggingSelection = false;
	hasSelection = false;
	doSelectToCaret = false;
	
	lineNumbersEnabled = false;
	
	caretPosition = 0;
	caretImagePosition = 0;

	horizontalPixelScroll = 0;
	horizontalCharacterScroll = 0;
	
	settingText = false;	
	
	needFullRedraw = false;

	isTypingWord = false;
	
	numLines = 0;
	
	setPositionMode(POSITION_TOPLEFT);
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
	linesContainer->ownsChildren = true;
	lineSpacing = conf->getNumericValue("Polycode", "textEditLineSpacing");
	
	st = conf->getNumericValue("Polycode", "textBgSkinT");
	sr = conf->getNumericValue("Polycode", "textBgSkinR");
	sb = conf->getNumericValue("Polycode", "textBgSkinB");
	sl = conf->getNumericValue("Polycode", "textBgSkinL");

	
	padding = conf->getNumericValue("Polycode", "textBgSkinPadding");
	
	textContainer = new UIElement();
	textContainer->ownsChildren = true;
	textContainer->enableScissor = true;

	linesContainer->addChild(textContainer);
	if(multiLine) {
		inputRect = new UIBox(conf->getStringValue("Polycode", "textBgSkinMultiline"),
						  st,sr,sb,sl,
						  width+(padding*2), height+(padding*2));		
	} else {
		inputRect = new UIBox(conf->getStringValue("Polycode", "textBgSkin"),
						  st,sr,sb,sl,
						  width+(padding*2), height+(padding*2));	
	}
	
	addChild(inputRect);		
	
	if(multiLine) {
		lineNumberBg = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
		lineNumberBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
		lineNumberBg->setColor(0.0, 0.0, 0.0, 0.3);
		addChild(lineNumberBg);
		lineNumberBg->visible = false;
		
		lineNumberAnchor = new ScreenEntity();
		linesContainer->addChild(lineNumberAnchor);
	} else {
		lineNumberBg = NULL;
		lineNumberAnchor = NULL;
		decoratorOffset = sl/2.0;
	}

	textContainer->setWidth(fabs(this->getWidth() - textContainer->getPosition2D().x - padding));
	textContainer->setHeight(fabs(this->getHeight() - textContainer->getPosition2D().y));
	textContainer->setPosition(padding + decoratorOffset, padding);
	
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
	textContainer->addChild(selectorRectTop);

	selectorRectMiddle = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectMiddle->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	selectorRectMiddle->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectMiddle->visible = false;
	textContainer->addChild(selectorRectMiddle);

	selectorRectBottom = new ScreenShape(ScreenShape::SHAPE_RECT, 1,1);
	selectorRectBottom->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	selectorRectBottom->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectBottom->visible = false;
	textContainer->addChild(selectorRectBottom);
		
	
	blinkerRect = new ScreenShape(ScreenShape::SHAPE_RECT, 1, fontSize+2,0,0);
	blinkerRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	blinkerRect->setColor(0,0,0,1);
	textContainer->addChild(blinkerRect);
	blinkerRect->visible = false;
	blinkerRect->setPosition(-horizontalPixelScroll,3);
	
	blinkTimer = new Timer(true, 500);
	blinkTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	focusable = true;
	this->width = width;
	this->height = rectHeight;
	setHitbox(width, rectHeight);
	
	scrollContainer = NULL;
	if(multiLine) {
		scrollContainer = new UIScrollContainer(linesContainer, false, true, 200, 200);
		scrollContainer->addEventListener(this, Event::CHANGE_EVENT);
		addChild(scrollContainer);
	} else {
		addChild(linesContainer);
	}
		
	undoStateIndex = 0;
	maxRedoIndex = 0;
	
	syntaxHighliter = NULL;
	
	textColor = Color(0.0,0.0,0.0,1.0);

	currentBufferLines = 0;
	neededBufferLines = 1;
	checkBufferLines();

	insertLine(true);
	updateCaretPosition();
	
	core = CoreServices::getInstance()->getCore();
	core->addEventListener(this, Core::EVENT_COPY);
	core->addEventListener(this, Core::EVENT_PASTE);
	core->addEventListener(this, Core::EVENT_CUT);
	core->addEventListener(this, Core::EVENT_UNDO);
	core->addEventListener(this, Core::EVENT_REDO);
	core->addEventListener(this, Core::EVENT_SELECT_ALL);
	indentSpacing = 4;
	indentType = INDENT_TAB;
}

void UITextInput::checkBufferLines() {

	if(neededBufferLines < currentBufferLines) 
		return;
	
	int aaMode = Label::ANTIALIAS_FULL;
	if(useStrongHinting) {
		aaMode = Label::ANTIALIAS_STRONG;
	}

	for(int i=0; i < neededBufferLines - currentBufferLines; i++) {
		if(multiLine) {
			ScreenLabel *newNumberLine = new ScreenLabel(L"", fontSize, fontName, aaMode);
			newNumberLine->color = lineNumberColor;
			lineNumberAnchor->addChild(newNumberLine);
			numberLines.push_back(newNumberLine);		
			
			if(!lineNumbersEnabled) {
				newNumberLine->visible = false;
			}
		}
	
		ScreenLabel *newLine = new ScreenLabel(L"", fontSize, fontName, aaMode);
		newLine->color = textColor;
		lineHeight = newLine->getHeight();
		textContainer->addChild(newLine);
		bufferLines.push_back(newLine);
	}
	
	currentBufferLines = neededBufferLines;
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

	if(lineStart == lineEnd && colStart == colEnd) {
		clearSelection();
		return;
	}

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
	
//	printf("SET lineStart:%d lineEnd:%d colStart:%d colEnd:%d\n", lineStart, lineEnd, colStart, colEnd);
	
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

	String topLine = lines[lineStart];	
	
	if(colStart+1 > topLine.length()) {
		colStart = topLine.length();
	}
		
	Number fColEnd  = colEnd;
	
	if(colEnd > topLine.length() || lineStart != lineEnd)
		fColEnd = topLine.length();

	Number topSize, topHeight, topX;
	
	selectorRectTop->visible = true;	
	topSize = bufferLines[0]->getLabel()->getTextWidthForString(topLine.substr(colStart,fColEnd-colStart)) ; 
	topHeight = lineHeight+lineSpacing;
	if(colStart >= 0) {
		topX = bufferLines[0]->getLabel()->getTextWidthForString(topLine.substr(0,colStart)) + 2;
	} else {
		topX = 0;
	}

	selectorRectTop->setScale(topSize, topHeight);
	selectorRectTop->setPosition(topX + (topSize/2.0) - horizontalPixelScroll, lineStart * (lineHeight+lineSpacing) + (topHeight/2.0));
	
	if(lineEnd > lineStart && lineEnd < lines.size()) {
		String bottomLine = lines[lineEnd];
		selectorRectBottom->visible = true;		
		Number bottomSize = bufferLines[0]->getLabel()->getTextWidthForString(bottomLine.substr(0,colEnd)) ; 
		if(bottomSize < 0)
			bottomSize = this->width-padding;
		Number bottomHeight = lineHeight+lineSpacing;
		selectorRectBottom->setScale(bottomSize, bottomHeight);
		selectorRectBottom->setPosition(bottomSize/2.0 - horizontalPixelScroll, lineEnd * (lineHeight+lineSpacing) + (bottomHeight/2.0));
		
		if(lineEnd != lineStart+1) {
			// need filler
			selectorRectMiddle->visible = true;		
			Number midSize = this->width-padding;
			Number midHeight = 0;			
			for(int i=lineStart+1; i < lineEnd;i++) {
				midHeight += lineHeight+lineSpacing;
			}
			selectorRectMiddle->setScale(midSize, midHeight);
			selectorRectMiddle->setPosition(midSize/2.0 - horizontalPixelScroll, ((lineStart+1) * (lineHeight+lineSpacing)) + (midHeight/2.0));										
			
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
		String ctext = lines[selectionTop];
		String newText = ctext.substr(0, selectionL);
		int rside = selectionR;
		if(rside > ctext.length()-1)
			rside = ctext.length() - 1;
		newText += ctext.substr(rside,ctext.length() - selectionR); 
		lines[selectionTop] = newText;
	} else {
		
		String ctext = lines[selectionTop];
		String newText = ctext.substr(0, selectionL);
		lines[selectionTop] = newText;

		ctext = lines[selectionBottom];
		
		int rside = selectionR;
		if(rside > ctext.length()-1)
			rside = ctext.length() - 1;
		newText = ctext.substr(rside,ctext.length() - selectionR); 
		
		lineOffset = selectionTop;
		selectLineFromOffset();
		caretPosition = lines[lineOffset].length();
		updateCaretPosition();
		lines[lineOffset] =  lines[lineOffset] + newText;
		
		removeLines(selectionTop+1, selectionBottom+1);
		
			
	}
	clearSelection();
	caretPosition = selectionL;
	updateCaretPosition();
	changedText();
}

void UITextInput::applySyntaxFormatting() {

	if(syntaxHighliter && multiLine) {
	
		int startLine = (-linesContainer->getPosition().y) / (lineHeight+lineSpacing);				
		unsigned int endLine = startLine + ((int)((height / (lineHeight+lineSpacing)))) + 1;					
		
		if(startLine < 0)
			startLine = 0;
		
		if(endLine > lines.size())
			endLine = lines.size();
	
		if(needFullRedraw) {
			startLine = 0;
			endLine = lines.size();
		}
	
	
		String totalText = L"";
		for(int i=startLine; i < endLine; i++) {
			totalText += lines[i];
			if(i < lines.size()-1)
				totalText += L"\n";
		}		
		
	std::vector<SyntaxHighlightToken> tokens = syntaxHighliter->parseText(totalText);	
		
	// DO SYNTAX HIGHLIGHTING
	if(needFullRedraw) {
		lineColors.clear();
		for(int i=0; i < lines.size(); i++) {
			lineColors.push_back(LineColorInfo());
		}		
		needFullRedraw = false;
	} else {
		std::vector<LineColorInfo> newInfo;
		
		for(int i=0; i < lines.size(); i++) {
			if((i >= startLine && i < endLine) || i >= lineColors.size()) {
				newInfo.push_back(LineColorInfo());
			} else {
				newInfo.push_back(lineColors[i]);
			}
		}
		
		lineColors = newInfo;
	}
	
	int lineIndex = startLine;
	int rangeStart = 0;
	int rangeEnd = 0;
		
	for(int i=0; i < tokens.size(); i++) {	
		if(tokens[i].text == "\n") {
			lineIndex++;
			if(lineIndex >= endLine) {
				lineIndex = endLine-1;
			}
			rangeStart = 0;
			rangeEnd = 0;
		} else {			
			if(lineIndex < lines.size()) {
				int textLength = tokens[i].text.length();
				if(tokens[i].text.length() > 1) {
					rangeEnd = rangeStart + textLength-1;
					lineColors[lineIndex].colors.push_back(LineColorData(tokens[i].color, rangeStart, rangeEnd));
					rangeStart = rangeStart + textLength; 
				} else {
					rangeEnd = rangeStart;
					lineColors[lineIndex].colors.push_back(LineColorData(tokens[i].color, rangeStart, rangeEnd));	
					rangeStart++;
				}				
			}
		}
	}			
	
	}
	readjustBuffer();	
}

void UITextInput::changedText(bool sendChangeEvent) {
	if(settingText)
		return;
	applySyntaxFormatting();
	if(sendChangeEvent) {
		dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
	}
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
	
	textContainer->setWidth(fabs(this->getWidth() - textContainer->getPosition2D().x - padding));
	textContainer->setHeight(fabs(this->getHeight() - textContainer->getPosition2D().y));
	textContainer->setPosition(padding + decoratorOffset, padding);		
	
	if(multiLine) {
		inputRect->setHitbox(width - scrollContainer->getVScrollWidth(), height);
		
		neededBufferLines = (height / ( lineHeight+lineSpacing)) + 1;
		checkBufferLines();
		renumberLines();
		applySyntaxFormatting();
		
	}
	
	if(multiLine && lineNumbersEnabled) {
		lineNumberBg->setShapeSize(decoratorOffset, height);
	}

	if(scrollContainer) {
		scrollContainer->Resize(width, height);
	}
}

int UITextInput::insertLine(bool after) {
	
	numLines++;	
		
	if(after) {	
		String newText = "";
		if(lines.size() > 0) {
			String ctext = lines[lineOffset];
			String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
			ctext = ctext.substr(0,caretPosition);
			lines[lineOffset] = ctext;
			newText = text2;
			caretPosition=0;
		}		
		
		vector<String>::iterator it;
		lineOffset = lineOffset + 1;
		if(lineOffset >= lines.size()) {
			it = lines.end();
		} else {
			it = lines.begin() + lineOffset;
		}
		lines.insert(it,newText);
		
		renumberLines();
		restructLines();
	} else {	
		// do we even need that? I don't think so.
	}	
	
	changedText();
	return 1;	
}

void UITextInput::enableLineNumbers(bool val) {
	lineNumbersEnabled = val;
	lineNumberBg->visible = lineNumbersEnabled;
	restructLines();
}

void UITextInput::renumberLines() {
	if(!multiLine)
		return;
	
	int totalLineNumber = lines.size();
	if(currentBufferLines > lines.size()) {
		totalLineNumber = currentBufferLines;
	}
		
	decoratorOffset = 0;	
	if(multiLine) {
		if(lineNumbersEnabled) {
			decoratorOffset = 15;
			if(totalLineNumber > 9) {
				decoratorOffset = 25;
			}
			if(totalLineNumber > 99) {
				decoratorOffset = 35;
			}			
			if(totalLineNumber > 999) {
				decoratorOffset = 45;
			}						
			if(totalLineNumber > 9999) {
				decoratorOffset = 55;
			}									
		}
	}
	
	lineNumberAnchor->setPositionX(padding+decoratorOffset - 10);

	// Update the position and width of the text accordingly.
	textContainer->setPosition(decoratorOffset + padding, padding);
	textContainer->setWidth(fabs(this->getWidth() - textContainer->getPosition2D().x - padding));
	textContainer->setHeight(fabs(this->getHeight() - textContainer->getPosition2D().y - padding));
	textContainer->scissorBox.setRect(textContainer->getPosition2D().x, textContainer->getPosition2D().y, textContainer->getWidth(), textContainer->getHeight()+padding);
}

void UITextInput::restructLines() {

	for(int i=0; i < bufferLines.size(); i++) {
		bufferLines[i]->setPosition(0, (i*(lineHeight+lineSpacing)),0.0f);
	}
	
	if(multiLine && lineNumbersEnabled) {
		lineNumberBg->setShapeSize(decoratorOffset, height);
	}
	
	if(scrollContainer) {
		scrollContainer->setContentSize(width,  (((lines.size()+1) * ((lineHeight+lineSpacing)))) + padding);
	}	
	
	if(multiLine) {
		inputRect->setHitbox(width - scrollContainer->getVScrollWidth(), height);
	}	
	
}

void UITextInput::setCaretPosition(int position) {
	if(position >= 0 && position < lines[lineOffset].length()) {
		caretPosition = position;
		updateCaretPosition();		
	}
}

void UITextInput::setText(String text, bool sendChangeEvent) {
	if(!multiLine) {
		lines[lineOffset] = text;
		caretPosition = text.length();
		clearSelection();				
		updateCaretPosition();		
	} else {
		selectAll();
		insertText(text);
		clearSelection();
	}
//	needFullRedraw = true;		
	changedText(sendChangeEvent);
}

void UITextInput::onLoseFocus() {
	blinkerRect->visible  = false;
	clearSelection();
}

String UITextInput::getText() {
	
	if(!multiLine) {
		return lines[0];
	} else {
		String totalText = L"";
		for(int i=0; i < lines.size(); i++) {
				totalText += lines[i];
				if(i < lines.size()-1)
					totalText += L"\n";
		}	
		return totalText;
	}
}

void UITextInput::updateCaretPosition() {
	// If this assertion fails, you likely called the function in the wrong
	// place in the constructor.
	assert(bufferLines.size() && lines.size());

	if(lineOffset > lines.size()-1)
		lineOffset = lines.size()-1;

	caretImagePosition = 0;
	if(caretPosition == 0) {
		caretImagePosition = 0;
	} else if(caretPosition > lines[lineOffset].length()) {
		caretPosition = lines[lineOffset].length();
		String caretSubString = lines[lineOffset].substr(0,caretPosition);
		caretImagePosition = bufferLines[0]->getLabel()->getTextWidthForString(caretSubString);
	} else {
		String caretSubString = lines[lineOffset].substr(0,caretPosition);
		caretImagePosition = bufferLines[0]->getLabel()->getTextWidthForString(caretSubString);
	}
	blinkerRect->visible  = true;
	blinkTimer->Reset();
	
	if(doSelectToCaret) {
		doSelectToCaret = false;
	}

	if(!multiLine) {
		// Make sure the new caret position is visible.

		// Try scrolling left.
		while(caretImagePosition <= horizontalPixelScroll && horizontalCharacterScroll > 0) {
			horizontalCharacterScroll--;

			// Update pixel scroll from new character scroll.
			String subString = lines[0].substr(0,horizontalCharacterScroll);
			horizontalPixelScroll = bufferLines[0]->getLabel()->getTextWidthForString(subString);
		}

		// Try scrolling right.
		while(caretImagePosition + blinkerRect->getWidth() > horizontalPixelScroll + textContainer->getWidth()) {
			horizontalCharacterScroll++;

			// Update pixel scroll from new character scroll.
			String subString = lines[0].substr(0,horizontalCharacterScroll);
			horizontalPixelScroll = bufferLines[0]->getLabel()->getTextWidthForString(subString);
		}

		bufferLines[0]->setPosition(-horizontalPixelScroll, 0);
	}
/*	
	if(multiLine) {	
		if(linesContainer->getPosition().y + currentLine->getPosition2D().y < 0.0) {
			scrollContainer->scrollVertical(-(lineHeight+lineSpacing+padding)/(scrollContainer->getContentSize().y));

		} else if(linesContainer->getPosition().y + currentLine->getPosition2D().y > scrollContainer->getHeight()) {
		scrollContainer->scrollVertical((lineHeight+lineSpacing+padding)/(scrollContainer->getContentSize().y));

		}
	}
	*/
}

void UITextInput::selectLineFromOffset() {
	// TODO: remove or fill out body
}

void UITextInput::dragSelectionTo(Number x, Number y) {
	x -= (padding * 2.0) + decoratorOffset;
	y -= padding;
	int lineOffset = y  / (lineHeight+lineSpacing);
	if(lineOffset > lines.size()-1)
		lineOffset = lines.size()-1;
	
	String selectToLine = lines[lineOffset];
	
	int len = selectToLine.length();
	Number slen = 0;
	int caretPosition = bufferLines[0]->getLabel()->getTextWidthForString(selectToLine.substr(0,len)) - horizontalPixelScroll;
	for(int i=0; i < len; i++) {
		slen = bufferLines[0]->getLabel()->getTextWidthForString(selectToLine.substr(0,i)) - horizontalPixelScroll;
		if(slen > x) {
			caretPosition = i;
			break;
		}
	}
	if(x > slen)
		caretPosition = len;
	
//	if(multiLine)
//		caretPosition++;
		
	if(caretPosition < 0)
		caretPosition = 0;		

	setSelection(this->lineOffset, lineOffset, this->caretPosition, caretPosition);
}

int UITextInput::caretSkipWordBack(int caretLine, int caretPosition) {
	for(int i=caretPosition; i > 0; i--) {
		String bit = lines[caretLine].substr(i,1);
		char chr = ((char*)bit.c_str())[0]; 		
		if(!isNumberOrCharacter(chr) && i < caretPosition-1) {
			return i+1;
		}
	}	
	return 0;
}

int UITextInput::caretSkipWordForward(int caretLine, int caretPosition) {
	int len = lines[caretLine].length();
	for(int i=caretPosition; i < len; i++) {
		String bit = lines[caretLine].substr(i,1);
		char chr = ((char*)bit.c_str())[0]; 
		if(!isNumberOrCharacter(chr) && i > caretPosition) {
			return i;
		}
	}
	return lines[caretLine].length();	
}

void UITextInput::selectWordAtCaret() {

	caretPosition = caretSkipWordBack(this->lineOffset,caretPosition);
	clearSelection();			
	updateCaretPosition();
	
	setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretSkipWordForward(this->lineOffset, caretPosition));					

	updateCaretPosition();	
}

void UITextInput::replaceAll(String what, String withWhat) {
	for(int i=0; i < lines.size(); i++) {
		lines[i] = lines[i].replace(what, withWhat);
	}
	needFullRedraw  = true;
	changedText();
}

void UITextInput::findString(String stringToFind, bool replace, String replaceString) {

	clearSelection();
	findMatches.clear();
	
	for(int i=0; i < lines.size(); i++) {


		String lineText = lines[i];
		
		int offset = 0;				
		int retVal = -1;
		do {
			retVal = lineText.find(stringToFind, offset);
			if(retVal != -1) {
				FindMatch match;
				match.lineNumber = i;
				match.caretStart = retVal;
				match.caretEnd = retVal + stringToFind.length();
				findMatches.push_back(match);		
				offset = retVal + stringToFind.length();
			}			
		} while(retVal != -1);
		
	}
	
	
	if(findMatches.size() > 0) {

		if(replace) {
			FindMatch match = findMatches[findIndex];
			String oldText = lines[match.lineNumber];
			String newText = oldText.substr(0,match.caretStart) + replaceString + oldText.substr(match.caretEnd);
			
			lines[match.lineNumber] = newText;
			findMatches[findIndex].caretEnd = findMatches[findIndex].caretStart + replaceString.length();
			changedText();			
		}
	
		findIndex = 0;
		findCurrent();
	}
}

void UITextInput::findNext() {
	if(findMatches.size() == 0)
		return;
	findIndex++;
	if(findIndex == findMatches.size()) {
		findIndex = 0;
	}
	findCurrent();
}

void UITextInput::findPrevious() {
	if(findMatches.size() == 0)
		return;

	findIndex--;
	if(findIndex < 0) {
		findIndex = findMatches.size()-1;
	}
	findCurrent();		
}

void UITextInput::findCurrent() {
	if(findMatches.size() == 0)
		return;

	FindMatch match = findMatches[findIndex];
	lineOffset = match.lineNumber;
	caretPosition = match.caretStart;
	lineOffset = match.lineNumber;
	updateCaretPosition();

	showLine(findMatches[findIndex].lineNumber, false);	
	
	setSelection(match.lineNumber, match.lineNumber, match.caretStart, match.caretEnd);
}

void UITextInput::setCaretToMouse(Number x, Number y) {
	clearSelection();
	x -= (padding) + decoratorOffset;
	y -= padding;
	//if(lines.size() > 1) {
		lineOffset = y  / (lineHeight+lineSpacing);
		if(lineOffset > lines.size()-1)
			lineOffset = lines.size()-1;
		selectLineFromOffset();	
	//}
	
	int len = lines[lineOffset].length();
	Number slen= 0;
	
	int newCaretPosition = -1;
	
	for(int i=1; i < len; i++) {
		slen = bufferLines[0]->getLabel()->getTextWidthForString(lines[lineOffset].substr(0,i)) - horizontalPixelScroll;
		Number slen_prev = bufferLines[0]->getLabel()->getTextWidthForString(lines[lineOffset].substr(0,i-1)) - horizontalPixelScroll;		
		if(x >= slen_prev && x <= slen) {
			if(x < slen_prev + ((slen - slen_prev) /2.0)) {
				newCaretPosition = i-1;
				break;			
			} else {
				newCaretPosition = i;
				break;
			}
		}
	}
	
	if(newCaretPosition == -1)
		newCaretPosition = 0;
	
	if(x > slen)
		newCaretPosition = len;
		
		
	caretPosition = newCaretPosition;	
		
	updateCaretPosition();
}

void UITextInput::removeLines(unsigned int startIndex, unsigned int endIndex) {
	lines.erase(lines.begin()+startIndex, lines.begin()+endIndex);
	renumberLines();
	restructLines();
	changedText();	
}

void UITextInput::selectAll() {
	setSelection(0, lines.size()-1, 0, lines[lines.size()-1].length());
}

void UITextInput::insertText(String text) {	
	vector<String> strings = text.split("\n");
	settingText = true;

	if(hasSelection)
		deleteSelection();

	if(strings.size() > 1) {
		String ctext = lines[lineOffset];
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += strings[0];
		lines[lineOffset] = ctext;
		caretPosition = ctext.length();
		
		for(int i=1; i < strings.size()-1; i++) {
			insertLine(true);
			ctext = strings[i];
			lines[lineOffset] = ctext;
			caretPosition = ctext.length();			
		}
		
		insertLine(true);
		ctext = strings[strings.size()-1] + text2;
		caretPosition = ctext.length();
		lines[lineOffset] = ctext;
		
	} else {
		String ctext = lines[lineOffset];
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += text + text2;
		caretPosition += text.length();
		lines[lineOffset] = ctext;
	}
	
	settingText = false;	

	restructLines();	
	renumberLines();	
	changedText();
	updateCaretPosition();		
	
}

String UITextInput::getLineText(unsigned int index) {
	if(index < lines.size()) {
		return lines[index];
	} else {
		return "";
	}
}       

String UITextInput::getSelectionText() {
	if(!hasSelection)
		return L"";
		
	String totalText = L"";

	// Set up iteration cursors
	int currentLine = selectionTop;
	int currentLeft = selectionL;

	// Iterate over the inner lines(we'll be appending \n to these)
	while(currentLine < selectionBottom) {
		totalText += lines[currentLine].substr(currentLeft, lines[currentLine].length()-currentLeft) + '\n';
		currentLine++;
		currentLeft = 0;
	}
	// Add the selection in the last line(no \n needed)
	totalText += lines[currentLine].substr(currentLeft, selectionR-currentLeft);

	return totalText;
}

void UITextInput::setSelectionColor(Color color) {
	selectorRectTop->color = color;
	selectorRectMiddle->color = color;
	selectorRectBottom->color = color;
}

void UITextInput::setCursorColor(Color color) {
	blinkerRect->color = color;
}

void UITextInput::setBackgroundColor(Color color) {
	inputRect->color = color;
}

void UITextInput::setLineNumberColor(Color color) {
	lineNumberColor = color;
	for(int i=0; i < numberLines.size(); i++) {
		numberLines[i]->color = lineNumberColor;
	}	
}

void UITextInput::setTextColor(Color color) {
	textColor = color;
	for(int i=0; i < bufferLines.size(); i++) {
		bufferLines[i]->color = textColor;
	}
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
	// By default, reset the isTypingWord status.
	// If we are typing a word after all, the caller
	// will immediately reset it to 1.
	isTypingWord = 0;
}

void UITextInput::setUndoState(UITextInputUndoState state) {
	clearSelection();
	setText(state.content);
	lineOffset = state.lineOffset;
	caretPosition = state.caretPosition;
	lineOffset = state.lineOffset;
	updateCaretPosition();
	
	if(state.hasSelection) {
		setSelection(lineOffset, state.selectionLine, caretPosition, state.selectionCaretPosition);
	}
	
	showLine(state.lineOffset, false);
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
	} else if (getLineText(lineOffset) != "") {
        if (!multiLine) { setText(""); }
        else {
            removeLines(lineOffset, lineOffset+1);
            caretPosition = 0;
            updateCaretPosition();
        }
    }
}

void UITextInput::Copy() {
	if(hasSelection) {
		CoreServices::getInstance()->getCore()->copyStringToClipboard(getSelectionText());
	} else {
        if (getLineText(lineOffset) != "") {
            CoreServices::getInstance()->getCore()->copyStringToClipboard(getLineText(lineOffset));
        }
    }
}

void UITextInput::Paste() {
	saveUndoState();
	insertText(CoreServices::getInstance()->getCore()->getClipboardString());
}

void UITextInput::showLine(unsigned int lineNumber, bool top) {
	// If there's no scroll container, no need to adjust the line.
	if(!multiLine) {
		return;
	}

	if(top) {
		scrollContainer->setScrollValue(0.0, ((((lineNumber) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
	} else {
		scrollContainer->setScrollValue(0.0, (((((lineNumber) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()/2.0))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));	
	}
}

bool UITextInput::isNumberOrCharacter(wchar_t charCode) {
	if(charCode > 47 && charCode < 58)
		return true;

	if(charCode > 64 && charCode < 91)
		return true;

	if(charCode > 96 && charCode < 123)
		return true;


	return false;
}

void UITextInput::onKeyDown(PolyKEY key, wchar_t charCode) {
	
	if(!hasFocus)
		return;
		
//	Logger::log("UCHAR: %d\n", charCode);	
	
	CoreInput *input = CoreServices::getInstance()->getCore()->getInput();
	
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
			if(caretPosition > 0 || lineOffset > 0) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					// Holding down shift allows you to select with the arrow keys.
					if(hasSelection) {
						if(selectionCaretPosition > 0)
							setSelection(lineOffset, selectionLine, this->caretPosition, selectionCaretPosition-1);
					} else {
						setSelection(lineOffset, lineOffset, caretPosition, max(caretPosition-1, 0));
					}
				} else {
					int newLineStart = lineOffset;
					int newCaretPosition = caretPosition;
					if(newCaretPosition > 0) {
						newCaretPosition--;
					} else if(newLineStart > 0) {
						newLineStart--;
						newCaretPosition = lines[newLineStart].length();
					}

					clearSelection();
					caretPosition = newCaretPosition;
					lineOffset = newLineStart;
					updateCaretPosition();
				}
			}
		}
		return;
	}
	
	if(key == KEY_RIGHT) {
		if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
			if(caretPosition < lines[lineOffset].length()) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, lines[selectionLine].length());					
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, lines[lineOffset].length());
					}
				} else {
					caretPosition = lines[lineOffset].length();
					clearSelection();
					updateCaretPosition();					
				}
			}
		} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
			if(caretPosition < lines[lineOffset].length()) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, caretSkipWordForward(selectionLine, selectionCaretPosition));
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretSkipWordForward(this->lineOffset, caretPosition));					
					}
				} else {				
					caretPosition = caretSkipWordForward(this->lineOffset,caretPosition);
					clearSelection();
					updateCaretPosition();										
				}
			}
		} else {
			if(caretPosition < lines[lineOffset].length() || lineOffset + 1 < lines.size()) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					// Holding down shift allows you to select with the arrow keys.
					if(hasSelection) {
						setSelection(this->lineOffset, selectionLine, this->caretPosition, selectionCaretPosition+1);
					} else {
						setSelection(this->lineOffset, this->lineOffset, this->caretPosition, caretPosition+1);
					}
				} else {
					clearSelection();

					int newLineEnd = lineOffset;
					int newCaretPosition = caretPosition;
					if(newCaretPosition < lines[lineOffset].length()) {
						newCaretPosition++;
					} else if(newLineEnd + 1 < lines.size()) {
						newLineEnd++;
						newCaretPosition = 0;
					}
					caretPosition = newCaretPosition;
					lineOffset = newLineEnd;
				}
				updateCaretPosition();
			}
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
            if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) < 0.0) {
                scrollContainer->setScrollValue(0.0, ((((lineOffset) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
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
            if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) > scrollContainer->getHeight()-lineHeight-lineSpacing) {
                scrollContainer->setScrollValue(0.0, (((((lineOffset) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()-lineHeight-lineSpacing))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));
            }
		}
		blinkerRect->visible  = true;		
		return;
	}
	
	if(key == KEY_ESCAPE) {
		if(!multiLine) {
			dispatchEvent(new Event(), Event::CANCEL_EVENT);		
		}
	}
	
	if(key == KEY_RETURN) {
		if(multiLine) {	
			saveUndoState();
			if(hasSelection) {
				deleteSelection();		
			}			
			insertLine(true);
			updateCaretPosition();
            if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) > scrollContainer->getHeight()-lineHeight-lineSpacing) {
                scrollContainer->setScrollValue(0.0, (((((lineOffset) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()-lineHeight-lineSpacing))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));
            }
		} else {
			dispatchEvent(new Event(), Event::COMPLETE_EVENT);
		}
		return;
	}

	// indent/shift text
	if (multiLine && (key == KEY_LEFTBRACKET || key == KEY_RIGHTBRACKET) &&
		(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER) ||
			input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
				shiftText( (key == KEY_RIGHTBRACKET) ? false : true );
				return;
	}

	// at this point, return if certain modifier keys are held down so as not to potentially add any unwanted text
	if (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER) || input->getKeyState(KEY_LCTRL) ||
		input->getKeyState(KEY_RCTRL) || input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT))
			return;
	
	String ctext = lines[lineOffset];
	
	bool _changedText = false;
		
	if((charCode > 31 && charCode < 127) || charCode > 127) {
		
		if(!isNumberOnly || (isNumberOnly && ((charCode > 47 && charCode < 58) || (charCode == '.' || charCode == '-')))) {
			if(!isNumberOrCharacter(charCode)) { 
				saveUndoState();
			} else if (!isTypingWord) {
				saveUndoState();
				isTypingWord = 1;
			}
			if(hasSelection)
				deleteSelection();
			ctext = lines[lineOffset];
			String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
			ctext = ctext.substr(0,caretPosition);
			ctext += charCode + text2;
			caretPosition++;
			_changedText = true;
		}
	}
	
	if(key == KEY_TAB && multiLine) {
		saveUndoState();
		if(hasSelection)
			deleteSelection();		
		ctext = lines[lineOffset];
		String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
		ctext = ctext.substr(0,caretPosition);
		ctext += (wchar_t)'\t' + text2;
		caretPosition++;
		_changedText = true;		
	}
	
	if(key == KEY_BACKSPACE) {
		if(hasSelection) {
			saveUndoState();
			deleteSelection();
			return;
		} else {
		ctext = lines[lineOffset];
		if(caretPosition > 0) {
			saveUndoState();
			if(ctext.length() > 0) {
				String text2 = ctext.substr(caretPosition, ctext.length()-caretPosition);
				ctext = ctext.substr(0,caretPosition-1);
				ctext += text2;
				caretPosition--;
				_changedText = true;				
			}
		} else {
			if(lineOffset > 0) {
				saveUndoState();			
				lineOffset--;
				selectLineFromOffset();
				caretPosition = lines[lineOffset].length();
				updateCaretPosition();
				lines[lineOffset] = lines[lineOffset] + ctext;	
				removeLines(lineOffset+1, lineOffset+2);
				return;
			}
		}
		}
        if (multiLine) {
            if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) < 0.0) {
                scrollContainer->setScrollValue(0.0, ((((lineOffset) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
            }
        }
	}
	
	lines[lineOffset] = ctext;
	
	if(_changedText) {
		changedText();
	}
	updateCaretPosition();
}

void UITextInput::Update() {

	if(hasSelection) {
		blinkerRect->visible = false;
	}

	blinkerRect->setPosition(caretImagePosition + 1 -horizontalPixelScroll, (lineOffset * ( lineHeight+lineSpacing)));

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

	textContainer->scissorBox.setRect(textContainer->getScreenPosition().x, textContainer->getScreenPosition().y, textContainer->getWidth(), textContainer->getHeight() + padding);
}

UITextInput::~UITextInput() {
	core->removeAllHandlersForListener(this);
	delete blinkTimer;

	linesContainer->ownsChildren = true;
	if(!ownsChildren) {
		delete linesContainer;
		delete inputRect;
		delete lineNumberBg;
	}
}

void UITextInput::readjustBuffer() {
	int bufferOffset = -linesContainer->position.y/ ( lineHeight+lineSpacing);	
	Number bufferLineOffset = bufferOffset * ( lineHeight+lineSpacing);	
	
	for(int i=0; i < bufferLines.size(); i++) {
		bufferLines[i]->getLabel()->clearColors();
		
		if(bufferOffset + i < lines.size()) {

			if(bufferOffset+i < lineColors.size()) {
				for(int j=0; j < lineColors[bufferOffset+i].colors.size(); j++) {
					bufferLines[i]->getLabel()->setColorForRange(lineColors[bufferOffset+i].colors[j].color, lineColors[bufferOffset+i].colors[j].rangeStart, lineColors[bufferOffset+i].colors[j].rangeEnd);
					bufferLines[i]->setColor(1.0, 1.0, 1.0, 1.0);
				}		
			}
			
			bufferLines[i]->setText(lines[bufferOffset+i]);
		} else {
			bufferLines[i]->setText("");
		}
		bufferLines[i]->setPosition(-horizontalPixelScroll, bufferLineOffset + (i*(lineHeight+lineSpacing)),0.0f);	
	}
	
	for(int i=0; i < numberLines.size(); i++) {
		if(lineNumbersEnabled) {
			numberLines[i]->setText(String::IntToString(bufferOffset+i+1));
			int textWidth = ceil(numberLines[i]->getLabel()->getTextWidth());			
			numberLines[i]->setPosition(-textWidth,padding + bufferLineOffset + (i*(lineHeight+lineSpacing)),0.0f);		
			numberLines[i]->visible = true;
		}
	}
	
}
		
void UITextInput::handleEvent(Event *event) {

	if(event->getDispatcher() == core && hasFocus) {
		switch(event->getEventCode()) {
			case Core::EVENT_UNDO:
				Undo();
			break;
			case Core::EVENT_REDO:
				Redo();
			break;
			case Core::EVENT_COPY:
				Copy();
			break;
			case Core::EVENT_CUT:
				Cut();
			break;
			case Core::EVENT_PASTE:
				Paste();
			break;
			case Core::EVENT_SELECT_ALL:
				selectAll();
			break;
			
		}
	}

	if(event->getDispatcher() == scrollContainer) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			applySyntaxFormatting();
		}
	}

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
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_TEXT);			
				if(draggingSelection) {
					dragSelectionTo(((InputEvent*)event)->mousePosition.x, ((InputEvent*)event)->mousePosition.y - linesContainer->getPosition().y);		
				}
			break;
			case InputEvent::EVENT_MOUSEOVER:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_TEXT);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);
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

void UITextInput::shiftText(bool left) {
	if (multiLine && (hasSelection || lines[lineOffset] != "")) {
		saveUndoState();
		
		String t = (wchar_t)'\t';
		
		if (hasSelection) {
			for (int i = selectionTop; i <= selectionBottom; i++) {
				if (i == selectionBottom && selectionCaretPosition <= 0)
					// at least one character of bottom line needs to be selected before indenting, so...
					break;
				if (indentType == INDENT_TAB) {
					if (left) {
						if (lines[i].substr(0,1) == t) {
							lines[i] = lines[i].substr(1, lines[i].length()-1);
							caretPosition--;
						}
					} else {
						lines[i] = t + lines[i];
						caretPosition++;
					}
				} else if (indentType == INDENT_SPACE) {
					if (left) {
						// TODO
					} else {
						// TODO
					}
				}
			}
		}
		else {
			if (indentType == INDENT_TAB) {
				if (left) {
					if (lines[lineOffset].substr(0,1) == t) {
						lines[lineOffset] = lines[lineOffset].substr(1, lines[lineOffset].length()-1);
						caretPosition--;
					}
				} else {
					lines[lineOffset] = t + lines[lineOffset];
					caretPosition++;
				}
			} else if (indentType == INDENT_SPACE) {
				if (left) {
					// TODO
				} else {
					// TODO
				}
			}
		}
		
		changedText();
		updateCaretPosition();
	}
}

void UITextInput::convertIndentToSpaces() {
	if (indentType == INDENT_TAB) {
		indentType = INDENT_SPACE;
		
		//TODO
	}
}

void UITextInput::convertIndentToTabs() {
	if (indentType == INDENT_SPACE) {
		indentType = INDENT_TAB;
		
		//TODO
	}
}