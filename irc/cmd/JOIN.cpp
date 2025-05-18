#include "../hdr/Server.hpp"

void Server::Join(std::vector<std::string> &params, Client &cli)
{
    if (!passChecker(cli))
        return;
        
    if (params.empty())
    {
        Server::writeMessage(cli._clientFd, ERR_NEEDMOREPARAMS(cli._nick, "JOIN"));
        return;
    }

    std::vector<std::string> channels = Server::splitString(params[0], ',');
    std::vector<std::string> keys = params.size() > 1 ? Server::splitString(params[1], ',') : std::vector<std::string>();

    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string chan = channels[i];
        std::string key = i < keys.size() ? keys[i] : "";

        if (chan.empty() || (chan[0] != '#' && chan[0] != '&') || chan.size() > 200 ||
            chan.find(' ') != std::string::npos || chan.find('\a') != std::string::npos || chan.find(',') != std::string::npos)
        {
            Server::writeMessage(cli._clientFd, ERR_INVCHANNAME);
            continue;
        }

        if (clientIsInThere(cli, chan) == 0)
        {
            if (!cli._nick.empty())
            {
                bool isThere = false;
                for (chanIt it = _channels.begin(); it != _channels.end(); ++it)
                {
                    if (it->_name == chan)
                    {
                        if (it->_key == key)
                        {
                            if (it->_userLimit != 0 && it->_channelClients.size() >= it->_userLimit)
                            {
                                Server::writeMessage(cli._clientFd, ERR_CHANNELISFULL(cli._nick, chan));
                                return;
                            }
                            it->_channelClients.push_back(cli);
                            it->_opNick = it->_channelClients[0]._nick;
                            Server::writeMessage(cli._clientFd, RPL_JOIN(cli._nick, cli._ip, chan));
                            println("Client " + cli._nick + " has entered \'" + chan + "\'", MAGENTA);
                            showRightGui(cli, *it);
                        }
                        else if (it->_key.empty())
                            Server::writeMessage(cli._clientFd, "Key not required for this channel!\r\n");
                        else
                            Server::writeMessage(cli._clientFd, ERR_BADCHANNELKEY(cli._nick, chan));
                        isThere = true;
                        break;
                    }
                }

                if (!isThere)
                {
                    Channel tmp;
                    tmp._name = chan;
                    if (!key.empty())
                        tmp._key = key;
                    tmp._channelClients.push_back(cli);
                    tmp._opNick = tmp._channelClients[0]._nick;
                    _channels.push_back(tmp);
                    Server::writeMessage(cli._clientFd, RPL_JOIN(cli._nick, cli._ip, chan));
                    if (!key.empty())
                        println("Channel " + chan + " created with " + key, MAGENTA);
                    else
                    {
                        Bot(cli, 1);
                        println("Channel " + chan + " created", MAGENTA);
                    }
                    showRightGui(cli, tmp);
                }
            }
            else
                Server::writeMessage(cli._clientFd, "Set your nick before!\r\n");
        }
        else
            Server::writeMessage(cli._clientFd, "You are already in this channel\r\n");
    }
}
