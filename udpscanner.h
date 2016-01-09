#ifndef UDPSCANNER_H
#define UDPSCANNER_H
#include <QObject>
#include <QJsonObject>
#include "serverstatus.h"

class QTimer;
class QElapsedTimer;
class QUdpSocket;
class QHostAddress;

// 发送UDP广播扫描当前子网端口23333的服务器
class UdpScanner : public QObject {
  Q_OBJECT
 public:
  explicit UdpScanner(const quint16 port, QObject *parent = 0);
  ~UdpScanner();

  void setGreetingMsg(QJsonObject *msg) { greetingMsg = msg; }

  const quint16 port;

 signals:
  void gotServerStatusList(ServerStatusList serverStatusList);
  void timeout();

 public slots:
  void startScan(const int timeout = 5000);
  void getResponse();
  void resetSocket();
  void updateGreeting(QJsonObject *msg) { greetingMsg = msg; }

 private:
  QUdpSocket *udpSocket;
  QTimer *timeoutTimer;
  QElapsedTimer *latencyTimer;
  QJsonObject *greetingMsg;
};

#endif  // UDPSCANNER_H
