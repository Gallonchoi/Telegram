#ifndef UDPSCANNER_H
#define UDPSCANNER_H
#include <QObject>
#include "serverstatus.h"

class QTimer;
class QElapsedTimer;
class QUdpSocket;
class QHostAddress;

// 发送UDP广播扫描当前子网端口23333的服务器
class UdpScanner : public QObject {
  Q_OBJECT
 public:
    explicit UdpScanner(QObject *parent = 0);
          ~UdpScanner();

 signals:
  void gotServerStatusList(ServerStatusList serverStatusList);

 public slots:
  void startScan(const int timeout = 5);
  void getResponse();
  void resetSocket();

 private:
  QUdpSocket *udpSocket;
  QTimer *timeoutTimer;
  QElapsedTimer *latencyTimer;
  int timeout;
};

#endif  // UDPSCANNER_H
