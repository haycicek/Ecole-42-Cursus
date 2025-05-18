#include "../hdr/Server.hpp"
#include "../hdr/Channel.hpp"

void Server::writeMessage(int fd, std::string const& message)
{
	if(fd < 3)
		return;
    if ((write(fd, message.c_str(), message.length())) < 0)
        println("Message cannot send!", RED);
}

void Server::writeAllMessage(std::vector<int> const& fds, std::string const& message)
{
    for (std::vector<int>::const_iterator it = fds.begin(); it != fds.end(); ++it)
        writeMessage(*it, message);
}

std::string Server::intToString(int n)
{
    std::stringstream ss;
    ss << n;
    std::string str = ss.str();
    return str;
}

int Server::portIsValid(std::string const& port)
{
    for (size_t i = 0; i < port.size(); ++i)
        if (!isdigit(port[i]))
            return 0;
	int portInt = std::atoi(port.c_str());
    if (portInt < 1024 || portInt > 49151)
        return 0;
    return 1;
}

int ft_wordcount(const std::string &s, char c)
{
	unsigned int index = 0;
	size_t i = 0;
	while (i < s.length())
	{
		if (s[i] == c)
			i++;
		else
		{
			while (i < s.length() && s[i] != c)
				i++;
			index++;
		}
	}
	return index;
}

int ft_wordlen(const std::string &s, char c, size_t start)
{
	int len = 0;
	while (start < s.length() && s[start] != c)
	{
		len++;
		start++;
	}
	return len;
}

std::vector<std::string> Server::splitString(const std::string &str, char delimiter)
{
	std::vector<std::string> result;
	size_t j = 0;
	size_t word_count = ft_wordcount(str, delimiter);

	while (result.size() < word_count)
	{
		while (j < str.length() && str[j] == delimiter)
			j++;
		int len = ft_wordlen(str, delimiter, j);
		if (len > 0)
			result.push_back(str.substr(j, len));
		j += len;
	}
	return result;
}

std::string Server::toUpper(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::vector<int> Channel::getFds() const
{
    std::vector<int> file;

    for (std::vector<Client>::const_iterator it = _channelClients.begin(); it != _channelClients.end(); ++it)
        file.push_back(it->_clientFd);
    return file;
}