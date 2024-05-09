#ifndef ABONNE_H_INCLUDED
#define ABONNE_H_INCLUDED
#include<string>
class abonne
{
protected:

    string nom , prenom ;
    int numtel, cin ;
    double solde;
public:
    void setnom(string nom );
    void setprenom(string prenom);
    void setnultem(int numtel);
    void setcin(int cin);
    void setsolde(double solde );
    string getnom();
    string getprenom();
    int getnumtel();
    int getcin();
    double getsolde();
    void saisir();
    void afficher();
    void recharge(double montant);
    void comsommer(int nbsec, double prixmin);

};


#endif // ABONNE_H_INCLUDED
