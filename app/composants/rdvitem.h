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

private slots:
    void onAfficher();
//    void onAfficherFormModif();
//    void onModifier(rdv ancien, rdv nouveau);
    void onSupprimer();

signals:
    void updated(rdv ancien, rdv nouveau);
    void deleted(std::string nom);

private:
    rdv d_rdv;
};

#endif // RDVITEM_H
