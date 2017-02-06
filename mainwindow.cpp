#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDriver"
#include "QtSql/QSqlQuery"
#include "QDebug"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chargerLesClients();
    chargerLesMachines();
    connect(qApp,SIGNAL(focusChanged(QWidget*,QWidget*)),this,SLOT(on_focusChanged(QWidget*,QWidget*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::majListeRechercheMachine(QString leTexte)
{
    qDebug()<<"void MainWindow::majListeRecherche(QString leTexte)";
    //s'exécute quand il faut raffraichir la liste de recherche
    if(sender()==ui->lineEditReference)
    {

        QString txtReq="select idModel,nature,codeModel,libelleMarque from Modele inner join Marque on Modele.marque=Marque.idMarque where codeModel like upper('%"+ui->lineEditReference->text()+"%')";
        qDebug()<<txtReq;
        QSqlQuery maReq(txtReq);
        //effacement de la liste
        ui->listWidgetResultatRecherche->clear();
        while(maReq.next())
        {
            QListWidgetItem*  nouvelElement=new QListWidgetItem(maReq.value("codeModel").toString()+" "+maReq.value("libelleMarque").toString());
            nouvelElement->setData(32,maReq.value("idModel").toString());
            nouvelElement->setData(33,maReq.value("codeModel").toString());
            nouvelElement->setData(34,maReq.value("libelleMarque").toString());
            nouvelElement->setData(35,maReq.value("nature").toString());
            ui->listWidgetResultatRecherche->insertItem(0,nouvelElement);

        }
    }
    else if(sender()==ui->lineEditMarque)
    {
        QString txtReq="select idModel,nature,codeModel,libelleMarque from Modele inner join Marque on Modele.marque=Marque.idMarque where libelleMarque like upper('%"+ui->lineEditMarque->text()+"%')";
        qDebug()<<txtReq;
        QSqlQuery maReq(txtReq);
        //effacement de la liste
        ui->listWidgetResultatRecherche->clear();
        while(maReq.next())
        {
            QListWidgetItem*  nouvelElement=new QListWidgetItem(maReq.value("codeModel").toString()+" "+maReq.value("libelleMarque").toString());
            nouvelElement->setData(32,maReq.value("idModel").toString());
            nouvelElement->setData(33,maReq.value("codeModel").toString());
            nouvelElement->setData(34,maReq.value("libelleMarque").toString());
            nouvelElement->setData(35,maReq.value("nature").toString());
            ui->listWidgetResultatRecherche->insertItem(0,nouvelElement);

        }
    }
    else if(sender()==ui->lineEditNomMachine)
    {
        QString txtReq="select idModel,nature,codeModel,libelleMarque from Modele inner join Marque on Modele.marque=Marque.idMarque where nature like upper('%"+ui->lineEditNomMachine->text()+"%')";
        qDebug()<<txtReq;
        QSqlQuery maReq(txtReq);
        //effacement de la liste
        ui->listWidgetResultatRecherche->clear();
        while(maReq.next())
        {
            QListWidgetItem*  nouvelElement=new QListWidgetItem(maReq.value("codeModel").toString()+" "+maReq.value("libelleMarque").toString());
            nouvelElement->setData(32,maReq.value("idModel").toString());
            nouvelElement->setData(33,maReq.value("codeModel").toString());
            nouvelElement->setData(34,maReq.value("libelleMarque").toString());
            nouvelElement->setData(35,maReq.value("nature").toString());
            ui->listWidgetResultatRecherche->insertItem(0,nouvelElement);

        }
    }
}

void MainWindow::on_focusChanged(QWidget* old, QWidget* nouveau)
{
    qDebug()<<"void MainWindow::on_focusChanged(QWidget* old, QWidget* nouveau)";
    if(nouveau==ui->lineEditReference)
    {
        disconnect(ui->lineEditMarque,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
        disconnect(ui->lineEditNomMachine,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
        //il est dans le modele on affiche les références
        //attacher l'evenement textChanged à la maj de la zone de droite
        connect(ui->lineEditReference,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
    }
    else if(nouveau==ui->lineEditNomMachine)
    {
        disconnect(ui->lineEditReference,SIGNAL(textChanged(QString)),this, SLOT(majListeRecherche(QString)));    
        disconnect(ui->lineEditMarque,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
        //il est dans le modele on affiche les références
        //attacher l'evenement textChanged à la maj de la zone de droite
        connect(ui->lineEditNomMachine,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));

    }
    else if(nouveau==ui->lineEditMarque)
    {
        disconnect(ui->lineEditReference,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
        disconnect(ui->lineEditNomMachine,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
        //il est dans le modele on affiche les références
        //attacher l'evenement textChanged à la maj de la zone de droite
        connect(ui->lineEditMarque,SIGNAL(textChanged(QString)),this, SLOT(majListeRechercheMachine(QString)));
    }
}

void MainWindow::chargerLesClients()
{
   QSqlQuery reqChargerClient;
   int ligneActu=0;
   //on efface tout
   ui->tableWidgetClient->setRowCount(0);
   /*CREATE TABLE `Client`(`idClient` int(11),`nomClient` varchar(45),`prenomClient` varchar(45),`telephoneClient` varchar(45),`emailClient` varchar(45),`adresseClient` varchar(45),'cpClient' varchar(6),'villeClient' varchar(45),primary key(`idClient`));
*/
   reqChargerClient.prepare("select nomClient,prenomClient,telephoneClient,emailClient,adresseClient,cpClient,villeClient from Client order by nomClient");
   if(reqChargerClient.exec())
   {
       ui->tableWidgetClient->setRowCount(reqChargerClient.size());
       while(reqChargerClient.next())//pour chaque client
       {

        //pour chaque champ à afficher
         for(int noCol=0;noCol<7;noCol++)
         {
            ui->tableWidgetClient->setItem(ligneActu,noCol,new QTableWidgetItem(reqChargerClient.value(noCol).toString()));
         }
          ligneActu++;//on passe à la ligne suivante

       }//fin du pour chaque client
   }//fin du if
   else
   {
       qDebug()<<"pb req";
   }

}//fin de chargerLesClients

void MainWindow::chargerLesMachines()
{
    QString txtReq="select nature,libelleMarque,codeModel,typeMoteur,concat(nomClient,concat(' ',prenomClient)), panneReparation, libelleEtat, idDevis,dateArrivee,dateFinalisation, nomUtilisateur "
                   "from Modele inner join Reparation on Reparation.outilRef=Modele.idModel "
                   "inner join Marque on Marque.idMarque=Modele.marque "
                   "inner join Client on Reparation.idClient=Client.idClient "
                   "inner join Etat_Reparation on Etat_Reparation.idEtat=Reparation.idEtat "
                   "inner join Utilisateur on Reparation.idUtilisateur=Utilisateur.idUtilisateur";
    qDebug()<<txtReq;
    QSqlQuery reqChargerMachine;
    reqChargerMachine.prepare(txtReq);
    if(reqChargerMachine.exec())
    {
        int ligneActu=0;
        ui->tableWidgetMachine->setRowCount(reqChargerMachine.size());
        if(reqChargerMachine.size()>0)
        {
            while(reqChargerMachine.next())
            {
                for(int noCol=0;noCol<11;noCol++)
                {
                    ui->tableWidgetMachine->setItem(ligneActu,noCol,new QTableWidgetItem(reqChargerMachine.value(noCol).toString()));
                }
                /*nomMachine=reqChargerMachine.value(0).toString();
          marqueMachine=reqChargerMachine.value(1).toString();*/
                int idType=reqChargerMachine.value(3).toInt();
                if(idType==1)
                {
                    typeMachine="Thermique";
                }
                else
                {
                    typeMachine="Electrique";
                }
                ui->tableWidgetMachine->setItem(ligneActu,3,new QTableWidgetItem(typeMachine));
                ligneActu++;
            }
        }//fin de requête ok
        else//la requête renvoie 0 ligne
        {
            //il n'y a pas de machine
            qDebug()<<"pas de machine pour l'instant";
        }
    }
    else//erreur lors du select des machines
    {
        qDebug()<<reqChargerMachine.lastError().text();
    }

}
int MainWindow::chercherIdClient()
{
    QSqlQuery reqIdClient;
    QString req="select idClient from Client where nomClient='"+nomClient+"' and telephoneClient='"+telClient+"'";
    qDebug()<<req;
    reqIdClient.prepare(req);
    reqIdClient.exec();
    reqIdClient.first();
    int numClient=reqIdClient.value(0).toInt();
    return numClient;
}

void MainWindow::viderLesChamps()
{
    nomClient="";
    prenomClient="";
    telClient="";
    emailCLient="";
    adresseClient="";
    cpClient="";
    villeClient="";

    ui->labelNomClient->setText(nomClient);
    ui->labelPrenomClient->setText(prenomClient);
    ui->labelTelClient->setText(telClient);
    ui->labelEmailClient->setText(emailCLient);
    ui->labelCPClient->setText(cpClient);
    ui->labelAdresseClient->setText(adresseClient);
    ui->labelVilleClient->setText(villeClient);







    ui->lineEditNom->setText(nomClient);
    ui->lineEditPrenom->setText(prenomClient);
    ui->lineEditTelephone->setText(telClient);
    ui->lineEditEmail->setText(emailCLient);
    ui->lineEditAdresse->setText(adresseClient);
    ui->lineEditCP->setText(cpClient);
    ui->lineEditVille->setText(villeClient);

    ui->tableWidgetMachineClient->setRowCount(0);

    ui->pushButtonSupprimerClient->setDisabled(true);
    ui->pushButtonAjouterMachine->setDisabled(true);
    ui->pushButtonModifierClient->setDisabled(true);

}

void MainWindow::on_pushButtonAjouterClient_clicked()
{
   nomClient=ui->lineEditNom->text();
   prenomClient=ui->lineEditPrenom->text();
   telClient=ui->lineEditTelephone->text();
   emailCLient=ui->lineEditEmail->text();
   adresseClient=ui->lineEditAdresse->text();
   cpClient=ui->lineEditCP->text();
   villeClient=ui->lineEditVille->text();

   QSqlQuery reqMaxId;
   reqMaxId.prepare("select max(idClient) from Client");
   reqMaxId.exec();
   reqMaxId.first();


   int maxId=reqMaxId.value(0).toInt();
   maxId++;
   QString nbClient=QString::number(maxId);
   QSqlQuery reqAjouterClient;

   QString reqAjoutClient="insert into Client(idClient,nomClient,prenomClient,telephoneClient,emailClient,villeClient,adresseClient,cpClient) values("+nbClient+",'"+nomClient+"','"+prenomClient+"','"+telClient+"','"+emailCLient+"','"+villeClient+"','"+adresseClient+"','"+cpClient+"')";
   qDebug()<<reqAjoutClient;
   reqAjouterClient.prepare(reqAjoutClient);
   reqAjouterClient.exec();

   viderLesChamps();
   chargerLesClients();
}

void MainWindow::on_pushButtonSupprimerClient_clicked()
{
   if(QMessageBox::warning(this,this->windowTitle(),"Etes-vous bien certain de vouloir supprimer ce client?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
   {
       int numClient=0;
       numClient=chercherIdClient();
       QString numClientSt=QString::number(numClient);

       QString reqSuppr="delete from Client where idClient="+numClientSt+"";
       qDebug()<<reqSuppr;

       QSqlQuery reqSupprClient;
       reqSupprClient.prepare(reqSuppr);
       reqSupprClient.exec();

       viderLesChamps();
       chargerLesClients();
   }
}
/**
 * @brief MainWindow::on_tableWidgetClient_cellClicked
 * @param row
 * @param column
 * Selection du client sur lequel on souhaite travailler
 */
void MainWindow::on_tableWidgetClient_cellClicked(int row, int column)
{
    //affichage des infos dans la zone de modification
    nomClient=ui->tableWidgetClient->item(row,0)->text();
    prenomClient=ui->tableWidgetClient->item(row,1)->text();
    telClient=ui->tableWidgetClient->item(row,2)->text();
    emailCLient=ui->tableWidgetClient->item(row,3)->text();
    adresseClient=ui->tableWidgetClient->item(row,4)->text();
    cpClient=ui->tableWidgetClient->item(row,5)->text();
    villeClient=ui->tableWidgetClient->item(row,6)->text();
    //on vide les machines du client
    ui->tableWidgetMachineClient->setRowCount(0);
    //à revoir
    int idClient=chercherIdClient();
    QString idClientS=QString::number(idClient);
    QString txtReq="select concat(outilNom,concat(' ',concat(libelleMarque,concat(' ',codeModel)))),date_format(dateArrivee,'%d/%m'),libelleEtat,if(dateFinalisation is null,datediff(now(),dateArrivee),'OK'),outilType,concat(nomClient,concat(' ', prenomClient)), panneReparation, idDevis,dateFinalisation, nomUtilisateur from Modele inner join Reparation on Reparation.outilRef=Modele.idModel inner join Marque on Marque.idMarque=Modele.marque inner join Client on Reparation.idClient=Client.idClient natural join Etat_Reparation natural join Utilisateur where Client.idClient="+idClientS+" order by Reparation.idEtat asc, dateArrivee desc";
    qDebug()<<txtReq;
    QSqlQuery chercherMachineDuClient;
    chercherMachineDuClient.prepare(txtReq);
    if(chercherMachineDuClient.exec())
    {

        int nbLigne=chercherMachineDuClient.size();
        if(nbLigne>0)
        {

            ui->tableWidgetMachineClient->setRowCount(nbLigne);

            int noLigne=0;
            while(chercherMachineDuClient.next())
            {
                QSqlRecord enregistrement=chercherMachineDuClient.record();
                //pour chaque champ à afficher
                for(int noCol=0;noCol<enregistrement.count();noCol++)
                {
                    ui->tableWidgetMachineClient->setItem(noLigne,noCol,new QTableWidgetItem(chercherMachineDuClient.value(noCol).toString()));

                }
                noLigne++;//on passe à la ligne suivante
            }
        }
        else
        {
            qDebug()<<"Ce client n'a pas de machine";
        }
    }
    else
    {
        qDebug()<<chercherMachineDuClient.lastError().databaseText();
    }

    ui->labelNomClient->setText(nomClient);
    ui->labelPrenomClient->setText(prenomClient);
    ui->labelTelClient->setText(telClient);
    ui->labelEmailClient->setText(emailCLient);
    ui->labelCPClient->setText(cpClient);
    ui->labelAdresseClient->setText(adresseClient);
    ui->labelVilleClient->setText(villeClient);


    ui->lineEditNom->setText(nomClient);
    ui->lineEditPrenom->setText(prenomClient);
    ui->lineEditTelephone->setText(telClient);
    ui->lineEditEmail->setText(emailCLient);
    ui->lineEditAdresse->setText(adresseClient);
    ui->lineEditCP->setText(cpClient);
    ui->lineEditVille->setText(villeClient);

    ui->pushButtonSupprimerClient->setEnabled(true);
    ui->pushButtonAjouterMachine->setEnabled(true);
    ui->pushButtonModifierClient->setEnabled(true);
}

void MainWindow::on_pushButtonDeselectionner_clicked()
{
    viderLesChamps();
}

void MainWindow::on_pushButtonModifierClient_clicked()
{
    int numClient=chercherIdClient();
    QString nbClient=QString::number(numClient);

    nomClient=ui->lineEditNom->text();
    prenomClient=ui->lineEditPrenom->text();
    telClient=ui->lineEditTelephone->text();
    emailCLient=ui->lineEditEmail->text();
    adresseClient=ui->lineEditAdresse->text();
    cpClient=ui->lineEditCP->text();
    villeClient=ui->lineEditVille->text();


    QSqlQuery reqAjouterClient;
    QString reqModif="update Client set nomClient='"+nomClient+"', prenomClient='"+prenomClient+"', telephoneClient='"+telClient+"',emailClient='"+emailCLient+"',adresseClient='"+adresseClient+"',cpClient='"+cpClient+"',villeClient='"+villeClient+"' where idClient="+nbClient+"";
    qDebug()<<reqModif;
    reqAjouterClient.prepare(reqModif);
    reqAjouterClient.exec();
    viderLesChamps();
    chargerLesClients();
}


void MainWindow::on_pushButtonRechercher_clicked()
{
    int ligneActu=0;
    QString nomRecherche=ui->lineEditRechercheClient->text();
    QSqlQuery reqRecherche;
    reqRecherche.prepare("select * from Client where nomClient='"+nomRecherche+"' OR telephoneClient='"+nomRecherche+"'");
    if(reqRecherche.exec())
    {
        ui->tableWidgetClient->setRowCount(0);
        while(reqRecherche.next())//pour chaque client
        {
         ui->tableWidgetClient->setRowCount(ligneActu+1);
         //pour chaque champ à afficher
          for(int noCol=0;noCol<7;noCol++)
          {
             ui->tableWidgetClient->setItem(ligneActu,noCol,new QTableWidgetItem(reqRecherche.value(noCol+1).toString()));
          }
           ligneActu++;//on passe à la ligne suivante

        }//fin du pour chaque client
    }//fin du if
    else
    {
        qDebug()<<"pb req";
    }

}

void MainWindow::on_pushButtonAjouterMachine_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonAjouterMachine_clicked()";
    int typeMachineInt;
    int idMaxMachine;


    QString maxId;
    QString idClientAct;

    //QString dateARentrer;

    QSqlQuery reqMaxIdMach;
    reqMaxIdMach.prepare("select ifnull(max(idReparation),100) from Reparation");
    if(reqMaxIdMach.exec())
    {
        reqMaxIdMach.first();
        idMaxMachine=reqMaxIdMach.value(0).toInt();
        idMaxMachine++;
        maxId=QString::number(idMaxMachine);
    }

    dateArrivee=dateArrivee.currentDate();
    QString dateARentrer=dateArrivee.toString("yyyy/MM/dd");
    nomMachine=ui->lineEditNomMachine->text();
    marqueMachine=ui->lineEditMarque->text();
    refMachine=ui->lineEditReference->text();
    //refMachine=ui->lineEditReference->property("numeroModele").toString();
    panneMachine=ui->lineEditPanne1->text();
    panneMachine=panneMachine+"&&"+ui->lineEditPanne2->text();
    panneMachine=panneMachine+"&&"+ui->lineEditPanne3->text();
    panneMachine=panneMachine+"&&"+ui->lineEditPanne4->text();
    panneMachine=panneMachine+"&&"+ui->lineEditPanne5->text();

    if(ui->radioButtonElectrique->isChecked())
    {
        typeMachineInt=0;
    }
    if(ui->radioButtonThermique->isChecked())
    {
        typeMachineInt=1;
    }
    idClientAct=QString::number(chercherIdClient());
    typeMachine=QString::number(typeMachineInt);
    //s'il y a besoin créer la marque
    QSqlQuery reqIdMarque("select idMarque from Marque where upper(libelleMarque)=upper('"+marqueMachine+"')");
    if(reqIdMarque.size()==0)
    {
        QSqlQuery reqObtientIdMarque("select ifnull(max(idMarque),0)+1 from Marque");
        reqObtientIdMarque.first();
        QString sonId=reqObtientIdMarque.value(0).toString();
        QSqlQuery reqInsertMarque("insert into Marque values("+sonId+",'"+marqueMachine+"'");
        reqInsertMarque.exec();
        qDebug()<<reqInsertMarque.lastError().text();
    }
    //obtention de l'identifiant de la marque
    reqIdMarque.exec();
    reqIdMarque.first();
    QString idMarque=reqIdMarque.value(0).toString();
    //recherche du modèle
    QString textReaq="select idModel from Modele where upper(codeModel)=upper('"+refMachine+"') and marque ="+idMarque;
    qDebug()<<textReaq;
    QSqlQuery reqIdModele(textReaq);
    reqIdModele.exec();
    qDebug()<<reqIdModele.lastError().text();
    //s'il y a besoin créer le modèle
    if(reqIdModele.size()==0)
    {
        QSqlQuery reqObtientIdModele("select ifnull(max(idModel),1)+1 from Modele");
        reqObtientIdModele.first();
        QString idDuModele=reqObtientIdModele.value(0).toString();
        qDebug()<<"creation du modele"<<idDuModele;
        QString txtRaq="insert into Modele values("+idDuModele+",'"+refMachine+"',"+idMarque+",'"+nomMachine+"',"+idMarque+")";
        qDebug()<<txtRaq;
        QSqlQuery reqInsertModele(txtRaq);
        reqInsertModele.exec();
        qDebug()<<reqInsertModele.lastError().text();
    }
    reqIdModele.exec();
    reqIdModele.first();
    QString idModele=reqIdModele.value(0).toString();
    //créer la réparation
    QSqlQuery insertMachine;
/*CREATE TABLE `Reparation`(`idReparation` int(11),`outilNom` varchar(45),`outilType` tinyint(2),`panneReparation` varchar(255),`outilRef` integer not null references Modele(idModel),`dateArrivee` DATE,`tempsPasse` int(11),`dateFinalisation` date,`idClient` int(11) NOT NULL,`idDevis` int(11) NOT NULL,`idEtat` int(11) NOT NULL,`refProduit` varchar(45) ,`idUtilisateur` int(11) NOT NULL, foreign key (`idClient`) references Client(`idClient`), foreign key (`idDevis`) references Devis_Reparation(`idDevis`), foreign key (`idEtat`) references Etat_Reparation(`idEtat`), foreign key (`refProduit`) references Produit(`refProduit`), foreign key (`idUtilisateur`) references Utilisateur(`idUtilisateur`),primary key(`idReparation`));
 */
    QString txtReq="insert into Reparation (idReparation,panneReparation,outilRef,dateArrivee,idClient,idEtat,idDevis,idUtilisateur) "
                   "values("+maxId+",'"
                   +panneMachine+"',"
                   +idModele+",'"
                   +dateARentrer+"',"
                   +idClientAct+",1,NULL,NULL)";//plannifier,pas de devis, pas de mecano affecté
    insertMachine.prepare(txtReq);
    qDebug()<<txtReq;
    insertMachine.exec();
    qDebug()<<insertMachine.lastError();
    chargerLesMachines();
//raz des zones de saisie
    ui->lineEditNomMachine->setText("");
    ui->lineEditReference->setText("");
    ui->lineEditMarque->setText("");
    ui->lineEditPanne1->setText("");
    ui->lineEditPanne2->setText("");
    ui->lineEditPanne3->setText("");
    ui->lineEditPanne4->setText("");
    ui->lineEditPanne5->setText("");

}

void MainWindow::on_pushButtonRechercher_2_clicked()
{
    chargerLesClients();
}

void MainWindow::on_pushButtonDeselectionner_2_clicked()
{
     viderLesChamps();
}

void MainWindow::on_lineEditMarque_returnPressed()
{

}

void MainWindow::on_listWidgetResultatRecherche_itemActivated(QListWidgetItem *item)
{
    //en 32 l'identifiant, 33 le modèle, 34 la marque, 35 la nature
    ui->lineEditReference->setText(item->data(33).toString());
    ui->lineEditReference->setProperty("numeroModele",item->data(32).toString());
    ui->lineEditMarque->setText(item->data(34).toString());
    ui->lineEditNomMachine->setText(item->data(35).toString());
}

void MainWindow::on_action_Fermer_triggered()
{
    close();
}
