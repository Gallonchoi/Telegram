#include "tcpclient.h"
#include "tcpconnection.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QAbstractSocket>

TcpClient::TcpClient(QObject *parent) : QObject(parent) {}

void TcpClient::connectTo(QHostAddress *host, const quint16 port) {
  auto tcpSocket = new QTcpSocket;

  connect(tcpSocket,
          static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(
              &QAbstractSocket::error),
          [this, tcpSocket] { this->displayErrors(tcpSocket->errorString()); });

  connect(tcpSocket, &QTcpSocket::connected, [this, tcpSocket] {
    auto connection = new TcpConnection(tcpSocket, TcpConnection::Type::Client,
                                        this->greetingMsg);
    connect(connection, SIGNAL(validated(TcpConnection *)), this,
            SIGNAL(connected(TcpConnection *)));
  });
  tcpSocket->connectToHost(*host, port);
}

void TcpClient::displayErrors(const QString &errors) {
  gotErrors(errors);
  qDebug() << errors;
}
