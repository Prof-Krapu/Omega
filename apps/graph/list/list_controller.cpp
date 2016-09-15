#include "list_controller.h"
#include <assert.h>

ListController::ListController(Responder * parentResponder, Graph::FunctionStore * functionStore) :
  ViewController(parentResponder),
  m_tableView(TableView(this)),
  m_activeCell(-1),
  m_manualScrolling(0),
  m_functionStore(functionStore),
  m_parameterController(ParameterController(this))
{
}

View * ListController::view() {
  setActiveCell(0);
  return &m_tableView;
}

const char * ListController::title() const {
  return "Fonctions";
}

void ListController::setActiveCell(int index) {
  if (index < 0 || index >= m_functionStore->numberOfFunctions()) {
    return;
  }

  m_activeCell = index;
  m_tableView.scrollToRow(index);
  FunctionCell * cell = (FunctionCell *)(m_tableView.cellAtIndex(index));
  cell->setParentResponder(this);
  app()->focus(cell);
}

bool ListController::handleEvent(Ion::Events::Event event) {
  switch (event) {
    case Ion::Events::Event::DOWN_ARROW:
      setActiveCell(m_activeCell+1);
      return true;
    case Ion::Events::Event::UP_ARROW:
      setActiveCell(m_activeCell-1);
      return true;
    case Ion::Events::Event::ENTER:
      ((StackViewController *) parentResponder())->push(&m_parameterController);
      return true;
    case Ion::Events::Event::PLUS:
      m_manualScrolling += 10;
      m_tableView.setContentOffset({0, m_manualScrolling});
      return true;
    default:
      return false;
  }
}

int ListController::numberOfCells() {
  return m_functionStore->numberOfFunctions();
};

View * ListController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_maxNumberOfCells);
  return &m_cells[index];
}

int ListController::reusableCellCount() {
  return k_maxNumberOfCells;
}

void ListController::willDisplayCellForIndex(View * cell, int index) {
  FunctionCell * myCell = (FunctionCell *)cell;
  myCell->setFunction(m_functionStore->functionAtIndex(index));
  myCell->setEven(index%2 == 0);
}

KDCoordinate ListController::cellHeight() {
  return 40;
}
