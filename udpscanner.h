#ifndef UDPSCANNER_H
#define UDPSCANNER_H
#include <QObject>
#include <QJsonObject>
#include "serverstatus.h"

class QTimer;
class QElapsedTimer;
class QUdpSocket;
class QHostAddress;
class Greeting;

// 发送UDP广播扫描当前子网的服务器
class UdpScanner : public QObject {
  Q_OBJECT
 public:
  explicit UdpScanner(const quint16 port, QObject *parent = 0);
  ~UdpScanner();

  void setGreetingMsg(Greeting *msg) { greetingMsg = msg; }

  const quint16 port;

 signals:
  void gotServerStatusList(ServerStatusList serverStatusList);
  void timeout();

 public slots:
  void startScan(const int timeout = 5000);
  void getResponse();
  void resetSocket();

 private:
  QUdpSocket *udpSocket;
  QTimer *timeoutTimer;
  QElapsedTimer *latencyTimer;
  Greeting *greetingMsg;
};

#endif  // UDPSCANNER_H
