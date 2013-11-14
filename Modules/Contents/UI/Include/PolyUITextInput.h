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
#include "PolySceneLabel.h"
#include "PolyScenePrimitive.h"
#include "PolyFontManager.h"
#include "PolyFont.h"
#include "PolyEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"
#include "PolyUIMenu.h"
#include "PolyUIElement.h"
#include "PolyTimer.h"
#include "PolyCoreInput.h"
#include "PolyCore.h"
#include <vector>
#include "PolyUIScrollContainer.h"

using namespace std;

#define MAX_TEXTINPUT_UNDO_STATES 30
#define UI_TEXT_INPUT_SCROLL_SPEED 70.0

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
			SyntaxHighlightToken() {
				overrideType = TOKEN_TYPE_NO_OVERRIDE;
			}
			
			SyntaxHighlightToken(String text, int type) { this->text = text; this->type = type; overrideType = TOKEN_TYPE_NO_OVERRIDE; }
			Color color;
			String text;
			int overrideType;
			unsigned int type;
			
			static const int TOKEN_TYPE_NO_OVERRIDE = 0;
			static const int TOKEN_TYPE_OVERRIDE_START = 1;
			static const int TOKEN_TYPE_OVERRIDE_END = 2;
			static const int TOKEN_TYPE_OVERRIDE_LINE = 3;						
	};

	class _PolyExport LineColorData {
		public:
			LineColorData() {}
			LineColorData(Color color, unsigned int rangeStart, unsigned int rangeEnd) {
				this->color = color;
				this->rangeStart = rangeStart;
				this->rangeEnd = rangeEnd;
			}
			Color color;
			int rangeStart;
			int rangeEnd;
	};
	
	class _PolyExport LineColorInfo {
		public:
			std::vector<LineColorData> colors;
			LineColorInfo getColorInfoForRange(int start, int length);
	};
		
	class _PolyExport UITextInputSyntaxHighlighter {
		public:		
			virtual std::vector<SyntaxHighlightToken> parseText(String text, SyntaxHighlightToken overrideToken) = 0;
	};

	class _PolyExport FindMatch {
		public:
			unsigned int lineNumber;
			unsigned int caretStart;
			unsigned int caretEnd;							
	};
	
	class WordWrapLine {
		public:
			WordWrapLine() {
				lastBufferIndex = -1;
				dirty = true;
			}
			String text;
			bool isWordWrap;
			int actualLineNumber;
			int lineStart;
			int lastBufferIndex;
			LineColorInfo colorInfo;
			bool dirty;
			SyntaxHighlightToken blockOverrideToken;			
	};
	
	class TextColorPair {
		public:
			LineColorInfo colorInfo;
			String text;
	};

	class LineInfo {
		public:
			LineInfo(){ wordWrapLineIndex = -1; }
			String text;
			int wordWrapLineIndex;
			LineColorInfo colorInfo;			
			SyntaxHighlightToken blockOverrideToken;
	};

	/**
	 * A text input element. Can be single- or multiline.
	 */
	class _PolyExport UITextInput : public UIElement {
		public:
			/**
			 * Create a new text input element.
			 * @param multiLine Whether the text field should consist of a single line,
			 *                  or of a multiline text editor with vertical scroll bar.
			 * @param width The width of the element.
			 * @param height The height of the element.
			 */
			UITextInput(bool multiLine, Number width, Number height);
			virtual ~UITextInput();
		
			void handleEvent(Event *event);
			void Update();
			
			/**
			 * Set the text contents of the input.
			 *
			 * If the input is single-line, insert the complete text into
			 * the line, without taking linebreaks into account.
			 *
			* If the input is multi-line, each line is inserted separately
			 * into the text field
			 *
			 * @param text The new text contents.
			 * @param sendChangeEvent If true (default), will send out an Event::CHANGE_EVENT 
			 */
			void setText(String text, bool sendChangeEvent = true);

			/**
			 * Returns the text contents of this element.
			 *
			 * For single-line, returns the contents of the first line.
			 * For multi-line, returns a string containing each line in
			 * the text field, separated by '\n'.
			 */
			String getText();
			void onLoseFocus();
		
			/**
			 * Insert a linebreak after the cursor and move
			 * the cursor to the new line.
			 *
			 * @param after Unused. This must be true.
			 */
			int insertLine(String lineText = "");

			void onKeyDown(PolyKEY key, wchar_t charCode);
		
			/**
			 * Clear the current selection.
			 */
			void clearSelection();

			/**
			 * Set the currentselection.
			 *
			 * If (lineStart, colStart) is further "right" or "down" than (lineEnd, colEnd),
			 * the two will automatically be swapped. It's thus enough to specify the two "edges"
			 * of the selection, without knowing which comes first.
			 *
			 * @param lineStart The line position of one edge of the selection.
			 * @param colStart The column position of one edge of the selection.
			 * @param lineEnd The line position of the other edge of the selection.
			 * @param colEnd The column position of the other edge of the selection.
			 */
			void setSelection(int lineStart, int lineEnd, int colStart, int colEnd);

			/**
			 * Remove the currently selected text from the text contents.
			 */
			void deleteSelection();

			/**
			 * Select the entire text contents.
			 */
			void selectAll();
		
			/**
			 * Reset the text contents and selection/caret to
			 * the last undo state.
			 */
			void Undo();

			/**
			 * Reset the text contents and selection/caret to
			 * the next undo state.
			 */
			void Redo();

			/**
			 * Remove the current selection and copy it to the clipboard.
			 */
			void Cut();

			/**
			 * Copy the current selection to the clipboard.
			 */
			void Copy();

			/**
			 * Replace the current selection with the contents of the clipboard.
			 */
			void Paste();
			
			/**
			 * Toggle line number display for each line.
			 * @param val true to enable, false to disable.
			 */
			void enableLineNumbers(bool val);
			
			/**
			 * Set the color of the text field background.
			 */
			void setBackgroundColor(Color color);

			/**
			 * Set the background color for selected text.
			 */
			void setSelectionColor(Color color);

			/**
			 * Set the color of the cursor.
			 */
			void setCursorColor(Color color);

			/**
			 * Set the foreground color of displayed text.
			 */
			void setTextColor(Color color);

			/**
			 * Set the foreground color of line numbers.
			 */
			void setLineNumberColor(Color color);
			
			void checkBufferLines();
			
			/**
			 * Find and replace in the text contents.
			 *
			 * @param what The string to find.
			 * @param withWhat The string to replace each occurrence with.
			 */
			void replaceAll(String what, String withWhat);
			
			/**
			 * Find and optionally replace a string.
			 *
			 * Sets the current selection to the first result. All results will be stored as instances of FindMatch
			 * in this->findMatches, and can later be retrieved with findNext(), findPrevious() and findCurrent().
			 *
			 * @param stringToFind The string to find occurrences of.
			 * @param replace Whether to replace occurrences with something.
			 * @param replaceString The string to replace occurrences with, only used if replace=true
			 */
			void findString(String stringToFind, bool replace=false, String replaceString="");

			std::vector<FindMatch> getFindMatches(String stringToFind);

			/**
			 * Set the current find result to the next one in the result list and select it
			 * in the text field.
			 */
			void findNext();

			/**
			 * Set the current find result to the previous one in the result list and select it
			 * in the text field.
			 */
			void findPrevious();

			/**
			 * Set the selection to the current result in the result list.
			 */
			void findCurrent();
			
			void showLine(unsigned int lineNumber, bool top);

			/**
			 * Set the syntax highlighter to use for formatting text.
			 *
			 * @param syntaxHighlighter The syntax highlighter instance to use.
			 */
			void setSyntaxHighlighter(UITextInputSyntaxHighlighter *syntaxHighlighter);
					
			void Resize(Number width, Number height);
			
			/**
			 * Toggles whether this input accepts only numbers.
			 *
			 * @param val true to only accept numbers, false otherwise.
			 */
			void setNumberOnly(bool val);
		
			/**
			 * Return the contents of a line.
			 *
			 * @param index The index of the line to get the contents of.
			 *              First line has index 0.
			 */
			String getLineText(unsigned int index);
			
			/**
			 * Return the currently selected text.
			 */
			String getSelectionText();

			/**
			 * Replace the current selection with the given text.
			 *
			 * @param text The string to insert.
			 */
			void insertText(String text, bool updateWordWrap = true);
			
			void setCaretPosition(int position);
			
			UIScrollContainer *getScrollContainer();
			
			bool useStrongHinting;
        
            void shiftText(bool left=false);
            void convertIndentToTabs();
            void convertIndentToSpaces();
			
			void doMultilineResize();
						
			static void setMenuSingleton(UIGlobalMenu *_globalMenu);
					
		protected:
		
			static UIGlobalMenu *globalMenuSingleton;
		
			void showCurrentLineIfOffscreen();
		
			void readjustBuffer(int lineStart=0, int lineEnd=-1);
			void updateWordWrap(int lineStart, int lineEnd);
			
			Number resizeTimer;

			Entity *lineNumberAnchor;
		
			void renumberLines();
			bool isNumberOrCharacter(wchar_t charCode);			
		
			bool lineNumbersEnabled;
		
			Color textColor;
			Color lineNumberColor;
				
			void setUndoState(UITextInputUndoState state);
			void saveUndoState();
			
			void setTextDiff(String text);
		
			bool isNumberOnly;
			
			void changedText(int lineStart, int lineEnd, bool sendChangeEvent = true);
			void applySyntaxFormatting(int startLine, int end);
			
			void applyTokenOverride(int lineIndex, SyntaxHighlightToken overrideToken);
			
			void setActualToCaret();
			void setOffsetToActual();
			
			void convertOffsetToActual(int lineOffset, int caretPosition, int *actualCaretPosition);
			
			void convertActualToOffset(int actualLineOffset, int actualCaretPosition, int *lineOffset, int *caretPosition);
					
			int caretSkipWordBack(int caretLine, int caretPosition);
			int caretSkipWordForward(int caretLine, int caretPosition);
		
			int lineOffsetToActualLineOffset(int lineOffset);
			void setActualLineOffset();
			void updateCaretPosition();
			void setCaretToMouse(Number x, Number y);
			void dragSelectionTo(Number x, Number y);
			
			void applyBlockOverrides();
			
			void updateSelectionRects();
		
			void selectWordAtCaret();
		
			void restructLines();
			void removeLines(unsigned int startIndex, unsigned int endIndex);
			
			std::vector<TextColorPair> makeWordWrapBuffer(LineInfo *lineInfo, String indentPrefix);
			std::vector<TextColorPair> splitTokens(String stringToSplit, LineColorInfo *stringColorInfo);
			
			UIRect *selectorRectTop;
			UIRect *selectorRectMiddle;
			UIRect *selectorRectBottom;		
			int numLines;			
			
			Number padding;
			Number lineSpacing;
		
			int selectionTop;
			int selectionBottom;
			int selectionL;
			int selectionR;
			
			UIRect *lineNumberBg;
            Number textInputOffsetY;
			
			int decoratorOffset;
		
			bool settingText;
		
			int selectionCaretPosition;
			int selectionLine;

			// Used only by single-line text input, so
			// that you can edit text longer than the width
			// of the line.
			// TODO/considerations: Use this to scroll a single
			// line in multi-line mode?
			int horizontalPixelScroll;
			// By how many characters have we scrolled right?
			int horizontalCharacterScroll;

		
			bool draggingSelection;
			bool hasSelection; 
			Number caretX,caretY;
		
			int caretPosition;
			int actualCaretPosition;
			
			bool doSelectToCaret;
			
			UITextInputSyntaxHighlighter *syntaxHighliter;
		
			Entity *linesContainer;

			// container for the actual text contents
			UIElement *textContainer; 
			
			vector<SceneLabel*> linesToDelete;	
			
			std::vector<FindMatch> findMatches;
			int findIndex;
			
			UITextInputUndoState undoStates[MAX_TEXTINPUT_UNDO_STATES];
			int undoStateIndex;
			int maxRedoIndex;
			bool isTypingWord;
		
			bool multiLine;
			Timer *blinkTimer;
			UIBox *inputRect;
			UIRect *blinkerRect;
			Vector2 dragMouseStart;
			
			Color selectionColor;
			void _setSelectionColor(Color color);
			
			Number st;
			Number sr;
			Number sb;
			Number sl;
			
			UIMenu *contextMenu;
			
			Vector2 selectionDragMouse;
		
			Number caretImagePosition;
			
			int currentBufferLines;
			int neededBufferLines;			
			
			UIScrollContainer *scrollContainer;
		
			String fontName;
			Number fontSize;
		
			Number lineHeight;
		
			int lineOffset;
			int actualLineOffset;
			
			vector<LineInfo> lines;
			vector<WordWrapLine> wordWrapLines;
									
			vector<SceneLabel*> bufferLines;
			vector<SceneLabel*> numberLines;
			
			Core *core;
			
			Number lastResizeWidth;
			
			Number _newWidth;
			Number _newHeight;
			bool didMultilineResize;
        
			enum indentTypes { INDENT_SPACE, INDENT_TAB } indentType;
			int indentSpacing;
			
	};
}
