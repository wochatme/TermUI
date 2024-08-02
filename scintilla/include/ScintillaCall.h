// SciTE - Scintilla based Text Editor
/** @file ScintillaCall.h
 ** Interface to calling a Scintilla instance.
 **/
// Copyright 1998-2019 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

/* Most of this file is automatically generated from the Scintilla.iface interface definition
 * file which contains any comments about the definitions. APIFacer.py does the generation. */

#ifndef SCINTILLACALL_H
#define SCINTILLACALL_H

namespace Scintilla {

enum class Message;	// Declare in case ScintillaMessages.h not included

// Declare in case ScintillaStructures.h not included
struct TextRangeFull;
struct TextToFindFull;
struct RangeToFormatFull;

class IDocumentEditable;

using FunctionDirect = intptr_t(*)(intptr_t ptr, unsigned int iMessage, uintptr_t wParam, intptr_t lParam, int *pStatus);

struct Failure {
	Scintilla::Status status;
	explicit Failure(Scintilla::Status status_) noexcept : status(status_) {
	}
};

struct Span {
	// An ordered range
	// end may be less than start when, for example, searching backwards
	Position start;
	Position end;
	explicit Span(Position position) noexcept : start(position), end(position) {
	}
	Span(Position start_, Position end_) noexcept : start(start_), end(end_) {
	}
	Position Length() const noexcept {
		if (end > start)
			return end - start;
		else
			return start - end;
	}
	bool operator==(const Span &other) const noexcept {
		return (other.start == start) && (other.end == end);
	}
};

class ScintillaCall {
	FunctionDirect fn;
	intptr_t ptr;
	intptr_t CallPointer(Message msg, uintptr_t wParam, void *s);
	intptr_t CallString(Message msg, uintptr_t wParam, const char *s);
	std::string CallReturnString(Message msg, uintptr_t wParam);
public:
	Scintilla::Status statusLastCall;
	ScintillaCall() noexcept;
	// All standard methods are fine

	void SetFnPtr(FunctionDirect fn_, intptr_t ptr_) noexcept;
	bool IsValid() const noexcept;
	intptr_t Call(Message msg, uintptr_t wParam=0, intptr_t lParam=0);

	// Common APIs made more structured and type-safe
	Position LineStart(Line line);
	Position LineEnd(Line line);
	Span SelectionSpan();
	Span TargetSpan();
	void SetTarget(Span span);
	void ColouriseAll();
	char CharacterAt(Position position);
	int UnsignedStyleAt(Position position);
	std::string StringOfSpan(Span span);
	std::string StringOfRange(Span span);
	Position ReplaceTarget(std::string_view text);
	Position ReplaceTargetRE(std::string_view text);
	Position ReplaceTargetMinimal(std::string_view text);
	Position SearchInTarget(std::string_view text);
	Span SpanSearchInTarget(std::string_view text);

