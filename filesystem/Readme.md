no copiar los archivos de prueba a esta carpeta del git porque son muy grandes
los pondremos en esta direccion /home/utnso/arhivoPrueba

cada uno debe descargarlos a su maquina
los links estan en utnso
http://www.utn.so/weather/201301hourly.txt.gz
http://www.utn.so/weather/201302hourly.txt.gz
http://www.utn.so/weather/201303hourly.txt.gz

----------------------------------------------------------
arbol de funciones
formatearMDFS()
>>liberaMemoriaFS(); inicializarFilesystem();
eliminarArchivo()
>>	eliminarElemento(nombreArchivo);
renombrarArchivo()
>>renombrarElemento(ptrArchivo, nuevoNombreArchivo);
moverArchivo()
>>buscarElementoPorNombre(nombreDirectorioDestino);
>>moverElemento(ptrArchivo, directorioDestino);
crearDirectorio()
>>crearElemento();
 eliminarDirectorio()
 >>eliminarElemento()
 renombrarDirectorio()
 >> buscarElementoPorNombre(nombreDirectorio);
 >>renombrarElemento(ptrDirectorio, nuevoNombreDirectorio);
  moverDirectorio()
  >>buscarElementoPorNombre(nombreDirectorioDestino);
  moverElemento(directorioOrigen, directorioDestino);
  
  copiarArchivoLocalAlMDFS()
  >>sacarUltimaParte(dirArchivoLocal);
  >>mapeoAmemoria(dirArchivo, ptrAMemoriaModificado, ptrTamanioDePagina);
  >>desMapea(*ptrTamanioDePagina, ptrComienzoMemoriaMapeada);
  >>divideBloques(&buffer[0], archivoEntrante);
  >>>>copiaDistribuyeYEmpaqueta(bloqueFinal, cantBloque, unElemento);
  >>>>>>puedoHacerCopias(cantBloques)
  >>>>>>distribucionInicial(bloqueListo,elemento);
  >>>>>>>>empaquetarYMandarPorSocket(bloqueListo, unNodoBloque); <--santiago
  void verUbicacionBloque() 
  actualizarListaDeArchivos(ubicacionDelBloqueEnNodo* unaUbicacion,
		element* unArchivo)
  void copiarBloque() 
  >>devuelveBloque(nombreArchivo, numeroBloque);
  >>solicitudCopiaDeBloque(); --> falta hacer
   
   borrarBloque() 
   >>buscarElementoPorNombre(nombreArchivo);
   >>actualizarListaDeArchivos(miUbicacion, ptrArchivo);
   >>>>
  
saludos