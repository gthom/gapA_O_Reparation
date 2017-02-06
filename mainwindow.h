#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDateEdit"
#include <QListWidgetItem>
#include <QSqlRelationalTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString numeroClient,nomClient,prenomClient,telClient,emailCLient,adresseClient,cpClient,villeClient;
    QString nomMachine,marqueMachine,panneMachine,refMachine,etatMachine,typeMachine,clientMachine,devisMachine,techMachine,tempsPasse;
    QDate dateArrivee,dateSortie;
    ~MainWindow();  
    void chargerLesTechniciens();
private slots:
    void majListeRechercheMachine(QString);
    void on_focusChanged(QWidget *, QWidget*);
    void on_pushButtonAjouterClient_clicked();

    void on_pushButtonSupprimerClient_clicked();

    void on_tableWidgetClient_cellClicked(int row, int column);

    void on_pushButtonDeselectionner_clicked();

    void on_pushButtonModifierClient_clicked();

    void on_pushButtonRechercher_clicked();

    void on_pushButtonAjouterMachine_clicked();

    void on_pushButtonRechercher_2_clicked();

    void on_pushButtonDeselectionner_2_clicked();

    void on_lineEditMarque_returnPressed();

    void on_listWidgetResultatRecherche_itemActivated(QListWidgetItem *item);

    void on_action_Fermer_triggered();

    void on_pushButtonAddTechnicien_clicked();

private:
    Ui::MainWindow *ui;
    void chargerLesClients();

    int chercherIdClient();

    void viderLesChamps();

    void chargerLesMachines();
    QSqlRelationalTableModel * tableModelTechnicien;

};

#endif // MAINWINDOW_H
