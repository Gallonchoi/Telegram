#include "tcpclient.h"
#include <QTcpSocket>
#include <QHostAddress>

TcpClient::TcpClient(QObject *parent) : QObject(parent), tcpSocket(NULL) {}

void TcpClient::connectTo(QHostAddress *host, const quint16 port) {
  if (tcpSocket) delete tcpSocket;
  tcpSocket = new QTcpSocket;
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(displayError(QAbstractSocket::SocketError)));
  connect(tcpSocket, SIGNAL(connected()), this, SLOT(getConnect()));
  tcpSocket->connectToHost(*host, port);
}

void TcpClient::displayErrors(QAbstractSocket::SocketError) {
  gotErrors(tcpSocket->errorString());
}

void TcpClient::getConnect() {
  connected(tcpSocket);
  tcpSocket = NULL;
}
