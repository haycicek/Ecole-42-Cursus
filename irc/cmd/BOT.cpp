#include "../hdr/Server.hpp"
#include <cstdlib>
#include <ctime>

void Server::Bot(Client &client, int flag)
{
    if (client._nick.empty())
    {
        Server::writeMessage(client._clientFd, ERR_NONICKNAMEGIVEN);
        return;
    }
    std::vector<std::string> params;

    if (flag == 0)
    {
        std::vector<std::string> join;
        join.push_back("#botChnl");
        (this->*_commands["JOIN"])(join, client);
        client._bot = 1;
        params.push_back(client._nick);
        params.push_back("Welcome to the bot channel! " + client._nick);
        Notice(params, _clients[0]);
    }
    else if (flag == 1)
    {
        std::vector<std::string> messages;
        messages.push_back("You could be the one in my dreams");
        messages.push_back("You could be much more than you seem");
        messages.push_back("Anything I wanted in life");
        messages.push_back("Do you understand what I mean?");
        messages.push_back("I can see that this could be fate");
        messages.push_back("I can love you more than they hate");
        messages.push_back("Doesn't matter who they will blame");
        messages.push_back("We can beat them at their own game");
        messages.push_back("I can see it in your eyes");
        messages.push_back("It doesn't come as a surprise");
        messages.push_back("I see you dancing all alone");
        messages.push_back("You feel it deep inside your bones");
        messages.push_back("We could be the same, no matter what they say");
        messages.push_back("I feel I'm turning the page");
        messages.push_back("They think they know us, but they don't");

        srand(time(0));
        int random = rand() % messages.size();
        params.push_back(client._nick);
        params.push_back(messages[random]);
        Privmsg(params, _clients[0]);
    }
}