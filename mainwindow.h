#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ScanWindow;
class LogWindow;
class AboutWindow;
class ConnectWindow;
class ServerScanner;
class ServerListener;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void showScanWindow();
  void hideScanWindow();
  void showLogWindow();
  void showAboutWindow();
  void showConnectWindow();
  void refreshMsgLength(const QString &content);

  void changeChannelTo(const int row, const int column);

 private:
  Ui::MainWindow *ui;
  ScanWindow *scanWindow;
  LogWindow *logWindow;
  AboutWindow *aboutWindow;
  ConnectWindow *connectWindow;
  ServerScanner *serverScanner;
  ServerListener *serverListener;
};

#endif  // MAINWINDOW_H
