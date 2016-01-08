#include "serverscanner.h"
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>
#include "serverstatus.h"

ServerScanner::ServerScanner(QObject *parent)
    : QObject(parent),
      timeoutTimer(new QTimer),
      latencyTimer(new QElapsedTimer) {
  connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(resetSocket()));
}

ServerScanner::~ServerScanner() {}

// 开始发送UDP广播报文扫描
void ServerScanner::startScan(const int timeout) {
  qDebug() << "Server scanner starts scanning";
  QByteArray datagram = "/r/n/n/nTelegram scan sender/r/n";
  udpSocket = new QUdpSocket;
  connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getResponse()));
  udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 23333);
  latencyTimer->start();
  timeoutTimer->start(timeout * 1000);
}

// 重置UDP socket
void ServerScanner::resetSocket() {
  qDebug() << "Scanner timeout";
  delete udpSocket;
}

// 收到回复
void ServerScanner::getResponse() {
  ServerStatusList serverStatusList = new QList<ServerStatus *>;
  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    QHostAddress *targetAddress = new QHostAddress;
    udpSocket->readDatagram(datagram.data(), datagram.size(), targetAddress);
    ServerStatus *serverStatus = new ServerStatus;
    serverStatus->address = targetAddress;
    int latency = latencyTimer->elapsed();  // 获取时延
    serverStatus->delay = latency > 0 ? latency : 0;
    serverStatus->username = datagram;
    qDebug() << serverStatus->username << serverStatus->address
             << serverStatus->delay;
    serverStatusList->append(serverStatus);
  }
  if (!serverStatusList->isEmpty()) {
    gotServerStatusList(serverStatusList);
  }
}
