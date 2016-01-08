#ifndef SERVERSCANNER_H
#define SERVERSCANNER_H
#include <QObject>
#include "serverstatus.h"

class QTimer;
class QElapsedTimer;
class QUdpSocket;
class QHostAddress;

// 发送UDP广播扫描当前子网端口23333的服务器
class ServerScanner : public QObject {
  Q_OBJECT
 public:
  explicit ServerScanner(QObject *parent = 0);
  ~ServerScanner();

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

#endif  // SERVERSCANNER_H
