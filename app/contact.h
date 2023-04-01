#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>
#include "./../src/personne.h"

class Contact : public QDialog
{
    Q_OBJECT

public:
    explicit Contact(personne* p, QWidget *parent = nullptr);
    void creerVue();

private:
    personne* d_personne;
};

#endif // CONTACT_H
