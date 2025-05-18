#include "../hdr/Server.hpp"

void Server::toChannel(std::vector<std::string>& params, Client& cli)
{
    if (params[0] == "#bot")
        Bot(cli, 1);
    if (isChannelExist(params[0]) == 0) {
        Server::writeMessage(cli._clientFd, ERR_NOSUCHCHANNEL(params[0], params[1]));
        return ;
    }
    if (clientIsInThere(cli, params[0]) == 1)
    {
        if (params[1][0] == ':') {
            getAfterColon(params);
        }
        for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (it->_nick != cli._nick && clientIsInThere(*it, params[0]) == 1) {
                it->_messageBox.push_back(RPL_PRIVMSG(cli._nick, params[0], params[1]));
                FD_SET(it->_clientFd, &_writeFds);
            }
        }
    }
}

void Server::toClient(std::vector<std::string>& params, Client& cli)
{
    int flag = 0;

    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (params[0] == it->_nick) {
            if (params[1][0] == ':') {
               getAfterColon(params);
            }
            it->_messageBox.push_back(RPL_PRIVMSG(cli._nick, params[0], params[1]));
            FD_SET(it->_clientFd, &_writeFds);
            flag = 1;
            return ;
        }
    }
    if (flag == 0)
        Server::writeMessage(cli._clientFd, ERR_NOSUCHNICK);
}

void Server::Privmsg(std::vector<std::string>& params, Client& cli)
{
    if (!passChecker(cli))
        return;
    if (params.size() < 2)
    {
        Server::writeMessage(cli._clientFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
        return ;
    }
    else if (params[0][0] == '#')
        toChannel(params, cli);
    else
        toClient(params, cli);
}
