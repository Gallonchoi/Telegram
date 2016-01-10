#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog {
  Q_OBJECT

 public:
  explicit AboutWindow(const QString &title, QWidget *parent = 0);
  ~AboutWindow();

 private slots:
  void hid();

 private:
  Ui::AboutWindow *ui;
};

#endif  // ABOUTWINDOW_H
