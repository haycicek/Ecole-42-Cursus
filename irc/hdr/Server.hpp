#pragma once

// hdr
#include "Print.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <vector>
#include <map>
#include <fcntl.h>

// define statements
#define RPL_PASS "Password accepted\r\n"
#define RPL_JOIN(nick, ip, channel)					":" + nick + "!" + nick + "@" + ip + " JOIN " + channel + "\r\n"
#define RPL_NAMREPLY(nick, channel, users)			": 353 " + nick + " = " + channel + " :" + users + "\r\n"
#define RPL_ENDOFNAMES(nick, channel)				": 366 " + nick + " " + channel + " :End of /NAMES list\r\n"
#define RPL_TOPIC(nick, ip, channel, topic)			":" + nick + "!" + nick + "@" + ip + " TOPIC " + channel + " :" + topic + "\r\n"       
#define RPL_INVITE(nick, ip, channel, target)       ":" + nick + "!" + nick + "@" + ip + " INVITE " + target + " " + channel + "\r\n"
#define RPL_PRIVMSG(source, target, message)		":" + source + " PRIVMSG " + target + " :" + message + "\r\n"
#define RPL_NOTICE(source, target, message)			":" + source + " NOTICE " + target + " :" + message + "\r\n"
#define RPL_NICK(nick, user, ip, newnick)			":" + nick + "!" + user + "@" + ip + " NICK :" + newnick + "\r\n"
#define RPL_KICK(source, channel, target, reason)	":" + source + " KICK " + channel + " " + target + " :" + reason + "\r\n"
#define RPL_PART(source, channel)					":" + source + " PART :" + channel + "\r\n"
#define RPL_QUIT(source, message)					":" + source + " QUIT :" + message + "\r\n"
#define RPL_MODE(source, channel, modes, args)		":" + source + " MODE " + channel + " " + modes + " " + args + "\r\n"

#define RPL_LISTSTART(nick, numusers)				": 321 " + nick + " Channel : "+ numusers + "\r\n"
#define RPL_LIST(nick, channel, numusers, topic)	": 322 " + nick + " " + channel + " " + numusers + " " + topic + "\r\n"
#define RPL_LISTEND(nick)							": 323 " + nick + " :End of /LIST\r\n"

/* [ERROR MESSAGES] */
#define ERR_CHANNELISFULL(source, channel)			": 471 " + source + " " + channel + " :Cannot join channel (+l)" + "\r\n"           //JOIN
#define ERR_BADCHANNELKEY(source, channel)			": 475 " + source + " " + channel + " :Cannot join channel (+k)" + "\r\n"           //JOIN
#define ERR_NEEDMOREPARAMS(source, command)			": 461 " + source + " " + command + " :Not enough parameters" + "\r\n"              //MODE
#define ERR_CHANOPRIVSNEEDED(source, channel)		": 482 " + source + " " + channel + " :You're not the channel operator" + "\r\n"    //MODE
#define ERR_CHANOPKICK(source, channel)				": 482 " + source + " " + channel + " :You cannot KICK yourself" + "\r\n"           //MODE
#define ERR_NOSUCHCHANNEL(source, channel)			": 403 " + source + " " + channel + " :No such channel" + "\r\n"                    //MODE
#define ERR_NICKNAMEINUSE(source)					": 433 " + source + " " + source  + " :Nickname is already in use" + "\r\n"         //NICK
#define ERR_NICKNAMEEMPTY(source)					": 433 " + source + " " + source  + " :Nickname cannot empty" + "\r\n"              //NICK
#define ERR_UNKNOWNMODE(source, channel, mode)		": 472 " + source + " " +  channel + " :Unknown Mode " + mode + "\r\n"              //MODE
#define RPL_NOTOPIC(nick, channel)					": 331 " + nick + " " + channel + " :No topic is set" + "\r\n"                      //TOPIC

#define ERR_ALREADYREGISTRED "Already registered\r\n"
#define ERR_PASSWDMISMATCH "Password mismatch\r\n"
#define ERR_NONICKNAMEGIVEN "No nickname given\r\n"
#define ERR_INVCHANNAME "Invalid channel name, must be: #<channel name> <?key>\r\n"
#define ERR_NOSUCHNICK ":No such nick\r\n"

class Server;
typedef void (Server::*Commands)(std::vector<std::string>& , Client&);
typedef std::vector<Client>::iterator cliIt;
typedef std::vector<Channel>::iterator chanIt;

class Server
{
    private:
        // variables
        int socket_fd;
        size_t _port;
        std::string _password;
        char _buffer[1024];
        
        // fd_set's
        fd_set _readFds;
        fd_set _writeFds;
        fd_set _readFdsSup;
        fd_set _writeFdsSup;
        int _clientCount;
    public:
        // variables
        std::map<std::string, Commands> _commands;
        std::vector<Channel> _channels;
        std::vector<Client> _clients;
        // methods
	
        std::map<std::string, std::vector<std::string> > getParams(std::string const& str);
        void showRightGui(Client &cli, Channel &cha);
        int isNickExist(std::string const&);
        int getOpFd(std::string const& opName);
        int clientIsInThere(Client&, std::string const&);
        int isChannelExist(std::string const&);
        int CheckNickDepends(std::vector<std::string>&, Client&);
        void toChannel(std::vector<std::string>&, Client&);
        void toClient(std::vector<std::string>&, Client&);
		void createSocket(size_t const& port);
        void setPort(size_t const&);
        void setPassword(std::string const&);
        void printStatus();
        void acceptRequest();
        void recvData(int*);
        void writeEvent();
        void initFds();
        void initCommands();
        void run();
        bool passChecker(Client&);
        void kickClient(cliIt&);
        void commandHandler(std::string&, Client&);
        void modesOp(chanIt&, std::vector<std::string>& params, int* flag);
        void modesLimit(chanIt&, std::vector<std::string>& params, int* flag);
        void modesKey(chanIt&, std::vector<std::string>& params, int* flag);
        void getAfterColon(std::vector<std::string>& params);
        Channel& getChannel(std::string const&);
        void startServer(size_t const &, std::string const &);
		void createBot();

        // commands
        void Pass(std::vector<std::string>&, Client&);
        void Nick(std::vector<std::string>&, Client&);
        void Join(std::vector<std::string>&, Client&);
        void User(std::vector<std::string>&, Client&);
        void Mode(std::vector<std::string>&, Client&);
        void Quit(std::vector<std::string>&, Client&);
        void Part(std::vector<std::string>&, Client&);
        void Privmsg(std::vector<std::string>&, Client&);
        void Kick(std::vector<std::string>&, Client&);
        void Topic(std::vector<std::string>&, Client&);
        void Notice(std::vector<std::string>&, Client&);
        void Invite(std::vector<std::string>&, Client&);
        void Who(std::vector<std::string>&, Client& cli);
        void Bot(Client& client, int flag);

        // constructor and destructor
        Server(): _clientCount(0) {};
        ~Server() {close(socket_fd);};

        //utils
        static void writeMessage(int, std::string const&);
		static void writeAllMessage(std::vector<int> const&, std::string const&);
		static std::string intToString(int);
		static int portIsValid(std::string const& port);
		static std::vector<std::string> splitString(const std::string &str, char delimiter);
        static std::string toUpper(const std::string &str);


};
