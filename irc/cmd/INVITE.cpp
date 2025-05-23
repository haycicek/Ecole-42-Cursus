#include "../hdr/Server.hpp"

void Server::Invite(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (isChannelExist(params[1]) == 0) {
        Server::writeMessage(cli._clientFd, ERR_NOSUCHCHANNEL(params[1], params[0]));
        return ;
    }
    size_t flag = 0;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_nick == params[0])
        {
            flag = 1;
            Channel chan = getChannel(params[1]);
            if (cli._nick != chan._opNick) {
                Server::writeMessage(cli._clientFd, ERR_CHANOPRIVSNEEDED(cli._nick, params[1]));
                return ;
            }
            Server::writeMessage(it->_clientFd, RPL_INVITE(cli._nick, cli._ipAddr, chan._name, params[1]));
        }
    }
    if (flag == 0)
        Server::writeMessage(cli._clientFd, ERR_NOSUCHNICK);
}
