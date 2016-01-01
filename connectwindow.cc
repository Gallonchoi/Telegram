#include "connectwindow.h"
#include "ui_connectwindow.h"

ConnectWindow::ConnectWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::connectWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  this->setWindowTitle("Connect to ...");
  QPushButton *cancelButton = ui->cancelButton;
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(hid()));
}

ConnectWindow::~ConnectWindow() { delete ui; }

void ConnectWindow::hid() { this->hide(); }
