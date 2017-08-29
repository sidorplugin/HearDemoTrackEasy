#include "validator.h"
#include "mainwindow.h"

Validator::Validator()
{
}


bool Validator::verify(int action, DataInput &input)
{
  bool result = false;

  switch (action) {
    case MainWindow::FetchAction :
    {
      QString genre = input.data(DataInput::Style).toString();
      QString period = input.data(DataInput::Period).toString();
      QString filter = input.data(DataInput::Filter).toString();
      if (!genre.isEmpty() || !period.isEmpty() || !filter.isEmpty())
        result = true;
    }
    break;

    case MainWindow::SearchAction :
    {
      QString searchString = input.data(DataInput::SearchText).toString();
      if (!searchString.isEmpty())
        result = true;
    }
    break;
  }

  return result;
}

