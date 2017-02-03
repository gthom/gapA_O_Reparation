#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDriver"
#include "QtSql/QSqlQuery"
#include "QDebug"
#include <QSqlError>
#include <QMessageBox>

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

void MainWindow::majListeRecherche(QString leTexte)
{
    qDebug()<<"void MainWindow::majListeRecherche(QString leTexte)";
    //s'exécute quand il faut raffraichir la liste de recherche
    if(sender()==ui->lineEditReference)
    {

        QString txtReq="select idModel,codeModel,libelleMarque from Modele inner join Marque on Modele.marque=Marque.idMarque where codeModel like upper('%"+ui->lineEditReference->text()+"%')";
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
            ui->listWidgetResultatRecherche->insertItem(0,nouvelElement);

        }
    }
}

void MainWindow::on_focusChanged(QWidget* old, QWidget* nouveau)
{
    qDebug()<<"void MainWindow::on_focusChanged(QWidget* old, QWidget* nouveau)";
    if(nouveau==ui->lineEditReference)
    {
        //il est dans le modele on affiche les références
        //attacher l'evenement textChanged à la maj de la zone de droite
        connect(ui->lineEditReference,SIGNAL(textChanged(QString)),this, SLOT(majListeRecherche(QString)));
    }
    else
    {
        disconnect(ui->lineEditReference,SIGNAL(textChanged(QString)),this, SLOT(majListeRecherche(QString)));
    }
}

