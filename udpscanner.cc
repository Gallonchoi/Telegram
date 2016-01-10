#include "udpscanner.h"
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include "serverstatus.h"
#include "greeting.h"

UdpScanner::UdpScanner(const quint16 port, QObject *parent)
    : QObject(parent),
      port(port),
      timeoutTimer(new QTimer),
      latencyTimer(new QElapsedTimer) {
  connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(resetSocket()));
}

UdpScanner::~UdpScanner() {}

// 开始发送UDP广播报文扫描
void UdpScanner::startScan(const int timeout) {
  qDebug() << "Server scanner starts scanning";

  // 初始化socket
  udpSocket = new QUdpSocket;
  connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getResponse()));
  // 发送问候
  QJsonDocument data(*(greetingMsg->msg));
  QByteArray datagram = data.toBinaryData();
  udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, port);
  // 初始化时延计时器和超时计时器
  latencyTimer->start();
  timeoutTimer->start(timeout);
}

// 重置UDP socket
void UdpScanner::resetSocket() {
  qDebug() << "Scanner timeout";
  timeoutTimer->stop();
  delete udpSocket;
  timeout();
}

// 收到回复
void UdpScanner::getResponse() {
  ServerStatusList serverStatusList = new QList<ServerStatus *>;
  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    QHostAddress *targetAddress = new QHostAddress;
    quint16 *targetPort = new quint16;
    udpSocket->readDatagram(datagram.data(), datagram.size(), targetAddress,
                            targetPort);
    ServerStatus *serverStatus = new ServerStatus;
    // NOTE: 对方地址默认为IPv6， 手动转换为IPv4
    serverStatus->address =
        new QHostAddress(targetAddress->toIPv4Address());  // 获取对方地址
    delete targetAddress;
    serverStatus->latency = latencyTimer->elapsed();  // 获取时延
    serverStatus->port = port;
    serverStatus->userinfo = new QJsonObject(
        QJsonDocument::fromBinaryData(datagram).object());  // 用户信息
    serverStatusList->append(serverStatus);
  }
  // 触发接收窗口信号
  if (!serverStatusList->isEmpty()) {
    gotServerStatusList(serverStatusList);
  }
}
