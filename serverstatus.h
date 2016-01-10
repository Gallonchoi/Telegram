#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include <QList>
#include <QHostAddress>
#include <QByteArray>

struct ServerStatus {
  QHostAddress* address;
  unsigned latency;
  quint16 port;
  QJsonObject* userinfo;
};

typedef QList<ServerStatus*>* ServerStatusList;

#endif  // SERVERSTATUS_H
