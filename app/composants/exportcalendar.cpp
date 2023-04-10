#include "exportcalendar.h"

#include <fstream>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>


ExportCalendar::ExportCalendar(LRdv *rdvs, QWidget *parent)
    : QDialog{parent}
    , d_lrdv{rdvs}
{
    creerInterface();
}

ExportCalendar::~ExportCalendar()
{}

void ExportCalendar::creerInterface()
{
    setWindowTitle("Exportation de rendez-vous");

    auto mainLayout{new QVBoxLayout(this)};
    setMinimumSize(300, 220);

    QDate currdate = QDate::currentDate();

    int firstDay = (currdate.dayOfWeek() > 1) ? currdate.day() + 1 - currdate.dayOfWeek() : currdate.day();
    int lastDay = firstDay + 6;

    d_dd_input = new QDateTimeEdit(QDate(currdate.year(), currdate.month(), firstDay));
    d_dd_input->setCalendarPopup(true);
    d_df_input = new QDateTimeEdit(QDate(currdate.year(), currdate.month(), lastDay));
    d_df_input->setCalendarPopup(true);

    mainLayout->addWidget(new QLabel{"Date de debut"}, 0);
    mainLayout->addWidget(d_dd_input);
    mainLayout->addSpacing(10);

    mainLayout->addWidget(new QLabel{"Date de fin"}, 0);
    mainLayout->addWidget(d_df_input);

    auto btn{new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"))};
    btn->setAutoDefault(false);
    mainLayout->addWidget(btn, 1, Qt::AlignBottom);

    connect(btn, &QPushButton::clicked, this, &ExportCalendar::onExporter);
}

void ExportCalendar::onExporter()
{

    QString directory = QDir::homePath();
    QLocale locale = QLocale();

    directory += "/" + QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/";

    QDate dd = d_dd_input->date();
    QDate df = d_df_input->date();

    date date_debut{static_cast<unsigned int>(dd.day()),
        static_cast<unsigned int>(dd.month()), static_cast<unsigned int>(dd.year())};
    date date_fin{static_cast<unsigned int>(df.day()),
        static_cast<unsigned int>(df.month()), static_cast<unsigned int>(df.year())};


    auto texte = directory + "UAGENDA_" + locale.toString(dd, "dd_MM_yyyy");
    texte += "-" + locale.toString(df, "dd_MM_yyyy") + ".ics";

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarde de l'agenda"),
            texte,
            tr("iCalendar files(*.ics *ifb *.iCal *.icalendar)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }

        std::ofstream ofs(fileName.toStdString());
        d_lrdv->exporter(ofs, date_debut, date_fin);

        QMessageBox::information(this, tr("Exportation"), "Les rendez-vous ont été exporté avec succès");
        close();
    }
}
