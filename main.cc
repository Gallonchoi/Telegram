//#include "telegram.hpp"
#include <QApplication>
#include <QHostInfo>
#include <QHostAddress>
#include <QAbstractSocket>
#include "mainwindow.h"
#include "scanwindow.h"
#include "connectwindow.h"
#include "aboutwindow.h"
#include "udplistener.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "greeting.h"

constexpr quint16 UDP_LISTENER_PORT = 23333;
constexpr quint16 TCP_SERVER_PORT = 23333;

// 获取本机IP地址
QStringList getIPAddress() {
// 获取IP地址
#ifdef _WIN32
  QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
  QList<QHostAddress> ipAddressList = hostInfo.addresses();
#else
  QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
#endif
  QStringList ipAddresses;
  // 获取本机公共IPv4地址
  foreach (const QHostAddress &address, ipAddressList) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol &&
        address != QHostAddress(QHostAddress::LocalHost))
      ipAddresses << address.toString();
  }
  return ipAddresses;
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  auto mainWindow = new MainWindow("Telegram");
  auto scanWindow = new ScanWindow("扫描");
  auto connectWindow = new ConnectWindow("连接到");
  auto aboutWindow = new AboutWindow("关于");
  // 按键事件
  QObject::connect(mainWindow, &MainWindow::scanButtonClicked, scanWindow,
                   &ScanWindow::show);
  QObject::connect(mainWindow, &MainWindow::connectButtonClicked, connectWindow,
                   &ConnectWindow::show);
  QObject::connect(mainWindow, &MainWindow::aboutButtonClicked, aboutWindow,
                   &AboutWindow::show);

  auto ips = getIPAddress();
  const auto ipString = ips.join("/");

  mainWindow->setIpAddress(ipString);

  // tcp和udp请求信息
  auto tcpGreetingMsg = new Greeting;
  auto udpGreetingMsg = new Greeting;
  tcpGreetingMsg->msg = new QJsonObject{{"name", mainWindow->getName()},
                                        {"ip", ipString},
                                        {"port", TCP_SERVER_PORT}};
  udpGreetingMsg->msg = new QJsonObject{{"name", mainWindow->getName()},
                                        {"ip", ipString},
                                        {"port", UDP_LISTENER_PORT}};
  // 更新用户名
  QObject::connect(mainWindow, &MainWindow::nameEditChanged,
                   [tcpGreetingMsg, udpGreetingMsg](const QString &name) {
                     tcpGreetingMsg->updateValue("name", name);
                     udpGreetingMsg->updateValue("name", name);
                   });
  // tcp server
  auto tcpServer = new TcpServer(TCP_SERVER_PORT);
  tcpServer->setGreetingMsg(tcpGreetingMsg);
  tcpServer->start();

  QObject::connect(tcpServer, SIGNAL(gotNewConnection(TcpConnection *)),
                   mainWindow, SLOT(appendConnection(TcpConnection *)));

  // tcp client
  auto tcpClient = new TcpClient;
  tcpClient->setGreetingMsg(tcpGreetingMsg);
  QObject::connect(tcpClient, SIGNAL(connected(TcpConnection *)), mainWindow,
                   SLOT(appendConnection(TcpConnection *)));
  connectWindow->initTcpClient(tcpClient);

  // udp 监听器
  auto udpListener = new UdpListener(UDP_LISTENER_PORT);
  udpListener->setGreetingMsg(udpGreetingMsg);
  udpListener->start();

  // udp扫描器
  scanWindow->initScanner(UDP_LISTENER_PORT, udpGreetingMsg);
  scanWindow->initTcpClient(tcpClient);  // 设置唯一TCPclient
  mainWindow->show();
  return app.exec();
}
