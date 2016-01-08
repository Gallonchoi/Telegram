#include "tcpconnection.h"
#include <QTcpSocket>

TcpConnection::TcpConnection(QTcpSocket *tcpSocket, Type type, QObject *parent)
    : QObject(parent), type(type), tcpSocket(tcpSocket) {}

TcpConnection::~TcpConnection() { delete tcpSocket; }

// 检测连接是否可用
bool TcpConnection::isValid() { return false; }
