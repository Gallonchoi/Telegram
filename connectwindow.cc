#include "connectwindow.h"
#include "ui_connectwindow.h"
#include <QRegExpValidator>

ConnectWindow::ConnectWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::connectWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  this->setWindowTitle("Connect to ...");
  QPushButton *cancelButton = ui->cancelButton;
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(hid()));

  // 只允许输入ip地址
  QString oIpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegExp oIpRegex("^" + oIpRange + "\\." + oIpRange + "\\." + oIpRange +
                   "\\." + oIpRange + "$");
  ui->ipEdit->setValidator(new QRegExpValidator(oIpRegex));
}

ConnectWindow::~ConnectWindow() { delete ui; }

void ConnectWindow::hid() { this->hide(); }