void MainWindow::chargerLesClients()
{
   QSqlQuery reqChargerClient;
   int ligneActu=0;
   //on efface tout
   ui->tableWidgetClient->setRowCount(0);
   reqChargerClient.prepare("select * from Client");
   if(reqChargerClient.exec())
   {
       while(reqChargerClient.next())//pour chaque client
       {
        ui->tableWidgetClient->setRowCount(ligneActu+1);
        //pour chaque champ à afficher
         for(int noCol=0;noCol<7;noCol++)
         {
            ui->tableWidgetClient->setItem(ligneActu,noCol,new QTableWidgetItem(reqChargerClient.value(noCol+1).toString()));
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
    QSqlQuery reqChargerMachine;
    int ligneActu=0;
    ui->tableWidgetMachine->setRowCount(0);
    reqChargerMachine.prepare("select * from Reparation");
    if(reqChargerMachine.exec())
    {
        while(reqChargerMachine.next())
        {
          ui->tableWidgetMachine->setRowCount(ligneActu+1);
          nomMachine=reqChargerMachine.value(1).toString();
          marqueMachine=reqChargerMachine.value(2).toString();
          QString idType=reqChargerMachine.value(3).toString();
          if(idType=="1")
          {
              typeMachine="Thermique";
          }
          else
          {
              typeMachine="Eléctrique";
          }

          refMachine=reqChargerMachine.value(4).toString();
          panneMachine=reqChargerMachine.value(6).toString();
          dateArrivee=reqChargerMachine.value(7).toDate();
          tempsPasse=reqChargerMachine.value(8).toString();
          dateSortie=reqChargerMachine.value(9).toDate();

          QString idClient=reqChargerMachine.value(10).toString();
          QSqlQuery reqChercheClient;
          reqChercheClient.prepare("select nomClient,prenomClient from Client where idClient="+idClient+"");
          if(reqChercheClient.exec())
          {
              reqChercheClient.first();
              clientMachine=reqChercheClient.value(0).toString()+" "+reqChercheClient.value(1).toString();
          }

          QString idDevis=reqChargerMachine.value(11).toString();
          QSqlQuery reqChercheDevis;
          reqChercheDevis.prepare("select etatDevis from Devis_Reparation where idDevis="+idDevis+"");
          if(reqChercheDevis.exec())
          {
              reqChercheDevis.first();
              devisMachine=reqChercheDevis.value(0).toString();
          }

          QString idEtat=reqChargerMachine.value(12).toString();
          QSqlQuery reqChercheEtat;
          reqChercheEtat.prepare("select libelleEtat from Etat_Reparation where idEtat="+idEtat+"");
          if(reqChercheEtat.exec())
          {
              reqChercheEtat.first();
              etatMachine=reqChercheEtat.value(0).toString();
          }

          QString idTech=reqChargerMachine.value(13).toString();
          QSqlQuery reqChercheTech;
          reqChercheTech.prepare("select nomUtilisateur from Utilisateur where idUtilisateur="+idTech+"");
          if(reqChercheTech.exec())
          {
              reqChercheTech.first();
              techMachine=reqChercheTech.value(0).toString();
          }

          ui->tableWidgetMachine->setItem(ligneActu,0,new QTableWidgetItem(nomMachine));
          ui->tableWidgetMachine->setItem(ligneActu,1,new QTableWidgetItem(marqueMachine));
          ui->tableWidgetMachine->setItem(ligneActu,2,new QTableWidgetItem(refMachine));
          ui->tableWidgetMachine->setItem(ligneActu,3,new QTableWidgetItem(typeMachine));
          ui->tableWidgetMachine->setItem(ligneActu,4,new QTableWidgetItem(clientMachine));
          ui->tableWidgetMachine->setItem(ligneActu,5,new QTableWidgetItem(panneMachine));
          ui->tableWidgetMachine->setItem(ligneActu,6,new QTableWidgetItem(etatMachine));
          ui->tableWidgetMachine->setItem(ligneActu,7,new QTableWidgetItem(devisMachine));
          ui->tableWidgetMachine->setItem(ligneActu,8,new QTableWidgetItem(dateArrivee.toString()));
          ui->tableWidgetMachine->setItem(ligneActu,9,new QTableWidgetItem(dateSortie.toString()));
          ui->tableWidgetMachine->setItem(ligneActu,10,new QTableWidgetItem(techMachine));
          ui->tableWidgetMachine->setItem(ligneActu,11,new QTableWidgetItem(tempsPasse));

          ligneActu++;
        }
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

    ui->labelNomClient_2->setText(nomClient);
    ui->labelPrenomClient_2->setText(prenomClient);
    ui->labelTelClient_2->setText(telClient);
    ui->labelEmailClient_2->setText(emailCLient);
    ui->labelCPClient_2->setText(cpClient);
    ui->labelAdresseClient_2->setText(adresseClient);
    ui->labelVilleClient_2->setText(villeClient);

    ui->labelNomClient_3->setText(nomClient);
    ui->labelPrenomClient_3->setText(prenomClient);
    ui->labelTelClient_3->setText(telClient);
    ui->labelEmailClient_3->setText(emailCLient);
    ui->labelCPClient_3->setText(cpClient);
    ui->labelAdresseClient_3->setText(adresseClient);
    ui->labelVilleClient_3->setText(villeClient);

    ui->labelNomClient_4->setText(nomClient);
    ui->labelPrenomClient_4->setText(prenomClient);
    ui->labelTelClient_4->setText(telClient);
    ui->labelEmailClient_4->setText(emailCLient);
    ui->labelCPClient_4->setText(cpClient);
    ui->labelAdresseClient_4->setText(adresseClient);
    ui->labelVilleClient_4->setText(villeClient);

    ui->lineEditNom->setText(nomClient);
    ui->lineEditPrenom->setText(prenomClient);
    ui->lineEditTelephone->setText(telClient);
    ui->lineEditEmail->setText(emailCLient);
    ui->lineEditAdresse->setText(adresseClient);
    ui->lineEditCP->setText(cpClient);
    ui->lineEditVille->setText(villeClient);

    ui->tableWidgetMachineClient->setRowCount(0);
    ui->tableWidgetMachineClient2->setRowCount(0);
    ui->tableWidgetMachineClient3->setRowCount(0);
    ui->tableWidgetMachineClient4->setRowCount(0);

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

void MainWindow::on_tableWidgetClient_cellClicked(int row, int column)
{
    nomClient=ui->tableWidgetClient->item(row,0)->text();
    prenomClient=ui->tableWidgetClient->item(row,1)->text();
    telClient=ui->tableWidgetClient->item(row,2)->text();
    emailCLient=ui->tableWidgetClient->item(row,3)->text();
    villeClient=ui->tableWidgetClient->item(row,4)->text();
    adresseClient=ui->tableWidgetClient->item(row,5)->text();
    cpClient=ui->tableWidgetClient->item(row,6)->text();

    int nbLigne=0;
    ui->tableWidgetMachineClient->setRowCount(0);
    ui->tableWidgetMachineClient2->setRowCount(0);
    ui->tableWidgetMachineClient3->setRowCount(0);
    ui->tableWidgetMachineClient4->setRowCount(0);
    int idClient=chercherIdClient();
    QString idClientS=QString::number(idClient);
    QSqlQuery chercherMachineDuClient;
    chercherMachineDuClient.prepare("select outilNom,dateArrivee from Reparation where idClient="+idClientS+"");
    if(chercherMachineDuClient.exec())
    {
        while(chercherMachineDuClient.next())
        {
            ui->tableWidgetMachineClient->setRowCount(nbLigne+1);
            ui->tableWidgetMachineClient2->setRowCount(nbLigne+1);
            ui->tableWidgetMachineClient3->setRowCount(nbLigne+1);
            ui->tableWidgetMachineClient4->setRowCount(nbLigne+1);
            //pour chaque champ à afficher
             for(int noCol=0;noCol<7;noCol++)
             {
                ui->tableWidgetMachineClient->setItem(nbLigne,noCol,new QTableWidgetItem(chercherMachineDuClient.value(noCol).toString()));
                ui->tableWidgetMachineClient2->setItem(nbLigne,noCol,new QTableWidgetItem(chercherMachineDuClient.value(noCol).toString()));
                ui->tableWidgetMachineClient3->setItem(nbLigne,noCol,new QTableWidgetItem(chercherMachineDuClient.value(noCol).toString()));
                ui->tableWidgetMachineClient4->setItem(nbLigne,noCol,new QTableWidgetItem(chercherMachineDuClient.value(noCol).toString()));
             }
              nbLigne++;//on passe à la ligne suivante
        }
    }


    ui->labelNomClient->setText(nomClient);
    ui->labelPrenomClient->setText(prenomClient);
    ui->labelTelClient->setText(telClient);
    ui->labelEmailClient->setText(emailCLient);
    ui->labelCPClient->setText(cpClient);
    ui->labelAdresseClient->setText(adresseClient);
    ui->labelVilleClient->setText(villeClient);

    ui->labelNomClient_2->setText(nomClient);
    ui->labelPrenomClient_2->setText(prenomClient);
    ui->labelTelClient_2->setText(telClient);
    ui->labelEmailClient_2->setText(emailCLient);
    ui->labelCPClient_2->setText(cpClient);
    ui->labelAdresseClient_2->setText(adresseClient);
    ui->labelVilleClient_2->setText(villeClient);

    ui->labelNomClient_3->setText(nomClient);
    ui->labelPrenomClient_3->setText(prenomClient);
    ui->labelTelClient_3->setText(telClient);
    ui->labelEmailClient_3->setText(emailCLient);
    ui->labelCPClient_3->setText(cpClient);
    ui->labelAdresseClient_3->setText(adresseClient);
    ui->labelVilleClient_3->setText(villeClient);

    ui->labelNomClient_4->setText(nomClient);
    ui->labelPrenomClient_4->setText(prenomClient);
    ui->labelTelClient_4->setText(telClient);
    ui->labelEmailClient_4->setText(emailCLient);
    ui->labelCPClient_4->setText(cpClient);
    ui->labelAdresseClient_4->setText(adresseClient);
    ui->labelVilleClient_4->setText(villeClient);

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

    QString dateARentrer;

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
    dateARentrer=dateArrivee.toString("yyyy/MM/dd");
    nomMachine=ui->lineEditNomMachine->text();
    marqueMachine=ui->lineEditMarque->text();
    //refMachine=ui->lineEditReference->text();
    refMachine=ui->lineEditReference->property("numeroModele").toString();
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

    QSqlQuery insertMachine;
/*CREATE TABLE `Reparation`(`idReparation` int(11),`outilNom` varchar(45),`outilType` tinyint(2),`panneReparation` varchar(255),`outilRef` integer not null references Modele(idModel),`dateArrivee` DATE,`tempsPasse` int(11),`dateFinalisation` date,`idClient` int(11) NOT NULL,`idDevis` int(11) NOT NULL,`idEtat` int(11) NOT NULL,`refProduit` varchar(45) ,`idUtilisateur` int(11) NOT NULL, foreign key (`idClient`) references Client(`idClient`), foreign key (`idDevis`) references Devis_Reparation(`idDevis`), foreign key (`idEtat`) references Etat_Reparation(`idEtat`), foreign key (`refProduit`) references Produit(`refProduit`), foreign key (`idUtilisateur`) references Utilisateur(`idUtilisateur`),primary key(`idReparation`));
 */
    QString txtReq="insert into Reparation (idReparation,outilNom,outilType,panneReparation,outilRef,dateArrivee,idClient,idEtat,idDevis,idUtilisateur) values("+maxId+","+
                                                                                                                                                         "'"+nomMachine+"',"
                                                                                                                                                           //+"'"+marqueMachine+"',"
                                                                                                                                                           +typeMachine+",'"
                                                                                                                                                           +panneMachine+"','"
                                                                                                                                                           +refMachine+"','"
                                                                                                                                                           +dateARentrer+"',"
                                                                                                                                                           +idClientAct+",2,2,1)";
    insertMachine.prepare(txtReq);
    qDebug()<<txtReq;
    qDebug()<<insertMachine.lastError();
    insertMachine.exec();
    qDebug()<<insertMachine.lastError();
    chargerLesMachines();

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
    ui->lineEditReference->setText(item->data(33).toString());
    ui->lineEditReference->setProperty("numeroModele",item->data(32).toString());
    ui->lineEditMarque->setText(item->data(34).toString());
}
