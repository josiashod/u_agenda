#include "rdvdialog.h"
#include "rdvitem.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>


RdvDialog::RdvDialog(QString titre, LRdv *rdvs, LRdv *apprdvs, LPersonne *lpersonne, QWidget *parent) :
    QDialog(parent)
  , d_titre{titre}
  , d_rdvs{rdvs}
  , d_apprdvs{apprdvs}
  , d_lpersonne{lpersonne}
{
    creerInterface();
    afficherRdvs();
}

RdvDialog::~RdvDialog()
{
    delete d_rdvs;
}

void RdvDialog::creerInterface()
{
    setWindowTitle(d_titre);
    setMinimumSize(450, 652);

    auto main{new QVBoxLayout(this)};
    d_list_rdvs = new QListWidget();

    d_btn_exporter = new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"));
    d_btn_exporter->setAutoDefault(false);

    d_btn_exporter->setDisabled(!d_rdvs->tete());

    connect(d_btn_exporter, &QPushButton::clicked, this, &RdvDialog::onExporter);

    main->addWidget(d_btn_exporter, 0, Qt::AlignRight);

    main->addWidget(d_list_rdvs, 1);
}

void RdvDialog::afficherRdvs()
{
    d_list_rdvs->clear();

    if(d_rdvs && d_rdvs->tete())
    {
        rdv *crt = d_rdvs->tete();

        while(crt)
        {
            auto item{new QListWidgetItem()};
            item->setSizeHint(QSize(0, 60));
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

            auto r{new RdvItem{*crt, d_apprdvs, d_lpersonne}};

            connect(r, &RdvItem::deleted, this, &RdvDialog::onSupprimer);
            connect(r, &RdvItem::updated, this, &RdvDialog::onModifier);
            d_list_rdvs->addItem(item);
            d_list_rdvs->setItemWidget(item, r);
            crt = crt->suivant();
        }
    }
    else
    {
        auto item{new QListWidgetItem("Aucun rendez-vous")};
        item->setSizeHint(QSize(0, 60));
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        item->setTextAlignment(Qt::AlignCenter);
        d_list_rdvs->addItem(item);
    }
}

void RdvDialog::onModifier(std::string nom, const rdv& r)
{
    rdv *nr = d_rdvs->trouverUn(nom);
    *nr = r;
    afficherRdvs();

    emit updated(nom, *nr);
}

void RdvDialog::onSupprimer(std::string nom)
{
    d_rdvs->supprimer(nom);
    afficherRdvs();
    d_btn_exporter->setDisabled(!d_rdvs->tete());
    emit deleted(nom);
}

void RdvDialog::onExporter()
{
    QString directory = QDir::homePath();
    QLocale locale = QLocale();

    directory += "/" + QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/";

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarde de l'agenda"),
            directory + "UAGENDA_" + locale.toString(QDate::currentDate(), "dd-MM-yyyy") + ".ics",
            tr("iCalendar files(*.ics *ifb *.iCal *.icalendar)"));

    if (fileName.isEmpty())
            return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }

        d_rdvs->exporterDans(fileName.toStdString());
        QString message = "Les rendez-vous ont été exporté avec succès";
        QMessageBox{QMessageBox::Information, tr("Information"), message}.exec();
    }
}
