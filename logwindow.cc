#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(QWidget *parent) : QDialog(parent), ui(new Ui::LogWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  this->setWindowTitle("Logs");
  QPushButton *closeButton = ui->closeButton;
  connect(closeButton, SIGNAL(clicked()), this, SLOT(hid()));
}

LogWindow::~LogWindow() { delete ui; }

void LogWindow::hid() { this->hide(); }
