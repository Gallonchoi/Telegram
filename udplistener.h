#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QByteArray>

class QUdpSocket;
class QHostAddress;

// 监听端口23333的UDP
class UdpListener : public QObject {
  Q_OBJECT
 public:
  explicit UdpListener(QObject *parent = 0);

  void setResponse(const QByteArray &newResponse) { response = newResponse; }

  void start();
 signals:

 private slots:
  void getRequest();

 private:
  QUdpSocket *udpSocket;
  QByteArray response;
};

#endif  // UDPLISTENER_H
