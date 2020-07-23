/*
	a_dialog include, created by wyretray, based and inspired on White_116 and Emmet_ ez_dialog include
*/

#define _d: 		#@_dialog_
#define dlg:%0(%1)	@_dialog_%0(%1, response, listitem, inputtext[]); \
					@_dialog_%0(%1, response, listitem, inputtext[])
#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

static const DIALOG_DEFAULT_ID = 255;

stock _ShowPlayerDialog(playerid, dialogID[], style, caption[], info[], primaryButton[], secondaryButton[])
{
	if(funcidx(dialogID) == -1 && strcmp(dialogID, "@_dialog_empty", true)) return printf("a_dialog: error: function %s is not defined", dialogID);
	if(strlen(dialogID) == 0) 
		return 	print("a_dialog: error: function name can not be an empty"),
				print("a_dialog: if you wish to create dialog without response - use \"_d:empty\" as dialogid");
	SetPVarString(playerid, "dialogFunction", dialogID);
	return ShowPlayerDialog(playerid, DIALOG_DEFAULT_ID, style, caption, info, primaryButton, secondaryButton);
}

// Hooking default callback
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != DIALOG_DEFAULT_ID) return false; // If it's not a include function - don't continue
	new dialogFunction[32];
	GetPVarString(playerid, "dialogFunction", dialogFunction, sizeof dialogFunction);
	if(strlen(inputtext) == 0) { if(CallLocalFunction(dialogFunction, "iii", playerid, response, listitem)) return 1; }
	else 
	{
		new itr = -1;
		while(inputtext[++itr])
		{
		    switch(inputtext[itr])
		    {
		        case 0x25: inputtext[itr] = 0x23; 
		        case 0x00 .. 0x1F: inputtext[itr] = 0x3F; 
		    }
		} 
		if(CallLocalFunction(dialogFunction, "iiis", playerid, response, listitem, inputtext)) return 1;
	}
	DeletePVar(playerid, "dialogFunction");
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