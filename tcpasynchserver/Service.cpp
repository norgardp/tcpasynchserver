#include "stdafx.h"
#include "Service.h"


Service::Service()
{
}


Service::~Service()
{
}


Service::Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock) :
	sock(sock)
{
}


void Service::StartHandling()
{
	boost::asio::async_read_until(*sock.get(), request, '\n', [this](
		const boost::system::error_code& ec, std::size_t bytes_transferred)
	{
		onRequestReceived(ec, bytes_transferred);
	});
}


void Service::onRequestReceived(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
	if (ec != 0)
	{
		std::cout << "Error " << ec.value() << " occurred." << std::endl;
		std::cout << "Error Message: " << ec.message() << std::endl;

		onFinish();
		return;
	}
	response = ProcessRequest(request);
	boost::asio::async_write(*sock.get(), boost::asio::buffer(response), [this](
		const boost::system::error_code& ec, std::size_t bytes_transferred)
	{
		onResponseSent(ec, bytes_transferred);
	});
}


void Service::onResponseSent(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
	if (ec != 0)
	{
		std::cout << "Error " << ec.value() << " occurred." << std::endl;
		std::cout << "Error Message: " << ec.message() << std::endl;

		onFinish();
	}
}


void Service::onFinish()
{
	delete this;
}


std::string Service::ProcessRequest(boost::asio::streambuf& request)
{
	// Pretend to do something
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::string response{ "response\n" };
	return response;
}
