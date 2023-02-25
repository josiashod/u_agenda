#ifndef RDVDIALOG_H
#define RDVDIALOG_H

#include <QDialog>

class QLineEdit;

class Rdv: public QWidget
{
    Q_OBJECT

public:
    explicit Rdv(QWidget *parent = nullptr, QString nomComplet = "");
    ~Rdv();
    void creerInterface();

private:
    QString d_nomComplet;
    QString d_numero;
};

class RdvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RdvDialog(QWidget *parent = nullptr, QString titre= "Liste Rdvs");
    ~RdvDialog();
    void creerInterface();

private:
    QString d_titre;
};

#endif // RDVDIALOG_H
