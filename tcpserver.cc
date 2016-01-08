#include "tcpserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

TcpServer::TcpServer(QObject *parent)
    : QObject(parent), tcpServer(new QTcpServer) {
  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
  if (tcpServer->listen(QHostAddress::Any, 23333)) {
    qDebug() << "TCP server start listening 23333";
  } else {
    qDebug() << "TCP server cannot start";
  }
}

void TcpServer::newConnection() {
  QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
  qDebug() << "Got new connection from " << tcpSocket->peerAddress().toString()
           << ":" << tcpSocket->peerPort();
  gotNewConnection(tcpSocket);
}
