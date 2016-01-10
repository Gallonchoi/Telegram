#include "tcpconnection.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include "greeting.h"

TcpConnection::TcpConnection(QTcpSocket *tcpSocket, Type type,
                             Greeting *greetingMsg, QObject *parent)
    : QObject(parent),
      type(type),
      tcpSocket(tcpSocket),
      greetingMsg(greetingMsg) {
  if (type == Type::Client) {
    // 对方为服务端, 先发送请求
    QJsonDocument data(*(greetingMsg->msg));
    QByteArray msg = data.toBinaryData();
    tcpSocket->write(msg);
  }
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvGreeting()));
}

TcpConnection::~TcpConnection() { delete tcpSocket; }

void TcpConnection::recvGreeting() {
  disconnect(tcpSocket, SIGNAL(readyRead()));
  QByteArray data = tcpSocket->readAll();
  userInfo = QJsonObject(QJsonDocument::fromBinaryData(data).object());
  if (type == Type::Server) {
    QJsonDocument data(*(greetingMsg->msg));
    QByteArray msg = data.toBinaryData();
    tcpSocket->write(msg);
  }
  validated(this);
}
