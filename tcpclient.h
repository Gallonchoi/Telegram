#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QJsonObject>

class QHostAddress;
class TcpConnection;
class Greeting;

class TcpClient : public QObject {
  Q_OBJECT
 public:
  explicit TcpClient(QObject *parent = 0);

  void connectTo(QHostAddress *host, const quint16 port);
  void setGreetingMsg(Greeting *msg) { greetingMsg = msg; }
 signals:
  void connected(TcpConnection *);
  void gotErrors(const QString &);
 private slots:
  void displayErrors(const QString &);

 private:
  Greeting *greetingMsg;
};

#endif  // TCPCLIENT_H
