/*
 *  PolyUITextInput.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenLabel.h"
#include "PolyScreenShape.h"
#include "PolyFont.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"
#include <vector>

using namespace std;

namespace Polycode {

	class _PolyExport UITextInput : public ScreenEntity {
		public:
			UITextInput(bool multiLine, Number width, Number height);
			~UITextInput();
		
			void handleEvent(Event *event);
			void Update();
			
			void setText(String text);
			String getText();
			void onLoseFocus();
		
			int insertLine(bool after);
		
			
			void onKeyDown(TAUKey key, wchar_t charCode);
		
			void clearSelection();
			void setSelection(int lineStart, int lineEnd, int colStart, int colEnd);
				
			void deleteSelection();		
			void selectAll();
		
			void Resize(int x, int y);
		
			String getSelectionText();
			void insertText(String text);
		
		protected:
		
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
			
			Number padding;
			Number lineSpacing;
		
			int selectionTop;
			int selectionBottom;
			int selectionL;
			int selectionR;		
		
			int selectionCaretPosition;
			int selectionLine;
		
			bool draggingSelection;
			bool hasSelection; 
			Number caretX,caretY;
		
			int caretPosition;
			bool doSelectToCaret;
		
			bool multiLine;
			Timer *blinkTimer;
			UIBox *inputRect;
			ScreenShape *blinkerRect;
		
			Number caretImagePosition;
		
			String fontName;
			Number fontSize;
		
			Number lineHeight;
		
			int lineOffset;
			ScreenLabel *currentLine;		
			vector<ScreenLabel*> lines;
			
	};
}