#ifndef Pub_Promo_H
#define Pub_Promo_H
#include "publicite.h"
#include "endroit.h"
#include "notification.h"


#include <QMainWindow>

namespace Ui {
class Pub_Promo;
}

class Pub_Promo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pub_Promo(QWidget *parent = nullptr);
    ~Pub_Promo();

private slots:
    void on_pb_ajouter_clicked();




    void on_Publicite_affichage_activated(const QModelIndex &index);


    void on_pb_supprimer_clicked();

    void on_modifier_3_clicked();
    void on_pb_ajouter_end_clicked();

    void on_pb_modifier_end_clicked();

    void on_pb_supprimer_end_clicked();

    void on_Endroit_affichage_activated(const QModelIndex &index);

    void refresh();

    void on_recherche_Endroit_textChanged();

    void on_recherche_Publicite_textChanged();

    void on_tri_croissant_Endroit_clicked();

    void on_tri_deccroissant_Endroit_clicked();

    void on_tri_croissant_publicite_clicked();

    void on_tri_deccroissant_publicite_clicked();

    void on_stat_Endroit_clicked();

    void on_stat_publicite_clicked();

    void on_pdf_publicite_clicked();

    void on_send_mail_clicked();
    void mailSent(QString );


private:
    Ui::Pub_Promo *ui;
    Publicite tmp_publicite;
    Endroit tmp_Endroit;
    Notification N;


};

#endif // Pub_Promo_H
