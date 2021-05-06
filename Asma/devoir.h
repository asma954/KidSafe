#ifndef Devoir_H
#define Devoir_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Devoir
{public:
    Devoir();
    Devoir(int,QString,QString);
    QString get_nom();
    QString get_etat();
    int get_numero();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int id,Devoir end);
    bool test_pourc(int);
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
    QSqlQueryModel *tricroissant();


private:
   int numero;
   QString nom,etat;
};

#endif // Devoir_H
