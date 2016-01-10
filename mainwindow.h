#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class ScanWindow;
class LogWindow;
class AboutWindow;
class ConnectWindow;
class UdpListener;
class QJsonObject;
class TcpServer;
class TcpConnection;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(const QString &title, QWidget *parent = 0);
  ~MainWindow();

  TcpConnection *getCurrentConnection() const;
  QString getName() const;

 signals:
  void scanButtonClicked(bool);
  void connectButtonClicked(bool);
  void logButtonClicked(bool);
  void aboutButtonClicked(bool);
  void nameEditChanged(const QString &);

 public slots:
  void setName(const QString &);
  void appendConnection(TcpConnection *);
  void changeChannelTo(TcpConnection *);

 private slots:
  void refreshMsgLength(const QString &content);

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
