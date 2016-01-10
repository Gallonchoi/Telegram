#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QJsonObject>

class QTcpSocket;
class Greeting;

class TcpConnection : public QObject {
  Q_OBJECT
 public:
  enum class Type { Server, Client };
  TcpConnection(QTcpSocket *, Type, Greeting *, QObject *parent = 0);
  ~TcpConnection();

  QJsonObject getUserInfo() const { return userInfo; }
  const Type type;
 signals:
  void validated(TcpConnection *);

 private slots:
  void recvGreeting();

 private:
  QTcpSocket *tcpSocket;
  Greeting *greetingMsg;
  QJsonObject userInfo;
};

#endif  // TCPCONNECTION_H
