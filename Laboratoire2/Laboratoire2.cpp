/*****************************************************************************/
/*Laboratoire 2                                                              */
/*Présenter à : Jérémy Bouchard                                              */
/*Réalisé par : Vincent Tremblay                                             */
/*              Jérome Blackburn Saucier                                     */
/*Code permanent : TREV11080000                                              */
/*                 BLAJ01019200                                              */
/*L'ensemble du travail utilise le code de base fournis par notre professeur */
/*Le laboratoire consiste a faire fonctionné un module c++ en python         */
/*****************************************************************************/



#include <Python.h>
#pragma comment(lib, "Strmiids.lib")
#include <stdio.h>
#include <conio.h>
#include <dshow.h>
#include <iostream>
#include "Controle.h"
#include <codecvt>

using namespace std;



PyObject* lecteur(PyObject* self, PyObject* args)
{
       
        char selectionControle = 'a';
        const char* path = NULL;
        PyArg_ParseTuple(args, "s", &path);

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(path);
        LPCWSTR result = wide.c_str();
      
        PyObject* python_val = Py_BuildValue("i", 1);

        Controle* control = new Controle(result);

                while (selectionControle != 'q' && selectionControle != 'Q') {

                    selectionControle = _getch();
                    switch (selectionControle) {

                    case 'A':
                    case 'a':
                        control->AvanceRapide();
                        break;
                    case 'P':
                    case 'p':

                        if (control->GetEtat() == ETAT_ENCOURS)
                        {
                            control->Pause();
                        }
                        else if (control->GetEtat() == ETAT_PAUSE)
                        {
                            control->Play();
                        } 
                        break;
                    case 'R':
                    case 'r':
                        control->RetourOrigine();
                        break;
                    default:
                        break;
                    }
                }
                control->~Controle();
        return python_val;
    
}




 static PyMethodDef methods[] = {

     {"lecteur", (PyCFunction)lecteur, METH_VARARGS, "read a video"},

 { NULL, NULL, 0, NULL }

 };

 static struct PyModuleDef Laboratoire2 = {
    
    PyModuleDef_HEAD_INIT, 
    "Laboratoire2",
    "Essais de laboratoire 2",
    -1,
    methods
 
 };

 PyMODINIT_FUNC PyInit_Laboratoire2()
 {
     return PyModule_Create(&Laboratoire2);
 }
   


