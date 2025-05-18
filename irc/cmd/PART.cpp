#include "../hdr/Server.hpp"

void Server::Part(std::vector<std::string>& params, Client& cli)
{
    if (!passChecker(cli))
        return;
    if (params.size()!= 2)
        Server::writeMessage(cli._clientFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
    else if (isChannelExist(params[0]))
    {
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->_name == params[0]) {
                for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                    if (it2->_nick == cli._nick) {
                        Server::writeMessage(cli._clientFd, RPL_PART(cli._nick, params[0]));
                        it->_channelClients.erase(it2);
                        if (it->_channelClients.size() > 0)
                            it->_opNick = it->_channelClients[0]._nick;
                        println("Client " + cli._nick + " has left channel " + params[0], RED);
                        break;
                    }
                }
                if (it->_channelClients.size() == 0) {
                    println("Channel " + it->_name + " is deleted", RED);
                    _channels.erase(it);
                }
                else
                    showRightGui(cli, *it);
                Server::writeMessage(cli._clientFd, RPL_PART(cli._nick, params[0]));
                break;
            }
        }
    }
    else    
        Server::writeMessage(cli._clientFd, ERR_NOSUCHCHANNEL(params[0], params[1]));
}
