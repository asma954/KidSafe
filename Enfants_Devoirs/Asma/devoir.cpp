#include "Devoir.h"
#include <QDebug>
#include "connexion.h"
Devoir::Devoir()
{
nom="";
numero=0;
etat="";



}
Devoir::Devoir(int numero,QString nom,QString etat)
{
  this->numero=numero;
  this->nom=nom;
  this->etat=etat;

}
int Devoir::get_numero(){return  numero;}
QString Devoir::get_etat(){return etat;}
QString Devoir::get_nom(){return  nom;}



bool Devoir::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO Devoir (numero,nom,etat) "
                    "VALUES (:numero, :nom,:etat)");
query.bindValue(":numero", numero);
query.bindValue(":nom", nom);
query.bindValue(":etat", etat);



return    query.exec();
}

QSqlQueryModel * Devoir::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from Devoir");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat "));



    return model;
}

bool Devoir::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from Devoir where numero = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Devoir::modifier(int id,Devoir end)
{   QSqlQuery query;

    query.prepare( "UPDATE Devoir SET numero=:numero,nom=:nom,etat=:etat WHERE numero=:numero");
    query.bindValue(":numero",id);
    query.bindValue(":nom",end.nom);
    query.bindValue(":etat",end.etat);




 return query.exec();
}



QSqlQueryModel *Devoir::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM Devoir " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat "));

    return model;
}


QSqlQueryModel * Devoir::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Devoir ORDER BY numero ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat "));

    return model;
}
QSqlQueryModel * Devoir::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Devoir ORDER BY numero DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat "));

    return model;
}
