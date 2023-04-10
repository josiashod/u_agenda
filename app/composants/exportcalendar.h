#ifndef EXPORTCALENDAR_H
#define EXPORTCALENDAR_H

#include <QDialog>

#include "./../src/lrdv.h"

class QDateTimeEdit;

class ExportCalendar : public QDialog
{
    Q_OBJECT
public:
    ExportCalendar(LRdv *rdvs, QWidget *parent = nullptr);
    ~ExportCalendar();

private slots:
    void onExporter();

private:
    LRdv* d_lrdv;
    QDateTimeEdit* d_dd_input;
    QDateTimeEdit* d_df_input;

    void creerInterface();
};

#endif // EXPORTCALENDAR_H
