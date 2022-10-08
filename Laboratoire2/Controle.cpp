#include "Controle.h"
#pragma comment(lib, "Strmiids.lib")
#include <stdio.h>
#include <conio.h>
#include <dshow.h>
#include <iostream>


Controle::Controle(LPCWSTR path)
{
    
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");

    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");

    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeeking);

    // Build the graph. IMPORTANT: Change this string to a file on your system.
    hr = pGraph->RenderFile(path, NULL);

    if (SUCCEEDED(hr))
    {
        // Run the graph.
        pControl->Run();
        pControl->Pause();
        m_state = ETAT_PAUSE;
    }
}

Controle::~Controle()
{
    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    pSeeking->Release();
    CoUninitialize();
}


void Controle::Play()
{
    if (m_state == ETAT_PAUSE) 
    {
        cout << "Play \n";
        pControl->Run();
        m_state = ETAT_ENCOURS;
    }
}

void Controle::Pause()
{
    if (m_state == ETAT_ENCOURS) 
    {
        cout << "Pause \n";
        pControl->Pause();
        m_state = ETAT_PAUSE;
    }
}

void Controle::AvanceRapide()
{
    pSeeking->GetRate(&rate);
    if (rate == 1.5) {
        cout << "already done at 1.5 \n ";
    }
    else {
        cout << "set at 1.5 \n";
        pSeeking->SetRate(1.5);
    }
}

void Controle::RetourOrigine()
{
    cout << "retour au debut \n";
    pControl->Pause();
    pSeeking->GetPositions(NULL, &t_now);
    pSeeking->SetPositions(&t_debut, AM_SEEKING_AbsolutePositioning, &t_now, AM_SEEKING_AbsolutePositioning);
    pControl->Run();
    m_state = ETAT_ENCOURS;
}

EtatDeFonction Controle::GetEtat()
{
    return m_state;
}

