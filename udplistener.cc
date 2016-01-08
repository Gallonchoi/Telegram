#include "udplistener.h"
#include <QUdpSocket>
#include <QHostAddress>

UdpListener::UdpListener(QObject *parent)
    : QObject(parent), udpSocket(NULL) {}

void UdpListener::start() {
  if (!udpSocket) {
    delete udpSocket;
  }

  udpSocket = new QUdpSocket;
  udpSocket->bind(23333, QUdpSocket::ShareAddress);
  connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getRequest()));
}

// 获取到请求, 返回应答
void UdpListener::getRequest() {
  QByteArray datagram;
  datagram.resize(udpSocket->pendingDatagramSize());
  QHostAddress *targetAddress = new QHostAddress;
  quint16 *targetPort = new quint16;
  udpSocket->readDatagram(datagram.data(), datagram.size(), targetAddress,
                          targetPort);
  qDebug() << "Listener get: " << datagram;
  udpSocket->writeDatagram(response, *targetAddress, *targetPort);
}
