#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QDialog>
#include "./../src/rdv.h"

class Rdv : public QDialog
{
    Q_OBJECT

public:
    explicit Rdv(rdv* r, QWidget *parent = nullptr);
    void creerVue();

private:
    rdv* d_rdv;
};

#endif // RENDEZVOUS_H
