#include "enfant.h"
#include <QDebug>
#include "connexion.h"
Enfant::Enfant()
{
nom="";
age=0;
}
Enfant::Enfant(QString nom,QString prenom,int age)
{
  this->nom=nom;
  this->age=age;
  this->prenom=prenom;

}
QString Enfant::get_nom(){return  nom;}
int Enfant::get_age(){return age;}
QString Enfant::get_prenom(){return  prenom;}



bool Enfant::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO Enfant (nom,prenom,age) "
                    "VALUES (:nom, :prenom,:age)");
query.bindValue(":nom", nom);
query.bindValue(":age", age);
query.bindValue(":prenom", prenom);



return    query.exec();
}

QSqlQueryModel * Enfant::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from Enfant");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));


    return model;
}

bool Enfant::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from Enfant where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Enfant::modifier(Enfant m,QString id)
{   QSqlQuery query;
    query.prepare( "UPDATE Enfant SET  nom=:nom,prenom=:prenom,age=:age WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",m.nom);
    query.bindValue(":age",m.age);
    query.bindValue(":prenom", m.prenom);



 return query.exec();
}

QSqlQueryModel *Enfant::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM Enfant " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    return model;
}



QSqlQueryModel * Enfant::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Enfant ORDER BY age ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));

    return model;
}
QSqlQueryModel * Enfant::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Enfant ORDER BY age DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    return model;
}
