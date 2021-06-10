/* Laboratorio Programacion IV - INCO/FING/UDELAR
 * Laboratorio 4 - Class declaration
 * Autores (por nombre):
 * 	Alexis Baladon
 * 	Guillermo Toyos
 * 	Jorge Machado
 * 	Juan Jose Mangado
 * 	Mathias Ramilo
 */

#ifndef iVideoJueGoController
#define iVideoJueGoController

#include <string>
#include <vector>

using std::vector;
using std::string;

class DtVideojuego;
class DtCategoria;
class DtEstadistica;
enum class TipoValido;
enum class TipoPago;

class IVideojuegoController{
public:
    virtual set<string> *obtenerNombreVideojuegosDesarrollados()=0;
    virtual set<string> *obtenerNombreVideojuegosInactivos()=0;
    virtual set<vector<DtVideojuego>> *obtenerSuscripcionesVideojuegos()=0;
    virtual set<DtCategoria> *obtenerCategoriasGenero()=0;
    virtual set<DtCategoria> *obtenerCategoriasPlataforma()=0;
    virtual set<DtCategoria> *obtenerCategoriasOtro()=0;
    virtual set<DtEstadistica> *obtenerEstadisticas(string)=0;
    virtual void ingresarDatosVideojuego(DtVideojuego)=0;
    virtual void ingresarSuscripcion(TipoValido, TipoPago)=0;
    virtual void seleccionarVideojuego(string)=0;
    virtual void seleccionarGenero(string)=0;
    virtual void seleccionarPlataforma(string)=0;
    virtual void seleccionarCategoriaOtro(string)=0;
    virtual void confirmarPublicacion()=0;
    virtual void confirmarSuscripcion()=0;
    virtual void confirmarEliminarVideojuego()=0;
    virtual void cancelarSuscripcion()=0;
    virtual void clearCache()=0;

    //Caso de uso AgregarCategoria:
    virtual set<string> *obtenerNombreCategorias()=0;
    virtual int cargarCategoria(DtCategoria)=0;
    virtual void confirmarAgregarCategoria()=0;

    virtual ~IVideojuegoController(){}
};

#endif
