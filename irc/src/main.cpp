#include "../hdr/Server.hpp"

Server* server = NULL;

void signalHandler(int signum)
{
	println("\nSignal received: " + convertString(strsignal(signum)), RED);
	delete server;
	server = NULL;
	exit(signum);
}

void signalCatcher()
{
	struct sigaction sa;
	sa.sa_handler = signalHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	std::vector<int> ignoredSignals;
    ignoredSignals.push_back(SIGKILL);
    ignoredSignals.push_back(SIGSTOP);
    ignoredSignals.push_back(SIGWINCH);
    ignoredSignals.push_back(SIGUSR1);
    ignoredSignals.push_back(SIGUSR2);

	for (int i = 1; i < NSIG; ++i)
		if (find(ignoredSignals.begin(), ignoredSignals.end(), i) == ignoredSignals.end())
			if (signal(i, signalHandler) == SIG_ERR)
				printlnErr("Signal error: " + convertString(strsignal(i)), RED);
}

int main(int ac, char **av)
{
    try {
        if (ac != 3)
            throw std::invalid_argument("USAGE:\n./ircserv <port> <password>");
        if (!Server::portIsValid(av[1]))
            throw std::invalid_argument("Invalid port number!\nMust be between 1024 and 49151.");
        server = new Server();
        signalCatcher();
        server->startServer(atoi(av[1]), av[2]);
    } catch (std::exception& e) {
        printlnErr(e.what(), RED);
    }
    if (server)
    {
        delete server;
        server = NULL;
    }
    return 0;
}
