#include "Enfant_Devoir.h"
#include "ui_Enfant_Devoir.h"
#include "enfant.h"
#include<QMessageBox>
#include <QComboBox>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPrinter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include"QSortFilterProxyModel"
#include <QtNetwork>
#include <QSslSocket>
QT_CHARTS_USE_NAMESPACE

#include "smtp.h"




Enfant_Devoir::Enfant_Devoir(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Enfant_Devoir)
{
ui->setupUi(this);

refresh();


}
void Enfant_Devoir::refresh(){
    ui->Enfant_affichage->setModel(tmp_Enfant.afficher());
    ui->Devoir_affichage->setModel(tmp_Devoir.afficher());

}

Enfant_Devoir::~Enfant_Devoir()
{
    delete ui;
}


//Crud Enfant
void Enfant_Devoir::on_pb_ajouter_clicked()
{
    QString nom= ui->lineEdit_nom->text();
    int age= ui->lineEdit_age->text().toInt();
    QString prenom= ui->lineEdit_prenom->text();
  Enfant e(nom,prenom,age);



  if (nom==NULL)
       {

           QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }

    else if (prenom==NULL)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prenom!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
  else if (age==NULL)
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP age!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }









  else{

  bool test=e.ajouter();
  if(test)
{

     refresh();
            N.notification_ajoutEnfant();

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une Enfant"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}}
void Enfant_Devoir::on_pb_supprimer_clicked()
{

    if(ui->Enfant_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir une Enfant du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int id=ui->Enfant_affichage->model()->data(ui->Enfant_affichage->model()->index(ui->Enfant_affichage->currentIndex().row(),0)).toInt();



            QString str = " Vous voulez vraiment supprimer \n la Enfant :";
                              int ret = QMessageBox::question(this, tr("Enfant"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (tmp_Enfant.supprimer(id)){
                                       N.notification_supprimerEnfant();
                                            refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Enfant non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}
}
void Enfant_Devoir::on_modifier_Enfant_clicked()
{
      QString id=ui->lineEdit_id_m->text();

    QString nom= ui->lineEdit_nom_m->text();
    int age= ui->lineEdit_age_m->text().toInt();
    QString prenom= ui->lineEdit_prenom_m->text();
  Enfant m(nom,prenom,age);



        if (nom==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }

          else if (age==NULL)
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP age!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }
        else if (prenom==NULL)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prenom!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }
        else if (id==NULL)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP identifiant !!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }









        else{






        bool test=tmp_Enfant.modifier(m,id);
        if(test)
        {



           N.notification_modifierEnfant();
                refresh();


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Enfant"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


      ui->lineEdit_id_m->clear();

        ui->lineEdit_nom_m->clear();
       ui->lineEdit_age_m->clear();
        ui->lineEdit_prenom_m->clear();





}}
void Enfant_Devoir::on_Enfant_affichage_activated(const QModelIndex &index)
{
    QString id=ui->Enfant_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM Enfant WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_id_m->setText(query.value(0).toString());
                ui->lineEdit_nom_m->setText(query.value(1).toString());
                ui->lineEdit_prenom_m->setText(query.value(2).toString());
                ui->lineEdit_age_m->setText(query.value(3).toString());


            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }
}
//Fin Crud Enfant



//Crud Devoir

void Enfant_Devoir::on_pb_ajouter_end_clicked()
{    int numero= ui->lineEdit_num_dev->text().toInt();
    QString nom= ui->lineEdit_nom_dev->text();
    QString etat =ui->lineEdit_etat_dev->text();
  Devoir dev(numero,nom,etat);



     if (numero==NULL)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP numero!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }

  else if (nom==NULL)
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else if (etat==NULL)
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP etat!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }








  else{
  bool test=dev.ajouter();
  if(test)
{

    refresh();
    N.notification_ajoutDevoir();
QMessageBox::information(nullptr, QObject::tr("Ajouter un Devoir"),
                  QObject::tr("Devoir ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Devoir"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}

void Enfant_Devoir::on_pb_modifier_end_clicked()
{
    int numero = ui->lineEdit_num_dev_m->text().toInt();
    QString nom= ui->lineEdit_nom_dev_m->text();
    QString etat= ui->lineEdit_etat_dev_m->text();
  Devoir dev(numero,nom,etat);


    if (numero==NULL)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP numero!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }

      else if (nom==NULL)
       {

           QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }
            else if (etat==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP etat!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }







    else{




    bool test=dev.modifier(numero,dev);
    if(test)
    {



        N.notification_modifierDevoir();
        refresh();
        QMessageBox::information(nullptr, QObject::tr("Modifier un Devoir"),
                          QObject::tr("Devoir modifiee.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier Devoir"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }


     ui->lineEdit_num_dev_m->clear();
     ui->lineEdit_etat_dev_m->clear();
     ui->lineEdit_nom_dev_m->clear();

}}

void Enfant_Devoir::on_pb_supprimer_end_clicked()
{
    if(ui->Devoir_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir un Devoir du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int id=ui->Devoir_affichage->model()->data(ui->Devoir_affichage->model()->index(ui->Devoir_affichage->currentIndex().row(),0)).toInt();










            QString str = " Vous voulez vraiment supprimer \n la Devoir :";
                              int ret = QMessageBox::question(this, tr("Devoir"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (tmp_Devoir.supprimer(id)){
                                       N.notification_supprimerDevoir();
                                            refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Devoir non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}

}

void Enfant_Devoir::on_Devoir_affichage_activated(const QModelIndex &index)
{
    QString id=ui->Devoir_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM Devoir WHERE numero='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_num_dev_m->setText(query.value(0).toString());
                ui->lineEdit_nom_dev_m->setText(query.value(1).toString());
                ui->lineEdit_etat_dev_m->setText(query.value(2).toString());







            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }

}


//Fin Crud Devoir


void Enfant_Devoir::on_recherche_Devoir_textChanged()
{
    if(ui->recherche_Devoir->text()!="")
        {        QString b=ui->comboBox_recherche_Devoir->currentText();
                QString a=ui->recherche_Devoir->text();
                ui->Devoir_affichage->setModel(tmp_Devoir.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
            }
             else
             ui->Devoir_affichage->setModel(tmp_Devoir.afficher());

}

void Enfant_Devoir::on_recherche_Enfant_textChanged()
{
    if(ui->recherche_Enfant->text()!="")
        {        QString b=ui->comboBox_recherche_Enfant->currentText();
                QString a=ui->recherche_Enfant->text();
                ui->Enfant_affichage->setModel(tmp_Enfant.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
            }
             else
             ui->Enfant_affichage->setModel(tmp_Enfant.afficher());

}

void Enfant_Devoir::on_tri_croissant_Devoir_clicked()
{
    ui->Devoir_affichage->setModel(tmp_Devoir.tricroissant());

}

void Enfant_Devoir::on_tri_deccroissant_Devoir_clicked()
{
    ui->Devoir_affichage->setModel(tmp_Devoir.trideccroissant());

}

void Enfant_Devoir::on_tri_croissant_Enfant_clicked()
{
    ui->Enfant_affichage->setModel(tmp_Enfant.tricroissant());

}

void Enfant_Devoir::on_tri_deccroissant_Enfant_clicked()
{
    ui->Enfant_affichage->setModel(tmp_Enfant.trideccroissant());

}



void Enfant_Devoir::on_stat_Enfant_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                    model->setQuery("select * from Enfant where AGE < 5 ");
                    float age=model->rowCount();
                    model->setQuery("select * from Enfant where AGE  between 5 and 10 ");
                    float agee=model->rowCount();
                    model->setQuery("select * from Enfant where AGE>10 ");
                    float ageee=model->rowCount();
                    float total=age+agee+ageee;
                    QString a=QString("moins de 5 ans "+QString::number((age*100)/total,'f',2)+"%" );
                    QString b=QString("entre 5 et 10 Ans"+QString::number((agee*100)/total,'f',2)+"%" );
                    QString c=QString("+10 Ans"+QString::number((ageee*100)/total,'f',2)+"%" );
                    QPieSeries *series = new QPieSeries();
                    series->append(a,age);
                    series->append(b,agee);
                    series->append(c,ageee);
            if (age!=0)
            {QPieSlice *slice = series->slices().at(0);
             slice->setLabelVisible();
             slice->setPen(QPen());}
            if ( agee!=0)
            {
                     // Add label, explode and define brush for 2nd slice
                     QPieSlice *slice1 = series->slices().at(1);
                     //slice1->setExploded();
                     slice1->setLabelVisible();
            }
            if(ageee!=0)
            {
                     // Add labels to rest of slices
                     QPieSlice *slice2 = series->slices().at(2);
                     //slice1->setExploded();
                     slice2->setLabelVisible();
            }
                    // Create the chart widget
                    QChart *chart = new QChart();
                    // Add data to chart with title and hide legend
                    chart->addSeries(series);
                    chart->setTitle("Pourcentage Par Age :Nombre Des Enfant "+ QString::number(total));
                    chart->legend()->hide();
                    // Used to display the chart
                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    chartView->resize(1000,500);
                    chartView->show();
}

void Enfant_Devoir::on_pdf_Enfant_clicked()
{
    QPdfWriter pdf("PdfEnfant.pdf");
                  QPainter painter(&pdf);
                 int i = 4000;
                      painter.setPen(Qt::blue);
                      painter.setFont(QFont("Arial", 30));
                      painter.drawText(2300,1200,"Liste Des Enfant");
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 50));
                     // painter.drawText(1100,2000,afficheDC);
                      painter.drawRect(1500,200,7300,2600);
                      //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                      painter.drawRect(0,3000,9600,500);
                      painter.setFont(QFont("Arial", 9));
                      painter.drawText(300,3300,"ID");
                      painter.drawText(2300,3300,"nom");
                      painter.drawText(4300,3300,"prenom");
                      painter.drawText(6300,3300,"AGE");



                      QSqlQuery query;
                      query.prepare("select * from Enfant");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(2300,i,query.value(1).toString());
                          painter.drawText(4300,i,query.value(2).toString());
                          painter.drawText(6300,i,query.value(3).toString());



                         i = i +500;
                      }
                      int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                          if (reponse == QMessageBox::Yes)
                          {
                              QDesktopServices::openUrl(QUrl::fromLocalFile("PdfEnfant.pdf"));

                              painter.end();
                          }
                          if (reponse == QMessageBox::No)
                          {
                               painter.end();
                          }
}




void Enfant_Devoir::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_Enfant();
}

void Enfant_Devoir::on_send_mail_clicked()
{

    Smtp* smtp = new Smtp("aura.forgetPass@gmail.com","Service100a","smtp.gmail.com",465);
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

       smtp->sendMail("aura.forgetPass@gmail.com",ui->rcpt->text(),ui->subject->text(),ui->msg->toPlainText());
}







