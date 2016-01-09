#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QJsonObject>

class QUdpSocket;
class QHostAddress;

// 监听端口23333的UDP
class UdpListener : public QObject {
  Q_OBJECT
 public:
  explicit UdpListener(const quint16 port, QObject *parent = 0);

  void start();

  const quint16 port;
  void setResponse(QJsonObject *res) { response = res; }

 signals:
  void gotRequest();

 public slots:
  void updateResponse(QJsonObject *res) { response = res; }
 private slots:
  void getRequest();

 private:
  QUdpSocket *udpSocket;
  QJsonObject *response;
};

#endif  // UDPLISTENER_H
