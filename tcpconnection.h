#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QJsonObject>

class QTcpSocket;

class TcpConnection : public QObject {
  Q_OBJECT
 public:
  enum class Type { Server, Client };
  explicit TcpConnection(QTcpSocket *, Type, QObject *parent = 0);
  ~TcpConnection();

  void isValid();
  void setGreetingMsg(QJsonObject *msg) { greetingMsg = msg; }
  const Type type;
 signals:

 public slots:

 private:
  QTcpSocket *tcpSocket;
  QJsonObject *greetingMsg;
};

#endif  // TCPCONNECTION_H
