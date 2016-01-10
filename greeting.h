#ifndef GREETING_H
#define GREETING_H

#include <QObject>
#include <QJsonObject>

class Greeting : public QObject {
  Q_OBJECT
 public:
  explicit Greeting(QObject* parent = 0);

  QJsonObject* msg;
 signals:

 public slots:
  void updateMsg(QJsonObject*);
  void updateValue(const QString& key, const QString& value);
};

#endif  // GREETING_H
