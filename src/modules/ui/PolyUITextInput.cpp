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
#include "PolyRenderer.h"

using namespace Polycode;

UIGlobalMenu* UITextInput::globalMenuSingleton = NULL;

void UITextInput::setMenuSingleton(UIGlobalMenu *_globalMenu) {
	globalMenuSingleton = _globalMenu;
}

UITextInput::UITextInput(bool multiLine, Number width, Number height, int customFontSize, const String &customFont, int customLineSpacing) : UIElement(width, height) {
	this->multiLine = multiLine;
	processInputEvents = true;
	isNumberOnly = false;
	
	didMultilineResize = true;
	actualLineOffset = -1;
	actualCaretPosition = 0;
	
	resizeTimer = 0;
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
	isTypingWord = false;
	
	numLines = 0;
	
	setAnchorPoint(0.0, 0.0, 0.0);
	Config *conf = CoreServices::getInstance()->getConfig();	
	
    if(customFont != "") {
        fontName = customFont;
    } else {
	if(multiLine)
		fontName = conf->getStringValue("Polycode", "uiTextInputFontNameMultiLine");
	else
		fontName = conf->getStringValue("Polycode", "uiTextInputFontName");
    }
    if(customFontSize != -1) {
        fontSize = customFontSize;
    } else {
        if(multiLine)
            fontSize = conf->getNumericValue("Polycode", "uiTextInputFontSizeMultiline");	
        else
            fontSize = conf->getNumericValue("Polycode", "uiTextInputFontSize");
    }
    
	Number rectHeight = height;
	if(!multiLine) {
		rectHeight = fontSize+10;
	} 

	linesContainer = new Entity();	
	linesContainer->processInputEvents = true;
	linesContainer->ownsChildren = true;
    
    if(customLineSpacing != -1) {
        lineSpacing = customLineSpacing;
    } else {
        lineSpacing = conf->getNumericValue("Polycode", "textEditLineSpacing");
    }
    
	st = conf->getNumericValue("Polycode", "textBgSkinT");
	sr = conf->getNumericValue("Polycode", "textBgSkinR");
	sb = conf->getNumericValue("Polycode", "textBgSkinB");
	sl = conf->getNumericValue("Polycode", "textBgSkinL");

	textInputOffsetY = conf->getNumericValue("Polycode", "uiTextInputFontOffsetY");
    if(multiLine) {
        textInputOffsetY = 0.0;
    }
    
	padding = conf->getNumericValue("Polycode", "textBgSkinPadding");
	
	textContainer = new UIElement();
	textContainer->ownsChildren = true;

	linesContainer->addChild(textContainer);
	if(multiLine) {
		inputRect = new UIBox(conf->getStringValue("Polycode", "textBgSkinMultiline"),
						  st,sr,sb,sl,
						  width+(padding*2), height+(padding*2));
        inputRect->setBlendingMode(Renderer::BLEND_MODE_NONE);
	} else {
		inputRect = new UIBox(conf->getStringValue("Polycode", "textBgSkin"),
						  st,sr,sb,sl,
						  width+(padding*2), height+(padding*2));
        
        inputRectSelected = new UIBox(conf->getStringValue("Polycode", "textBgSkinFocus"),
                              st,sr,sb,sl,
                              width+(padding*2), height+(padding*2));
        inputRectSelected->visible = false;
        addChild(inputRectSelected);
	}
	
	addChild(inputRect);		
	
	if(multiLine) {
		lineNumberBg = new UIRect(1,1);
		lineNumberBg->setAnchorPoint(-1.0, -1.0, 0.0);
		lineNumberBg->setColor(0.5, 0.5, 0.5, 1.0);
		addChild(lineNumberBg);
		lineNumberBg->visible = false;
		
		lineNumberAnchor = new Entity();
		linesContainer->addChild(lineNumberAnchor);
	} else {
		lineNumberBg = NULL;
		lineNumberAnchor = NULL;
		decoratorOffset = sl/2.0;
	}

	textContainer->setWidth(fabs(this->getWidth() - textContainer->getPosition2D().x - padding));
	textContainer->setHeight(fabs(this->getHeight() - textContainer->getPosition2D().y));
	textContainer->setPosition(padding + decoratorOffset, padding + textInputOffsetY);
	
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);	
	inputRect->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);		
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);		
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	inputRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	inputRect->processInputEvents = true;
	inputRect->setAnchorPoint(-1.0, -1.0, 0.0);
	
	selectionColor = Color(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1.0f);
	
	selectorRectTop = new UIRect(1,1);
//	selectorRectTop->setAnchorPoint(-1.0, -1.0, 0.0);
	selectorRectTop->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectTop->visible = false;
	textContainer->addChild(selectorRectTop);

	selectorRectMiddle = new UIRect(1,1);
//	selectorRectMiddle->setAnchorPoint(-1.0, -1.0, 0.0);	
	selectorRectMiddle->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectMiddle->visible = false;
	textContainer->addChild(selectorRectMiddle);

	selectorRectBottom = new UIRect(1,1);
//	selectorRectBottom->setAnchorPoint(-1.0, -1.0, 0.0);	
	selectorRectBottom->setColor(181.0f/255.0f, 213.0f/255.0f, 255.0f/255.0f, 1);
	selectorRectBottom->visible = false;
	textContainer->addChild(selectorRectBottom);
		
	
	blinkerRect = new UIRect(1, fontSize+2);
	blinkerRect->setAnchorPoint(-1.0, -1.0, 0.0);
	blinkerRect->setColor(0,0,0,1);
	textContainer->addChild(blinkerRect);
	blinkerRect->visible = false;
	blinkerRect->setPosition(-horizontalPixelScroll,3);
	
	blinkTimer = new Timer(true, 500);
	blinkTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	focusable = true;
	setWidth(width);
	setHeight(rectHeight);
	
	scrollContainer = NULL;
	if(multiLine) {
		scrollContainer = new UIScrollContainer(linesContainer, false, true, width, height);
		scrollContainer->addEventListener(this, Event::CHANGE_EVENT);
		addChild(scrollContainer);
	} else {
		addChild(linesContainer);
		textContainer->enableScissor = true;
	}
		
	undoStateIndex = 0;
	maxRedoIndex = 0;
	
	syntaxHighliter = NULL;
	
	textColor = Color(0.0,0.0,0.0,1.0);

	currentBufferLines = 0;
	neededBufferLines = 1;
	checkBufferLines();

	insertLine();
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
	
	core->getInput()->addEventListenerUnique(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListenerUnique(this, InputEvent::EVENT_MOUSEUP);
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
			SceneLabel *newNumberLine = new SceneLabel(L"", fontSize, fontName, aaMode);
            newNumberLine->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
			newNumberLine->color = lineNumberColor;
			newNumberLine->positionAtBaseline = true;
			lineNumberAnchor->addChild(newNumberLine);
			numberLines.push_back(newNumberLine);		
			
			if(!lineNumbersEnabled) {
				newNumberLine->visible = false;
			}
		}
	
		SceneLabel *newLine = new SceneLabel(L"", fontSize, fontName, aaMode);
        newLine->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
		newLine->positionAtBaseline = true;
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
	if(colStart < 0)
		colStart = 0;
	if(colEnd < 0)
		colEnd = 0;

	clearSelection();

	_setSelectionColor(selectionColor);

	if(lineStart == lineEnd && colStart == colEnd) {
		return;
	}

	if(lineStart == actualLineOffset) {
		selectionLine = lineEnd;
	} else {
		selectionLine = lineStart;	
	}

	if(colStart == actualCaretPosition) {
		selectionCaretPosition = colEnd;
	} else {
		selectionCaretPosition = colStart;
	}

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
	
	if(lineStart > lines.size()-1) {
		return;	
	}
	
	String topLine = lines[lineStart].text;
	
	if(colStart+1 > topLine.length()) {
		colStart = topLine.length();
	}	

	hasSelection = true;
	
	selectionTop = lineStart;
	selectionBottom = lineEnd;
	selectionL = colStart;
	selectionR = colEnd;
	
	if(!settingText) {
		updateSelectionRects();
	}
}

