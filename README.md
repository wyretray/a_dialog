### Об инклуде
Данный инклуд добавляет возможность обрабатывать диалоги не в коллбэке OnDialogResponse, а в отдельной конструкции, например как ZCMD, DC_CMD и т.д.

### Синтаксис
Создание диалога точно такое же, как и стандартное, однако Вам необходимо добавить нижний пробел в начало функции и указать ID диалога в виде _d:dialog

    _ShowPlayerDialog(playerid, _d:dialogid, style, caption[], info[], button1[], button2[])

Для дальнейшего взаимодействия с диалогом создайте следующую конструкцию в любой части мода (исключая коллбэки)

    dlg:dialogid(playerid)
    {
    	/* Ваш код здесь */
    	return 1;
    }

### Пример использования

Создадим диалог с ID login.

    _ShowPlayerDialog(playerid, _d:login, DIALOG_STYLE_PASSWORD, "Авторизация", "Введите ваш пароль", "Войти", "Отмена");

И взаимодействие с ним (то, что обычно Вы обрабатываете в OnDialogResponse)

    dlg:login(playerid)
    {
    	printf("ID игрока %i", playerid);
    	printf("Введенный текст: %s", inputtext);
    	printf("Кнопка %i", response);
    	return 1;
    }

Внутри этой конструкции Вам будут доступны стандартные переменные, такие как playerid, response, listitem и inputtext