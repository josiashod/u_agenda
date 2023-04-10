#ifndef RDVDIALOG_H
#define RDVDIALOG_H

#include <QDialog>
#include "./../src/lrdv.h"
#include "./../src/lpersonne.h"

class QListWidget;
class QPushButton;

class RdvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RdvDialog(QString titre= "Liste Rdvs", LRdv *rdvs = nullptr, LRdv *apprdvs = nullptr, LPersonne *lpersonne = nullptr, QWidget *parent = nullptr);
    ~RdvDialog();

private slots:
    void onSupprimer(std::string nom);
    void onModifier(std::string nom, const rdv& r);
    void onExporter();

signals:
    void updated(std::string nom, const rdv& r);
    void deleted(std::string nom);

private:
    QString d_titre;
    LRdv *d_rdvs;
    LRdv *d_apprdvs;
    LPersonne *d_lpersonne;
    QListWidget *d_list_rdvs;
    QPushButton *d_btn_exporter;

    void creerInterface();
    void afficherRdvs();
};

#endif // RDVDIALOG_H
