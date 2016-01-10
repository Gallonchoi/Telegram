#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QDialog>

namespace Ui {
class connectWindow;
}

class ConnectWindow : public QDialog {
  Q_OBJECT

 public:
  explicit ConnectWindow(const QString &title, QWidget *parent = 0);
  ~ConnectWindow();

 private slots:
  void hid();

 private:
  Ui::connectWindow *ui;
};

#endif  // CONNECTWINDOW_H
