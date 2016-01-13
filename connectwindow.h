#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QDialog>

namespace Ui {
class connectWindow;
}

class TcpClient;

class ConnectWindow : public QDialog {
  Q_OBJECT

 public:
  explicit ConnectWindow(const QString &title, QWidget *parent = 0);
  ~ConnectWindow();

  void initTcpClient(TcpClient *client) { tcpClient = client; }

 private slots:
  void connectTo();

 private:
  Ui::connectWindow *ui;
  TcpClient *tcpClient;
};

#endif  // CONNECTWINDOW_H
