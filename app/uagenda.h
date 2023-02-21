#ifndef UAGENDA_H
#define UAGENDA_H

#include <QWidget>

class UAgenda : public QWidget
{
    Q_OBJECT

public:
    UAgenda(QWidget *parent = nullptr);
    ~UAgenda();
    void creerInterface();
};
#endif // UAGENDA_H
