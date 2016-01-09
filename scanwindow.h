#ifndef SCANWINDOW_H
#define SCANWINDOW_H

#include <QDialog>
#include "serverstatus.h"

class UdpScanner;
class QHostAddress;
class ServerStatus;
class QJsonObject;

namespace Ui {
class ScanWindow;
}

class ScanWindow : public QDialog {
  Q_OBJECT

 public:
  explicit ScanWindow(QWidget *parent = 0);
  ~ScanWindow();

  void initScanner(const quint16 port, QJsonObject *request);

 signals:
  void hid();

 private slots:
  void appendServers(ServerStatusList);
  void finishScan();
  void startScan();
  void cancelScan();

 private:
  Ui::ScanWindow *ui;
  UdpScanner *udpScanner;
  ServerStatusList serverStatusList;
};

#endif  // SCANWINDOW_H
