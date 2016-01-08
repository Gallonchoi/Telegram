#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
class QTcpServer;
class QTcpSocket;

class TcpServer : public QObject {
  Q_OBJECT
 public:
  explicit TcpServer(QObject *parent = 0);

  void listen(const quint16 port);

 signals:
  void gotNewConnection(QTcpSocket *);

 public slots:
  void newConnection();

 private:
  QTcpServer *tcpServer;
};

#endif  // TCPSERVER_H
