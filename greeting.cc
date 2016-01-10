#include "greeting.h"

Greeting::Greeting(QObject *parent) : QObject(parent) {}

void Greeting::updateMsg(QJsonObject *msg) { this->msg = msg; }

void Greeting::updateValue(const QString &key, const QString &value) {
  (*msg)[key] = value;
}
