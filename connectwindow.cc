#include "connectwindow.h"
#include "ui_connectwindow.h"
#include <QRegExpValidator>
#include "tcpclient.h"
#include <QHostAddress>

ConnectWindow::ConnectWindow(const QString &title, QWidget *parent)
    : QDialog(parent), ui(new Ui::connectWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  this->setWindowTitle(title);
  auto cancelButton = ui->cancelButton;
  connect(cancelButton, &QPushButton::clicked, this, &ConnectWindow::hide);
  auto connectButton = ui->connectButton;
  connect(connectButton, &QPushButton::clicked, this,
          &ConnectWindow::connectTo);

  // 只允许输入ip地址
  QString oIpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegExp oIpRegex("^" + oIpRange + "\\." + oIpRange + "\\." + oIpRange +
                   "\\." + oIpRange + "$");
  ui->ipEdit->setValidator(new QRegExpValidator(oIpRegex));
}

ConnectWindow::~ConnectWindow() { delete ui; }

void ConnectWindow::connectTo() {
  const auto ip = ui->ipEdit->text();
  const quint16 port = ui->portEdit->text().toInt();
  auto host = new QHostAddress(ip);
  tcpClient->connectTo(host, port);
  hide();
}
