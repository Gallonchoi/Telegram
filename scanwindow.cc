#include "scanwindow.h"
#include "ui_scanwindow.h"
#include "udpscanner.h"
#include <QHostAddress>
#include <QDebug>

ScanWindow::ScanWindow(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint),
      ui(new Ui::ScanWindow),
      serverStatusList(new QList<ServerStatus *>) {
  ui->setupUi(this);
  this->setWindowTitle("Scan servers");
  this->setFixedSize(this->width(), this->height());

  QPushButton *cancelButton = ui->cancelButton;
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelScan()));

  qDebug() << "scan window is constructing";
}

ScanWindow::~ScanWindow() {
  delete ui;
  qDebug() << "scan window is destructing";
}

void ScanWindow::initScanner(const quint16 port, QJsonObject *request) {
  QPushButton *refreshButton = ui->refreshButton;
  udpScanner = new UdpScanner(port);
  udpScanner->setGreetingMsg(request);
  connect(refreshButton, SIGNAL(clicked()), this, SLOT(startScan()));
  connect(refreshButton, SIGNAL(clicked()), udpScanner, SLOT(startScan()));
  connect(udpScanner, SIGNAL(timeout()), this, SLOT(finishScan()));
  connect(udpScanner, SIGNAL(gotServerStatusList(ServerStatusList)), this,
          SLOT(appendServers(ServerStatusList)));
  qDebug() << "init scanner";
}

void ScanWindow::startScan() {
  // 开始扫描
  ui->refreshButton->setDisabled(true);
  ui->refreshButton->setText("Refreshing");
  if (serverStatusList) {
    foreach (ServerStatus *serverStatus, *serverStatusList) {
      delete serverStatus;
    }
    serverStatusList->clear();
    ui->serverTable->clearContents();
    ui->serverTable->setRowCount(0);
  }
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

void ScanWindow::appendServers(ServerStatusList serverStatusList) {
  QTableWidget *serverTable = ui->serverTable;
  foreach (ServerStatus *serverStatus, *serverStatusList) {
    if (this->serverStatusList->indexOf(serverStatus) != -1) {
      // 已经存在列表中
      continue;
    }
    this->serverStatusList->append(serverStatus);
    QJsonObject *userinfo = serverStatus->userinfo;
    QTableWidgetItem *username =
        new QTableWidgetItem((*userinfo)["username"].toString());
    QTableWidgetItem *ipAddress =
        new QTableWidgetItem(serverStatus->address->toString());
    QTableWidgetItem *delay =
        new QTableWidgetItem(QString("%1 ms").arg(serverStatus->latency));
    serverTable->insertRow(serverTable->rowCount());
    serverTable->setItem(serverTable->rowCount() - 1, 0, username);
    serverTable->setItem(serverTable->rowCount() - 1, 1, ipAddress);
    serverTable->setItem(serverTable->rowCount() - 1, 2, delay);
  }
}
