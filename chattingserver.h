#ifndef CHATTINGSERVER_H
#define CHATTINGSERVER_H
#include <QObject>

class ChattingServer : public QObject {
  Q_OBJECT
 public:
  explicit ChattingServer(QObject *parent = 0);

 signals:

 public slots:
};

#endif  // CHATTINGSERVER_H
