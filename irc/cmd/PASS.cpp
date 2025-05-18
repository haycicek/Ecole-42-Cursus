#include "../hdr/Server.hpp"

void Server::Pass(std::vector<std::string>& params, Client& cli)
{
    if (params.size() != 1)
        Server::writeMessage(cli._clientFd, ERR_NEEDMOREPARAMS(params[0], _password));
    else if (cli._passChecked == 1)
        Server::writeMessage(cli._clientFd, ERR_ALREADYREGISTRED);
    else if (params[0] == _password)
    {
        cli._passChecked = 1;
        Server::writeMessage(cli._clientFd, RPL_PASS);
    }
    else
        Server::writeMessage(cli._clientFd, ERR_PASSWDMISMATCH);
    if(cli._bot == 0 && !cli._nick.empty())
        Bot(cli, 0);   
}
