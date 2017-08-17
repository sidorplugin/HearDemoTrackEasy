#ifndef WAITINGWIDGET_H
#define WAITINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMovie>

static const double CENTER_POSITION_FROM_PARENT_TOP = 0.5;
static const char* const STYLESHEET =
    "QLabel {"
    "  font-weight: bold;"
    "  padding: 10px 15px;"
    "  border: 1px solid;"
    "  border-radius: 5px;"
    "}"
    "[class=Info] {"
    "  background-color: rgba(255, 255, 153, 200);"
    "  border-color: orange;"
    "}"
    "[class=Ok] {"
    "  background-color: rgba(204, 255, 153, 200);"
    "  border-color: green;"
    "}"
    "[class=Error] {"
    "  background-color: rgba(255, 153, 153, 200);"
    "  border-color: red;"
    "}"
    "[class=Wait] {"
    "  background-color: rgba(224, 224, 224, 200);"
    "  border-color: gray;"
    "}";

class WaitingWidget : public QWidget
{
  Q_OBJECT
public:
  explicit WaitingWidget(QWidget *parent = 0);
  ~WaitingWidget();

  // Устанавливает в виджет текстовую информацию о состоянии обработки.
  void setFetchingPage(int count, int total);

protected:
    void resizeEvent( QResizeEvent* );

signals:

public slots:
    void start();
    void stop();

private:

private:
    QLabel* m_label;
    QLabel* m_textLabel;
    QMovie* m_movie;
    QWidget* m_parent;

};

#endif // WAITINGWIDGET_H
