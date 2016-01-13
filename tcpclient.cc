#include "tcpclient.h"
#include "tcpconnection.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QAbstractSocket>

TcpClient::TcpClient(QObject *parent) : QObject(parent) {}

void TcpClient::connectTo(QHostAddress *host, const quint16 port) {
  auto tcpSocket = new QTcpSocket;

  // 错误处理
  connect(tcpSocket,
          static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(
              &QAbstractSocket::error),
          [this, tcpSocket] { this->displayErrors(tcpSocket->errorString()); });

  // 连接成功
  connect(tcpSocket, &QTcpSocket::connected, [this, tcpSocket] {
    auto connection = new TcpConnection(tcpSocket, TcpConnection::Type::Client,
                                        this->greetingMsg);
    // 检测连接是否可用(交换用户信息)
    connect(connection, SIGNAL(validated(TcpConnection *)), this,
            SIGNAL(connected(TcpConnection *)));
  });
  tcpSocket->connectToHost(*host, port);
}

void TcpClient::displayErrors(const QString &errors) {
  gotErrors(errors);
  qDebug() << errors;
}
