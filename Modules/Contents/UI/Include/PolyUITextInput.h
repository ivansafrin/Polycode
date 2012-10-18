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

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenLabel.h"
#include "PolyScreenShape.h"
#include "PolyFontManager.h"
#include "PolyFont.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"
#include "PolyUIElement.h"
#include "PolyTimer.h"
#include "PolyCoreInput.h"
#include "PolyCore.h"
#include <vector>
#include "PolyUIScrollContainer.h"

using namespace std;

#define MAX_TEXTINPUT_UNDO_STATES 30

namespace Polycode {

	class UITextInputUndoState {
		public:
			String content;
			unsigned int lineOffset;
			unsigned int caretPosition;
			bool hasSelection;			
			int selectionLine;
			int selectionCaretPosition;
	};
	
	class _PolyExport SyntaxHighlightToken {
		public:
			SyntaxHighlightToken(String text, int type) { this->text = text; this->type = type; }
			Color color;
			String text;
			unsigned int type;
	};
	
	class _PolyExport UITextInputSyntaxHighlighter {
		public:		
			virtual std::vector<SyntaxHighlightToken> parseText(String text) = 0;
	};

	class _PolyExport UITextInput : public UIElement {
		public:
			UITextInput(bool multiLine, Number width, Number height);
			~UITextInput();
		
			void handleEvent(Event *event);
			void Update();
			
			void setText(String text);
			String getText();
			void onLoseFocus();
		
			int insertLine(bool after);
		
			void changedText();
			
			void onKeyDown(PolyKEY key, wchar_t charCode);
		
			void clearSelection();
			void setSelection(int lineStart, int lineEnd, int colStart, int colEnd);
				
			void deleteSelection();		
			void selectAll();
		
			void Undo();
			void Redo();
			void Cut();
			void Copy();
			void Paste();
			
			void showLine(unsigned int lineNumber, bool top);

			void setSyntaxHighlighter(UITextInputSyntaxHighlighter *syntaxHighliter);
					
			void Resize(Number width, Number height);
			
			void setNumberOnly(bool val);
		
			String getSelectionText();
			void insertText(String text);
			
			UIScrollContainer *getScrollContainer();
		
		protected:
				
			void setUndoState(UITextInputUndoState state);
			void saveUndoState();
		
			bool isNumberOnly;
		
			int caretSkipWordBack(int caretLine, int caretPosition);
			int caretSkipWordForward(int caretLine, int caretPosition);
		
			void selectLineFromOffset();
			void updateCaretPosition();
			void setCaretToMouse(Number x, Number y);
			void dragSelectionTo(Number x, Number y);		
		
			void selectWordAtCaret();
		
			void restructLines();
			void removeLine(ScreenLabel *line);
		
			ScreenShape *selectorRectTop;
			ScreenShape *selectorRectMiddle;
			ScreenShape *selectorRectBottom;		
			int numLines;
			
			bool needFullRedraw;
			
			Number padding;
			Number lineSpacing;
		
			int selectionTop;
			int selectionBottom;
			int selectionL;
			int selectionR;		
		
			bool settingText;
		
			int selectionCaretPosition;
			int selectionLine;
		
			bool draggingSelection;
			bool hasSelection; 
			Number caretX,caretY;
		
			int caretPosition;
			bool doSelectToCaret;
			
			UITextInputSyntaxHighlighter *syntaxHighliter;
		
			ScreenEntity *linesContainer;
			
			vector<ScreenLabel*> linesToDelete;		
			
			UITextInputUndoState undoStates[MAX_TEXTINPUT_UNDO_STATES];
			int undoStateIndex;
			int maxRedoIndex;
		
			bool multiLine;
			Timer *blinkTimer;
			UIBox *inputRect;
			ScreenShape *blinkerRect;
		
			Number caretImagePosition;
			
			UIScrollContainer *scrollContainer;
		
			String fontName;
			Number fontSize;
		
			Number lineHeight;
		
			int lineOffset;
			ScreenLabel *currentLine;		
			vector<ScreenLabel*> lines;
			
	};
}