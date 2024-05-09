#ifndef OUVRAGE_H_INCLUDED
#define OUVRAGE_H_INCLUDED

class ouvrage {
protected:
    int code ;
    string titre;
    int nbexemp;
    float prix;
public:
    ouvrage();
    ouvrage(int code , string titre, int nbexemp, float prix );
    ~ouvrage();
    int getcode(){ return code;};
    string gettitre(){return titre; };
    int getnbre(){return nbexemp;};
    float getprix(){return prix;};

    void setcode(int code);
    void settitre(string titre);
    void setnb( int nbexemp);
    void setprix(float prix );

    void afficher();
    float totalouvrage();





};



#endif // OUVRAGE_H_INCLUDED
