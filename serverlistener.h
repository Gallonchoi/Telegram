#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QObject>
#include <QByteArray>

class QUdpSocket;
class QHostAddress;

// 监听端口23333的UDP
class ServerListener : public QObject {
  Q_OBJECT
 public:
  explicit ServerListener(QObject *parent = 0);

  void setResponse(const QByteArray &newResponse) { response = newResponse; }

  void start();
 signals:

 private slots:
  void getRequest();

 private:
  QUdpSocket *udpSocket;
  QByteArray response;
};

#endif  // SERVERLISTENER_H
