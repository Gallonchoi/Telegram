#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QJsonObject>

class QTcpServer;
class QTcpSocket;
class TcpConnection;
class Greeting;

class TcpServer : public QObject {
  Q_OBJECT
 public:
  explicit TcpServer(const quint16 port, QObject *parent = 0);

  void start();
  void setGreetingMsg(Greeting *msg) { greetingMsg = msg; }

  const quint16 port;
 signals:
  void gotNewConnection(TcpConnection *);

 public slots:
  void acceptConnection();

 private:
  QTcpServer *tcpServer;

  Greeting *greetingMsg;
};

#endif  // TCPSERVER_H
