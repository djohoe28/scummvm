/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef BLADERUNNER_UI_SCROLLBOX_H
#define BLADERUNNER_UI_SCROLLBOX_H

#include "bladerunner/ui/ui_component.h"

#include "common/array.h"
#include "common/rect.h"
#include "common/str.h"

namespace BladeRunner {

typedef void UIScrollBoxCallback(void *callbackData, void *source, int lineData, int mouseButton);

class UIScrollBox : public UIComponent
{
private:
	static const int kLineHeight = 10;
	static const int k3DFrameColors[];
	static const int kTextBackgroundColors[];
	static const int kTextColors1[];
	static const int kTextColors2[];
	static const int kTextColors3[];
	static const int kTextColors4[];

	struct Line {
		Common::String text;
		int lineData;
		int flags;
		int checkboxFrame;
	};

	int                   _selectedLineState;
	int                   _scrollUpButtonState;
	int                   _scrollDownButtonState;
	int                   _scrollAreaUpState;
	int                   _scrollAreaDownState;
	int                   _scrollBarState;

	int                   _hoveredLine;
	int                   _selectedLineIndex;

	bool                  _scrollUpButtonHover;
	bool                  _scrollDownButtonHover;
	bool                  _scrollAreaUpHover;
	bool                  _scrollAreaDownHover;
	bool                  _scrollBarHover;

	bool                  _mouseButton;

	UIScrollBoxCallback  *_lineSelectedCallback;
	void                 *_callbackData;

	bool                  _isVisible;
	int                   _style;
	bool                  _center;

	int                   _timeLastScroll;
	int                   _timeLastCheckbox;
	int                   _timeLastHighlight;

	int                   _highlightFrame;

	Common::Rect          _rect;
	Common::Rect          _scrollBarRect;

	int                   _lineCount;
	int                   _maxLineCount;
	Common::Array<Line *> _lines;
	int                   _maxLinesVisible;
	int                   _firstLineVisible;

public:
	UIScrollBox(BladeRunnerEngine *vm, UIScrollBoxCallback *lineSelectedCallback, void *callbackData, int maxLineCount, int style, bool center, Common::Rect rect,Common::Rect scrollBarRect);
	~UIScrollBox();

	void draw(Graphics::Surface &surface);

	void handleMouseMove(int mouseX, int mouseY);
	void handleMouseDown(bool alternateButton);
	void handleMouseUp(bool alternateButton);

	void show();
	void hide();

	void clearLines();
	void addLine(const Common::String &text, int lineData, int flags);
	void addLine(const char *text, int lineData, int flags);
	void sortLines();

	int getSelectedLineData();

	void checkAll();
	void uncheckAll();
	void toggleCheckBox(int lineData);

	bool hasLine(int lineData);

	void resetHighlight(int lineData);
	void setFlags(int lineData, int flags);
	void resetFlags(int lineData, int flags);

private:
	static int sortFunction(const void *line1, const void *line2);

	void draw3DFrame(Graphics::Surface &surface, Common::Rect rect, bool pressed, int style);

	void scrollUp();
	void scrollDown();

	int findLine(int lineData);
};

} // End of namespace BladeRunner

#endif