#ifndef EVENT_H
#define EVENT_H

#include <QDialog>
#include "./../src/rdv.h"

class Event : public QDialog
{
    Q_OBJECT

public:
    explicit Event(const rdv& r, QWidget *parent = nullptr);
    void creerVue();

signals:
    void deleted(std::string nom);

private slots:
    void onSupprimer();

private:
    rdv d_rdv;
};

#endif // RENDEZVOUS_H
