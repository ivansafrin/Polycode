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
			UITextInput(bool multiLine, float width, float height);
			~UITextInput();
		
			void handleEvent(Event *event);
			void Update();
			
			void setText(wstring text);
			wstring getText();
			void onLoseFocus();
		
			int insertLine(bool after);
			
			void onKeyDown(TAUKey key, wchar_t charCode);
		
			void clearSelection();
			void setSelection(int lineStart, int lineEnd, int colStart, int colEnd);
				
			void deleteSelection();		
			void selectAll();
		
			void Resize(int x, int y);
		
			wstring getSelectionText();
			void insertText(wstring text);
		
		protected:
		
			int caretSkipWordBack(int caretLine, int caretPosition);
			int caretSkipWordForward(int caretLine, int caretPosition);
		
			void selectLineFromOffset();
			void updateCaretPosition();
			void setCaretToMouse(float x, float y);
			void dragSelectionTo(float x, float y);		
		
			void selectWordAtCaret();
		
			void restructLines();
			void removeLine(ScreenLabel *line);
		
			ScreenShape *selectorRectTop;
			ScreenShape *selectorRectMiddle;
			ScreenShape *selectorRectBottom;		
			int numLines;
			
			float padding;
			float lineSpacing;
		
			int selectionTop;
			int selectionBottom;
			int selectionL;
			int selectionR;		
		
			int selectionCaretPosition;
			int selectionLine;
		
			bool draggingSelection;
			bool hasSelection; 
			float caretX,caretY;
		
			int caretPosition;
			bool doSelectToCaret;
		
			bool multiLine;
			Timer *blinkTimer;
			UIBox *inputRect;
			ScreenShape *blinkerRect;
		
			float caretImagePosition;
		
			string fontName;
			float fontSize;
		
			float lineHeight;
		
			int lineOffset;
			ScreenLabel *currentLine;		
			vector<ScreenLabel*> lines;
			
	};
}