#ifndef Enfant_Devoir_H
#define Enfant_Devoir_H
#include "enfant.h"
#include "devoir.h"
#include "notification.h"


#include <QMainWindow>

namespace Ui {
class Enfant_Devoir;
}

class Enfant_Devoir : public QMainWindow
{
    Q_OBJECT

public:
    explicit Enfant_Devoir(QWidget *parent = nullptr);
    ~Enfant_Devoir();

private slots:
    void on_pb_ajouter_clicked();




    void on_Enfant_affichage_activated(const QModelIndex &index);


    void on_pb_supprimer_clicked();

    void on_modifier_Enfant_clicked();
    void on_pb_ajouter_end_clicked();

    void on_pb_modifier_end_clicked();

    void on_pb_supprimer_end_clicked();

    void on_Devoir_affichage_activated(const QModelIndex &index);

    void refresh();

    void on_recherche_Devoir_textChanged();

    void on_recherche_Enfant_textChanged();

    void on_tri_croissant_Devoir_clicked();

    void on_tri_deccroissant_Devoir_clicked();

    void on_tri_croissant_Enfant_clicked();

    void on_tri_deccroissant_Enfant_clicked();


    void on_stat_Enfant_clicked();

    void on_pdf_Enfant_clicked();

    void on_send_mail_clicked();
    void mailSent(QString );




private:
    Ui::Enfant_Devoir *ui;
    Enfant tmp_Enfant;
    Devoir tmp_Devoir;
    Notification N;


};

#endif // Enfant_Devoir_H
