#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;
class QHostAddress;

class TcpClient : public QObject {
  Q_OBJECT
 public:
  explicit TcpClient(QObject *parent = 0);

  void connectTo(QHostAddress *host, const quint16 port);
 signals:
  void connected(QTcpSocket *);
  void gotErrors(const QString &);
 private slots:
  void displayErrors(QAbstractSocket::SocketError);
  void getConnect();

 private:
  QTcpSocket *tcpSocket;
};

#endif  // TCPCLIENT_H
