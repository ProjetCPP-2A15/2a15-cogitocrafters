#ifndef ETUDIANT_H_INCLUDED
#define ETUDIANT_H_INCLUDED
#include <string>
class etudiant
{
protected:
    string  nom , prenom;
    float tab_note[10];

public:
    etudiant(){
    for (int i=0;i<10; i++)
        tab_note[i]=0;

    }


};


#endif // ETUDIANT_H_INCLUDED
