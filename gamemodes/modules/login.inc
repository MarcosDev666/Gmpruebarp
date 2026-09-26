#include <YSI_Coding\y_hooks>

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	//
	case DIALOG_REGISTRO:
	{
        if(response)
		{
		new contra[128];
		EMensaje(playerid, VERDECLARO, "Bien! Continuemos con el registro.");
		ShowPlayerDialog(playerid, DIALOG_GENERO, DIALOG_STYLE_MSGBOX, "Genero", "Seleccione su genero.", "[*]Masculino", "Femenino");
		format(contra,sizeof(contra),"%s",inputtext);
		Jugador[playerid][Contra] = contra;
		}
		else
		{
		Kick(playerid);
		}
    }
    //
	case DIALOG_GENERO:
	{
		if(response)
		{
		Jugador[playerid][Genero] = 0;
		Jugador[playerid][Ropa] = 46;
		EMensaje(playerid,-1,"Has seleccionado {FFFF00}masculino{FFFFFF}.");
		ShowPlayerDialog(playerid, DIALOG_EDAD, DIALOG_STYLE_INPUT, "[*]Edad", "[*]Ingrese su edad\n\nMinimo 18 - Maximo 90.", "Continuar", "Cancelar");
		}
		else
		{
		Jugador[playerid][Genero] = 1;
		Jugador[playerid][Ropa] = 12;
		EMensaje(playerid,-1,"Has seleccionado {FFFF00}femenino{FFFFFF}.");
		ShowPlayerDialog(playerid, DIALOG_EDAD, DIALOG_STYLE_INPUT, "[*]Edad", "[>]Ingrese su edad\n\nMinimo 18 - Maximo 90.", "Continuar", "Cancelar");
		}
	  }
	//
	case DIALOG_EDAD:
	{
	     if(response)
		 {
		 if(strval(inputtext) < 18 || strval(inputtext) > 100) return ShowPlayerDialog(playerid, DIALOG_EDAD, DIALOG_STYLE_INPUT, "[>]Edad", "[*]Ingrese su edad\n\n{FF0000}Minimo 18 - Maximo 90.", "Continuar", "Cancelar");
		 Jugador[playerid][Edad] = strval(inputtext);
		 SetSpawnInfo(playerid, 0, Jugador[playerid][Ropa], 1484.1082, -1668.4976, 14.9159, 0.0000, 0,0,0,0,0,0);
		 SetPVarInt(playerid, "PuedeIngresar", 1);
		 SpawnPlayer(playerid);
		 CrearCuenta(playerid);
	     }
		 else
		 {
		 Kick(playerid);
		 }
	}
	//
	case DIALOG_INGRESO:
	{
        if(response)
		{
		new query[520];
		mysql_format(dbsql, query, sizeof query,"SELECT * FROM cuentas WHERE Nombre = '%s' AND Contra = '%s'",NombreJugador(playerid),inputtext);
		mysql_pquery(dbsql, query, "IngresoJugador","d", playerid);
		}
		else
		{
		Kick(playerid);
		}
	}
	//
	}
	return 1;
}

public VerificarUsuario(playerid)
{
	new Rows;
    Rows = cache_get_row_count();
    if(!Rows)
    {
    CamaraInicio(playerid);
	ShowPlayerDialog(playerid, DIALOG_REGISTRO, DIALOG_STYLE_INPUT, "Registro", "Bienvenido\n\nIngrese una contraseña para registrarse.", "Registrar", "Cancelar");
	}
	else
	{
	CamaraInicio(playerid);
	ShowPlayerDialog(playerid, DIALOG_INGRESO, DIALOG_STYLE_INPUT, "[*] Ingreso", "[>]Bienvenido\n\nIngrese su contraseña para ingresar.", "Continuar", "Cancelar");
	}
	return 1;
}
stock CamaraInicio(playerid)
{
SetPlayerCameraPos(playerid, 1533.2587, -1763.7717, 73.6204);
SetPlayerCameraLookAt(playerid, 1532.9288, -1762.8286, 73.0504);
SetPlayerPos(playerid,1513.4531, -1782.2853, 68.0610);
TogglePlayerControllable(playerid,0);
return 1;
}
stock NombreJugador(playerid)
{
new nombre[MAX_PLAYER_NAME];
GetPlayerName(playerid, nombre, sizeof(nombre));
return nombre;
}
public CrearCuenta(playerid)
{
new query[520],aviso[125];
mysql_format(dbsql, query, sizeof query, "INSERT INTO `cuentas`(`Nombre`, `Contra`, `Ropa`, `X`, `Y`, `Z`, `Genero`, `Vida`, `Dinero`) VALUES ('%s','%s','%i','1484.1082', '-1668.4976', '14.9159','%i','100','100000')",
NombreJugador(playerid),
Jugador[playerid][Contra],
Jugador[playerid][Ropa],
Jugador[playerid][Genero]);
mysql_query(dbsql, query);
EMensaje(playerid,VERDECLARO,"Felicitaciones! Registro completo.");
EMensaje(playerid,-1,"Has completado el resgistro, bienvenido a el servidor, disfruta tu estadia.");
EMensaje(playerid,-1, "Has recibido una bonificacion extra en tu cuenta por estar en nuestro comienzo.");
format(aviso,sizeof(aviso),"Cuenta creada: %s - Edad: %d - Genero: %d", NombreJugador(playerid), Jugador[playerid][Edad], Jugador[playerid][Genero]);
print(aviso);
return 1;
}

