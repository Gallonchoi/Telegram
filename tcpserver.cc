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

void TcpServer::acceptConnection() {
  QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
  qDebug() << "Got new connection from " << tcpSocket->peerAddress().toString()
           << ":" << tcpSocket->peerPort();
  TcpConnection *connection =
      new TcpConnection(tcpSocket, TcpConnection::Type::Server);
  if (connection->isValid())
    gotNewConnection(connection);
  else
    delete connection;
}
