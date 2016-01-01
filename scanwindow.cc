#include "scanwindow.h"
#include "ui_scanwindow.h"
#include "serverscanner.h"
#include <QHostAddress>
#include <QDebug>

ScanWindow::ScanWindow(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint), ui(new Ui::ScanWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Scan servers");
  this->setFixedSize(this->width(), this->height());

  QPushButton *cancelButton = ui->cancelButton;
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelScan()));
  QPushButton *refreshButton = ui->refreshButton;
  serverScanner = new ServerScanner(10000);
  connect(refreshButton, SIGNAL(clicked()), serverScanner, SLOT(startScan()));
  connect(serverScanner, SIGNAL(gotServerStatusList(ServerStatusList)), this,
          SLOT(appendServers(ServerStatusList)));

  qDebug() << "scan window is constructing";
}

ScanWindow::~ScanWindow() {
  delete ui;
  qDebug() << "scan window is destructing";
}

void ScanWindow::cancelScan() {
  this->hid();
  this->hide();
}

void ScanWindow::appendServers(QList<ServerStatus *> *serverStatusList) {
  QTableWidget *serverTable = ui->serverTable;
  foreach (ServerStatus *serverStatus, *serverStatusList) {
    QTableWidgetItem *username = new QTableWidgetItem(serverStatus->username);
    QTableWidgetItem *ipAddress =
        new QTableWidgetItem(serverStatus->address->toString());
    QTableWidgetItem *delay =
        new QTableWidgetItem(QString("%1 ms").arg(serverStatus->delay));
    serverTable->insertRow(serverTable->rowCount());
    serverTable->setItem(serverTable->rowCount() - 1, 0, username);
    serverTable->setItem(serverTable->rowCount() - 1, 1, ipAddress);
    serverTable->setItem(serverTable->rowCount() - 1, 2, delay);
  }
}
