#pragma once
class Service
{
public:
	Service();
	~Service();
	Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
private:
	std::shared_ptr<boost::asio::ip::tcp::socket> sock;
	std::string response;
	boost::asio::streambuf request;
public:
	void StartHandling();
private:
	void onRequestReceived(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void onResponseSent(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void onFinish();
public:
	std::string ProcessRequest(boost::asio::streambuf& request);
};

