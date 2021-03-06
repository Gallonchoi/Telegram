#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scanwindow.h"
#include "aboutwindow.h"
#include "connectwindow.h"
#include "udplistener.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "tcpconnection.h"
#include "inboxwidget.h"
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
  auto connectToButton = ui->connectToButton;
  auto aboutButton = ui->aboutButton;

  connect(scanButton, &QPushButton::clicked, this,
          &MainWindow::scanButtonClicked);
  connect(connectToButton, &QPushButton::clicked, this,
          &MainWindow::connectButtonClicked);
  connect(aboutButton, &QPushButton::clicked, this,
          &MainWindow::aboutButtonClicked);

  auto nameEdit = ui->nameEdit;

  connect(nameEdit, &QLineEdit::textChanged, this,
          &MainWindow::nameEditChanged);

  // 聊天历史tab
  auto inboxTab = ui->inboxTab;
  inboxTab->clear();
  // 关闭事件
  connect(inboxTab, &QTabWidget::tabCloseRequested, [this](const int index) {
    auto tabItem = tabList[index];
    tabItem->closeConnection();
  });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setIpAddress(const QString &ip) {
  ui->ipAddressEdit->setText(ip);
}

// 获取用户名
QString MainWindow::getName() const { return ui->nameEdit->text(); }

// 添加新连接
void MainWindow::appendConnection(TcpConnection *conn) {
  auto userInfo = conn->getUserInfo();
  const auto name = userInfo["name"].toString();
  const auto ip = userInfo["ip"].toString();
  const auto type = conn->getTypeString();

  // 更新连接总数
  if (conn->type == TcpConnection::Type::Server) {
    ui->serverConnEdit->setText(
        QString::number(ui->serverConnEdit->text().toInt() + 1));
  } else {
    ui->clientConnEdit->setText(
        QString::number(ui->clientConnEdit->text().toInt() + 1));
  }
  // 添加连接窗口tab
  auto inboxTab = ui->inboxTab;
  auto connTabItem = new InboxWidget(conn);
  inboxTab->addTab(connTabItem, name);
  const int index = inboxTab->indexOf(connTabItem);
  tabList.insert(index, connTabItem);

  // 添加连接到连接列表
  auto connTable = ui->connTable;
  connTable->insertRow(connTable->rowCount());
  auto idItem = new QTableWidgetItem(QString::number(index));
  auto nameItem = new QTableWidgetItem(name);
  auto ipItem = new QTableWidgetItem(ip);
  auto typeItem = new QTableWidgetItem(type);
  connTable->setItem(connTable->rowCount() - 1, 0, idItem);
  connTable->setItem(connTable->rowCount() - 1, 1, nameItem);
  connTable->setItem(connTable->rowCount() - 1, 2, ipItem);
  connTable->setItem(connTable->rowCount() - 1, 4, typeItem);

  // 获取延迟
  connect(connTabItem, &InboxWidget::gotLatency,
          [connTable, index](const QString &latency) {
            for (int i = 0; i < connTable->rowCount(); ++i) {
              if (connTable->item(i, 0)->text().toInt() == index) {
                auto latencyItem = new QTableWidgetItem(latency);
                connTable->setItem(i, 3, latencyItem);
                break;
              }
            }
          });
  connTabItem->getLatency();

  // 当连接销毁时，从连接列表中去除连接
  connect(conn, &TcpConnection::destroyed, [this, conn, connTable, index] {
    if (conn->type == TcpConnection::Type::Server) {
      ui->serverConnEdit->setText(
          QString::number(ui->serverConnEdit->text().toInt() - 1));
    } else {
      ui->clientConnEdit->setText(
          QString::number(ui->clientConnEdit->text().toInt() - 1));
    }

    for (int i = 0; i < connTable->rowCount(); ++i) {
      if (connTable->item(i, 0)->text().toInt() == index) {
        connTable->removeRow(i);
        break;
      }
    }
  });
}
