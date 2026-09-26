/* ///////////////////////////////////////////////////////////////

GM BASE CREADA Y ACTUALIZADA POR BARRIONUEVO

- Respetar estos creditos de arriba, todo lo demas pueden editarlo con gusto :D
- La gamemode es totalmente de 0.

ADVERTENCIA: la gamemode al compilarla tiene 2 warnings con respecto al cache_get_row_count
por lo que el ingreso, y registro no funcionaran correctamente. Deben cambiar la funcion
de las dos lineas acorde a la version actual. Hecho esto, podran usar la gamemode sin
ningun tipo de problema. La gamemode fue creada en un dia, por lo cual cualquier hallazgo
de algun error pueden solucionarlo en un segundo, no son muchas lineas. Aunque revisando bien
el unico problema eran los warnings que mencione, lo demas va de manera perfecta.

Mi discord: rulitosssx

///////////////////////////////////////////////////////////////// */
#include "../gamemodes/includes.inc"

//----------------------------------------------------------//

public OnGameModeInit()
{
	dbsql = mysql_connect(samp_host, samp_user, samp_contra, samp_db);
	if (mysql_errno(dbsql) != 0)
	{
    	printf("---- CONEXION INCORRECTA CON LA BASE DE DATOS ----");

		SendRconCommand("exit");
    	return 1;
	}
	else
	{
    	printf("---- CONEXION CORRECTA CON LA BASE DE DATOS -  2024 -----");
	}

	
	ShowPlayerMarkers(1);
	ShowNameTags(1);

	SendRconCommand("hostname "SERVER_HOSTNAME);
	SendRconCommand("gamemodetext "SERVER_GAMEMODE);
	SendRconCommand("language "SERVER_LANGUAGE);
	return 1;
}