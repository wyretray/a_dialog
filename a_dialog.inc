#define _d: 		#@_dialog_
#define dlg:%0(%1)	@_dialog_%0(%1, response, listitem, inputtext[]); \
					@_dialog_%0(%1, response, listitem, inputtext[])
#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

static const DIALOG_DEFAULT_ID = 255;

stock _ShowPlayerDialog(playerid, dialogID[], style, caption[], info[], primaryButton[], secondaryButton[])
{
	if(funcidx(dialogID) == -1 && strcmp(dialogID, "@_dialog_empty", true)) return printf("a_dialog: Ошибка: функция %s не найдена", dialogID);
	if(strlen(dialogID) == 0) 
		return 	print(!"a_dialog: Ошибка: название функции не может быть пустым"),
				print(!"a_dialog: Если Вы хотите создать диалог без взаимодействия, используйте \"_d:empty\" в качестве ID диалога");

	SetPVarString(playerid, !"dialogFunction", dialogID);
	SetPVarInt(playerid, !"dialogStyle", style);

	return ShowPlayerDialog(playerid, DIALOG_DEFAULT_ID, style, caption, info, primaryButton, secondaryButton);
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != DIALOG_DEFAULT_ID) return false;

	new dialogFunction[32];
	GetPVarString(playerid, !"dialogFunction", dialogFunction, sizeof dialogFunction);
	DeletePVar(playerid, !"dialogFunction");

	new dialogStyle = GetPVarInt(playerid, !"dialogStyle");
	DeletePVar(playerid, !"dialogStyle");

	switch(dialogStyle)
	{
		case DIALOG_STYLE_INPUT, DIALOG_STYLE_PASSWORD: 
		{
			if(isnull(inputtext)) CallLocalFunction(dialogFunction, !"iiis", playerid, response, listitem, "\1");
			else CallLocalFunction(dialogFunction, !"iiis", playerid, response, listitem, inputtext);
		}
		default: CallLocalFunction(dialogFunction, !"iii", playerid, response, listitem);
	}
    return 1;
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse a_dialog_OnDialogResponse
#if defined a_dialog_OnDialogResponse
    forward a_dialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif	