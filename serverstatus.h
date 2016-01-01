#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include <QString>
#include <QList>
#include <QHostAddress>

struct ServerStatus {
  QHostAddress* address;
  unsigned delay;
  QString username;
};

typedef QList<ServerStatus*>* ServerStatusList;

#endif  // SERVERSTATUS_H
