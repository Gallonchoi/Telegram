#ifndef SCANWINDOW_H
#define SCANWINDOW_H

#include <QDialog>
#include "serverstatus.h"

class UdpScanner;
class QHostAddress;
class ServerStatus;
class Greeting;
class TcpConnection;
class TcpClient;

namespace Ui {
class ScanWindow;
}

class ScanWindow : public QDialog {
  Q_OBJECT

 public:
  explicit ScanWindow(const QString &title, QWidget *parent = 0);
  ~ScanWindow();

  void initScanner(const quint16 port, Greeting *request);
  void initTcpClient(TcpClient *tcpClient) { this->tcpClient = tcpClient; }

 signals:
  void hid();
  void gotNewConnection(TcpConnection *);

 private slots:
  void appendServers(ServerStatusList);
  void finishScan();
  void startScan();
  void cancelScan();
  void tryToConnect(int, int);

 private:
  Ui::ScanWindow *ui;
  UdpScanner *udpScanner;
  TcpClient *tcpClient;
};

#endif  // SCANWINDOW_H
