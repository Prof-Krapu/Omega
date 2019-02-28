#ifndef SEQUENCE_LIST_PARAM_CONTROLLER_H
#define SEQUENCE_LIST_PARAM_CONTROLLER_H

#include "../../shared/storage_list_parameter_controller.h"
#include "../../shared/parameter_text_field_delegate.h"
#include "../sequence.h"
#include "../sequence_store.h"
#include "type_parameter_controller.h"

namespace Sequence {

class ListController;

class ListParameterController : public Shared::StorageListParameterController, public SelectableTableViewDelegate, public Shared::ParameterTextFieldDelegate {
public:
  ListParameterController(::InputEventHandlerDelegate * inputEventHandlerDelegate, ListController * list);
  const char * title() override;
  bool handleEvent(Ion::Events::Event event) override;
  HighlightCell * reusableCell(int index) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;

  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  void tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) override;
  Shared::TextFieldDelegateApp * textFieldDelegateApp() override;
private:
#if FUNCTION_COLOR_CHOICE
  constexpr static int k_totalNumberOfCell = 5;
#else
  constexpr static int k_totalNumberOfCell = 4;
#endif
  int totalNumberOfCells() const override;
  Shared::ExpiringPointer<Sequence> sequence() { return static_cast<Shared::ExpiringPointer<Sequence>>(function()); }
  bool hasInitialRankRow() const;
  MessageTableCellWithChevronAndExpression m_typeCell;
  MessageTableCellWithEditableText m_initialRankCell;
  char m_draftTextBuffer[MessageTableCellWithEditableText::k_bufferLength];
  TypeParameterController m_typeParameterController;
};

}

#endif
