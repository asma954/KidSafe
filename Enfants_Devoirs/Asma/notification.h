#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QSystemTrayIcon>
#include<QString>
class Notification
{
public:
    Notification();
    void notification_ajoutDevoir();
    void notification_ajoutEnfant();
    void notification_supprimerDevoir();
    void notification_supprimerEnfant();
    void notification_modifierDevoir();
    void notification_modifierEnfant();
    void mail_Enfant();






};

#endif // NOTIFICATION_H
