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


RdvDialog::RdvDialog(QString titre, LRdv *rdvs, QWidget *parent) :
    QDialog(parent)
  , d_titre{titre}
  , d_rdvs{rdvs}
{
    creerInterface();
    afficherRdvs();
}

RdvDialog::~RdvDialog()
{
}

void RdvDialog::creerInterface()
{
    setWindowTitle(d_titre);
    setMinimumSize(450, 652);

    auto main{new QVBoxLayout(this)};
    d_list_rdvs = new QListWidget();

    auto btnExporter{new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"))};
    btnExporter->setAutoDefault(false);

    connect(btnExporter, &QPushButton::clicked, this, &RdvDialog::onExporter);

    main->addWidget(btnExporter, 0, Qt::AlignRight);

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

            auto r{new RdvItem{*crt}};

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
