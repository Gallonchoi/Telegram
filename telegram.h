#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QWidget>

class Telegram : public QWidget {
    Q_OBJECT

public:
    Telegram(QWidget *parent = 0);
    ~Telegram();

private slots:
    void host();
    void scan();

private:
};

#endif // TELEGRAM_H
