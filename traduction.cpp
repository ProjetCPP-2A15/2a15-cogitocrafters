#include "mainwindow.h"
#include "ui_mainwindow.h"

//*********************************************************************   SETTINGS    ***********************************************************
void MainWindow::on_logout_7_clicked()
{
    ui->StackedWidget->setCurrentIndex(6);
    //ui->setting->setCurrentIndex(0);
}




void MainWindow::on_arsexe_3_currentIndexChanged(int index)
{
    QTranslator translator;
       switch (index) {
           case 0: // English
               qApp->removeTranslator(&translator);
               ui->pushButtonProduct->setText("Products");
               ui->pushButtonArtist->setText("Artists");
               ui->pushButtonEvents->setText("Events");
               ui->pushButtonAssociation->setText("Associations");
               ui->pushButtonGuest->setText("Guests");
               ui->pushButtonEmployee->setText("Employees");


                //***************************************************************** englais partie artiste *************************************************
               //phone
               ui->Nb_Emp_3->setText("phone :");
               ui->id_127->setText("phone :");
               ui->label_phoneGuest_3->setText("Adress:");
               ui->Nb_Emp_6->setText("phone :");
               ui->label_29->setText("phone");

               //Name :
               ui->label_23->setText("Name :");
               ui->Nom_3->setText("Name :");
               ui->id_138->setText("Name :");
               ui->label_ageGuest_3->setText("Name");
               ui->label_31->setText("Name :");
               ui->label_42->setText("Last Name");
               ui->label_30->setText("Adress");
               ui->label_43->setText("Mail");
               //Last Name :
               ui->label_25->setText("Last Name :");
               ui->heure_debut_3->setText("Last Name :");
               ui->id_139->setText("Last Name :");
               ui->label_nameGuest_3->setText("Phone:");

               //Adress :
               ui->label_24->setText("Adress :");
               ui->description_3->setText("Adress :");
               ui->id_135->setText("Adress :");
               ui->label_adresseGuest_3->setText("Last name:");

               // Mail :
               ui->label_28->setText("Field :");
               ui->lieux_3->setText("Mail :");
               ui->id_134->setText("Mail :");
               ui->label_genderGuest_4->setText("Mail :");

               //Domaine :
               ui->label_27->setText("Domain :");
               ui->price_5->setText("Domain :");
               ui->id_136->setText("Domain :");
               ui->label_emailGuest_3->setText("Domain :");


               // Cin Number :
               ui->ID_3->setText("Cin Number :");
               ui->id_137->setText("Cin Number :");
               ui->label_21->setText("  Cin");


               // Gender :
               ui->price_4->setText("Gender :");
               ui->id_133->setText("Gender :");

               //Description :
               ui->description_5->setText("Description :");
               ui->id_141->setText("Description :");

               //photo
               ui->arpicture->setText("picture :");
               ui->arpicture_2->setText("picture :");

               //les button
               ui->label_174->setText("Add New Artist ");
               ui->label_175->setText("Update Artist");
               ui->label_218->setText("Delete Artist");
               ui->label_234->setText("An Artist's information");


               //*************************************************   EMPLOYEE  ****************************************************************************

                              ui->label_813->setText("Employee List");
                              ui->label_AddNewEmployee->setText("Add New Employee");
                              ui->anemployeesinfo_10->setText("Pie chart showing gender");
                              ui->updateEmployee_19->setText("Update Employee");

                              ui->label_818->setText("  Number ");
                              ui->label_Cin->setText("CIN Number");

                              ui->label_815->setText("Name ");
                              ui->label_Name->setText("Name");

                              ui->label_817->setText("Last Name ");
                              ui->label_Lastname->setText("Last Name");

                              ui->label_814->setText("Address ");
                              ui->label_Address->setText("Address");


                              ui->label_816->setText("Position ");
                              ui->label_Function->setText("Position");

                              ui->label_819->setText("Email ");
                              ui->label_Mail->setText("Email");

                              ui->id_DateBirth->setText("Date of Birth");
                              ui->label_Sex->setText("Gender");

                              ui->label_PhoneNumber->setText("Phone Number");
                              ui->label_Password->setText("Password");

                              ui->pushButton_UpDateImageEmployee->setText("Change Employee Image");




                              //**************************  Association***********************************************

                              ui->label_172->setText("Association List");
                              ui->label_178->setText("Add Association");
                              ui->label_328->setText("Update Association");
                              ui->label_235->setText("Association Information");

                              ui->label_cinGuest_6->setText("Name ");
                              ui->label_226->setText("Name:");

                              ui->label_cinGuest_7->setText("Address ");
                              ui->label_227->setText("Address:");

                              ui->label_cinGuest_8->setText("Budget ");
                              ui->label_228->setText("Budget:");

                              ui->label_cinGuest_9->setText("Description ");
                              ui->label_227->setText("Description:");

                              ui->label_cinGuest_15->setText("Type ");





//******************************************    GUEST   ********************************************************************************


                    ui->label_326->setText("List Guest");
                    ui->label_189->setText("Add New Guest");
                    ui->label_140->setText("Update Guest");
                    ui->label_218->setText("An Guest's Information");

                    ui->label_cinGuest->setText("Cin");
                    ui->label_192->setText("Cin");


                    ui->label_nameGuest->setText("Full Name");
                    ui->label_194->setText("Full Name");


                    ui->label_ageGuest->setText("Age");
                    ui->label_204->setText("Age");

                    ui->label_genderGuest->setText("Gender");
                    ui->label_205->setText("Gender");


                    ui->label_adresseGuest->setText("Adress");
                    ui->label_195->setText("Adress");

                    ui->label_phoneGuest->setText("Phone");
                    ui->label_202->setText("Phone");

                    ui->label_emailGuest->setText("Email");
                    ui->label_203->setText("Email");



//********************************************* PRODUCT  ***********************************************************************************************

                    ui->label_128->setText("List Of Product");
                    ui->label_49->setText("Add New Product");
                    ui->label_231->setText("An Product's Information");
                    ui->label_329->setText("Update Guest");
                    ui->label_89->setText("Chatbot");
                    ui->label_223->setText("Delete Product");

                    ui->label_71->setText("ID");

                    ui->label_70->setText("Field");
                    ui->label_199->setText("Field");

                    ui->label_75->setText("Name");
                    ui->label_201->setText("Name");

                    ui->label_72->setText("Creation Date");
                    ui->label_210->setText("Creation Date");

                    ui->label_88->setText("Type");
                    ui->label_200->setText("Type");

                    ui->label_90->setText("Dimention");
                    ui->label_198->setText("Dimention");

                    ui->label_91->setText("Weight");
                    ui->label_206->setText("Weight");

                    ui->label_211->setText("Price");
                    ui->label_217->setText("Description");






      //*****************************************  EVENEMENT  *******************************************************************************************

                    ui->label_60->setText("List Of Event");
                    ui->label_59->setText("Add New Event");
                    ui->label_61->setText("Event Calendar");
                    ui->label_87->setText("Statistic");
                    ui->titlr_2->setText("An Event's Participal Information");
                    ui->titlr_3->setText("All Guest's Information");
                    ui->titlr->setText("An Event's Information");
                    ui->label_184->setText("Update Event");


                    ui->label_41->setText("ID");
                    ui->label_146->setText("ID");


                    ui->label_32->setText("Event Noun");
                    ui->label_147->setText("Event Noun");


                    ui->label_39->setText("Location");
                    ui->label_150->setText("Location");


                    ui->label_37->setText("Start Date");
                    ui->label_148->setText("Start Date");


                    ui->label_38->setText("End Date");
                    ui->label_152->setText("End Date");


                    ui->label_34->setText("Price Of Ticket");
                    ui->label_153->setText("Price Of Ticket");


                    ui->label_33->setText("Employee Number");
                    ui->label_35->setText("Start Hour");
                    ui->label_36->setText("End Hour");
                    ui->label_40->setText("Description");

               break;
           case 1: // Français
               translator.load(":/translations/fr.qm");
               qApp->installTranslator(&translator);
               ui->pushButtonProduct->setText("Produit");
               ui->pushButtonArtist->setText("Artist");
               ui->pushButtonEvents->setText("Evenement");
               ui->pushButtonAssociation->setText("Association");
               ui->pushButtonGuest->setText("Visiteur");
               ui->pushButtonEmployee->setText("Employee");


               //**********************************************************  partie Artiste Français  ****************************************

               //phone
               ui->Nb_Emp_3->setText("Telephone :");
               ui->id_127->setText("Telephone :");
               ui->label_phoneGuest_3->setText("Adresse:");
               ui->Nb_Emp_6->setText("Telephone :");
               ui->label_29->setText("Telephone");

               //Name :
               ui->label_23->setText("Nom :");
               ui->Nom_3->setText("Nom :");
               ui->id_138->setText("Nom :");
               ui->label_ageGuest_3->setText("Nom");
               ui->label_31->setText("Nom");
               ui->label_42->setText("Prenom");
               ui->label_30->setText("Adresse");
               ui->label_43->setText("Email");

               //Last Name :
               ui->label_25->setText("Prenom :");
               ui->heure_debut_3->setText("Prenom :");
               ui->id_139->setText("Prenom :");
               ui->label_nameGuest_3->setText("Numero:");

               //Adress :
               ui->label_24->setText("Adresse :");
               ui->description_3->setText("Adresse :");
               ui->id_135->setText("Adresse :");
               ui->label_adresseGuest_3->setText("Prenom:");

               // Mail :
               ui->label_28->setText("Domaine :");
               ui->lieux_3->setText("Email :");
               ui->id_134->setText("Email :");
               ui->label_genderGuest_4->setText("Email :");

               //Domaine :
               ui->label_27->setText("Domaine :");
               ui->price_5->setText("Domaine :");
               ui->id_136->setText("Domaine :");
               ui->label_emailGuest_3->setText("Domaine :");


               // Cin Number :
               ui->ID_3->setText("Cin Numero :");
               ui->id_137->setText("Cin Numero :");
               ui->label_cinGuest_14->setText("Cin Numero :");
               ui->label_21->setText("  Num");


               // Gender :
               ui->price_4->setText("Sexe :");
               ui->id_133->setText("Sexe :");

               //Description :
               ui->description_5->setText("Description :");
               ui->id_141->setText("Description :");

               //photo
               ui->arpicture->setText("image :");
               ui->arpicture_2->setText("image :");

               //les button
               ui->label_174->setText("Ajouter Artiste");
               ui->label_175->setText("Modifier Artiste");
               ui->label_218->setText("Supprimer Artiste");
               ui->label_234->setText("Information sur Artiste");

//*************************************************   EMPLOYEE  ****************************************************************************

               ui->label_813->setText("Liste des employees ");
               ui->label_AddNewEmployee->setText("Ajouter Employee ");
               ui->anemployeesinfo_10->setText("Pie chart showing gender ");
               ui->updateEmployee_19->setText("Modifier Employee");

               ui->label_818->setText("  Numero ");
               ui->label_Cin->setText("Numero Cin");

               ui->label_815->setText("Nom ");
               ui->label_Name->setText("Nom");

               ui->label_817->setText("Prenom ");
               ui->label_Lastname->setText("Prenom");

               ui->label_814->setText("Adresse ");
               ui->label_Address->setText("Adresse");


               ui->label_816->setText("Fonction ");
               ui->label_Function->setText("Fonction");

               ui->label_819->setText("Email ");
               ui->label_Mail->setText("Email");

               ui->id_DateBirth->setText("Date de naissance");
               ui->label_Sex->setText("Sexe");

               ui->label_PhoneNumber->setText("Telephone");
               ui->label_Password->setText("Mot passe");

               ui->pushButton_UpDateImageEmployee->setText("changer image employee");




               //**************************  Association***********************************************

               ui->label_172->setText("Liste des association");
               ui->label_178->setText("Ajouter Association");
               ui->label_328->setText("Modifier Association");
               ui->label_235->setText("Information d'association");

               ui->label_cinGuest_6->setText("Nom ");
               ui->label_226->setText("Nom :");

               ui->label_cinGuest_7->setText("Adresse ");
               ui->label_227->setText("Adresse :");

               ui->label_cinGuest_8->setText("budget ");
               ui->label_228->setText("budget :");

               ui->label_cinGuest_9->setText("Description ");
               ui->label_227->setText("Description :");

               ui->label_cinGuest_15->setText("Type ");


 //******************************************    INVITÉ   ********************************************************************************


                                   ui->label_326->setText("Liste des Invités");
                                   ui->label_189->setText("Ajouter un Nouvel Invité");
                                   ui->label_140->setText("Mettre à Jour l'Invité");
                                   ui->label_218->setText("Informations d'un Invité");

                                   ui->label_cinGuest->setText("CIN");
                                   ui->label_192->setText("CIN");


                                   ui->label_nameGuest->setText("Nom Complet");
                                   ui->label_194->setText("Nom Complet");


                                   ui->label_ageGuest->setText("Âge");
                                   ui->label_204->setText("Âge");

                                   ui->label_genderGuest->setText("Genre");
                                   ui->label_205->setText("Genre");


                                   ui->label_adresseGuest->setText("Adresse");
                                   ui->label_195->setText("Adresse");

                                   ui->label_phoneGuest->setText("Téléphone");
                                   ui->label_202->setText("Téléphone");

                                   ui->label_emailGuest->setText("Email");
                                   ui->label_203->setText("Email");

//********************************************* PRODUIT  ***********************************************************************************************

                                                       ui->label_128->setText("Liste des Produits");
                                                       ui->label_49->setText("Ajouter un Nouveau Produit");
                                                       ui->label_231->setText("Informations sur un Produit");
                                                       ui->label_329->setText("Mettre à Jour le Produit");
                                                       ui->label_89->setText("Chatbot");
                                                       ui->label_223->setText("Supprimer le Produit");

                                                       ui->label_71->setText("ID");

                                                       ui->label_70->setText("Domaine");
                                                       ui->label_199->setText("Domaine");

                                                       ui->label_75->setText("Nom");
                                                       ui->label_201->setText("Nom");

                                                       ui->label_72->setText("Date Création");
                                                       ui->label_210->setText("Date de Création");

                                                       ui->label_88->setText("Type");
                                                       ui->label_200->setText("Type");

                                                       ui->label_90->setText("Dimensions");
                                                       ui->label_198->setText("Dimensions");

                                                       ui->label_91->setText("Poids");
                                                       ui->label_206->setText("Poids");

                                                       ui->label_211->setText("Prix");
                                                       ui->label_217->setText("Description");



//*****************************************  ÉVÉNEMENT  *******************************************************************************************

                                                                           ui->label_60->setText("Liste des Événements");
                                                                           ui->label_59->setText("Ajouter un Nouvel Événement");
                                                                           ui->label_61->setText("Calendrier des Événements");
                                                                           ui->label_87->setText("Statistiques");
                                                                           ui->titlr_2->setText("Informations sur la Participation à l'Événement");
                                                                           ui->titlr_3->setText("Informations sur Tous les Invités");
                                                                           ui->titlr->setText("Informations sur l'Événement");
                                                                           ui->label_184->setText("Mettre à Jour l'Événement");


                                                                           ui->label_41->setText("ID");
                                                                           ui->label_146->setText("ID");


                                                                           ui->label_32->setText("Nom ");
                                                                           ui->label_147->setText("Nom ");


                                                                           ui->label_39->setText("Lieu");
                                                                           ui->label_150->setText("Lieu");


                                                                           ui->label_37->setText("Date Début");
                                                                           ui->label_148->setText("Date Début");


                                                                           ui->label_38->setText("Date Fin");
                                                                           ui->label_152->setText("Date Fin");


                                                                           ui->label_34->setText("Prix");
                                                                           ui->label_153->setText("Prix");


                                                                           ui->label_33->setText("Nombre d'Employés");
                                                                           ui->label_35->setText("Heure de Début");
                                                                           ui->label_36->setText("Heure de Fin");
                                                                           ui->label_40->setText("Description");





               break;
           case 2: // Arabe
               translator.load(":/translations/ar.qm");
               qApp->installTranslator(&translator);
               break;
       }
}
