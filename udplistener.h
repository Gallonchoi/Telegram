#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QJsonObject>

class QUdpSocket;
class QHostAddress;
class Greeting;

// 监听端口23333的UDP
class UdpListener : public QObject {
  Q_OBJECT
 public:
  explicit UdpListener(const quint16 port, QObject *parent = 0);

  void start();

  const quint16 port;
  void setGreetingMsg(Greeting *msg) { greetingMsg = msg; }

 signals:
  void gotRequest();

 private slots:
  void getRequest();

 private:
  QUdpSocket *udpSocket;
  Greeting *greetingMsg;
};

#endif  // UDPLISTENER_H
