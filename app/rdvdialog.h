#ifndef RDVDIALOG_H
#define RDVDIALOG_H

#include <QDialog>
#include "./../src/lrdv.h"

class QListWidget;
class QPushButton;

class RdvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RdvDialog(QString titre= "Liste Rdvs", LRdv *rdvs = nullptr, QWidget *parent = nullptr);
    ~RdvDialog();
    void creerInterface();
    void afficherRdvs();

private slots:
    void onSupprimer(std::string nom);
    void onExporter();

signals:
    void updated(rdv ancien, rdv nouveau);
    void deleted(std::string nom);

private:
    QString d_titre;
    LRdv *d_rdvs;
    QListWidget *d_list_rdvs;
    QPushButton *d_btn_exporter;
};

#endif // RDVDIALOG_H
