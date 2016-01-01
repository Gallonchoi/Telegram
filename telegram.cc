#include "telegram.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLabel>
#include <QListWidget>
#include <QFont>
#include <QtNetwork/QNetworkInterface>
#include <QDebug>

Telegram::Telegram(QWidget *parent) : QWidget(parent) {
  // draw
  QGridLayout *mainLayout = new QGridLayout;
  // 用户列表
  QListWidget *userList = new QListWidget;
  QLabel *userListLabel = new QLabel("Users");
  QVBoxLayout *userListLayout = new QVBoxLayout;
  userListLayout->addWidget(userListLabel);
  userListLayout->addWidget(userList);
  userListLabel->setAlignment(Qt::AlignCenter);
  QFont userListLabelFont = userListLabel->font();
  userListLabelFont.setBold(true);
  userListLabel->setFont(userListLabelFont);
  userListLabel->setFixedHeight(30);
  // 消息输入框
  QLineEdit *messageEdit = new QLineEdit;
  // 消息发送按钮
  QPushButton *sendButton = new QPushButton("Send");
  // 消息接收框
  QPlainTextEdit *inbox = new QPlainTextEdit;
  inbox->setReadOnly(true);
  inbox->setFixedSize(1000, 200);
  // 启动服务器按钮
  QPushButton *hostButton = new QPushButton("Host");
  hostButton->setStyleSheet("background: red");
  connect(hostButton, SIGNAL(clicked()), this, SLOT(host()));
  // 加入服务器按钮
  QPushButton *scanButton = new QPushButton("Scan");
  // 用户信息
  QLabel *userLabel = new QLabel("Username");
  QLineEdit *userEdit = new QLineEdit;
  QLabel *userIPLabel = new QLabel("IP");
  QLineEdit *userIP = new QLineEdit;
  userIP->setReadOnly(true);

  QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
  userIP->setText(ipList[2].toString());  // FIXME get real ip
  QHBoxLayout *userLayout = new QHBoxLayout;
  userLayout->addWidget(userLabel);
  userLayout->addWidget(userEdit);
  userLayout->addWidget(userIPLabel);
  userLayout->addWidget(userIP);

  mainLayout->addLayout(userListLayout, 0, 0, 3, 1);
  mainLayout->addLayout(userLayout, 0, 1);
  mainLayout->addWidget(hostButton, 0, 2);
  mainLayout->addWidget(scanButton, 0, 3);
  mainLayout->addWidget(inbox, 1, 1, 1, 4);
  mainLayout->addWidget(messageEdit, 2, 1, 1, 2);
  mainLayout->addWidget(sendButton, 2, 3);
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);  // 设置大小为固定
  setLayout(mainLayout);
}

Telegram::~Telegram() {}

void Telegram::host() {
  // create server
  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
  clickedButton->setText("Hosting");
  clickedButton->setStyleSheet("background: green");
  clickedButton->setEnabled(false);
}

void Telegram::scan() {}
