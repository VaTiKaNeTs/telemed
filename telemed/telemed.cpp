// telemed.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <tgbot/tgbot.h>

#include "knTypes.h"

#include "config.h"
#include "modules/botCmd/botCmd.h"


using namespace std;
using namespace TgBot;

/****************************************************************************************************/
#define BOT_API_TOKEN "8191200173:AAFQbZZ5mKIWIba4WowIXvJ0ymjMmjewEm4"

/****************************************************************************************************/
void tgLoop(Bot& bot);

/****************************************************************************************************/


/****************************************************************************************************/
int main()
{
    Bot bot(BOT_API_TOKEN);

    botCmdInit(bot);

    FILE* file;
    errno_t err = 0;
    err = fopen_s(&file, "testic.json", "w");
    if (err)
    {
        printf("file error %d\n", err);
    }
    fprintf(file, "{\n");
    fprintf(file, "\"username\": \"%s\"\n", "Kirill");
    fprintf(file, "}\n");
    fclose(file);

    botCmdStart(bot);
    BotCmdAny(bot);

    tgLoop(bot);

    return 0;
}

/****************************************************************************************************/
void tgLoop(Bot& bot)
{
    signal(SIGINT, [](int s)
        {
            printf("SIGINT got\n");
            exit(0);
        });

    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (exception& e)
    {
        printf("error: %s\n", e.what());
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
