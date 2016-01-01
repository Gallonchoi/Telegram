#ifndef SERVERSCANNER_H
#define SERVERSCANNER_H
#include <QObject>
#include "serverstatus.h"

class QTimer;
class QElapsedTimer;
class QUdpSocket;
class QHostAddress;

class ServerScanner : public QObject {
  Q_OBJECT
 public:
  explicit ServerScanner(const unsigned port);
  ~ServerScanner();

  const unsigned port;
 signals:
  void gotServerStatusList(ServerStatusList serverStatusList);

 public slots:
  void startScan(const int timeout = 5);
  void getResponse();

 private:
  QUdpSocket *udpSocket;
  QTimer *timeoutTimer;
  QElapsedTimer *delayTimer;
  int timeout;
};

#endif  // SERVERSCANNER_H
