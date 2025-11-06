#include <iostream>
#include "grafo.h"

using namespace std;

int main() {

  Grafo *rutasMedicas = new Grafo();
  
// --- Requisito: 6 Centros Médicos ---
  cout << "Insertando Centros Medicos..." << endl;
  rutasMedicas->InsertaVertice("H001", "Hospital Rebagliati", "HOSPITAL", "Av. Rebagliati 490, Jesus Maria");
  rutasMedicas->InsertaVertice("H002", "Hospital Almenara", "HOSPITAL", "Av. Grau 800, La Victoria");
  rutasMedicas->InsertaVertice("C001", "Clinica Delgado", "CONSULTORIO", "Calle Gral. Borgoño 1150, Miraflores");
  rutasMedicas->InsertaVertice("L001", "Laboratorio ROE", "LABORATORIO", "Av. Arequipa 2080, Lince");
  rutasMedicas->InsertaVertice("C002", "Posta Medica Jesus Maria", "CONSULTORIO", "Jr. Huiracocha 1500, Jesus Maria");
  rutasMedicas->InsertaVertice("H003", "Hospital del Niño", "HOSPITAL", "Av. Brasil 600, Breña");
  cout << "---------------------------------------------" << endl;


  // --- Requisito: 10 Rutas ---
  cout << "\nInsertando Rutas..." << endl;
  rutasMedicas->InsertaArista("H001", "C001", 3.5, "vehicular");
  rutasMedicas->InsertaArista("H001", "L001", 2.1, "peatonal");
  rutasMedicas->InsertaArista("H001", "H003", 1.8, "ambulancia");
  rutasMedicas->InsertaArista("H002", "H001", 7.2, "vehicular");
  rutasMedicas->InsertaArista("C001", "L001", 1.5, "peatonal");
  rutasMedicas->InsertaArista("L001", "H001", 2.2, "vehicular");
  rutasMedicas->InsertaArista("L001", "C002", 3.0, "vehicular");
  rutasMedicas->InsertaArista("C002", "H003", 1.0, "peatonal");
  rutasMedicas->InsertaArista("H003", "H001", 1.9, "ambulancia");
  rutasMedicas->InsertaArista("C002", "H001", 2.5, "vehicular");
  cout << "---------------------------------------------" << endl;


  
  // 1. Mostrar Lista Completa
  cout << "\n--- Mostrando Lista de Adyacencia Completa ---" << endl;
  rutasMedicas->MostrarListaAdyacencia();

  // 2. Visualizar centros conectados
  cout << "\n--- Visualizar centros conectados a [H001] ---" << endl;
  rutasMedicas->MostrarAdyacentes("H001");

  cout << "\n--- Visualizar centros conectados a [L001] ---" << endl;
  rutasMedicas->MostrarAdyacentes("L001");

  // 3. Buscar si existe ruta
  cout << "\n--- Buscando si existe ruta ---" << endl;
  if (rutasMedicas->ExisteRuta("H001", "H003"))
    cout << "SI existe ruta directa de H001 a H003" << endl;
  else
    cout << "NO existe ruta directa de H001 a H003" << endl;
  
  if (rutasMedicas->ExisteRuta("H002", "L001"))
    cout << "SI existe ruta directa de H002 a L001" << endl;
  else
    cout << "NO existe ruta directa de H002 a L001" << endl;
  
  cout << "---------------------------------------------" << endl;

  
  // --- Prueba de Eliminación (Funcionalidad obligatoria) ---
  
  // 4. Eliminar Arista
  cout << "\n--- Eliminando ruta H001 -> C001 ---" << endl;
  rutasMedicas->EliminarArista("H001", "C001"); 
  cout << "---------------------------------------------" << endl;


  // 5. Eliminar Vertice
  cout << "\n--- Eliminando Centro Medico C002 ---" << endl;
  rutasMedicas->EliminarVertice("C002");
  cout << "---------------------------------------------" << endl;


  cout << "\n--- Mostrando Lista de Adyacencia Final ---" << endl;
  rutasMedicas->MostrarListaAdyacencia();
  cout << "---------------------------------------------" << endl;
  
  delete rutasMedicas;
  return 0;
}
