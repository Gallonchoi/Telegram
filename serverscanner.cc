#include "serverscanner.h"
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>
#include "serverstatus.h"

ServerScanner::ServerScanner(const unsigned port)
    : port(port),
      udpSocket(new QUdpSocket),
      timeoutTimer(new QTimer),
      delayTimer(new QElapsedTimer) {
  udpSocket->bind(port, QUdpSocket::ShareAddress);
  connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(getResponse()));
}

ServerScanner::~ServerScanner() {}

void ServerScanner::startScan(const int timeout) {
  qDebug() << "Server scanner starts scanning";
  QByteArray datagram = "/r/n/n/nTelegram scan sender/r/n";
  udpSocket->writeDatagram(datagram.data(), datagram.size(),
                           QHostAddress::Broadcast, port);
  delayTimer->start();
  this->timeout = timeout;
  getResponse();
}

void ServerScanner::getResponse() {
  ServerStatusList serverStatusList = new QList<ServerStatus *>;
  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    QHostAddress *targetAddress = new QHostAddress;
    udpSocket->readDatagram(datagram.data(), datagram.size(), targetAddress);
    ServerStatus *serverStatus = new ServerStatus;
    serverStatus->address = targetAddress;
    int delay = delayTimer->elapsed() - 1000;
    serverStatus->delay = delay > 0 ? delay : 0;
    serverStatus->username = datagram;
    qDebug() << serverStatus->username << serverStatus->address
             << serverStatus->delay;
    serverStatusList->append(serverStatus);
  }
  if (!serverStatusList->isEmpty()) {
    gotServerStatusList(serverStatusList);
  }
  if (timeout > 0) {
    timeoutTimer->start(1000);
  } else if (timeout < 0) {
    timeoutTimer->stop();
    qDebug() << "Scanner timeout";
  }
  --timeout;
}
