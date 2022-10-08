#pragma once
#include <dshow.h>
#include <new>
#include <Windows.h>

using namespace std;

enum EtatDeFonction
{
    ETAT_ENCOURS,
    ETAT_PAUSE, 
};

class Controle
{
public:

    Controle();
    Controle(LPCWSTR path);
    ~Controle();
    
    void Play();
    void Pause();
    void AvanceRapide();
    void RetourOrigine();
    EtatDeFonction GetEtat();
  
private:

    EtatDeFonction m_state;
    double rate;
    REFERENCE_TIME t_debut = 0, t_now;

    IGraphBuilder* pGraph = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;
    IMediaSeeking* pSeeking = NULL;

};
