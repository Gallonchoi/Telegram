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
  const Type type;  // 在此连接中对方的类型
  QString getTypeString() const {
    if (type == Type::Client) {
      return "Client";
    } else {
      return "Server";
    }
  }
 signals:
  void validated(TcpConnection *);
  void recvMessage(QJsonObject *content);

 public slots:
  void sendMessage(QJsonObject *content);

 private slots:
  void readyRead();
  void recvGreeting();

 private:
  QTcpSocket *tcpSocket;
  Greeting *greetingMsg;
  QJsonObject userInfo;
};

#endif  // TCPCONNECTION_H
