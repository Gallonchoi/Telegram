#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class QJsonObject;
class TcpConnection;
class InboxWidget;

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
  void appendConnection(TcpConnection *);

 private:
  Ui::MainWindow *ui;
  QMap<int, InboxWidget *> tabList;  // 以tab中的index为key， tab为Value
};

#endif  // MAINWINDOW_H
