#include "tcpconnection.h"

TcpConnection::TcpConnection(QTcpSocket *tcpSocket, Type type, QObject *parent)
    : QObject(parent), type(type), tcpSocket(tcpSocket) {}

TcpConnection::~TcpConnection() { delete tcpSocket; }

bool TcpConnection::isValid() {

}
