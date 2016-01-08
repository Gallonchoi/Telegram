#include "udplistener.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QJsonDocument>

UdpListener::UdpListener(const quint16 port, QObject *parent)
    : port(port), QObject(parent), udpSocket(NULL) {
  response = new QJsonObject({{"username", "Unknown"}, {"ip", "Unknown"}});
}

void UdpListener::start() {
  if (!udpSocket) {
    delete udpSocket;
  }

  // 初始化socket 并监听端口
  udpSocket = new QUdpSocket;
  udpSocket->bind(QHostAddress::AnyIPv4, port);
  connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getRequest()));
}

// 获取到请求, 返回应答
void UdpListener::getRequest() {
  QByteArray datagram;
  datagram.resize(udpSocket->pendingDatagramSize());
  QHostAddress *targetAddress = new QHostAddress;
  quint16 *targetPort = new quint16;
  // 接收请求
  udpSocket->readDatagram(datagram.data(), datagram.size(), targetAddress,
                          targetPort);
  qDebug() << "Listener get: "
           << QJsonDocument::fromBinaryData(datagram).toJson();
  // 返回应答
  QJsonDocument data(*response);
  QByteArray res = data.toBinaryData();
  udpSocket->writeDatagram(res, *targetAddress, *targetPort);
}