void UITextInput::updateSelectionRects() {

	int lineStart;
	int lineEnd;
	int colStart;
	int colEnd;
	
	convertActualToOffset(selectionTop, selectionL, &lineStart, &colStart);
	convertActualToOffset(selectionBottom, selectionR, &lineEnd, &colEnd);
	
							
	String topLine = wordWrapLines[lineStart].text;
			
	Number fColEnd  = colEnd;
	
	if(colEnd > topLine.length() || lineStart != lineEnd)
		fColEnd = topLine.length();

	Number topSize, topHeight, topX;
	
	selectorRectTop->visible = true;
	
	topSize = bufferLines[0]->getTextWidthForString(topLine.substr(colStart,fColEnd-colStart));
	topHeight = lineHeight+lineSpacing;
	if(colStart >= 0) {
		topX = bufferLines[0]->getTextWidthForString(topLine.substr(0,colStart));
	} else {
		topX = 0;
	}
	
	if(topSize < 4) {
		topSize = 4;
	}
	selectorRectTop->Resize(topSize, topHeight);
	selectorRectTop->setPosition(topX - horizontalPixelScroll, lineStart * (lineHeight+lineSpacing));
	
	if(lineEnd > lineStart && lineEnd < wordWrapLines.size()) {
		String bottomLine = wordWrapLines[lineEnd].text;
		selectorRectBottom->visible = true;		
		Number bottomSize = bufferLines[0]->getTextWidthForString(bottomLine.substr(0,colEnd)) ; 
		if(bottomSize < 0)
			bottomSize = this->getWidth()-padding;
		Number bottomHeight = lineHeight+lineSpacing;
		
		if(bottomSize < 4) {
			bottomSize = 4;
		}

		selectorRectBottom->Resize(bottomSize, bottomHeight);
		selectorRectBottom->setPosition(-horizontalPixelScroll, lineEnd * (lineHeight+lineSpacing));
		
		if(lineEnd != lineStart+1) {
			// need filler
			selectorRectMiddle->visible = true;		
			Number midSize = this->getWidth()-padding;
			Number midHeight = 0;			
			for(int i=lineStart+1; i < lineEnd;i++) {
				midHeight += lineHeight+lineSpacing;
			}
			selectorRectMiddle->Resize(midSize, midHeight);
			selectorRectMiddle->setPosition(- horizontalPixelScroll, ((lineStart+1) * (lineHeight+lineSpacing)));
			
		}
		
	}
}

void UITextInput::deleteSelection() {
	if(selectionTop == selectionBottom) {
		String ctext = lines[selectionTop].text;
		String newText = ctext.substr(0, selectionL);
		int rside = selectionR;
		if(rside > ctext.length()-1)
			rside = ctext.length() - 1;
		newText += ctext.substr(rside,ctext.length() - selectionR); 
		lines[selectionTop].text = newText;
	} else {
		
		String ctext = lines[selectionTop].text;
		String newText = ctext.substr(0, selectionL);
		lines[selectionTop].text = newText;

		ctext = lines[selectionBottom].text;
		
		int rside = selectionR;
		if(rside > ctext.length()-1)
			rside = ctext.length() - 1;
		newText = ctext.substr(rside,ctext.length() - selectionR); 
		
		actualLineOffset = selectionTop;		
		actualCaretPosition = lines[actualLineOffset].text.length();
		setOffsetToActual();		
		updateCaretPosition();
		
		lines[actualLineOffset].text =  lines[actualLineOffset].text + newText;
		
		removeLines(selectionTop+1, selectionBottom);
		
			
	}
	clearSelection();
	actualCaretPosition = selectionL;
	updateCaretPosition();
	
	setActualLineOffset();
	
	changedText(actualLineOffset,actualLineOffset);
}

void UITextInput::applyTokenOverride(int lineIndex, SyntaxHighlightToken overrideToken) {
	if(overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE) {
	
	
		bool previousLineInBlockOverride = false;
		if(lineIndex > 0) {		
			if(lines[lineIndex-1].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_LINE ||  lines[lineIndex-1].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) {
				previousLineInBlockOverride = true;
			}
		}	
	
		if(lines[lineIndex].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START && !previousLineInBlockOverride) {
			for(int l=lineIndex; l < lines.size(); l++) {

				if(lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START && l != lineIndex) {
					return;
				}
			
				if(lines[l].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
				lines[l].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;
				int _lineOffset = lines[l].wordWrapLineIndex;
				while((_lineOffset < wordWrapLines.size()) && (wordWrapLines[_lineOffset].actualLineNumber == l)) {
					wordWrapLines[_lineOffset].blockOverrideToken = lines[l].blockOverrideToken;
					wordWrapLines[_lineOffset].dirty = true;
					_lineOffset++;
				}
				} else {
					changedText(l,l,false);
				}
			}		
		}

		
		if(lines[lineIndex].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
			if(previousLineInBlockOverride) {
			for(int l=lineIndex; l < lines.size(); l++) {
			
				if((lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END || lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) && l != lineIndex) {
				
					if(lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
						changedText(l,l,false);
					}								
					return;
				}			
			
				lines[l].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_LINE;
				lines[l].blockOverrideToken.color = lines[lineIndex-1].blockOverrideToken.color;
				int _lineOffset = lines[l].wordWrapLineIndex;
				while((_lineOffset < wordWrapLines.size()) && (wordWrapLines[_lineOffset].actualLineNumber == l)) {
					wordWrapLines[_lineOffset].blockOverrideToken = lines[l].blockOverrideToken;
					wordWrapLines[_lineOffset].dirty = true;
					_lineOffset++;
				}
			}
			} else {
				lines[lineIndex].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;
			}
		}


	}
	
		if(overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) {
			for(int l=lineIndex; l < lines.size(); l++) {
						
				if((lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END || lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) && l != lineIndex) {
				
					if(lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
						changedText(l,l,false);
					}
					return;
				}
				
				lines[l].blockOverrideToken = overrideToken;
				if(l != lineIndex) {					
					lines[l].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_LINE;
				}				
				int _lineOffset = lines[l].wordWrapLineIndex;
				while((_lineOffset < wordWrapLines.size()) && (wordWrapLines[_lineOffset].actualLineNumber == l)) {
					wordWrapLines[_lineOffset].blockOverrideToken = lines[l].blockOverrideToken;
					wordWrapLines[_lineOffset].dirty = true;
					_lineOffset++;
				}
			}
		}
		
		if(overrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
			for(int l=lineIndex; l < lines.size(); l++) {
			
				if(lines[l].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END || l == lineIndex) {
				
				if((lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) && l != lineIndex) {
					return;
				}				

				lines[l].blockOverrideToken = overrideToken;
				if(l != lineIndex) {					
					lines[l].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;
				}				
				
				int _lineOffset = lines[l].wordWrapLineIndex;
				while((_lineOffset < wordWrapLines.size()) && (wordWrapLines[_lineOffset].actualLineNumber == l)) {
					wordWrapLines[_lineOffset].blockOverrideToken = lines[l].blockOverrideToken;
					wordWrapLines[_lineOffset].dirty = true;
					_lineOffset++;
				}
				} else {
					if(lines[l].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
						changedText(l,l,false);
					}												
				}
			}
		}	
}

