#ifndef Enfant_H
#define Enfant_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QTime>

class Enfant
{public:
    Enfant();
    Enfant(QString,QString,int);
    QString get_nom();
    int get_age();
    QString get_prenom();

    QString get_duree();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(Enfant m,QString id);
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
    QSqlQueryModel *tricroissant();




private:
    QString nom;
    int age;
    QString prenom;
};

#endif // Enfant_H
