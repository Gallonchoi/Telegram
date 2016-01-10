#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(const QString &title, QWidget *parent)
    : QDialog(parent), ui(new Ui::LogWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  this->setWindowTitle(title);
  QPushButton *closeButton = ui->closeButton;
  connect(closeButton, SIGNAL(clicked()), this, SLOT(hid()));
}

LogWindow::~LogWindow() { delete ui; }

void LogWindow::hid() { this->hide(); }