void UITextInput::applyBlockOverrides() {
	for(int i=0; i < wordWrapLines.size(); i++) {
		wordWrapLines[i].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;	
	}

	for(int i=0; i < lines.size(); i++) {
		if(lines[i].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START && lines[i].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {		
		lines[i].blockOverrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;		
		}
	}
	
	for(int i=0; i < lines.size(); i++) {
		if(lines[i].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START || lines[i].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
				applyTokenOverride(i, lines[i].blockOverrideToken);
		}
	}
}

void UITextInput::applySyntaxFormatting(int startLine, int endLine) {

	if(syntaxHighliter && multiLine) {
			
		if(startLine < 0)
			startLine = 0;
		
		if(endLine > lines.size())
			endLine = lines.size();
			
		String totalText = L"";
		for(int i=startLine; i < endLine+1; i++) {
			totalText += lines[i].text;
			if(i < endLine)
				totalText += L"\n";
		}		

	SyntaxHighlightToken _blockOverrideToken;
	if(startLine > 0) {
		_blockOverrideToken = lines[startLine-1].blockOverrideToken;
	}
	
	std::vector<SyntaxHighlightToken> tokens = syntaxHighliter->parseText(totalText, _blockOverrideToken);	
	
	int lineIndex = startLine;
	lines[lineIndex].colorInfo.colors.clear();
	int rangeStart = 0;
	int rangeEnd = 0;
	
	
	SyntaxHighlightToken _overrideToken;
			
	for(int i=0; i < tokens.size(); i++) {

		if(tokens[i].overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START || tokens[i].overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) {
			_overrideToken = tokens[i];
		}
	
		if(tokens[i].text == "\n") {
			applyTokenOverride(lineIndex, _overrideToken);
			_overrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE;
			lineIndex++;
			if(lineIndex < lines.size() && i < tokens.size()-1) {
				lines[lineIndex].colorInfo.colors.clear();
			}
			rangeStart = 0;
			rangeEnd = 0;
		} else {			
			if(lineIndex < lines.size()) {
				int textLength = tokens[i].text.length();
				if(tokens[i].text.length() > 1) {
					rangeEnd = rangeStart + textLength-1;
					lines[lineIndex].colorInfo.colors.push_back(LineColorData(tokens[i].color, rangeStart, rangeEnd));
					rangeStart = rangeStart + textLength; 
				} else {
					rangeEnd = rangeStart;
					lines[lineIndex].colorInfo.colors.push_back(LineColorData(tokens[i].color, rangeStart, rangeEnd));
					rangeStart++;
				}				
			}
		}
	}
	
	}

//	readjustBuffer(startLine, endLine);	
}

void UITextInput::changedText(int lineStart, int lineEnd, bool sendChangeEvent) {
	if(lineStart <0) {
		lineStart = 0;
	}
	
	if(lineEnd > lines.size()-1) {
		lineEnd = lines.size()-1;
	}

	if(settingText)
		return;

	applySyntaxFormatting(lineStart, lineEnd);	
	updateWordWrap(lineStart, lineEnd);
		
	if(sendChangeEvent) {
		dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
	}
}

void UITextInput::setSyntaxHighlighter(UITextInputSyntaxHighlighter *syntaxHighliter) {
	this->syntaxHighliter = syntaxHighliter;
}

void UITextInput::doMultilineResize() {

	if(multiLine) {
		int bufferOffset = -linesContainer->getPosition().y/ ( lineHeight+lineSpacing);	
		
		int realLineOffset = -1;
		if(bufferOffset > 0 && bufferOffset < wordWrapLines.size()) {
			realLineOffset = wordWrapLines[bufferOffset].actualLineNumber;
		}
		
		if(getWidth() != lastResizeWidth) {	
			updateWordWrap(0, lines.size()-1);
		}
		
		if(realLineOffset > -1 && realLineOffset < lines.size()) {
			showLine(realLineOffset, true);
		}
		renumberLines();
		restructLines();		
		readjustBuffer();
		if(lineNumbersEnabled) {
			lineNumberBg->Resize(decoratorOffset, getHeight());
		}
	}
	
	lastResizeWidth = getWidth();
		
	didMultilineResize = true;
	
	if(hasSelection) {
		updateSelectionRects();
	}
}

void UITextInput::Resize(Number width, Number height) {

	resizeTimer = 0;
	didMultilineResize = false;
	
	inputRect->resizeBox(width, height);
    if(!multiLine) {
        inputRectSelected->resizeBox(width, height);
    }
	setWidth(width);
	setHeight(height);
	matrixDirty = true;	
	
	if(multiLine) {
		neededBufferLines = (height / ( lineHeight+lineSpacing)) + 1;
		checkBufferLines();
		renumberLines();
		readjustBuffer();
		if(lineNumbersEnabled) {
			lineNumberBg->Resize(decoratorOffset, height);
		}		
	}
	
	if(scrollContainer) {
		scrollContainer->Resize(width, height);
	}
	
	textContainer->setWidth(fabs(this->getWidth() - textContainer->getPosition2D().x - padding));
	textContainer->setHeight(fabs(this->getHeight() - textContainer->getPosition2D().y));
	textContainer->setPosition(padding + decoratorOffset, padding + textInputOffsetY);
}

int UITextInput::insertLine(String lineText) {
	
	numLines++;	
		
		String newText = lineText;
		if(lines.size() > 0 && !settingText) {
			String ctext = lines[actualLineOffset].text;
			String text2 = ctext.substr(actualCaretPosition, ctext.length()-actualCaretPosition);
			ctext = ctext.substr(0,actualCaretPosition);
			lines[actualLineOffset].text = ctext;
			newText = newText+text2;
			actualCaretPosition=0;
			caretPosition = 0;
		}		
		
		vector<LineInfo>::iterator it;
						
		lineOffset = lineOffset + 1;
		actualLineOffset = actualLineOffset + 1;
	
		if(actualLineOffset >= lines.size()) {
			it = lines.end();
		} else {
			it = lines.begin() + actualLineOffset;
		}
		
		SyntaxHighlightToken _overrideToken;
		
		if(actualLineOffset > 0) {
			if(lines[actualLineOffset-1].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START && lines[actualLineOffset-1].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END) { 
				_overrideToken = lines[actualLineOffset-1].blockOverrideToken;
			} else if(lines[actualLineOffset-1].blockOverrideToken.overrideType == SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) {
				_overrideToken = lines[actualLineOffset-1].blockOverrideToken;
				_overrideToken.overrideType = SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_LINE;
			}
		}
		
		LineInfo info;
		info.text = newText;
		info.blockOverrideToken = _overrideToken;
		lines.insert(it,info);
		
		WordWrapLine line;		
		line.text = info.text;
		line.isWordWrap = false;
		line.blockOverrideToken = _overrideToken;
		line.actualLineNumber = actualLineOffset+1;
		lines[actualLineOffset].wordWrapLineIndex = lineOffset;
		line.colorInfo = lines[actualLineOffset].colorInfo;
		
		vector<WordWrapLine>::iterator wit;
		wit = wordWrapLines.begin() + lineOffset;
		wordWrapLines.insert(wit,line);


		for(int i=actualLineOffset+1; i < lines.size(); i++) {
			lines[i].wordWrapLineIndex += 1;
		}
		
		for(int i=lineOffset+1; i < wordWrapLines.size(); i++) {
			wordWrapLines[i].actualLineNumber += 1;
			wordWrapLines[i].dirty = true;
		}
		
		if(!settingText) {
		
		restructLines();
		changedText(actualLineOffset-1, actualLineOffset);		
		}		
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
		lineNumberBg->Resize(decoratorOffset, getHeight());
	}
	
	if(scrollContainer) {
		scrollContainer->setContentSize(getWidth(),  (((wordWrapLines.size()+1) * ((lineHeight+lineSpacing)))) + padding);
	}
}

void UITextInput::setCaretPosition(int position) {
	if(position >= 0 && position < lines[lineOffset].text.length()) {
		caretPosition = position;
		updateCaretPosition();		
	}
}

void UITextInput::setText(String text, bool sendChangeEvent) {
	if(!multiLine) {
		lines[lineOffset].text = text;
		horizontalCharacterScroll = 0;
		horizontalPixelScroll = 0;
		actualCaretPosition = text.length();
		clearSelection();				
		changedText(0, 0);
		updateCaretPosition();		
	} else {
		selectAll();
		insertText(text, false);
		clearSelection();
		changedText(0, lines.size()-1, false);
//		wordWrapLines.clear();
		doMultilineResize();
		applyBlockOverrides();
	}
}

void UITextInput::onLoseFocus() {
	blinkerRect->visible  = false;
	clearSelection();
}

String UITextInput::getText() {
	
	if(!multiLine) {
		return lines[0].text;
	} else {
		String totalText = L"";
		for(int i=0; i < lines.size(); i++) {
				totalText += lines[i].text;
				if(i < lines.size()-1)
					totalText += L"\n";
		}	
		return totalText;
	}
}

void UITextInput::convertOffsetToActual(int lineOffset, int caretPosition, int *actualCaretPosition) {
	int actualLineOffset = wordWrapLines[lineOffset].actualLineNumber;

	if(wordWrapLines[lineOffset].isWordWrap == true) {
		int lineIndex = lineOffset;
		int totalActualCaretPosition = caretPosition - wordWrapLines[lineOffset].lineStart;		
		while((lineIndex >= 0) && (wordWrapLines[lineIndex].isWordWrap == true)) {
			lineIndex--;
			totalActualCaretPosition += wordWrapLines[lineIndex].text.size() - wordWrapLines[lineIndex].lineStart;			
		}
		*actualCaretPosition = totalActualCaretPosition;
	} else {
		*actualCaretPosition = caretPosition;
	}
	
	if((*actualCaretPosition) > lines[actualLineOffset].text.size()) {
		*actualCaretPosition = lines[actualLineOffset].text.size();
	}


}


void UITextInput::setActualToCaret() {
	convertOffsetToActual(lineOffset, caretPosition, &actualCaretPosition);
}

void UITextInput::convertActualToOffset(int actualLineOffset, int actualCaretPosition, int *lineOffset, int *caretPosition) {
	*lineOffset = lines[actualLineOffset].wordWrapLineIndex;
				
	int totalTextWidth = wordWrapLines[(*lineOffset)].text.size() - wordWrapLines[(*lineOffset)].lineStart;

	*caretPosition = actualCaretPosition;
	
	while(actualCaretPosition > totalTextWidth) {
		*caretPosition -= (wordWrapLines[(*lineOffset)].text.size() - wordWrapLines[(*lineOffset)].lineStart);
		(*lineOffset)++;
		if((*lineOffset) > wordWrapLines.size()-1) {
			(*lineOffset) = wordWrapLines.size()-1;
			break;
		}
		totalTextWidth += wordWrapLines[(*lineOffset)].text.size() - wordWrapLines[(*lineOffset)].lineStart;
	}
	*caretPosition += wordWrapLines[(*lineOffset)].lineStart;
}


void UITextInput::setOffsetToActual() {
	convertActualToOffset(actualLineOffset, actualCaretPosition, &lineOffset, &caretPosition);	
}

void UITextInput::updateCaretPosition() {
	// If this assertion fails, you likely called the function in the wrong
	// place in the constructor.	
	assert(bufferLines.size() && wordWrapLines.size());


	setOffsetToActual();


	if(lineOffset > wordWrapLines.size()-1) {
		lineOffset = wordWrapLines.size()-1;
		setActualLineOffset();
	}

	caretImagePosition = 0;
	if(caretPosition == 0) {
		caretImagePosition = 0;
	} else if(caretPosition > wordWrapLines[lineOffset].text.length()) {
		caretPosition = wordWrapLines[lineOffset].text.length();
		String caretSubString = wordWrapLines[lineOffset].text.substr(0,caretPosition);
		caretImagePosition = bufferLines[0]->getTextWidthForString(caretSubString);
	} else {
		String caretSubString = wordWrapLines[lineOffset].text.substr(0,caretPosition);
		caretImagePosition = bufferLines[0]->getTextWidthForString(caretSubString);
	}
	
	if(!hasSelection) {
		blinkerRect->visible  = true;
	}
	
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
			String subString = wordWrapLines[0].text.substr(0,horizontalCharacterScroll);
			horizontalPixelScroll = bufferLines[0]->getTextWidthForString(subString);
		}

		// Try scrolling right.
		while(caretImagePosition + blinkerRect->getWidth() > horizontalPixelScroll + textContainer->getWidth()) {
			horizontalCharacterScroll++;

			// Update pixel scroll from new character scroll.
			String subString = wordWrapLines[0].text.substr(0,horizontalCharacterScroll);
			horizontalPixelScroll = bufferLines[0]->getTextWidthForString(subString);
		}

		bufferLines[0]->setPosition(-horizontalPixelScroll, 0);
	}
	
	blinkerRect->setPosition(caretImagePosition + 1 -horizontalPixelScroll, (lineOffset * ( lineHeight+lineSpacing)));	
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

