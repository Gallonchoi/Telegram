#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scanwindow.h"
#include "logwindow.h"
#include "aboutwindow.h"
#include "connectwindow.h"
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
  // Scan window settings
  QPushButton *scanButton = ui->scanButton;
  connect(scanButton, SIGNAL(clicked()), this, SLOT(showScanWindow()));
  this->setWindowTitle("Telegram");
  this->setFixedSize(this->width(), this->height());
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

  // IP address
  QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
  QStringList ipAddresses;
  foreach (const QHostAddress &address, ipAddressList) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol &&
        address != QHostAddress(QHostAddress::LocalHost))
      ipAddresses << address.toString();
  }
  ui->ipAddressEdit->setText(ipAddresses.join("/"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showScanWindow() {
  this->setEnabled(false);
  scanWindow->show();
}

void MainWindow::hideScanWindow() { this->setEnabled(true); }

void MainWindow::refreshMsgLength(const QString &content) {
  QLabel *msgLengthLabel = ui->messageLengthLabel;
  QLineEdit *msgEdit = ui->messageEdit;
  msgLengthLabel->setText(
      QString("%1/%2").arg(content.length(), 2).arg(msgEdit->maxLength()));
}

void MainWindow::showLogWindow() { logWindow->show(); }

void MainWindow::showAboutWindow() { aboutWindow->show(); }

void MainWindow::showConnectWindow() { connectWindow->show(); }

void MainWindow::changeChannelTo(const int row, const int) {
  QTextBrowser *inboxBrowser = ui->inboxBrowser;
  QTableWidget *connTable = ui->connTable;
  const QString username = connTable->item(row, 0)->text();
  const QString ipAddress = ui->connTable->item(row, 1)->text();
  inboxBrowser->append(
      QString("Changing channel to %1(%2)").arg(username).arg(ipAddress));
}
