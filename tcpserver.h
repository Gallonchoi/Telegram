#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;
class TcpConnection;

class TcpServer : public QObject {
  Q_OBJECT
 public:
  explicit TcpServer(const quint16 port, QObject *parent = 0);

  void start();

  const quint16 port;
 signals:
  void gotNewConnection(TcpConnection *);

 public slots:
  void acceptConnection();

 private:
  QTcpServer *tcpServer;
};

#endif  // TCPSERVER_H