int UITextInput::lineOffsetToActualLineOffset(int lineOffset) {
	if(lineOffset < wordWrapLines.size()) {
		return wordWrapLines[lineOffset].actualLineNumber;
	} else {
		return 0;
	}
}

void UITextInput::setActualLineOffset() {
	actualLineOffset = lineOffsetToActualLineOffset(lineOffset);	
}

void UITextInput::dragSelectionTo(Number x, Number y) {
	x -= (padding * 2.0) + decoratorOffset;
	y -= padding;
	int lineOffset = y  / (lineHeight+lineSpacing);
	if(lineOffset > wordWrapLines.size()-1)
		lineOffset = wordWrapLines.size()-1;
	
	String selectToLine = wordWrapLines[lineOffset].text;
	
	int len = selectToLine.length();
	Number slen = 0;
	int caretPosition = bufferLines[0]->getTextWidthForString(selectToLine.substr(0,len)) - horizontalPixelScroll;
	for(int i=0; i < len; i++) {
		slen = bufferLines[0]->getTextWidthForString(selectToLine.substr(0,i)) - horizontalPixelScroll;
		if(slen > x) {
			caretPosition = i;
			break;
		}
	}
	if(x > slen)
		caretPosition = len;
			
	if(caretPosition < 0)
		caretPosition = 0;		

	int newActualCaret;
	convertOffsetToActual(lineOffset, caretPosition, &newActualCaret);

	setSelection(this->actualLineOffset, wordWrapLines[lineOffset].actualLineNumber, this->actualCaretPosition, newActualCaret);
		
	if(lineOffset > this->lineOffset) {	
		lineOffset += 1;
		if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) > scrollContainer->getHeight()-lineHeight-lineSpacing) {
					scrollContainer->setScrollValue(0.0, (((((lineOffset) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()-lineHeight-lineSpacing))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));
		}
	} else {
		if(lineOffset > 0) {
			lineOffset -= 1;
		}
		if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) < 0.0) {
			scrollContainer->setScrollValue(0.0, ((((lineOffset) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
		}		
	}
	
}

int UITextInput::caretSkipWordBack(int caretLine, int caretPosition) {
	for(int i=caretPosition; i > 0; i--) {
		String bit = lines[caretLine].text.substr(i,1);
		char chr = ((char*)bit.c_str())[0]; 		
		if(!isNumberOrCharacter(chr) && i < caretPosition-1) {
			return i+1;
		}
	}
    String bit = lines[caretLine].text;
    char chr = ((char*)bit.c_str())[0];
    if(isNumberOrCharacter(chr)) {
        return 0;
    } else {
        return 1;
    }
}

int UITextInput::caretSkipWordForward(int caretLine, int caretPosition) {
	int len = lines[caretLine].text.length();
	for(int i=caretPosition; i < len; i++) {
		String bit = lines[caretLine].text.substr(i,1);
		char chr = ((char*)bit.c_str())[0]; 
		if(!isNumberOrCharacter(chr) && i > caretPosition) {
			return i;
		}
	}
	return lines[caretLine].text.length();	
}

void UITextInput::selectWordAtCaret() {

	actualCaretPosition = caretSkipWordBack(actualLineOffset,actualCaretPosition);
	setOffsetToActual();
	clearSelection();			
	updateCaretPosition();
	
	setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, caretSkipWordForward(actualLineOffset, actualCaretPosition));					

	updateCaretPosition();	
}

void UITextInput::replaceAll(String what, String withWhat) {
	for(int i=0; i < lines.size(); i++) {
		lines[i].text = lines[i].text.replace(what, withWhat);
		changedText(i,i);
	}
}

std::vector<FindMatch> UITextInput::getFindMatches(String stringToFind) {
	std::vector<FindMatch> findMatches;
	
	for(int i=0; i < lines.size(); i++) {
		String lineText = lines[i].text;
		
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
	return findMatches;
}

void UITextInput::findString(String stringToFind, bool replace, String replaceString) {

	clearSelection();
	findMatches.clear();		
	findMatches = getFindMatches(stringToFind);
		
	if(findMatches.size() > 0) {

		if(replace) {
			FindMatch match = findMatches[findIndex];
			String oldText = lines[match.lineNumber].text;
			String newText = oldText.substr(0,match.caretStart) + replaceString + oldText.substr(match.caretEnd);
			
			lines[match.lineNumber].text = newText;
			findMatches[findIndex].caretEnd = findMatches[findIndex].caretStart + replaceString.length();
			changedText(match.lineNumber, match.lineNumber);
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
	_setSelectionColor(Color(0.5, 0.2, 0.4, 1.0));	
}

void UITextInput::setCaretToMouse(Number x, Number y) {
	clearSelection();
	x -= (padding) + decoratorOffset;
	y -= padding;
	//if(lines.size() > 1) {
		lineOffset = y  / (lineHeight+lineSpacing);
		if(lineOffset > wordWrapLines.size()-1)
			lineOffset = wordWrapLines.size()-1;
		setActualLineOffset();	
	//}
	
	int len = wordWrapLines[lineOffset].text.length();
	Number slen= 0;
	
	int newCaretPosition = -1;
	
	for(int i=1; i < len; i++) {
		slen = bufferLines[0]->getTextWidthForString(wordWrapLines[lineOffset].text.substr(0,i)) - horizontalPixelScroll;
		Number slen_prev = bufferLines[0]->getTextWidthForString(wordWrapLines[lineOffset].text.substr(0,i-1)) - horizontalPixelScroll;		
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
		
	setActualToCaret();
	updateCaretPosition();
}

void UITextInput::removeLines(unsigned int startIndex, unsigned int endIndex) {	

	int startLine = lines[startIndex].wordWrapLineIndex;
	int endLine = lines[endIndex].wordWrapLineIndex;	
	
	int actualLineNumber = endIndex;
	while(actualLineNumber == endIndex && endLine <= wordWrapLines.size()) {
		endLine++;
		if(endLine == wordWrapLines.size()) {
			break;
		} else {
			actualLineNumber = wordWrapLines[endLine].actualLineNumber;
		}
	}
	
	lines.erase(lines.begin()+startIndex, lines.begin()+(endIndex+1));
	wordWrapLines.erase(wordWrapLines.begin()+startLine, wordWrapLines.begin()+endLine);
	
	for(int i=startIndex; i < lines.size(); i++) {
		lines[i].wordWrapLineIndex -= (endLine-startLine);
	}
	
	for(int i=startLine; i < wordWrapLines.size(); i++) {
		wordWrapLines[i].actualLineNumber -= ((endIndex+1)-startIndex);
		wordWrapLines[i].dirty = true;
	}
	
	// always need an existing line
	if(lines.size() == 0) {
		actualLineOffset = -1;
		lineOffset = -1;
		insertLine();
	}
	
	
	renumberLines();
	restructLines();
	readjustBuffer();
}

void UITextInput::selectAll() {
	actualLineOffset = 0;
	actualCaretPosition = 0;
	selectionLine = lines.size()-1;
	
	setSelection(0, lines.size()-1, 0, lines[lines.size()-1].text.length());
}

void UITextInput::insertText(String text, bool updateWordWrap) {	

	vector<String> strings;
	if(multiLine) {
		strings = text.split("\n");
	} else {
		String singleLine = text.replace("\n", "");
		strings.push_back(singleLine);
	}
	
	settingText = true;

	if(hasSelection)
		deleteSelection();

	int startChangeOffset = actualLineOffset;
	
	if(strings.size() > 1) {
		String ctext = lines[actualLineOffset].text;
		String text2 = ctext.substr(actualCaretPosition, ctext.length()-actualCaretPosition);
		ctext = ctext.substr(0,actualCaretPosition);
		ctext += strings[0];
		lines[actualLineOffset].text = ctext;
		actualCaretPosition = ctext.length();
		
		for(int i=1; i < strings.size()-1; i++) {
			insertLine(strings[i]);
			ctext = strings[i];
			actualCaretPosition = ctext.length();			
		}
		
		insertLine();
		ctext = strings[strings.size()-1] + text2;
		actualCaretPosition = ctext.length();
		lines[actualLineOffset].text = ctext;
		
	} else {
		String newText = "";
		if(strings.size() > 0) {
			newText = strings[0];
		}
		String ctext = lines[actualLineOffset].text;
		String text2 = ctext.substr(actualCaretPosition, ctext.length()-actualCaretPosition);
		ctext = ctext.substr(0,actualCaretPosition);
		ctext += newText + text2;
		actualCaretPosition += newText.length();
		lines[actualLineOffset].text = ctext;
	}
	
	settingText = false;	

	if(updateWordWrap) {
		restructLines();	
		renumberLines();
		changedText(startChangeOffset, actualLineOffset);
		updateCaretPosition();	
	}
}

String UITextInput::getLineText(unsigned int index) {
	if(index < lines.size()) {
		return lines[index].text;
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
		totalText += lines[currentLine].text.substr(currentLeft, lines[currentLine].text.length()-currentLeft) + '\n';
		currentLine++;
		currentLeft = 0;
	}
	// Add the selection in the last line(no \n needed)
	totalText += lines[currentLine].text.substr(currentLeft, selectionR-currentLeft);

	return totalText;
}

void UITextInput::setSelectionColor(Color color) {
	selectionColor = color;
	_setSelectionColor(color);
}

void UITextInput::_setSelectionColor(Color color) {
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
	newState.caretPosition = actualCaretPosition;
	newState.lineOffset = actualLineOffset;
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

void UITextInput::setTextDiff(String text) {

	settingText = true;

	std::vector<String> strings = text.split("\n");
	
	int linesDiff = lines.size()-strings.size();
	
	// CHECK INSERTS
	int diffLineStart = -1;
	int diffLineEnd = -1;
	
	for(int i=0; i < strings.size(); i++) {
		if(i < lines.size()) {
			if(strings[i] != lines[i].text) {
				diffLineStart = i;
				break;
			}
		} else {
			diffLineStart = i;
			break;
		}
	}

	int linesOffset = lines.size()-1;	
	for(int i=strings.size()-1; i >= 0; i--, linesOffset--) {
		if(linesOffset >= 0) {
			if(strings[i] != lines[linesOffset].text) {
				diffLineEnd = i+1;
				break;
			}
		} else {
			diffLineEnd = i+1;
			break;
		}
	}
	
	if(diffLineEnd > strings.size()-1) {
		diffLineEnd = strings.size()-1;
	}

	int linesAdded = 0;	
	if(diffLineStart == -1 || diffLineEnd == -1) {
	} else {
	
		if(diffLineStart > diffLineEnd) {
			int tmp = diffLineEnd;
			diffLineEnd = diffLineStart;			
			diffLineStart = tmp;
		}
	
		if( diffLineEnd >= diffLineStart) {
			actualLineOffset = diffLineStart-1;
			if(actualLineOffset == -1) {
				lineOffset = -1;
			} else {
				lineOffset = lines[actualLineOffset].wordWrapLineIndex;
			}
			
			for(int i=diffLineStart; i <= diffLineEnd; i++) {
				insertLine(strings[i]);
				linesAdded++;
			}
			
			settingText = false;
			changedText(diffLineStart-1, diffLineEnd+1, false);
			
		} else {
		}
	}
	
	settingText = false;


	diffLineStart = -1;
	diffLineEnd = -1;	
	
	// CHECK REMOVES
	
	for(int i=0; i < lines.size(); i++) {
		if(i < strings.size()) {
			if(lines[i].text != strings[i]) {
				diffLineStart = i;
				break;
			}
		} else {
			diffLineStart = i;
			break;
		}
	}
	
	diffLineEnd = diffLineStart + (linesAdded + linesDiff) - 1;
	
	if(diffLineStart == -1 || diffLineEnd == -1) {
	} else {
		if( diffLineEnd >= diffLineStart) {		
			removeLines(diffLineStart, diffLineEnd);
			readjustBuffer();
		}
	}
	
	applyBlockOverrides();	
}

void UITextInput::setUndoState(UITextInputUndoState state) {
	clearSelection();
	if(multiLine) {
		setTextDiff(state.content);	
	} else {
		setText(state.content);
	}
	actualLineOffset = state.lineOffset;
	actualCaretPosition = state.caretPosition;
	updateCaretPosition();
	
	if(state.hasSelection) {
		setSelection(actualLineOffset, state.selectionLine, actualCaretPosition, state.selectionCaretPosition);
	}
	
	renumberLines();
	restructLines();		
	readjustBuffer();

	showCurrentLineIfOffscreen();
}

void UITextInput::showCurrentLineIfOffscreen() {
	if(!multiLine)
		return;
		
	int bufferOffset = -linesContainer->getPosition().y/ ( lineHeight+lineSpacing);	
	int heightInLines = (getHeight() / ( lineHeight+lineSpacing)) + 1;
			
	if(lines[actualLineOffset].wordWrapLineIndex > bufferOffset && lines[actualLineOffset].wordWrapLineIndex < bufferOffset + heightInLines) {
	
	} else {
		showLine(actualLineOffset, false);	
	}
}

void UITextInput::Undo() {
	if(undoStateIndex > 0) {
		if(undoStateIndex == maxRedoIndex) {
			saveUndoState();
			undoStateIndex -= 2;			
			setUndoState(undoStates[undoStateIndex]);			
		} else {
			undoStateIndex--;
			setUndoState(undoStates[undoStateIndex]);
		}
	}
}

void UITextInput::Redo() {
	if(undoStateIndex < MAX_TEXTINPUT_UNDO_STATES-1 && undoStateIndex < maxRedoIndex-1) {
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
            removeLines(lineOffset, lineOffset);
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
	String clip = CoreServices::getInstance()->getCore()->getClipboardString().replace("\r\n", "\n");
	clip = clip.replace("\r", "\n");
	insertText(clip);
}

void UITextInput::showLine(unsigned int lineNumber, bool top) {
	// If there's no scroll container, no need to adjust the line.
	
	int offsetLineNumber, offsetCaretPosition;
	convertActualToOffset(lineNumber, 0, &offsetLineNumber, &offsetCaretPosition);
	
	if(!multiLine) {
		return;
	}
	
	scrollContainer->setContentSize(getWidth(),  (((wordWrapLines.size()+1) * ((lineHeight+lineSpacing)))) + padding);

	if(top) {
		scrollContainer->setScrollValue(0.0, ((((offsetLineNumber) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
	} else {
		scrollContainer->setScrollValue(0.0, (((((offsetLineNumber) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()/2.0))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));	
	}
}

bool UITextInput::isNumberOrCharacter(wchar_t charCode) {

    if(charCode == '\t' || charCode == ' ') return false;
	if(charCode == '_') return true;

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
	
	CoreInput *input = CoreServices::getInstance()->getCore()->getInput();
	
	if(key == KEY_LEFT) {
		if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
			
				if(hasSelection) {
				
					int localLineOffset;
					int localCaretPosition;
					convertActualToOffset(selectionLine, selectionCaretPosition, &localLineOffset, &localCaretPosition);
	
					int newCaretPosition;				
					convertOffsetToActual(localLineOffset, wordWrapLines[localLineOffset].lineStart, &newCaretPosition);

					setSelection(actualLineOffset, selectionLine, actualCaretPosition, newCaretPosition);
				} else {
					int newCaretPosition;				
					convertOffsetToActual(lineOffset, wordWrapLines[lineOffset].lineStart, &newCaretPosition);
												
					setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, newCaretPosition);
				}
			} else {
				caretPosition = wordWrapLines[lineOffset].lineStart;
				clearSelection();				
				setActualToCaret();			
				updateCaretPosition();
			}
		} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				if(hasSelection) {
					setSelection(actualLineOffset, selectionLine, actualCaretPosition, caretSkipWordBack(selectionLine, selectionCaretPosition));
				} else {
					setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, caretSkipWordBack(actualLineOffset, actualCaretPosition));					
				}
			} else {				
				actualCaretPosition = caretSkipWordBack(actualLineOffset,actualCaretPosition);
				clearSelection();				
				updateCaretPosition();			
			}
		} else {
			if(actualCaretPosition > 0 || lineOffset > 0) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					// Holding down shift allows you to select with the arrow keys.
					if(hasSelection) {
						if(selectionCaretPosition > 0)
							setSelection(actualLineOffset, selectionLine, actualCaretPosition, selectionCaretPosition-1);
					} else {
						setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, max(actualCaretPosition-1, 0));
					}
				} else {
					int newLineStart = actualLineOffset;
					int newCaretPosition = actualCaretPosition;
					if(newCaretPosition > 0) {
						newCaretPosition--;
					} else if(newLineStart > 0) {
						newLineStart--;
						newCaretPosition = lines[newLineStart].text.length();
					}

					clearSelection();
					actualCaretPosition = newCaretPosition;
					actualLineOffset = newLineStart;
					updateCaretPosition();
				}
			}
		}
		return;
	}
	
	if(key == KEY_RIGHT) {
		if(input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
			if(caretPosition < wordWrapLines[lineOffset].text.length()) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				
					if(hasSelection) {
					
						int localLineOffset;
						int localCaretPosition;
						convertActualToOffset(selectionLine, selectionCaretPosition, &localLineOffset, &localCaretPosition);
					
						int newCaretPosition;	
						convertOffsetToActual(localLineOffset, wordWrapLines[localLineOffset].text.length(), &newCaretPosition);				
						
						setSelection(actualLineOffset, selectionLine, actualCaretPosition, newCaretPosition);
					} else {
						int newCaretPosition;				
						convertOffsetToActual(lineOffset, wordWrapLines[lineOffset].text.length(), &newCaretPosition);					
						setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, newCaretPosition);
					}
				} else {
					caretPosition = wordWrapLines[lineOffset].text.length();					
					clearSelection();
					setActualToCaret();
					updateCaretPosition();
				}
			}
		} else if (input->getKeyState(KEY_LALT) || input->getKeyState(KEY_RALT)) {
			if(actualCaretPosition < lines[actualLineOffset].text.length()) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					if(hasSelection) {
						setSelection(actualLineOffset, selectionLine, actualCaretPosition, caretSkipWordForward(selectionLine, selectionCaretPosition));
					} else {
						setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, caretSkipWordForward(actualLineOffset, actualCaretPosition));					
					}
				} else {				
					actualCaretPosition = caretSkipWordForward(actualLineOffset,actualCaretPosition);
					clearSelection();
					updateCaretPosition();										
				}
			}
		} else {
			if(actualCaretPosition < lines[actualLineOffset].text.length() || lineOffset + 1 < lines.size()) {
				if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
					// Holding down shift allows you to select with the arrow keys.
					if(hasSelection) {
						setSelection(actualLineOffset, selectionLine, actualCaretPosition, selectionCaretPosition+1);
					} else {
						setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, actualCaretPosition+1);
					}
				} else {
					clearSelection();

					int newLineEnd = actualLineOffset;
					int newCaretPosition = actualCaretPosition;
					if(newCaretPosition < lines[actualLineOffset].text.length()) {
						newCaretPosition++;
					} else if(newLineEnd + 1 < lines.size()) {
						newLineEnd++;
						newCaretPosition = 0;
					}
					actualCaretPosition = newCaretPosition;
					actualLineOffset = newLineEnd;
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

	if(key == KEY_HOME) {
		if (actualCaretPosition < lines[actualLineOffset].text.length() || lineOffset + 1 < lines.size()) {
			if (input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				// Holding down shift allows you to select with the arrow keys.
				if (hasSelection) {
					setSelection(actualLineOffset, selectionLine, actualCaretPosition, 0);
				} else {
					setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, 0);
				}
			} else {
				clearSelection();

				int newLineEnd = actualLineOffset;
				actualCaretPosition = 0;
				actualLineOffset = newLineEnd;
			}
			updateCaretPosition();
		}
		return;
	}
	
	if(key == KEY_END) {
		if (actualCaretPosition < lines[actualLineOffset].text.length() || lineOffset + 1 < lines.size()) {
			if (input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {
				// Holding down shift allows you to select with the arrow keys.
				if (hasSelection) {
					setSelection(actualLineOffset, selectionLine, actualCaretPosition, lines[selectionLine].text.length());
				} else {
					setSelection(actualLineOffset, actualLineOffset, actualCaretPosition, lines[actualLineOffset].text.length());
				}
			} else {
				clearSelection();

				int newLineEnd = actualLineOffset;
				actualCaretPosition = lines[actualLineOffset].text.length();
				actualLineOffset = newLineEnd;
			}
			updateCaretPosition();
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
					int selectionOffset, selectionCaret;
					convertActualToOffset(selectionLine, selectionCaretPosition, &selectionOffset, &selectionCaret);					
					if(selectionOffset > 0) {
						if(wordWrapLines[selectionOffset-1].actualLineNumber == selectionLine) {
							int actualAdjust;
							convertOffsetToActual(selectionOffset, selectionCaret, &actualAdjust);
							selectionCaret = actualAdjust - wordWrapLines[selectionOffset].text.length();
						}														
						setSelection(actualLineOffset, wordWrapLines[selectionOffset-1].actualLineNumber, actualCaretPosition, selectionCaret);
					}
				} else {
					if(lineOffset > 0) {
						int newActualCaretPosition;
						convertOffsetToActual(lineOffset-1, caretPosition, &newActualCaretPosition);
						setSelection(actualLineOffset, wordWrapLines[lineOffset-1].actualLineNumber, actualCaretPosition, newActualCaretPosition);
					}
				}
				
				// scroll up if selection going out of view 
				int selectionOffset, selectionCaret;
				convertActualToOffset(selectionLine, selectionCaretPosition, &selectionOffset, &selectionCaret);				
				if(linesContainer->getPosition().y + (selectionOffset*(lineHeight+lineSpacing)+padding) < 0.0) {
					scrollContainer->setScrollValue(0.0, ((((selectionOffset) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
				}							
			} else {
				clearSelection();				
				if(lineOffset > 0) {
					lineOffset--;
					setActualLineOffset();					
					setActualToCaret();
					updateCaretPosition();							
				}
				
				// scroll up if cursor going out of view 
				if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) < 0.0) {
					scrollContainer->setScrollValue(0.0, ((((lineOffset) * ((lineHeight+lineSpacing)))) + padding)/(scrollContainer->getContentSize().y-scrollContainer->getHeight()));
				}				
			}
		}
		if(!hasSelection) {
			blinkerRect->visible  = true;
		}
		return;
	}
	
	if(key == KEY_DOWN) {
		if(multiLine) {
			if(input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT)) {			
				if(hasSelection) {
					int selectionOffset, selectionCaret;
					convertActualToOffset(selectionLine, selectionCaretPosition, &selectionOffset, &selectionCaret);
				
					if(selectionOffset < wordWrapLines.size()-1) {						
						if(wordWrapLines[selectionOffset+1].actualLineNumber == selectionLine) {
							int actualAdjust;
							convertOffsetToActual(selectionOffset, selectionCaret, &actualAdjust);
							selectionCaret = actualAdjust + wordWrapLines[selectionOffset].text.length();
						}
						setSelection(actualLineOffset, wordWrapLines[selectionOffset+1].actualLineNumber, actualCaretPosition, selectionCaret);
					}
				} else {				
					if(lineOffset < wordWrapLines.size()-1) {
						int newActualCaretPosition;
						convertOffsetToActual(lineOffset+1, caretPosition, &newActualCaretPosition);					
						setSelection(actualLineOffset, wordWrapLines[lineOffset+1].actualLineNumber, actualCaretPosition, newActualCaretPosition);											
					}
				}
				
				// scroll down if selection going out of view 
				int selectionOffset, selectionCaret;
				convertActualToOffset(selectionLine, selectionCaretPosition, &selectionOffset, &selectionCaret);				
				if(linesContainer->getPosition().y + (selectionOffset*(lineHeight+lineSpacing)+padding) > scrollContainer->getHeight()-lineHeight-lineSpacing) {
					scrollContainer->setScrollValue(0.0, (((((selectionOffset) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()-lineHeight-lineSpacing))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));
				}
																
			} else {				
				clearSelection();
				if(lineOffset < wordWrapLines.size()-1) {
					lineOffset++;
					setActualLineOffset();
					setActualToCaret();					
					updateCaretPosition();										
				}
				
				// scroll down if cursor going out of view 			
				if(linesContainer->getPosition().y + (lineOffset*(lineHeight+lineSpacing)+padding) > scrollContainer->getHeight()-lineHeight-lineSpacing) {
					scrollContainer->setScrollValue(0.0, (((((lineOffset) * ((lineHeight+lineSpacing)))) + padding-(scrollContainer->getHeight()-lineHeight-lineSpacing))/(scrollContainer->getContentSize().y-scrollContainer->getHeight())));
				}				
			}			
		}
		if(!hasSelection) {
			blinkerRect->visible  = true;
		}
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
			insertLine();
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
	
	String ctext = lines[actualLineOffset].text;
	
	bool _changedText = false;
		
	if(((charCode > 31 && charCode < 127) || charCode > 127) && key != KEY_DELETE && key != KEY_HOME && key != KEY_END) {
		
		if(!isNumberOnly || (isNumberOnly && ((charCode > 47 && charCode < 58) || (charCode == '.' || charCode == '-')))) {
			if(!isNumberOrCharacter(charCode)) { 
				saveUndoState();
			} else if (!isTypingWord) {
				saveUndoState();
				isTypingWord = 1;
			}
			if(hasSelection)
				deleteSelection();
			ctext = lines[actualLineOffset].text;
			String text2 = ctext.substr(actualCaretPosition, ctext.length()-actualCaretPosition);
			ctext = ctext.substr(0,actualCaretPosition);
			ctext += charCode + text2;
			actualCaretPosition++;
			_changedText = true;
			
			showCurrentLineIfOffscreen();
		}
	}
	
	if(key == KEY_TAB && multiLine) {
		saveUndoState();
		if(hasSelection)
			deleteSelection();		
		ctext = lines[actualLineOffset].text;
		String text2 = ctext.substr(actualCaretPosition, ctext.length()-actualCaretPosition);
		ctext = ctext.substr(0,actualCaretPosition);
		ctext += (wchar_t)'\t' + text2;
		actualCaretPosition++;
		_changedText = true;		
	}
	
	if(key == KEY_DELETE) {
		if(hasSelection) {
			saveUndoState();
			deleteSelection();
			return;
		} else {
			ctext = lines[actualLineOffset].text;
			if(actualCaretPosition < ctext.length()) {
				if(ctext.length() > 0) {
					String text2 = ctext.substr(actualCaretPosition+1, ctext.length()-actualCaretPosition);
					ctext = ctext.substr(0,actualCaretPosition);
					ctext += text2;
					_changedText = true;
				} else {
					return;
				}
			} else {
				if(actualLineOffset < lines.size() - 1) {
					saveUndoState();
					lines[actualLineOffset].text = ctext + lines[actualLineOffset+1].text;
					removeLines(actualLineOffset+1, actualLineOffset+1);
					changedText(actualLineOffset, actualLineOffset);
					updateCaretPosition();
					return;
				} else {
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
	
	if(key == KEY_BACKSPACE) {
		if(hasSelection) {
			saveUndoState();
			deleteSelection();
			return;
		} else {
		ctext = lines[actualLineOffset].text;
		
		if(actualCaretPosition > 0) {
			saveUndoState();
			if(ctext.length() > 0) {
				String text2 = ctext.substr(actualCaretPosition, ctext.length()-actualCaretPosition);
				ctext = ctext.substr(0,actualCaretPosition-1);
				ctext += text2;
				actualCaretPosition--;
				_changedText = true;			
			}
		} else {
			if(actualLineOffset > 0) {
				saveUndoState();			
				actualLineOffset--;
				actualCaretPosition = lines[actualLineOffset].text.length();
				lines[actualLineOffset].text = lines[actualLineOffset].text + ctext;	
				removeLines(actualLineOffset+1, actualLineOffset+1);
				changedText(actualLineOffset, actualLineOffset);
				setOffsetToActual();
				updateCaretPosition();
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
	
	lines[actualLineOffset].text = ctext;
	
	if(_changedText) {
		changedText(actualLineOffset, actualLineOffset);
	}
	updateCaretPosition();
}

void UITextInput::Update() {
	resizeTimer += core->getElapsed();
	
    
    if(!multiLine) {
        inputRectSelected->visible = hasFocus;
        inputRect->visible = !hasFocus;
    }
    
	if(draggingSelection) {
		if(selectionDragMouse != dragMouseStart) {
			dragSelectionTo(selectionDragMouse.x, selectionDragMouse.y - linesContainer->getPosition().y);	
		}
	}
	
	if(resizeTimer > 0.2 && !didMultilineResize) {
		doMultilineResize();
	}
	
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

	textContainer->scissorBox.setRect(textContainer->getScreenPositionForMainCamera().x, textContainer->getScreenPositionForMainCamera().y, textContainer->getWidth(), textContainer->getHeight() + padding);
}

UITextInput::~UITextInput() {
	core->removeAllHandlersForListener(this);
	core->getInput()->removeAllHandlersForListener(this);
	delete blinkTimer;

	linesContainer->ownsChildren = true;
	if(!ownsChildren) {
		delete linesContainer;
		delete inputRect;
		delete lineNumberBg;
	}
}

LineColorInfo LineColorInfo::getColorInfoForRange(int start, int length) {
	LineColorInfo retInfo;
	for(int i=0; i < colors.size(); i++) {
		if(colors[i].rangeStart <= start + length && colors[i].rangeEnd >= start) {
			LineColorData newData;
			newData.color = colors[i].color;
			
			newData.rangeStart = colors[i].rangeStart - start;
			if(newData.rangeStart < 0) {
				newData.rangeStart = 0;		
			}

			newData.rangeStart = colors[i].rangeStart - start;
			if(newData.rangeStart < 0) {
				newData.rangeStart = 0;		
			}
			
			newData.rangeEnd = colors[i].rangeEnd - start;
			if(newData.rangeEnd < 0) {
				newData.rangeEnd = 0;		
			}

			newData.rangeEnd = colors[i].rangeEnd - start;
			if(newData.rangeEnd > length) {
				newData.rangeEnd = length;		
			}
			
//			if(newData.rangeStart != newData.rangeEnd)
				retInfo.colors.push_back(newData);
		}
	}
	return retInfo;
}

std::vector<TextColorPair> UITextInput::splitTokens(String stringToSplit, LineColorInfo *stringColorInfo) {
    std::vector<TextColorPair> result;	
	
    size_t pos = 0, lastPos = 0;
    while ((pos = stringToSplit.find_first_of(";,| .():-+/*", lastPos)) != string::npos)
    {
		TextColorPair chunk;
		chunk.text = stringToSplit.contents.substr(lastPos, pos-lastPos+1);
		if(stringColorInfo) {
			chunk.colorInfo = stringColorInfo->getColorInfoForRange(lastPos, pos-lastPos+1);
		}
        result.push_back(chunk);
        lastPos = pos+1;
    }
	TextColorPair chunk;
	chunk.text = stringToSplit.contents.substr(lastPos);
	if(stringColorInfo) {
		chunk.colorInfo = stringColorInfo->getColorInfoForRange(lastPos, stringToSplit.size()-lastPos);
	}

    result.push_back(chunk);
    return result;
}

std::vector<TextColorPair> UITextInput::makeWordWrapBuffer(LineInfo *lineInfo, String indentPrefix) {

	String text = lineInfo->text;
	std::vector<TextColorPair> retVec;
	
	if(bufferLines[0]->getTextWidthForString(text) < getWidth() - decoratorOffset - padding) {
			return retVec;
	}		
	
	LineColorInfo *stringColorInfo = &lineInfo->colorInfo;
	
	std::vector<TextColorPair> parts = splitTokens(text, stringColorInfo);

	String checkString;
	LineColorInfo colorInfo;	
	
	if(parts.size() == 1) {
		TextColorPair pair;
		pair.text = text;
		pair.colorInfo = lineInfo->colorInfo;
		retVec.push_back(pair);
	} else {
	
		for(int i=0; i < parts.size(); i++) {
			String _checkString = checkString + parts[i].text;
			if(bufferLines[0]->getTextWidthForString(indentPrefix+_checkString) > getWidth() - decoratorOffset - padding) {
				if(retVec.size() == 0) {
					TextColorPair pair;
					pair.text = checkString;
					pair.colorInfo = colorInfo;
					retVec.push_back(pair);
				} else {
					TextColorPair pair;
					pair.text = indentPrefix+checkString;
					pair.colorInfo = colorInfo;
					for(int c=0; c < pair.colorInfo.colors.size(); c++) {
						pair.colorInfo.colors[c].rangeStart += indentPrefix.size();
						pair.colorInfo.colors[c].rangeEnd += indentPrefix.size();
					}
					
					retVec.push_back(pair);
				}
				checkString = "";
				colorInfo = LineColorInfo();				
			}						
			for(int c=0; c < parts[i].colorInfo.colors.size(); c++) {
				parts[i].colorInfo.colors[c].rangeStart += checkString.size();
				parts[i].colorInfo.colors[c].rangeEnd += checkString.size();
			}
			
			checkString = checkString + parts[i].text;			
			colorInfo.colors.insert(colorInfo.colors.end(), parts[i].colorInfo.colors.begin(), parts[i].colorInfo.colors.end() );
		}
				
		if(retVec.size() == 0) {
			TextColorPair pair;
			pair.text = checkString;
			pair.colorInfo = lineInfo->colorInfo;			
			retVec.push_back(pair);				
		} else {
			TextColorPair pair;
			pair.text = indentPrefix+checkString;
			pair.colorInfo = colorInfo;		
			for(int c=0; c < pair.colorInfo.colors.size(); c++) {
				pair.colorInfo.colors[c].rangeStart += indentPrefix.size();
				pair.colorInfo.colors[c].rangeEnd += indentPrefix.size();
			}
			
			retVec.push_back(pair);				
		}
	}
	
	return retVec;
}

void UITextInput::updateWordWrap(int lineStart, int lineEnd) {

	if(!multiLine) {
		wordWrapLines.clear();
		WordWrapLine line;
		line.text = lines[0].text;
		line.isWordWrap = false;		
		line.actualLineNumber = 0;
		line.lineStart = 0;
		wordWrapLines.push_back(line);
		lines[0].wordWrapLineIndex = 0;
		readjustBuffer(0, 0);		
		return;
	}

	int wordWrapRangeBegin = lines[lineStart].wordWrapLineIndex;
	int wordWrapRangeEnd = lines[lineEnd].wordWrapLineIndex;

	if(wordWrapRangeBegin == -1) {
		wordWrapRangeBegin = 0;
	}

	if(wordWrapRangeEnd == -1) {
		wordWrapRangeEnd = wordWrapLines.size()-1;
	}

	if(wordWrapLines.size()) {
		do {
			wordWrapRangeEnd++;
		}
		// put wordWrapLines[wordWrapRangeEnd] at the end, as wordWrapRangeEnd is "1" and throws an assertation in debug|win32|vc2012 if wordWrapLines.size() is "1"
		while(wordWrapRangeEnd < wordWrapLines.size() && wordWrapLines[wordWrapRangeEnd].isWordWrap);
		
		wordWrapLines.erase(wordWrapLines.begin()+wordWrapRangeBegin, wordWrapLines.begin()+wordWrapRangeEnd);
	}
	
	int insertPoint = wordWrapRangeBegin;
	
	for(int i=lineStart; i < lineEnd+1; i++) {
		String indentPrefix = lines[i].text.substr(0, lines[i].text.contents.find_first_not_of(" \t", 0));
		
		std::vector<TextColorPair> wrapLines = makeWordWrapBuffer(&lines[i], indentPrefix);
		if(wrapLines.size() > 0) {
			for(int j=0; j < wrapLines.size(); j++) {
				WordWrapLine line;
				line.text = wrapLines[j].text;
				if(j == 0) {
					line.isWordWrap = false;
					line.lineStart = 0;
					lines[i].wordWrapLineIndex = insertPoint;
				} else {
					line.isWordWrap = true;
					line.lineStart = indentPrefix.size();
				}
				line.actualLineNumber = i;
				line.blockOverrideToken = lines[i].blockOverrideToken;
				line.colorInfo = wrapLines[j].colorInfo;
				wordWrapLines.insert(wordWrapLines.begin()+insertPoint, line);
				insertPoint++;
			}
		} else {
				WordWrapLine line;		
				line.text = lines[i].text;
				line.isWordWrap = false;
				line.actualLineNumber = i;
				line.lineStart = 0;
				lines[i].wordWrapLineIndex = insertPoint;
				line.colorInfo = lines[i].colorInfo;		
				line.blockOverrideToken = lines[i].blockOverrideToken;
				wordWrapLines.insert(wordWrapLines.begin()+insertPoint, line);
				insertPoint++;				
		}
	}
	
	int actualLineNumber = wordWrapLines[insertPoint-1].actualLineNumber;
	for(int i=insertPoint; i < wordWrapLines.size(); i++) {
		if(!wordWrapLines[i].isWordWrap) {
			actualLineNumber++;		
			lines[actualLineNumber].wordWrapLineIndex = i;		
		}
	}
								
	readjustBuffer(wordWrapRangeBegin, wordWrapRangeEnd);
}

void UITextInput::readjustBuffer(int lineStart, int lineEnd) {

	if(scrollContainer) {
		scrollContainer->getVScrollBar()->setTickSize((UI_TEXT_INPUT_SCROLL_SPEED * lineHeight) / scrollContainer->getContentSize().y);
	}
	
	if(lineEnd == -1) {
		lineEnd = wordWrapLines.size()-1;
	}

	int bufferOffset = -linesContainer->getPosition().y/ ( lineHeight+lineSpacing);	
	Number bufferLineOffset = bufferOffset * ( lineHeight+lineSpacing);	

	for(int i=0; i < bufferLines.size(); i++) {
		if(bufferOffset + i < wordWrapLines.size()) {	
		if(wordWrapLines[bufferOffset+i].dirty || wordWrapLines[bufferOffset+i].lastBufferIndex != i || wordWrapLines[bufferOffset+i].text != bufferLines[i]->getText()) { 
		bufferLines[i]->getLabel()->clearColors();
		wordWrapLines[bufferOffset+i].dirty = false;
		wordWrapLines[bufferOffset+i].lastBufferIndex = i;
		
			if(wordWrapLines[bufferOffset+i].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_NO_OVERRIDE && wordWrapLines[bufferOffset+i].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_END && wordWrapLines[bufferOffset+i].blockOverrideToken.overrideType != SyntaxHighlightToken::TOKEN_TYPE_OVERRIDE_START) {

				bufferLines[i]->getLabel()->setColorForRange(wordWrapLines[bufferOffset+i].blockOverrideToken.color, 0, wordWrapLines[bufferOffset+i].text.size()-1);
				bufferLines[i]->setColor(1.0, 1.0, 1.0, 1.0);			
			} else {
			for(int j=0; j < wordWrapLines[bufferOffset+i].colorInfo.colors.size(); j++) {
				bufferLines[i]->getLabel()->setColorForRange(wordWrapLines[bufferOffset+i].colorInfo.colors[j].color, wordWrapLines[bufferOffset+i].colorInfo.colors[j].rangeStart, wordWrapLines[bufferOffset+i].colorInfo.colors[j].rangeEnd);
				bufferLines[i]->setColor(1.0, 1.0, 1.0, 1.0);
			}
			}		
			}
//			if(bufferOffset+i >= lineStart && bufferOffset+i <= lineEnd) {			
				bufferLines[i]->setText(wordWrapLines[bufferOffset+i].text);
//			}
			bufferLines[i]->visible = true;
		} else {
			bufferLines[i]->visible = false;
		}
		bufferLines[i]->setPosition(-horizontalPixelScroll, bufferLineOffset + (i*(lineHeight+lineSpacing)),0.0f);
	}

	for(int i=0; i < numberLines.size(); i++) {
	
	
		if(bufferOffset + i < wordWrapLines.size()) {
		if(lineNumbersEnabled) {	
		
//			if(bufferOffset+i >= lineStart && bufferOffset+i <= lineEnd) {												
				numberLines[i]->setText(String::IntToString(wordWrapLines[bufferOffset+i].actualLineNumber+1));
				int textWidth = ceil(numberLines[i]->getWidth());			
				numberLines[i]->setPosition(-textWidth,padding + bufferLineOffset + (i*(lineHeight+lineSpacing)),0.0f);		
//			}
			
			if(wordWrapLines[bufferOffset+i].isWordWrap) {
				numberLines[i]->visible = false;			
			} else {
				numberLines[i]->visible = true;
			}
		}
		} else {
			numberLines[i]->visible = false;		
		}
		
	}

}


void UITextInput::handleEvent(Event *event) {

	if(event->getDispatcher() == core->getInput()) {
		if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
			InputEvent *inputEvent = (InputEvent*) event;
			onKeyDown(inputEvent->key, inputEvent->charCode);
		}
		if (event->getEventCode() == InputEvent::EVENT_MOUSEUP) {
			draggingSelection = false;
		}
	}

	if(event->getDispatcher() == contextMenu) {
		UIMenuItem *item = contextMenu->getSelectedItem();
		if(item->_id == "copy") {
			Copy();
		} else if(item->_id == "cut") {
			Cut();
		} else if(item->_id == "paste") {
			Paste();
		} else if(item->_id == "select_all") {
			selectAll();
		}
	}


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
			readjustBuffer();
		}
	}

	if(event->getDispatcher() == inputRect) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:			
				if(((InputEvent*)event)->getMouseButton() == CoreInput::MOUSE_BUTTON2) {
					if(globalMenuSingleton) {
						contextMenu = globalMenuSingleton->showMenuAtMouse(100);

						contextMenu->addOption("Copy", "copy");
						contextMenu->addOption("Cut", "cut");
						contextMenu->addOption("Paste", "paste");
						contextMenu->addDivider();
						contextMenu->addOption("Select All", "select_all");	
						contextMenu->fitToScreenVertical();
						contextMenu->addEventListener(this, UIEvent::OK_EVENT);
						return;						
					}
				} else {
					focusSelf();
					setCaretToMouse(((InputEvent*)event)->mousePosition.x, ((InputEvent*)event)->mousePosition.y - linesContainer->getPosition().y);
					selectionDragMouse = ((InputEvent*)event)->mousePosition;				
					dragMouseStart = ((InputEvent*)event)->mousePosition;
					draggingSelection = true;
				}
			break;
			case InputEvent::EVENT_MOUSEWHEEL_UP:
				if(scrollContainer) {
					scrollContainer->_onMouseWheelUp();
				}
			break;
			case InputEvent::EVENT_MOUSEWHEEL_DOWN:
				if(scrollContainer) {
					scrollContainer->_onMouseWheelDown();
				}
			break;
			case InputEvent::EVENT_DOUBLECLICK:
				selectWordAtCaret();
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_TEXT);			
				if(draggingSelection) {
					selectionDragMouse = ((InputEvent*)event)->mousePosition;
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
	
    UIElement::handleEvent(event);
}

void UITextInput::onGainFocus() {
    blinkerRect->visible  = true;
    blinkTimer->Reset();
    if(!multiLine) {
        selectAll();
    }
}

void UITextInput::shiftText(bool left) {
	if (multiLine && (hasSelection || lines[lineOffset].text != "")) {
		saveUndoState();
		
		String t = (wchar_t)'\t';
		
		if (hasSelection) {
			for (int i = selectionTop; i <= selectionBottom; i++) {
				if (i == selectionBottom && selectionCaretPosition <= 0)
					// at least one character of bottom line needs to be selected before indenting, so...
					break;
				if (indentType == INDENT_TAB) {
					if (left) {
						if (lines[i].text.substr(0,1) == t) {
							lines[i].text = lines[i].text.substr(1, lines[i].text.length()-1);
							caretPosition--;
						}
					} else {
						lines[i].text = t + lines[i].text;
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
					if (lines[lineOffset].text.substr(0,1) == t) {
						lines[lineOffset].text = lines[lineOffset].text.substr(1, lines[lineOffset].text.length()-1);
						caretPosition--;
					}
				} else {
					lines[lineOffset].text = t + lines[lineOffset].text;
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
		
		changedText(selectionTop, selectionBottom);
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