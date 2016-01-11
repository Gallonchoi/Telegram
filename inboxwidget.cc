#include "inboxwidget.h"
#include "ui_inboxwidget.h"
#include "tcpconnection.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QTime>
#include <QTabWidget>

InboxWidget::InboxWidget(TcpConnection *connection, QWidget *parent)
    : QWidget(parent), connection(connection), ui(new Ui::InboxWidget) {
  ui->setupUi(this);
  // 信息输入框长度提示
  auto msgEdit = ui->messageEdit;
  auto msgLengthLabel = ui->messageLengthLabel;
  msgLengthLabel->setText(QString("%1/%2")
                              .arg(msgEdit->text().length(), 2)
                              .arg(msgEdit->maxLength()));
  connect(msgEdit, &QLineEdit::textChanged, [msgLengthLabel, msgEdit] {
    msgLengthLabel->setText(QString("%1/%2")
                                .arg(msgEdit->text().length(), 2)
                                .arg(msgEdit->maxLength()));
  });

  // 发送信息触发
  auto sendButton = ui->sendButton;
  connect(msgEdit, &QLineEdit::returnPressed, this, &InboxWidget::sendMessage);
  connect(sendButton, &QPushButton::clicked, this, &InboxWidget::sendMessage);
  connect(ui->resetButton, &QPushButton::clicked,
          [msgEdit] { msgEdit->clear(); });

  // 消息框自动滚动
  auto inboxScroll = ui->inboxScrollArea;
  auto vScroll = inboxScroll->verticalScrollBar();
  connect(vScroll, &QScrollBar::rangeChanged,
          [vScroll] { vScroll->setValue(vScroll->maximum()); });

  ui->inboxContentLayout->setAlignment(Qt::AlignTop);

  // 收到信息
  connect(connection, &TcpConnection::recvMessage, this,
          &InboxWidget::recvMessage);

  // 连接不可用时，禁用此tab
  connect(connection, &TcpConnection::destroyed, [this] {
    disconnect();
    this->setDisabled(true);
  });

  // 主动关闭连接
  connect(this, &InboxWidget::closeConnection, [this] {
    this->connection->deleteLater();
    disconnect();
    this->setDisabled(true);
  });
}

InboxWidget::~InboxWidget() { delete ui; }

// 更新'输入框'长度
void InboxWidget::refreshMsgLength(const QString &content) {
  auto msgLengthLabel = ui->messageLengthLabel;
  auto msgEdit = ui->messageEdit;
  msgLengthLabel->setText(
      QString("%1/%2").arg(content.length(), 2).arg(msgEdit->maxLength()));
}

// 发送信息
void InboxWidget::sendMessage() {
  const auto content = ui->messageEdit->text();
  ui->messageEdit->clear();
  auto contentJson = new QJsonObject{{"content", content}};
  connection->sendMessage(contentJson);
  displaySendMsg(content);
}

// 收到信息
void InboxWidget::recvMessage(QJsonObject *msg) {
  auto content = (*msg)["content"].toString();
  displayRecvMsg(content);
}

// 显示警告信息
void InboxWidget::displayAlertMsg(const QString &content) {
  auto inboxLayout = ui->inboxContentLayout;
  auto contentLabel = new QLabel(content);
  contentLabel->setStyleSheet(
      "border: 1px solid;"
      "margin: 10px 0px;"
      "padding:15px 10px 15px 50px;"
      "background-repeat: no-repeat;"
      "background-position: 10px center;"
      "color: #D8000C;"
      "background-color: #FFBABA;");
  contentLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  inboxLayout->addWidget(contentLabel, 0, Qt::AlignHCenter);
}

// 显示提醒信息
void InboxWidget::displayInfoMsg(const QString &content) {
  auto inboxLayout = ui->inboxContentLayout;
  auto contentLabel = new QLabel(content);
  contentLabel->setStyleSheet(
      "border: 1px solid;"
      "margin: 10px 0px;"
      "padding:15px 10px 15px 50px;"
      "background-repeat: no-repeat;"
      "background-position: 10px center;"
      "color: #00529B;"
      "background-color: #BDE5F8;");
  contentLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  inboxLayout->addWidget(contentLabel, 0, Qt::AlignHCenter);
}

// 显示发送的信息
void InboxWidget::displaySendMsg(const QString &content) {
  auto inboxLayout = ui->inboxContentLayout;
  QString newContent = content;
  const int charEveryCol = 25;
  for (int i = charEveryCol; i < content.length(); i += charEveryCol + 1) {
    newContent.insert(i, '\n');
  }
  auto contentLabel = new QLabel(newContent);
  auto timeLabel = new QLabel(QTime::currentTime().toString());
  contentLabel->setStyleSheet(
      "color: white;"
      "padding: 18px 20px;"
      "line-height: 26px;"
      "font-size: 16px;"
      "border-radius: 7px;"
      "margin-bottom: 30px;"
      "width: 90%;"
      "position: relative;"
      "background: #86BB71;");
  timeLabel->setStyleSheet(
      "color: #a8aab1;"
      "padding-left: 6px;");
  contentLabel->setWordWrap(true);
  contentLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  timeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  inboxLayout->addWidget(timeLabel, 1, Qt::AlignLeft);
  inboxLayout->addWidget(contentLabel, 1, Qt::AlignLeft);
}

// 显示收到的信息
void InboxWidget::displayRecvMsg(const QString &content) {
  auto inboxLayout = ui->inboxContentLayout;
  QString newContent = content;
  const int charEveryCol = 25;
  for (int i = charEveryCol; i < content.length(); i += charEveryCol + 1) {
    newContent.insert(i, '\n');
  }
  auto contentLabel = new QLabel(newContent);
  auto timeLabel = new QLabel(QTime::currentTime().toString());
  contentLabel->setStyleSheet(
      "color: white;"
      "padding: 18px 20px;"
      "line-height: 26px;"
      "font-size: 16px;"
      "border-radius: 7px;"
      "margin-bottom: 30px;"
      "width: 90%;"
      "position: relative;"
      "background: #94C2ED;");
  timeLabel->setStyleSheet(
      "color: #a8aab1;"
      "padding-left: 6px;");
  contentLabel->setWordWrap(true);
  contentLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  timeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  inboxLayout->addWidget(timeLabel, 1, Qt::AlignRight);
  inboxLayout->addWidget(contentLabel, 1, Qt::AlignRight);
}
