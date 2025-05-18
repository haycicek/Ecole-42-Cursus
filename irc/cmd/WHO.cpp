#include "../hdr/Server.hpp"

void Server::Who(std::vector<std::string>& params, Client& cli)
{
    if (!passChecker(cli))
        return;
    if (params.size() != 1)
        return ;
    if (isChannelExist(params[0]) == false)
        Server::writeMessage(cli._clientFd,ERR_NOSUCHCHANNEL(params[0], cli._nick));
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == params[0])
        {
            Server::writeMessage(cli._clientFd, "Users in this channel:\r\n");
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                Server::writeMessage(cli._clientFd, "* " + it2->_nick + "\r\n");
            }
            return;
        }
    }
}
