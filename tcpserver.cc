#include "tcpserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "tcpconnection.h"

TcpServer::TcpServer(const quint16 port, QObject *parent)
    : QObject(parent), port(port), tcpServer(new QTcpServer) {
  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void TcpServer::start() {
  if (tcpServer->listen(QHostAddress::Any, port)) {
    qDebug() << "TCP server start listening " << port;
  } else {
    qDebug() << "TCP server cannot start";
  }
}

// 收到新连接
void TcpServer::acceptConnection() {
  auto tcpSocket = tcpServer->nextPendingConnection();
  qDebug() << "Got new connection from " << tcpSocket->peerAddress().toString()
           << ":" << tcpSocket->peerPort();
  auto connection =
      new TcpConnection(tcpSocket, TcpConnection::Type::Server, greetingMsg);
  connect(connection, SIGNAL(validated(TcpConnection *)), this,
          SIGNAL(gotNewConnection(TcpConnection *)));
}
