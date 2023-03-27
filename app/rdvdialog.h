#ifndef RDVDIALOG_H
#define RDVDIALOG_H

#include <QDialog>
#include "./../src/lrdv.h"

class QListWidget;

class RdvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RdvDialog(QString titre= "Liste Rdvs", LRdv *rdvs = nullptr, QWidget *parent = nullptr);
    ~RdvDialog();
    void creerInterface();
    void afficherRdvs();

private slots:
    void onExporter();

private:
    QString d_titre;
    LRdv *d_rdvs;
    QListWidget *d_list_rdvs;
};

#endif // RDVDIALOG_H
