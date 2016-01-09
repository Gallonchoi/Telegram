#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scanwindow.h"
#include "logwindow.h"
#include "aboutwindow.h"
#include "connectwindow.h"
#include "udplistener.h"
#include <QDebug>
#include <QObject>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      scanWindow(new ScanWindow),
      logWindow(new LogWindow),
      aboutWindow(new AboutWindow),
      connectWindow(new ConnectWindow) {
  ui->setupUi(this);

  // IP address
  QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
  QStringList ipAddresses;
  foreach (const QHostAddress &address, ipAddressList) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol &&
        address != QHostAddress(QHostAddress::LocalHost))
      ipAddresses << address.toString();
  }
  ui->ipAddressEdit->setText(ipAddresses.join("/"));

  // Scan window settings
  scannerRequest = new QJsonObject{{"username", ui->nameEdit->text()},
                                   {"ip", ui->ipAddressEdit->text()}};
  scanWindow->initScanner(23333, scannerRequest);
  // 显示窗口事件
  QPushButton *scanButton = ui->scanButton;
  connect(scanButton, SIGNAL(clicked()), this, SLOT(showScanWindow()));
  this->setWindowTitle("Telegram");
  this->setFixedSize(this->width(), this->height());
  // 隐藏窗口
  connect(scanWindow, SIGNAL(hid()), this, SLOT(hideScanWindow()));
  // Message sender settings
  QLineEdit *msgEdit = ui->messageEdit;
  connect(msgEdit, SIGNAL(textChanged(QString)), this,
          SLOT(refreshMsgLength(QString)));
  QLabel *msgLengthLabel = ui->messageLengthLabel;
  msgLengthLabel->setText(QString("%1/%2")
                              .arg(msgEdit->text().length(), 2)
                              .arg(msgEdit->maxLength()));
  // Log window settings
  QPushButton *logButton = ui->logButton;
  connect(logButton, SIGNAL(clicked()), this, SLOT(showLogWindow()));

  // About window settings
  QPushButton *aboutButton = ui->aboutButton;
  connect(aboutButton, SIGNAL(clicked()), this, SLOT(showAboutWindow()));

  // Connect window settings
  QPushButton *connectButton = ui->connectToButton;
  connect(connectButton, SIGNAL(clicked()), this, SLOT(showConnectWindow()));

  // Connections table settings
  QTableWidget *connTable = ui->connTable;
  connect(connTable, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(changeChannelTo(int, int)));

  // UDP 监听
  udpListener = new UdpListener(23333);
  listenerResponse = new QJsonObject{{"username", ui->nameEdit->text()},
                                     {"ip", ui->ipAddressEdit->text()}};
  udpListener->setResponse(listenerResponse);
  connect(ui->nameEdit, SIGNAL(textChanged(QString)),
          SLOT(changeUsername(QString)));
  udpListener->start();
}

MainWindow::~MainWindow() { delete ui; }

// 显示'扫描'窗口
void MainWindow::showScanWindow() {
  this->setEnabled(false);
  scanWindow->show();
}

// 隐藏'扫描'窗口
void MainWindow::hideScanWindow() { this->setEnabled(true); }

// 更新'输入框'长度
void MainWindow::refreshMsgLength(const QString &content) {
  QLabel *msgLengthLabel = ui->messageLengthLabel;
  QLineEdit *msgEdit = ui->messageEdit;
  msgLengthLabel->setText(
      QString("%1/%2").arg(content.length(), 2).arg(msgEdit->maxLength()));
}

// 显示'日志'窗口
void MainWindow::showLogWindow() { logWindow->show(); }

// 显示'关于'窗口
void MainWindow::showAboutWindow() { aboutWindow->show(); }

// 显示'连接'窗口
void MainWindow::showConnectWindow() { connectWindow->show(); }

// 更换通信频道动作
void MainWindow::changeChannelTo(const int row, const int) {
  QTextBrowser *inboxBrowser = ui->inboxBrowser;
  QTableWidget *connTable = ui->connTable;
  const QString username = connTable->item(row, 0)->text();
  const QString ipAddress = ui->connTable->item(row, 1)->text();
  inboxBrowser->append(
      QString("Changing channel to %1(%2)").arg(username).arg(ipAddress));
}

// 修改用户名
void MainWindow::changeUsername(const QString &username) {
  (*listenerResponse)["username"] = username;
  (*scannerRequest)["username"] = username;
}