public IngresoJugador(playerid)
{
if(cache_get_row_count() == 0)
{
ShowPlayerDialog(playerid, DIALOG_INGRESO, DIALOG_STYLE_INPUT, "[*]Ingreso", "Error!\n\nLa contraseña no es correcta.", "Continuar", "Cancelar");
}
else
{
Jugador[playerid][Ropa] = cache_get_value_int(0, "Ropa", Jugador[playerid][Ropa]);
Jugador[playerid][X] = cache_get_value_float(0, "X", Jugador[playerid][X]);
Jugador[playerid][Y] = cache_get_value_float(0, "Y", Jugador[playerid][Y]);
Jugador[playerid][Z] = cache_get_value_float(0, "Z", Jugador[playerid][Z]);
Jugador[playerid][Genero] = cache_get_value_int(0, "Genero", Jugador[playerid][Genero]);
Jugador[playerid][Vida] = cache_get_value_float(100, "Vida", Jugador[playerid][Vida]);
Jugador[playerid][Chaleco] = cache_get_value_float(0, "Chaleco", Jugador[playerid][Chaleco]);
Jugador[playerid][Muertes] = cache_get_value_int(0, "Muertes", Jugador[playerid][Muertes]);
Jugador[playerid][Asesinatos] = cache_get_value_int(0, "Asesinatos", Jugador[playerid][Asesinatos]);
Jugador[playerid][Faccion] = Jugador[playerid][Faccion] = cache_get_value_int(0, "Faccion", Jugador[playerid][Faccion]);
Jugador[playerid][Rango] = cache_get_value_int(0, "Rango", Jugador[playerid][Rango]);
Jugador[playerid][Trabajo] = cache_get_value_int(0, "Trabajo", Jugador[playerid][Trabajo]);
Jugador[playerid][Dinero] = cache_get_value_int(0, "Dinero", Jugador[playerid][Dinero]);
Jugador[playerid][Int] = cache_get_value_int(0, "Int", Jugador[playerid][Int]);
Jugador[playerid][VW] = cache_get_value_int(0, "VW", Jugador[playerid][VW]);
Jugador[playerid][Edad] = cache_get_value_int(0, "Edad", Jugador[playerid][Edad]);
SetPVarInt(playerid, "PuedeIngresar", 1);
IngresarJugador(playerid);
}
return 1;
}

public IngresarJugador(playerid)
{
SetSpawnInfo(playerid, 0, Jugador[playerid][Ropa], Jugador[playerid][X],Jugador[playerid][Y],Jugador[playerid][Z], 0.0000, 0,0,0,0,0,0);
SpawnPlayer(playerid);
SetPlayerHealth(playerid, Jugador[playerid][Vida]);
SetPlayerArmour(playerid,Jugador[playerid][Chaleco]);
GivePlayerMoney(playerid,Jugador[playerid][Dinero]);
SetPlayerVirtualWorld(playerid,Jugador[playerid][VW]);
SetPlayerInterior(playerid,Jugador[playerid][Int]);
SetPlayerSkin(playerid,Jugador[playerid][Ropa]);
return 1;
}

public GuardarJugador(playerid)
{
new query[520],Float:jX,Float:jY,Float:jZ,Float:hp,Float:chale,pVW,pInt;
GetPlayerPos(playerid, jX, jY, jZ);
GetPlayerHealth(playerid, hp);
GetPlayerArmour(playerid, chale);
Jugador[playerid][VW] = GetPlayerVirtualWorld(playerid);
Jugador[playerid][Int] = GetPlayerInterior(playerid);
pVW = GetPlayerVirtualWorld(playerid);
pInt = GetPlayerInterior(playerid);
mysql_format(dbsql, query, sizeof query, "UPDATE `cuentas` SET `Ropa`='%i',`X`='%f',`Y`='%f',`Z`='%f',`Genero`='%i',`Vida`='%f',`Chaleco`='%f',`Muertes`='%i',`Asesinatos`='%i' WHERE `Nombre`='%s'",
Jugador[playerid][Ropa],
jX,
jY,
jZ,
Jugador[playerid][Genero],
hp,
chale,
Jugador[playerid][Muertes],
Jugador[playerid][Asesinatos],
NombreJugador(playerid));
mysql_query(dbsql, query);
//
mysql_format(dbsql, query, sizeof query, "UPDATE `cuentas` SET `Edad`='%i', `Faccion`='%i', `Rango`='%i', `Trabajo`='%i', `Dinero`='%i' WHERE `Nombre`='%s'",
Jugador[playerid][Edad],
Jugador[playerid][Faccion],
Jugador[playerid][Rango],
Jugador[playerid][Trabajo],
Jugador[playerid][Dinero],
NombreJugador(playerid));
mysql_query(dbsql, query);

mysql_format(dbsql, query, sizeof query, "UPDATE `cuentas` SET `VW`='%i', `Interior`='%i' WHERE `Nombre`='%s'",
pVW,
pInt,
NombreJugador(playerid));
mysql_query(dbsql, query);

return 1;
}
