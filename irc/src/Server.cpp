#include "../hdr/Server.hpp"

void Server::initCommands()
{
    _commands["PASS"] = &Server::Pass;
    _commands["NICK"] = &Server::Nick;
    _commands["JOIN"] = &Server::Join;
    _commands["USER"] = &Server::User;
    _commands["QUIT"] = &Server::Quit;
    _commands["PART"] = &Server::Part;
    _commands["PRIVMSG"] = &Server::Privmsg;
    _commands["NOTICE"] = &Server::Notice;
    _commands["KICK"] = &Server::Kick;
    _commands["INVITE"] = &Server::Invite;
    _commands["MODE"] = &Server::Mode;
    _commands["WHO"] = &Server::Who;
    _commands["TOPIC"] = &Server::Topic; 
}


void Server::createSocket(size_t const& port)
{
	int opt = 1;
    struct sockaddr_in server_addr;
   
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        throw std::system_error(errno, std::system_category(), "Socket creation failed");

    fcntl(socket_fd, F_SETFL, O_NONBLOCK); 

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) 
        throw std::system_error(errno, std::system_category(), "Setsockopt failed");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        throw std::system_error(errno, std::system_category(), "Bind failed");
  
    if (listen(socket_fd, SOMAXCONN) < 0)  
        throw std::system_error(errno, std::system_category(), "Listen failed");
}
void Server::acceptRequest() 
{
    Client client_tmp;
    sockaddr_in client_addr; 
    socklen_t client_size = sizeof(client_addr); 

    client_tmp._clientFd = accept(socket_fd, (sockaddr *)&client_addr, &client_size); 
    fcntl(client_tmp._clientFd, F_SETFL, O_NONBLOCK); 
    if (client_tmp._clientFd <= 0) 
        throw std::system_error(errno, std::system_category(), "Accept failed"); 
    client_tmp._port = ntohs(client_addr.sin_port); 
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_tmp._ipAddr, INET_ADDRSTRLEN); 
    FD_SET(client_tmp._clientFd, &_readFds); 
    println("New client connected!", GREEN);
    _clientCount++;
    _clients.push_back(client_tmp); 
}

std::map<std::string, std::vector<std::string> > Server::getParams(const std::string& str) {
    std::stringstream ss(str);
    std::string tmp;
    std::map<std::string, std::vector<std::string> > ret;
    std::vector<std::string> params;
    ss >> tmp;
    std::string cmd = toUpper(tmp);
    while (true) {
        if (ret.find(cmd) != ret.end())
            return ret;
        params.clear();
        if (!(ss >> tmp) || _commands.find(tmp) != _commands.end()) {
            ret[cmd] = std::vector<std::string>(1, "");
            if (_commands.find(tmp) != _commands.end()) {
                cmd = toUpper(tmp);
                continue;
            }
            return ret;
        }
        do
            params.push_back(tmp);
        while (ss >> tmp && _commands.find(tmp) == _commands.end());
        ret[cmd] = params;
        if (ss.eof())
            return ret;
        cmd = toUpper(tmp);
    }
    return ret;
}

void Server::commandHandler(std::string& str, Client& cli)
{
    std::map<std::string, std::vector<std::string> > params = getParams(str);

    for (std::map<std::string, std::vector<std::string> >::iterator it = params.begin(); it != params.end(); ++it)
    {
        if (_commands.find(it->first) == _commands.end())
            Server::writeMessage(cli._clientFd, "421 : " + it->first + " :Unknown command!\r\n");
        else
            (this->*_commands[it->first])(it->second, cli);
    }
}

void Server::recvData(int* state)
{
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (FD_ISSET(it->_clientFd, &_readFdsSup))
        {
            *state = 0;
            int readed = read(it->_clientFd, _buffer, 1024);
            if (readed <= 0)
            {
                std::vector<std::string> tmp;
                tmp.push_back("");
                (this->*_commands["QUIT"])(tmp, *it);
            }
            else
            {
                _buffer[readed] = 0;
                std::string tmp = _buffer;
                if (tmp == "\n")
                {
                    *state = 0; 
                    break;
                }
                if (tmp[tmp.length() - 1] != '\n')
                {
                    it->_buffer += tmp;
                    *state = 0;
                    break;
                }
                else
                    it->_buffer = it->_buffer + tmp;
                commandHandler(it->_buffer, *it);
                it->_buffer.clear();
            }
            break;
        }
    }
}

void Server::initFds()
{
    FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFdsSup);
    FD_ZERO(&_writeFdsSup);
    FD_SET(socket_fd, &_readFds);
}

void Server::writeEvent()
{
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->_clientFd < 3)
            continue;
        if (FD_ISSET(it->_clientFd, &_writeFdsSup))
        {
            int writed = write(it->_clientFd, it->_messageBox[0].c_str(), it->_messageBox[0].size());
            it->_messageBox.erase(it->_messageBox.begin());
            if (it->_messageBox.empty())
                FD_CLR(it->_clientFd, &_writeFds);
            if (writed <= 0)
            {
                std::vector<std::string> tmp;
                tmp.push_back("");
                (this->*_commands["QUIT"])(tmp, *it);
            }
            break ;
        }
    }
}


void Server::run()
{
    int state = 0;
    initFds();
    while (1)
    {
        _readFdsSup = _readFds;
        _writeFdsSup = _writeFds;
        state = select(_clientCount + 4, &_readFdsSup, &_writeFdsSup, NULL, 0);
        if (FD_ISSET(socket_fd, &_readFdsSup)) {
            acceptRequest();
            state = 0; continue;
        }
        if (state) {
            recvData(&state);
            if (state == 0)
                continue;
        }
        if (state) {
            writeEvent();
            state = 0;
            continue;
        }
    }
}

void Server::createBot()
{
    Client bot;
    bot._nick = "botobot";
    bot._user = "boto";
    bot._realName = "boto";
    bot._clientFd = 1;
    bot._passChecked = 1;
    _clients.push_back(bot);
    _clientCount++;
    std::vector<std::string> tmp;
    tmp.push_back("#botChnl");
    (this->*_commands["JOIN"]) (tmp, bot);
    println("Bot created!", GREEN);
}

void Server::startServer(size_t const& port, std::string const& password)
{
    setPort(port);
    setPassword(password);
    initCommands();
    createSocket(port);
    printStatus();
    createBot();
    run();
}