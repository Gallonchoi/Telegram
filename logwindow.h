#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>

namespace Ui {
class LogWindow;
}

class LogWindow : public QDialog {
  Q_OBJECT

 public:
  explicit LogWindow(const QString &title, QWidget *parent = 0);
  ~LogWindow();

 private slots:
  void hid();

 private:
  Ui::LogWindow *ui;
};

#endif  // LOGWINDOW_H
