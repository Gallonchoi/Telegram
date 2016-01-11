#include "tcpconnection.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QTime>
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
  connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

TcpConnection::~TcpConnection() { delete tcpSocket; }

// 接收握手请求或回应
void TcpConnection::recvGreeting() {
  disconnect(tcpSocket, SIGNAL(readyRead()), 0, 0);
  QByteArray data = tcpSocket->readAll();
  userInfo = QJsonObject(QJsonDocument::fromBinaryData(data).object());
  if (type == Type::Server) {
    QJsonDocument data(*(greetingMsg->msg));
    QByteArray msg = data.toBinaryData();
    tcpSocket->write(msg);
  }
  validated(this);
  connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpConnection::readyRead);
}

void TcpConnection::readyRead() {
  qDebug() << "read";
  QByteArray data = tcpSocket->readAll();
  auto message = new QJsonObject(QJsonDocument::fromBinaryData(data).object());
  message->insert("time", QJsonValue(QTime::currentTime().toString()));
  recvMessage(message);
}

void TcpConnection::sendMessage(QJsonObject *content) {
  qDebug() << "send";
  QJsonDocument data(*content);
  QByteArray msg = data.toBinaryData();
  tcpSocket->write(msg);
  delete content;
}
