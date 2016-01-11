#ifndef INBOXWIDGET_H
#define INBOXWIDGET_H

#include <QWidget>

namespace Ui {
class InboxWidget;
}

class TcpConnection;

class InboxWidget : public QWidget {
  Q_OBJECT

 public:
  explicit InboxWidget(TcpConnection *, QWidget *parent = 0);
  ~InboxWidget();

 signals:
  void closeConnection();

 private slots:
  void refreshMsgLength(const QString &content);
  void sendMessage();
  void recvMessage(QJsonObject *msg);
  void displayAlertMsg(const QString &);        // 显示警告信息
  void displayInfoMsg(const QString &);         // 显示提示信息
  void displayRecvMsg(const QString &content);  // 显示收到的信息
  void displaySendMsg(const QString &content);  // 显示发送的信息

 private:
  Ui::InboxWidget *ui;
  TcpConnection *connection;
};

#endif  // INBOXWIDGET_H
