#ifndef SCANWINDOW_H
#define SCANWINDOW_H

#include <QDialog>
#include "serverstatus.h"

class ServerScanner;
class QHostAddress;
class ServerStatus;

namespace Ui {
class ScanWindow;
}

class ScanWindow : public QDialog {
  Q_OBJECT

 public:
  explicit ScanWindow(QWidget *parent = 0);
  ~ScanWindow();

 signals:
  void hid();

 private slots:
  void appendServers(ServerStatusList);
  void cancelScan();

 private:
  Ui::ScanWindow *ui;
  ServerScanner *serverScanner;
};

#endif  // SCANWINDOW_H
