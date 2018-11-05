#include "stdafx.h"
#include "Acceptor.h"



Acceptor::Acceptor(boost::asio::io_service& ios, unsigned int port_no) :
	ios(ios), acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_no)), isStopped(false)
{
}


Acceptor::~Acceptor()
{
}


void Acceptor::Start()
{
	acceptor.listen();
	InitAccept();
}


void Acceptor::Stop()
{
	isStopped.store(true);
}


void Acceptor::InitAccept()
{
	std::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(ios));
	acceptor.async_accept(*sock.get(), [this, sock](const boost::system::error_code& ec)
	{
		OnAccept(ec, sock);
	});
}


void Acceptor::OnAccept(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
	if (ec == 0)
		(new Service)->StartHandling();
	else
	{
		std::cout << "Error " << ec.value() << " occurred." << std::endl;
		std::cout << "Error Message: " << ec.message() << std::endl;
	}

	if (!isStopped.load())
		InitAccept();
	else
		acceptor.close();
}