	// Generated APIs
//++Autogenerated -- start of section automatically generated from Scintilla.iface
//**\(\*\n\)
	void AddText(Position length, const char *text);
	void AddStyledText(Position length, const char *c);
	void InsertText(Position pos, const char *text);
	void ChangeInsertion(Position length, const char *text);
	void ClearAll();
	void DeleteRange(Position start, Position lengthDelete);
	void ClearDocumentStyle();
	Position Length();
	int CharAt(Position pos);
	Position CurrentPos();
	Position Anchor();
	int StyleAt(Position pos);
	int StyleIndexAt(Position pos);
	void Redo();
	void SetUndoCollection(bool collectUndo);
	void SelectAll();
	void SetSavePoint();
	Position GetStyledText(void *tr);
	Position GetStyledTextFull(TextRangeFull *tr);
	bool CanRedo();
	Line MarkerLineFromHandle(int markerHandle);
	void MarkerDeleteHandle(int markerHandle);
	int MarkerHandleFromLine(Line line, int which);
	int MarkerNumberFromLine(Line line, int which);
	bool UndoCollection();
	Scintilla::WhiteSpace ViewWS();
	void SetViewWS(Scintilla::WhiteSpace viewWS);
	Scintilla::TabDrawMode TabDrawMode();
	void SetTabDrawMode(Scintilla::TabDrawMode tabDrawMode);
	Position PositionFromPoint(int x, int y);
	Position PositionFromPointClose(int x, int y);
	void GotoLine(Line line);
	void GotoPos(Position caret);
	void SetAnchor(Position anchor);
	Position GetCurLine(Position length, char *text);
	std::string GetCurLine(Position length);
	Position EndStyled();
	void ConvertEOLs(Scintilla::EndOfLine eolMode);
	Scintilla::EndOfLine EOLMode();
	void SetEOLMode(Scintilla::EndOfLine eolMode);
	void StartStyling(Position start, int unused);
	void SetStyling(Position length, int style);
	bool BufferedDraw();
	void SetBufferedDraw(bool buffered);
	void SetTabWidth(int tabWidth);
	int TabWidth();
	void SetTabMinimumWidth(int pixels);
	int TabMinimumWidth();
	void ClearTabStops(Line line);
	void AddTabStop(Line line, int x);
	int GetNextTabStop(Line line, int x);
	void SetCodePage(int codePage);
	void SetFontLocale(const char *localeName);
	int FontLocale(char *localeName);
	std::string FontLocale();
	Scintilla::IMEInteraction IMEInteraction();
	void SetIMEInteraction(Scintilla::IMEInteraction imeInteraction);
	void MarkerDefine(int markerNumber, Scintilla::MarkerSymbol markerSymbol);
	void MarkerSetFore(int markerNumber, Colour fore);
	void MarkerSetBack(int markerNumber, Colour back);
	void MarkerSetBackSelected(int markerNumber, Colour back);
	void MarkerSetForeTranslucent(int markerNumber, ColourAlpha fore);
	void MarkerSetBackTranslucent(int markerNumber, ColourAlpha back);
	void MarkerSetBackSelectedTranslucent(int markerNumber, ColourAlpha back);
	void MarkerSetStrokeWidth(int markerNumber, int hundredths);
	void MarkerEnableHighlight(bool enabled);
	int MarkerAdd(Line line, int markerNumber);
	void MarkerDelete(Line line, int markerNumber);
	void MarkerDeleteAll(int markerNumber);
	int MarkerGet(Line line);
	Line MarkerNext(Line lineStart, int markerMask);
	Line MarkerPrevious(Line lineStart, int markerMask);
	void MarkerDefinePixmap(int markerNumber, const char *pixmap);
	void MarkerAddSet(Line line, int markerSet);
	void MarkerSetAlpha(int markerNumber, Scintilla::Alpha alpha);
	Scintilla::Layer MarkerGetLayer(int markerNumber);
	void MarkerSetLayer(int markerNumber, Scintilla::Layer layer);
	void SetMarginTypeN(int margin, Scintilla::MarginType marginType);
	Scintilla::MarginType MarginTypeN(int margin);
	void SetMarginWidthN(int margin, int pixelWidth);
	int MarginWidthN(int margin);
	void SetMarginMaskN(int margin, int mask);
	int MarginMaskN(int margin);
	void SetMarginSensitiveN(int margin, bool sensitive);
	bool MarginSensitiveN(int margin);
	void SetMarginCursorN(int margin, Scintilla::CursorShape cursor);
	Scintilla::CursorShape MarginCursorN(int margin);
	void SetMarginBackN(int margin, Colour back);
	Colour MarginBackN(int margin);
	void SetMargins(int margins);
	int Margins();
	void StyleClearAll();
	void StyleSetFore(int style, Colour fore);
	void StyleSetBack(int style, Colour back);
	void StyleSetBold(int style, bool bold);
	void StyleSetItalic(int style, bool italic);
	void StyleSetSize(int style, int sizePoints);
	void StyleSetFont(int style, const char *fontName);
	void StyleSetEOLFilled(int style, bool eolFilled);
	void StyleResetDefault();
	void StyleSetUnderline(int style, bool underline);
	Colour StyleGetFore(int style);
	Colour StyleGetBack(int style);
	bool StyleGetBold(int style);
	bool StyleGetItalic(int style);
	int StyleGetSize(int style);
	int StyleGetFont(int style, char *fontName);
	std::string StyleGetFont(int style);
	bool StyleGetEOLFilled(int style);
	bool StyleGetUnderline(int style);
	Scintilla::CaseVisible StyleGetCase(int style);
	Scintilla::CharacterSet StyleGetCharacterSet(int style);
	bool StyleGetVisible(int style);
	bool StyleGetChangeable(int style);
	bool StyleGetHotSpot(int style);
	void StyleSetCase(int style, Scintilla::CaseVisible caseVisible);
	void StyleSetSizeFractional(int style, int sizeHundredthPoints);
	int StyleGetSizeFractional(int style);
	void StyleSetWeight(int style, Scintilla::FontWeight weight);
	Scintilla::FontWeight StyleGetWeight(int style);
	void StyleSetCharacterSet(int style, Scintilla::CharacterSet characterSet);
	void StyleSetHotSpot(int style, bool hotspot);
	void StyleSetCheckMonospaced(int style, bool checkMonospaced);
	bool StyleGetCheckMonospaced(int style);
	void StyleSetInvisibleRepresentation(int style, const char *representation);
	int StyleGetInvisibleRepresentation(int style, char *representation);
	std::string StyleGetInvisibleRepresentation(int style);
	void SetElementColour(Scintilla::Element element, ColourAlpha colourElement);
	ColourAlpha ElementColour(Scintilla::Element element);
	void ResetElementColour(Scintilla::Element element);
	bool ElementIsSet(Scintilla::Element element);
	bool ElementAllowsTranslucent(Scintilla::Element element);
	ColourAlpha ElementBaseColour(Scintilla::Element element);
	void SetSelFore(bool useSetting, Colour fore);
	void SetSelBack(bool useSetting, Colour back);
	Scintilla::Alpha SelAlpha();
	void SetSelAlpha(Scintilla::Alpha alpha);
	bool SelEOLFilled();
	void SetSelEOLFilled(bool filled);
	Scintilla::Layer SelectionLayer();
	void SetSelectionLayer(Scintilla::Layer layer);
	Scintilla::Layer CaretLineLayer();
	void SetCaretLineLayer(Scintilla::Layer layer);
	bool CaretLineHighlightSubLine();
	void SetCaretLineHighlightSubLine(bool subLine);
	void SetCaretFore(Colour fore);
	void AssignCmdKey(int keyDefinition, int sciCommand);
	void ClearCmdKey(int keyDefinition);
	void ClearAllCmdKeys();
	void SetStylingEx(Position length, const char *styles);
	void StyleSetVisible(int style, bool visible);
	int CaretPeriod();
	void SetCaretPeriod(int periodMilliseconds);
	void SetWordChars(const char *characters);
	int WordChars(char *characters);
	std::string WordChars();
	void SetCharacterCategoryOptimization(int countCharacters);
	int CharacterCategoryOptimization();
	void BeginUndoAction();
	void EndUndoAction();
	int UndoActions();
	void SetUndoSavePoint(int action);
	int UndoSavePoint();
	void SetUndoDetach(int action);
	int UndoDetach();
	void SetUndoTentative(int action);
	int UndoTentative();
	void SetUndoCurrent(int action);
	int UndoCurrent();
	void PushUndoActionType(int type, Position pos);
	void ChangeLastUndoActionText(Position length, const char *text);
	int UndoActionType(int action);
	Position UndoActionPosition(int action);
	int UndoActionText(int action, char *text);
	std::string UndoActionText(int action);
	void IndicSetStyle(int indicator, Scintilla::IndicatorStyle indicatorStyle);
	Scintilla::IndicatorStyle IndicGetStyle(int indicator);
	void IndicSetFore(int indicator, Colour fore);
	Colour IndicGetFore(int indicator);
	void IndicSetUnder(int indicator, bool under);
	bool IndicGetUnder(int indicator);
	void IndicSetHoverStyle(int indicator, Scintilla::IndicatorStyle indicatorStyle);
	Scintilla::IndicatorStyle IndicGetHoverStyle(int indicator);
	void IndicSetHoverFore(int indicator, Colour fore);
	Colour IndicGetHoverFore(int indicator);
	void IndicSetFlags(int indicator, Scintilla::IndicFlag flags);
	Scintilla::IndicFlag IndicGetFlags(int indicator);
	void IndicSetStrokeWidth(int indicator, int hundredths);
	int IndicGetStrokeWidth(int indicator);
	void SetWhitespaceFore(bool useSetting, Colour fore);
	void SetWhitespaceBack(bool useSetting, Colour back);
	void SetWhitespaceSize(int size);
	int WhitespaceSize();
	void SetLineState(Line line, int state);
	int LineState(Line line);
	int MaxLineState();
	bool CaretLineVisible();
	void SetCaretLineVisible(bool show);
	Colour CaretLineBack();
	void SetCaretLineBack(Colour back);
	int CaretLineFrame();
	void SetCaretLineFrame(int width);
	void StyleSetChangeable(int style, bool changeable);
	void AutoCShow(Position lengthEntered, const char *itemList);
	void AutoCCancel();
	bool AutoCActive();
	Position AutoCPosStart();
	void AutoCComplete();
	void AutoCStops(const char *characterSet);
	void AutoCSetSeparator(int separatorCharacter);
	int AutoCGetSeparator();
	void AutoCSelect(const char *select);
	void AutoCSetCancelAtStart(bool cancel);
	bool AutoCGetCancelAtStart();
	void AutoCSetFillUps(const char *characterSet);
	void AutoCSetChooseSingle(bool chooseSingle);
	bool AutoCGetChooseSingle();
	void AutoCSetIgnoreCase(bool ignoreCase);
	bool AutoCGetIgnoreCase();
	void UserListShow(int listType, const char *itemList);
	void AutoCSetAutoHide(bool autoHide);
	bool AutoCGetAutoHide();
	void AutoCSetOptions(Scintilla::AutoCompleteOption options);
	Scintilla::AutoCompleteOption AutoCGetOptions();
	void AutoCSetDropRestOfWord(bool dropRestOfWord);
	bool AutoCGetDropRestOfWord();
	void RegisterImage(int type, const char *xpmData);
	void ClearRegisteredImages();
	int AutoCGetTypeSeparator();
	void AutoCSetTypeSeparator(int separatorCharacter);
	void AutoCSetMaxWidth(int characterCount);
	int AutoCGetMaxWidth();
	void AutoCSetMaxHeight(int rowCount);
	int AutoCGetMaxHeight();
	void AutoCSetStyle(int style);
	int AutoCGetStyle();
	void SetIndent(int indentSize);
	int Indent();
	void SetUseTabs(bool useTabs);
	bool UseTabs();
	void SetLineIndentation(Line line, int indentation);
	int LineIndentation(Line line);
	Position LineIndentPosition(Line line);
	Position Column(Position pos);
	Position CountCharacters(Position start, Position end);
	Position CountCodeUnits(Position start, Position end);
	void SetHScrollBar(bool visible);
	bool HScrollBar();
	void SetIndentationGuides(Scintilla::IndentView indentView);
	Scintilla::IndentView IndentationGuides();
	void SetHighlightGuide(Position column);
	Position HighlightGuide();
	Position LineEndPosition(Line line);
	int CodePage();
	Colour CaretFore();
	bool ReadOnly();
	void SetCurrentPos(Position caret);
	void SetSelectionStart(Position anchor);
	Position SelectionStart();
	void SetSelectionEnd(Position caret);
	Position SelectionEnd();
	void SetEmptySelection(Position caret);
	void SetPrintMagnification(int magnification);
	int PrintMagnification();
	void SetPrintColourMode(Scintilla::PrintOption mode);
	Scintilla::PrintOption PrintColourMode();
	Position FindText(Scintilla::FindOption searchFlags, void *ft);
	Position FindTextFull(Scintilla::FindOption searchFlags, TextToFindFull *ft);
	Position FormatRange(bool draw, void *fr);
	Position FormatRangeFull(bool draw, RangeToFormatFull *fr);
	void SetChangeHistory(Scintilla::ChangeHistoryOption changeHistory);
	Scintilla::ChangeHistoryOption ChangeHistory();
	Line FirstVisibleLine();
	Position GetLine(Line line, char *text);
	std::string GetLine(Line line);
	Line LineCount();
	void AllocateLines(Line lines);
	void SetMarginLeft(int pixelWidth);
	int MarginLeft();
	void SetMarginRight(int pixelWidth);
	int MarginRight();
	bool Modify();
	void SetSel(Position anchor, Position caret);
	Position GetSelText(char *text);
	std::string GetSelText();
	Position GetTextRange(void *tr);
	Position GetTextRangeFull(TextRangeFull *tr);
	void HideSelection(bool hide);
	bool SelectionHidden();
	int PointXFromPosition(Position pos);
	int PointYFromPosition(Position pos);
	Line LineFromPosition(Position pos);
	Position PositionFromLine(Line line);
	void LineScroll(Position columns, Line lines);
	void ScrollCaret();
	void ScrollRange(Position secondary, Position primary);
	void ReplaceSel(const char *text);
	void SetReadOnly(bool readOnly);
	void Null();
	bool CanPaste();
	bool CanUndo();
	void EmptyUndoBuffer();
	void Undo();
	void Cut();
	void Copy();
	void Paste();
	void Clear();
	void SetText(const char *text);
	Position GetText(Position length, char *text);
	std::string GetText(Position length);
	Position TextLength();
	void *DirectFunction();
	void *DirectStatusFunction();
	void *DirectPointer();
	void SetOvertype(bool overType);
	bool Overtype();
	void SetCaretWidth(int pixelWidth);
	int CaretWidth();
	void SetTargetStart(Position start);
	Position TargetStart();
	void SetTargetStartVirtualSpace(Position space);
	Position TargetStartVirtualSpace();
	void SetTargetEnd(Position end);
	Position TargetEnd();
	void SetTargetEndVirtualSpace(Position space);
	Position TargetEndVirtualSpace();
	void SetTargetRange(Position start, Position end);
	Position TargetText(char *text);
	std::string TargetText();
	void TargetFromSelection();
	void TargetWholeDocument();
	Position ReplaceTarget(Position length, const char *text);
	Position ReplaceTargetRE(Position length, const char *text);
	Position ReplaceTargetMinimal(Position length, const char *text);
	Position SearchInTarget(Position length, const char *text);
	void SetSearchFlags(Scintilla::FindOption searchFlags);
	Scintilla::FindOption SearchFlags();
	void CallTipShow(Position pos, const char *definition);
	void CallTipCancel();
	bool CallTipActive();
	Position CallTipPosStart();
	void CallTipSetPosStart(Position posStart);
	void CallTipSetHlt(Position highlightStart, Position highlightEnd);
	void CallTipSetBack(Colour back);
	void CallTipSetFore(Colour fore);
	void CallTipSetForeHlt(Colour fore);
	void CallTipUseStyle(int tabSize);
	void CallTipSetPosition(bool above);
	Line VisibleFromDocLine(Line docLine);
	Line DocLineFromVisible(Line displayLine);
	Line WrapCount(Line docLine);
	void SetFoldLevel(Line line, Scintilla::FoldLevel level);
	Scintilla::FoldLevel FoldLevel(Line line);
	Line LastChild(Line line, Scintilla::FoldLevel level);
	Line FoldParent(Line line);
	void ShowLines(Line lineStart, Line lineEnd);
	void HideLines(Line lineStart, Line lineEnd);
	bool LineVisible(Line line);
	bool AllLinesVisible();
	void SetFoldExpanded(Line line, bool expanded);
	bool FoldExpanded(Line line);
	void ToggleFold(Line line);
	void ToggleFoldShowText(Line line, const char *text);
	void FoldDisplayTextSetStyle(Scintilla::FoldDisplayTextStyle style);
	Scintilla::FoldDisplayTextStyle FoldDisplayTextGetStyle();
	void SetDefaultFoldDisplayText(const char *text);
	int GetDefaultFoldDisplayText(char *text);
	std::string GetDefaultFoldDisplayText();
	void FoldLine(Line line, Scintilla::FoldAction action);
	void FoldChildren(Line line, Scintilla::FoldAction action);
	void ExpandChildren(Line line, Scintilla::FoldLevel level);
	void FoldAll(Scintilla::FoldAction action);
	void EnsureVisible(Line line);
	void SetAutomaticFold(Scintilla::AutomaticFold automaticFold);
	Scintilla::AutomaticFold AutomaticFold();
	void SetFoldFlags(Scintilla::FoldFlag flags);
	void EnsureVisibleEnforcePolicy(Line line);
	void SetTabIndents(bool tabIndents);
	bool TabIndents();
	void SetBackSpaceUnIndents(bool bsUnIndents);
	bool BackSpaceUnIndents();
	void SetMouseDwellTime(int periodMilliseconds);
	int MouseDwellTime();
	Position WordStartPosition(Position pos, bool onlyWordCharacters);
	Position WordEndPosition(Position pos, bool onlyWordCharacters);
	bool IsRangeWord(Position start, Position end);
	void SetIdleStyling(Scintilla::IdleStyling idleStyling);
	Scintilla::IdleStyling IdleStyling();
	void SetWrapMode(Scintilla::Wrap wrapMode);
	Scintilla::Wrap WrapMode();
	void SetWrapVisualFlags(Scintilla::WrapVisualFlag wrapVisualFlags);
	Scintilla::WrapVisualFlag WrapVisualFlags();
	void SetWrapVisualFlagsLocation(Scintilla::WrapVisualLocation wrapVisualFlagsLocation);
	Scintilla::WrapVisualLocation WrapVisualFlagsLocation();
	void SetWrapStartIndent(int indent);
	int WrapStartIndent();
	void SetWrapIndentMode(Scintilla::WrapIndentMode wrapIndentMode);
	Scintilla::WrapIndentMode WrapIndentMode();
	void SetLayoutCache(Scintilla::LineCache cacheMode);
	Scintilla::LineCache LayoutCache();
	void SetScrollWidth(int pixelWidth);
	int ScrollWidth();
	void SetScrollWidthTracking(bool tracking);
	bool ScrollWidthTracking();
	int TextWidth(int style, const char *text);
	void SetEndAtLastLine(bool endAtLastLine);
	bool EndAtLastLine();
	int TextHeight(Line line);
	void SetVScrollBar(bool visible);
	bool VScrollBar();
	void AppendText(Position length, const char *text);
	Scintilla::PhasesDraw PhasesDraw();
	void SetPhasesDraw(Scintilla::PhasesDraw phases);
	void SetFontQuality(Scintilla::FontQuality fontQuality);
	Scintilla::FontQuality FontQuality();
	void SetFirstVisibleLine(Line displayLine);
	void SetMultiPaste(Scintilla::MultiPaste multiPaste);
	Scintilla::MultiPaste MultiPaste();
	int Tag(int tagNumber, char *tagValue);
	std::string Tag(int tagNumber);
	void LinesJoin();
	void LinesSplit(int pixelWidth);
	void SetFoldMarginColour(bool useSetting, Colour back);
	void SetFoldMarginHiColour(bool useSetting, Colour fore);
	void SetAccessibility(Scintilla::Accessibility accessibility);
	Scintilla::Accessibility Accessibility();
	void LineDown();
	void LineDownExtend();
	void LineUp();
	void LineUpExtend();
	void CharLeft();
	void CharLeftExtend();
	void CharRight();
	void CharRightExtend();
	void WordLeft();
	void WordLeftExtend();
	void WordRight();
	void WordRightExtend();
	void Home();
	void HomeExtend();
	void LineEnd();
	void LineEndExtend();
	void DocumentStart();
	void DocumentStartExtend();
	void DocumentEnd();
	void DocumentEndExtend();
	void PageUp();
	void PageUpExtend();
	void PageDown();
	void PageDownExtend();
	void EditToggleOvertype();
	void Cancel();
	void DeleteBack();
	void Tab();
	void BackTab();
	void NewLine();
	void FormFeed();
	void VCHome();
	void VCHomeExtend();
	void ZoomIn();
	void ZoomOut();
	void DelWordLeft();
	void DelWordRight();
	void DelWordRightEnd();
	void LineCut();
	void LineDelete();
	void LineTranspose();
	void LineReverse();
	void LineDuplicate();
	void LowerCase();
	void UpperCase();
	void LineScrollDown();
	void LineScrollUp();
	void DeleteBackNotLine();
	void HomeDisplay();
	void HomeDisplayExtend();
	void LineEndDisplay();
	void LineEndDisplayExtend();
	void HomeWrap();
	void HomeWrapExtend();
	void LineEndWrap();
	void LineEndWrapExtend();
	void VCHomeWrap();
	void VCHomeWrapExtend();
	void LineCopy();
	void MoveCaretInsideView();
	Position LineLength(Line line);
	void BraceHighlight(Position posA, Position posB);
	void BraceHighlightIndicator(bool useSetting, int indicator);
	void BraceBadLight(Position pos);
	void BraceBadLightIndicator(bool useSetting, int indicator);
	Position BraceMatch(Position pos, int maxReStyle);
	Position BraceMatchNext(Position pos, Position startPos);
	bool ViewEOL();
	void SetViewEOL(bool visible);
	IDocumentEditable *DocPointer();
	void SetDocPointer(IDocumentEditable *doc);
	void SetModEventMask(Scintilla::ModificationFlags eventMask);
	Position EdgeColumn();
	void SetEdgeColumn(Position column);
	Scintilla::EdgeVisualStyle EdgeMode();
	void SetEdgeMode(Scintilla::EdgeVisualStyle edgeMode);
	Colour EdgeColour();
	void SetEdgeColour(Colour edgeColour);
	void MultiEdgeAddLine(Position column, Colour edgeColour);
	void MultiEdgeClearAll();
	Position MultiEdgeColumn(int which);
	void SearchAnchor();
	Position SearchNext(Scintilla::FindOption searchFlags, const char *text);
	Position SearchPrev(Scintilla::FindOption searchFlags, const char *text);
	Line LinesOnScreen();
	void UsePopUp(Scintilla::PopUp popUpMode);
	bool SelectionIsRectangle();
	void SetZoom(int zoomInPoints);
	int Zoom();
	IDocumentEditable *CreateDocument(Position bytes, Scintilla::DocumentOption documentOptions);
	void AddRefDocument(IDocumentEditable *doc);
	void ReleaseDocument(IDocumentEditable *doc);
	Scintilla::DocumentOption DocumentOptions();
	Scintilla::ModificationFlags ModEventMask();
	void SetCommandEvents(bool commandEvents);
	bool CommandEvents();
	void SetFocus(bool focus);
	bool Focus();
	void SetStatus(Scintilla::Status status);
	Scintilla::Status Status();
	void SetMouseDownCaptures(bool captures);
	bool MouseDownCaptures();
	void SetMouseWheelCaptures(bool captures);
	bool MouseWheelCaptures();
	void SetCursor(Scintilla::CursorShape cursorType);
	Scintilla::CursorShape Cursor();
	void SetControlCharSymbol(int symbol);
	int ControlCharSymbol();
	void WordPartLeft();
	void WordPartLeftExtend();
	void WordPartRight();
	void WordPartRightExtend();
	void SetVisiblePolicy(Scintilla::VisiblePolicy visiblePolicy, int visibleSlop);
	void DelLineLeft();
	void DelLineRight();
	void SetXOffset(int xOffset);
	int XOffset();
	void ChooseCaretX();
	void GrabFocus();
	void SetXCaretPolicy(Scintilla::CaretPolicy caretPolicy, int caretSlop);
	void SetYCaretPolicy(Scintilla::CaretPolicy caretPolicy, int caretSlop);
	void SetPrintWrapMode(Scintilla::Wrap wrapMode);
	Scintilla::Wrap PrintWrapMode();
	void SetHotspotActiveFore(bool useSetting, Colour fore);
	Colour HotspotActiveFore();
	void SetHotspotActiveBack(bool useSetting, Colour back);
	Colour HotspotActiveBack();
	void SetHotspotActiveUnderline(bool underline);
	bool HotspotActiveUnderline();
	void SetHotspotSingleLine(bool singleLine);
	bool HotspotSingleLine();
	void ParaDown();
	void ParaDownExtend();
	void ParaUp();
	void ParaUpExtend();
	Position PositionBefore(Position pos);
	Position PositionAfter(Position pos);
	Position PositionRelative(Position pos, Position relative);
	Position PositionRelativeCodeUnits(Position pos, Position relative);
	void CopyRange(Position start, Position end);
	void CopyText(Position length, const char *text);
	void SetSelectionMode(Scintilla::SelectionMode selectionMode);
	void ChangeSelectionMode(Scintilla::SelectionMode selectionMode);
	Scintilla::SelectionMode SelectionMode();
	void SetMoveExtendsSelection(bool moveExtendsSelection);
	bool MoveExtendsSelection();
	Position GetLineSelStartPosition(Line line);
	Position GetLineSelEndPosition(Line line);
	void LineDownRectExtend();
	void LineUpRectExtend();
	void CharLeftRectExtend();
	void CharRightRectExtend();
	void HomeRectExtend();
	void VCHomeRectExtend();
	void LineEndRectExtend();
	void PageUpRectExtend();
	void PageDownRectExtend();
	void StutteredPageUp();
	void StutteredPageUpExtend();
	void StutteredPageDown();
	void StutteredPageDownExtend();
	void WordLeftEnd();
	void WordLeftEndExtend();
	void WordRightEnd();
	void WordRightEndExtend();
	void SetWhitespaceChars(const char *characters);
	int WhitespaceChars(char *characters);
	std::string WhitespaceChars();
	void SetPunctuationChars(const char *characters);
	int PunctuationChars(char *characters);
	std::string PunctuationChars();
	void SetCharsDefault();
	int AutoCGetCurrent();
	int AutoCGetCurrentText(char *text);
	std::string AutoCGetCurrentText();
	void AutoCSetCaseInsensitiveBehaviour(Scintilla::CaseInsensitiveBehaviour behaviour);
	Scintilla::CaseInsensitiveBehaviour AutoCGetCaseInsensitiveBehaviour();
	void AutoCSetMulti(Scintilla::MultiAutoComplete multi);
	Scintilla::MultiAutoComplete AutoCGetMulti();
	void AutoCSetOrder(Scintilla::Ordering order);
	Scintilla::Ordering AutoCGetOrder();
	void Allocate(Position bytes);
	Position TargetAsUTF8(char *s);
	std::string TargetAsUTF8();
	void SetLengthForEncode(Position bytes);
	Position EncodedFromUTF8(const char *utf8, char *encoded);
	std::string EncodedFromUTF8(const char *utf8);
	Position FindColumn(Line line, Position column);
	Scintilla::CaretSticky CaretSticky();
	void SetCaretSticky(Scintilla::CaretSticky useCaretStickyBehaviour);
	void ToggleCaretSticky();
	void SetPasteConvertEndings(bool convert);
	bool PasteConvertEndings();
	void ReplaceRectangular(Position length, const char *text);
	void SelectionDuplicate();
	void SetCaretLineBackAlpha(Scintilla::Alpha alpha);
	Scintilla::Alpha CaretLineBackAlpha();
	void SetCaretStyle(Scintilla::CaretStyle caretStyle);
	Scintilla::CaretStyle CaretStyle();
	void SetIndicatorCurrent(int indicator);
	int IndicatorCurrent();
	void SetIndicatorValue(int value);
	int IndicatorValue();
	void IndicatorFillRange(Position start, Position lengthFill);
	void IndicatorClearRange(Position start, Position lengthClear);
	int IndicatorAllOnFor(Position pos);
	int IndicatorValueAt(int indicator, Position pos);
	Position IndicatorStart(int indicator, Position pos);
	Position IndicatorEnd(int indicator, Position pos);
	void SetPositionCache(int size);
	int PositionCache();
	void SetLayoutThreads(int threads);
	int LayoutThreads();
	void CopyAllowLine();
	void CutAllowLine();
	void *CharacterPointer();
	void *RangePointer(Position start, Position lengthRange);
	Position GapPosition();
	void IndicSetAlpha(int indicator, Scintilla::Alpha alpha);
	Scintilla::Alpha IndicGetAlpha(int indicator);
	void IndicSetOutlineAlpha(int indicator, Scintilla::Alpha alpha);
	Scintilla::Alpha IndicGetOutlineAlpha(int indicator);
	void SetExtraAscent(int extraAscent);
	int ExtraAscent();
	void SetExtraDescent(int extraDescent);
	int ExtraDescent();
	int MarkerSymbolDefined(int markerNumber);
	void MarginSetText(Line line, const char *text);
	int MarginGetText(Line line, char *text);
	std::string MarginGetText(Line line);
	void MarginSetStyle(Line line, int style);
	int MarginGetStyle(Line line);
	void MarginSetStyles(Line line, const char *styles);
	int MarginGetStyles(Line line, char *styles);
	std::string MarginGetStyles(Line line);
	void MarginTextClearAll();
	void MarginSetStyleOffset(int style);
	int MarginGetStyleOffset();
	void SetMarginOptions(Scintilla::MarginOption marginOptions);
	Scintilla::MarginOption MarginOptions();
	void AnnotationSetText(Line line, const char *text);
	int AnnotationGetText(Line line, char *text);
	std::string AnnotationGetText(Line line);
	void AnnotationSetStyle(Line line, int style);
	int AnnotationGetStyle(Line line);
	void AnnotationSetStyles(Line line, const char *styles);
	int AnnotationGetStyles(Line line, char *styles);
	std::string AnnotationGetStyles(Line line);
	int AnnotationGetLines(Line line);
	void AnnotationClearAll();
	void AnnotationSetVisible(Scintilla::AnnotationVisible visible);
	Scintilla::AnnotationVisible AnnotationGetVisible();
	void AnnotationSetStyleOffset(int style);
	int AnnotationGetStyleOffset();
	void ReleaseAllExtendedStyles();
	int AllocateExtendedStyles(int numberStyles);
	void AddUndoAction(int token, Scintilla::UndoFlags flags);
	Position CharPositionFromPoint(int x, int y);
	Position CharPositionFromPointClose(int x, int y);
	void SetMouseSelectionRectangularSwitch(bool mouseSelectionRectangularSwitch);
	bool MouseSelectionRectangularSwitch();
	void SetMultipleSelection(bool multipleSelection);
	bool MultipleSelection();
	void SetAdditionalSelectionTyping(bool additionalSelectionTyping);
	bool AdditionalSelectionTyping();
	void SetAdditionalCaretsBlink(bool additionalCaretsBlink);
	bool AdditionalCaretsBlink();
	void SetAdditionalCaretsVisible(bool additionalCaretsVisible);
	bool AdditionalCaretsVisible();
	int Selections();
	bool SelectionEmpty();
	void ClearSelections();
	void SetSelection(Position caret, Position anchor);
	void AddSelection(Position caret, Position anchor);
	int SelectionFromPoint(int x, int y);
	void DropSelectionN(int selection);
	void SetMainSelection(int selection);
	int MainSelection();
	void SetSelectionNCaret(int selection, Position caret);
	Position SelectionNCaret(int selection);
	void SetSelectionNAnchor(int selection, Position anchor);
	Position SelectionNAnchor(int selection);
	void SetSelectionNCaretVirtualSpace(int selection, Position space);
	Position SelectionNCaretVirtualSpace(int selection);
	void SetSelectionNAnchorVirtualSpace(int selection, Position space);
	Position SelectionNAnchorVirtualSpace(int selection);
	void SetSelectionNStart(int selection, Position anchor);
	Position SelectionNStart(int selection);
	Position SelectionNStartVirtualSpace(int selection);
	void SetSelectionNEnd(int selection, Position caret);
	Position SelectionNEndVirtualSpace(int selection);
	Position SelectionNEnd(int selection);
	void SetRectangularSelectionCaret(Position caret);
	Position RectangularSelectionCaret();
	void SetRectangularSelectionAnchor(Position anchor);
	Position RectangularSelectionAnchor();
	void SetRectangularSelectionCaretVirtualSpace(Position space);
	Position RectangularSelectionCaretVirtualSpace();
	void SetRectangularSelectionAnchorVirtualSpace(Position space);
	Position RectangularSelectionAnchorVirtualSpace();
	void SetVirtualSpaceOptions(Scintilla::VirtualSpace virtualSpaceOptions);
	Scintilla::VirtualSpace VirtualSpaceOptions();
	void SetRectangularSelectionModifier(int modifier);
	int RectangularSelectionModifier();
	void SetAdditionalSelFore(Colour fore);
	void SetAdditionalSelBack(Colour back);
	void SetAdditionalSelAlpha(Scintilla::Alpha alpha);
	Scintilla::Alpha AdditionalSelAlpha();
	void SetAdditionalCaretFore(Colour fore);
	Colour AdditionalCaretFore();
	void RotateSelection();
	void SwapMainAnchorCaret();
	void MultipleSelectAddNext();
	void MultipleSelectAddEach();
	int ChangeLexerState(Position start, Position end);
	Line ContractedFoldNext(Line lineStart);
	void VerticalCentreCaret();
	void MoveSelectedLinesUp();
	void MoveSelectedLinesDown();
	void SetIdentifier(int identifier);
	int Identifier();
	void RGBAImageSetWidth(int width);
	void RGBAImageSetHeight(int height);
	void RGBAImageSetScale(int scalePercent);
	void MarkerDefineRGBAImage(int markerNumber, const char *pixels);
	void RegisterRGBAImage(int type, const char *pixels);
	void ScrollToStart();
	void ScrollToEnd();
	void SetTechnology(Scintilla::Technology technology);
	Scintilla::Technology Technology();
	void *CreateLoader(Position bytes, Scintilla::DocumentOption documentOptions);
	void FindIndicatorShow(Position start, Position end);
	void FindIndicatorFlash(Position start, Position end);
	void FindIndicatorHide();
	void VCHomeDisplay();
	void VCHomeDisplayExtend();
	bool CaretLineVisibleAlways();
	void SetCaretLineVisibleAlways(bool alwaysVisible);
	void SetLineEndTypesAllowed(Scintilla::LineEndType lineEndBitSet);
	Scintilla::LineEndType LineEndTypesAllowed();
	Scintilla::LineEndType LineEndTypesActive();
	void SetRepresentation(const char *encodedCharacter, const char *representation);
	int Representation(const char *encodedCharacter, char *representation);
	std::string Representation(const char *encodedCharacter);
	void ClearRepresentation(const char *encodedCharacter);
	void ClearAllRepresentations();
	void SetRepresentationAppearance(const char *encodedCharacter, Scintilla::RepresentationAppearance appearance);
	Scintilla::RepresentationAppearance RepresentationAppearance(const char *encodedCharacter);
	void SetRepresentationColour(const char *encodedCharacter, ColourAlpha colour);
	ColourAlpha RepresentationColour(const char *encodedCharacter);
	void EOLAnnotationSetText(Line line, const char *text);
	int EOLAnnotationGetText(Line line, char *text);
	std::string EOLAnnotationGetText(Line line);
	void EOLAnnotationSetStyle(Line line, int style);
	int EOLAnnotationGetStyle(Line line);
	void EOLAnnotationClearAll();
	void EOLAnnotationSetVisible(Scintilla::EOLAnnotationVisible visible);
	Scintilla::EOLAnnotationVisible EOLAnnotationGetVisible();
	void EOLAnnotationSetStyleOffset(int style);
	int EOLAnnotationGetStyleOffset();
	bool SupportsFeature(Scintilla::Supports feature);
	Scintilla::LineCharacterIndexType LineCharacterIndex();
	void AllocateLineCharacterIndex(Scintilla::LineCharacterIndexType lineCharacterIndex);
	void ReleaseLineCharacterIndex(Scintilla::LineCharacterIndexType lineCharacterIndex);
	Line LineFromIndexPosition(Position pos, Scintilla::LineCharacterIndexType lineCharacterIndex);
	Position IndexPositionFromLine(Line line, Scintilla::LineCharacterIndexType lineCharacterIndex);
	void StartRecord();
	void StopRecord();
	int Lexer();
	void Colourise(Position start, Position end);
	void SetProperty(const char *key, const char *value);
	void SetKeyWords(int keyWordSet, const char *keyWords);
	int Property(const char *key, char *value);
	std::string Property(const char *key);
	int PropertyExpanded(const char *key, char *value);
	std::string PropertyExpanded(const char *key);
	int PropertyInt(const char *key, int defaultValue);
	int LexerLanguage(char *language);
	std::string LexerLanguage();
	void *PrivateLexerCall(int operation, void *pointer);
	int PropertyNames(char *names);
	std::string PropertyNames();
	Scintilla::TypeProperty PropertyType(const char *name);
	int DescribeProperty(const char *name, char *description);
	std::string DescribeProperty(const char *name);
	int DescribeKeyWordSets(char *descriptions);
	std::string DescribeKeyWordSets();
	Scintilla::LineEndType LineEndTypesSupported();
	int AllocateSubStyles(int styleBase, int numberStyles);
	int SubStylesStart(int styleBase);
	int SubStylesLength(int styleBase);
	int StyleFromSubStyle(int subStyle);
	int PrimaryStyleFromStyle(int style);
	void FreeSubStyles();
	void SetIdentifiers(int style, const char *identifiers);
	int DistanceToSecondaryStyles();
	int SubStyleBases(char *styles);
	std::string SubStyleBases();
	int NamedStyles();
	int NameOfStyle(int style, char *name);
	std::string NameOfStyle(int style);
	int TagsOfStyle(int style, char *tags);
	std::string TagsOfStyle(int style);
	int DescriptionOfStyle(int style, char *description);
	std::string DescriptionOfStyle(int style);
	void SetILexer(void *ilexer);
	Scintilla::Bidirectional Bidirectional();
	void SetBidirectional(Scintilla::Bidirectional bidirectional);

//--Autogenerated -- end of section automatically generated from Scintilla.iface

};

}

#endif