#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scanwindow.h"
#include "logwindow.h"
#include "aboutwindow.h"
#include "connectwindow.h"
#include "udplistener.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "tcpconnection.h"
#include <QDebug>
#include <QObject>
#include <QNetworkInterface>
#include <QHostInfo>

MainWindow::MainWindow(const QString &title, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle(title);
  this->setFixedSize(this->width(), this->height());

  auto scanButton = ui->scanButton;
  auto logButton = ui->logButton;
  auto connectToButton = ui->connectToButton;
  auto aboutButton = ui->aboutButton;

  connect(scanButton, SIGNAL(clicked(bool)), this,
          SIGNAL(scanButtonClicked(bool)));
  connect(logButton, SIGNAL(clicked(bool)), this,
          SIGNAL(logButtonClicked(bool)));
  connect(connectToButton, SIGNAL(clicked(bool)), this,
          SIGNAL(connectButtonClicked(bool)));
  connect(aboutButton, SIGNAL(clicked(bool)), this,
          SIGNAL(aboutButtonClicked(bool)));

  auto nameEdit = ui->nameEdit;

  connect(nameEdit, SIGNAL(textChanged(QString)), this,
          SIGNAL(nameEditChanged(QString)));

  // 扫描窗口设置
  // 初始化广播扫描器
  /*scannerRequest = new QJsonObject{{"username", ui->nameEdit->text()},
                                   {"ip", ui->ipAddressEdit->text()}};
  scanWindow->initScanner(23333, scannerRequest);
  connect(scanWindow, SIGNAL(gotNewConnection(TcpConnection *)), this,
          SLOT(getNewConnection(TcpConnection *)));
  // 显示窗口事件
  QPushButton *scanButton = ui->scanButton;
  connect(scanButton, SIGNAL(clicked()), this, SLOT(showScanWindow()));
  this->setWindowTitle("Telegram");
  this->setFixedSize(this->width(), this->height());
  // 隐藏窗口
  connect(scanWindow, SIGNAL(hid()), this, SLOT(hideScanWindow()));
  // 信息发送设置
  QLineEdit *msgEdit = ui->messageEdit;
  connect(msgEdit, SIGNAL(textChanged(QString)), this,
          SLOT(refreshMsgLength(QString)));
  QLabel *msgLengthLabel = ui->messageLengthLabel;
  msgLengthLabel->setText(QString("%1/%2")
                              .arg(msgEdit->text().length(), 2)
                              .arg(msgEdit->maxLength())); */
}

MainWindow::~MainWindow() { delete ui; }

// 更新'输入框'长度
void MainWindow::refreshMsgLength(const QString &content) {
  QLabel *msgLengthLabel = ui->messageLengthLabel;
  QLineEdit *msgEdit = ui->messageEdit;
  msgLengthLabel->setText(
      QString("%1/%2").arg(content.length(), 2).arg(msgEdit->maxLength()));
}

QString MainWindow::getName() const { return ui->nameEdit->text(); }

void MainWindow::setName(const QString &) {}

void MainWindow::appendConnection(TcpConnection *conn) {
  auto userInfo = conn->getUserInfo();
  qDebug() << conn << userInfo;
  //  qDebug() << (*userInfo)["name"];
}

// 更换通信频道动作
void MainWindow::changeChannelTo(TcpConnection *) {
  //  QTextBrowser *inboxBrowser = ui->inboxBrowser;
  //  QTableWidget *connTable = ui->connTable;
  //  const QString username = connTable->item(row, 0)->text();
  //  const QString ipAddress = connTable->item(row, 1)->text();
  //  inboxBrowser->append(
  //      QString("Changing channel to %1(%2)").arg(username).arg(ipAddress));
}

// 收到新连接
// void MainWindow::getNewConnection(TcpConnection *conn) {
//  if (conn->type == TcpConnection::Type::Server) {
//    serverConnections.append(conn);
//    ui->serverConnEdit->setText(QString::number(serverConnections.size()));
//  } else {
//    clientConnections.append(conn);
//    ui->clientConnEdit->setText(QString::number(clientConnections.size()));
//  }
//  auto userInfo = conn->userInfo;

//  QTableWidget *connTable = ui->connTable;
//  connTable->insertRow(connTable->rowCount());
//  auto username = new QTableWidgetItem((*userInfo)["username"].toString());
//  auto ip = new QTableWidgetItem((*userInfo)["ip"].toString());
//  connTable->setItem(connTable->rowCount() - 1, 0, username);
//  connTable->setItem(connTable->rowCount() - 1, 1, ip);
//}
