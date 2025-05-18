#include "../hdr/Server.hpp"

void Server::Notice(std::vector<std::string>& params, Client& cli)
{
    if (!passChecker(cli))
        return;
    if (params[0][0] == '#') {
        Server::writeMessage(cli._clientFd, "Cannot notice a channel\r\n");
        return ;
    }
    if (params.size() != 2) {
        Server::writeMessage(cli._clientFd, ERR_NEEDMOREPARAMS(cli._nick, "NOTICE"));
        return ;
    }
    if (cli._nick == params[0]) {
        Server::writeMessage(cli._clientFd, "Cannot notice yourself\r\n");
        return ;
    }
    size_t flag = 0;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_nick == params[0])
        {
            if (params[1][0] == ':')
                getAfterColon(params);
            flag = 1;
            it->_messageBox.push_back(RPL_NOTICE(cli._nick, params[0], params[1]));
            FD_SET(it->_clientFd, &_writeFds);
            break;
        }
    }
    if (flag == 0) {
        Server::writeMessage(cli._clientFd, ERR_NOSUCHNICK);
    }
}
