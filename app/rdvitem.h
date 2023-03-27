#ifndef RDVITEM_H
#define RDVITEM_H


#include <QWidget>
#include "./../src/rdv.h"

class QLineEdit;

class RdvItem: public QWidget
{
    Q_OBJECT

public:
    explicit RdvItem(const rdv& r, QWidget *parent = nullptr);
    ~RdvItem();
    void creerInterface();

private:
    rdv d_rdv;
};

#endif // RDVITEM_H
