#include "scanwindow.h"
#include "ui_scanwindow.h"
#include "udpscanner.h"
#include "tcpclient.h"
#include "greeting.h"
#include <QHostAddress>
#include <QDebug>
#include <QTcpSocket>

ScanWindow::ScanWindow(const QString &title, QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint), ui(new Ui::ScanWindow) {
  ui->setupUi(this);
  this->setWindowTitle(title);
  this->setFixedSize(this->width(), this->height());

  QPushButton *cancelButton = ui->cancelButton;
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelScan()));

  QTableWidget *serverTable = ui->serverTable;
  connect(serverTable, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(tryToConnect(int, int)));
}

ScanWindow::~ScanWindow() {
  delete ui;
  qDebug() << "scan window is destructing";
}

// 初始化扫描器
void ScanWindow::initScanner(const quint16 port, Greeting *greetingMsg) {
  QPushButton *refreshButton = ui->refreshButton;
  udpScanner = new UdpScanner(port);
  udpScanner->setGreetingMsg(greetingMsg);
  connect(refreshButton, SIGNAL(clicked()), this, SLOT(startScan()));
  connect(udpScanner, SIGNAL(timeout()), this, SLOT(finishScan()));
  connect(udpScanner, SIGNAL(gotServerStatusList(ServerStatusList)), this,
          SLOT(appendServers(ServerStatusList)));
  qDebug() << "init scanner";
}

void ScanWindow::startScan() {
  // 开始扫描
  ui->refreshButton->setDisabled(true);
  ui->refreshButton->setText("Refreshing");

  ui->serverTable->clearContents();
  ui->serverTable->setRowCount(0);
  udpScanner->startScan();
}

// 扫描结束
void ScanWindow::finishScan() {
  ui->refreshButton->setEnabled(true);
  ui->refreshButton->setText("Refresh");
}

void ScanWindow::cancelScan() {
  this->hid();
  this->hide();
}

// 扫描到服务器
void ScanWindow::appendServers(ServerStatusList serverStatusList) {
  auto serverTable = ui->serverTable;
  for (auto serverStatus : *serverStatusList) {
    auto userinfo = serverStatus->userinfo;
    auto username = new QTableWidgetItem((*userinfo)["name"].toString());
    auto ipAddress = new QTableWidgetItem(serverStatus->address->toString());
    auto port = new QTableWidgetItem(QString::number(serverStatus->port));
    auto latency =
        new QTableWidgetItem(QString("%1 ms").arg(serverStatus->latency));
    serverTable->insertRow(serverTable->rowCount());
    serverTable->setItem(serverTable->rowCount() - 1, 0, username);
    serverTable->setItem(serverTable->rowCount() - 1, 1, ipAddress);
    serverTable->setItem(serverTable->rowCount() - 1, 2, port);
    serverTable->setItem(serverTable->rowCount() - 1, 3, latency);
  }
  // 清除
  for (auto serverStatus : *serverStatusList) {
    delete serverStatus->address;
    delete serverStatus->userinfo;
    delete serverStatus;
  }
}

// 连接所选服务器
void ScanWindow::tryToConnect(int row, int) {
  auto serverTable = ui->serverTable;
  const auto ipAddress = serverTable->item(row, 1)->text();
  const quint16 port = serverTable->item(row, 2)->text().toInt();
  QHostAddress *host = new QHostAddress(ipAddress);
  tcpClient->connectTo(host, port);
}
