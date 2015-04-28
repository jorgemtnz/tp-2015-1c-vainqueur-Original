# tp-2015-1c-vainqueur

 /home/utnso/TPOperativos.
 estado ya en consola y dentro de la carpeta TPOperativos

1. hacer el git pull vainqueur master (se recomienda esto y no el git clone)
2. creo archivo y hago el git add
3. git commit -m "mensaje de lo que hice"
4. git push vainqueur master 

otra opci{on para el punto 4. 

4. git push -u vainqueur master

esto hace que recuerde el nombre del repositorio 
por lo que ya no habria que volver a ponerlo,

ahora se debe hacer :
git config --global push.default simple

entonces la próxima vez que hagamos el push sería

4. git push 

eh igualmente se pude hacer a partir de este momento solamente git pull
ya que recuerda el nombre del repositorio y el branch que este activo será el
que subirá.
-----------------------------------------------------------
Problemas y solución
----------------------------
problema: necesitamos regresar a un commit anterior
consecuencia: al hacerlo aplicando el comando corrrespondiente.Todo volvera a su estado anterior del ultimo commit, al que hemos regresado. Entonces se borraran todos los archivos creados nuevos, y se perderan las modificiones realizadas.
solución: ir creando una copia de los archivos que tenemos para poder tenerlos. Por lo que es conveniente tener además varios branch para trabajar.
