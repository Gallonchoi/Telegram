#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(const QString &title, QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  this->setWindowTitle(title);
  QPushButton *closeButton = ui->closeButton;
  connect(closeButton, SIGNAL(clicked()), this, SLOT(hid()));
}

AboutWindow::~AboutWindow() { delete ui; }

void AboutWindow::hid() { this->hide(); }
