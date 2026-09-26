#include <YSI_Coding\y_hooks>

//----------------------------------------------------------//
public OnPlayerConnect(playerid)
{
    new query[520], nombre[MAX_PLAYER_NAME];
    GetPlayerName(playerid, nombre, sizeof(nombre));
    mysql_format(dbsql, query, sizeof(query), "SELECT * FROM cuentas WHERE Nombre = '%s'", nombre);
    mysql_pquery(dbsql, query, "VerificarUsuario", "d", playerid);
 	return 1;
}
//----------------------------------------------------------//

public OnPlayerSpawn(playerid)
{
    if(GetPVarInt(playerid, "PuedeIngresar") == 0)
	{
	Kick(playerid);
	}
	return 1;
}

//----------------------------------------------------------//

public OnPlayerDeath(playerid, killerid, reason)
{
	Jugador[playerid][Muertes]++;
	Jugador[killerid][Asesinatos]++;
   	return 1;
}
//----------------------------------------------------------//

public OnPlayerRequestClass(playerid, classid)
{
	return 0;
}

//----------------------------------------------------------//

public OnPlayerUpdate(playerid)
{
	return 1;
}

//----------------------------------------------------------//

public OnPlayerDisconnect(playerid, reason)
{
	GuardarJugador(playerid);
	return 1;
}

//----------------------------------------------------------//